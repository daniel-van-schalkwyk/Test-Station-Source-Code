#ifndef geyser_daq_controller_H
#define geyser_daq_controller_H

//include all necessary libraries
#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <OneWire.h>
#include <SPI.h>
#include <SD.h>
#include <DallasTemperature.h>
#include "RTClib.h"
#include <RTCDue.h>
#include "temp_sensor_address_reg.h"
#include <temp_cal_coefs.h>
#include <Adafruit_ADS1015.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define wifiPort                Serial2
#define inletWaterComms         Serial1
/** Define all pins used by the microcontroller **/
#define chamberControlBus       23 
#define oneWireBus0             25
#define oneWireBus1             27
#define oneWireBus2             29
#define oneWireBus3             31
#define oneWireBus4             33
#define oneWireBus5             35       
#define oneWireBus6             37       
#define oneWireBus7             39       
#define sd_CS                   2       // The chip select pin used for SD SPI communication
// Interrupt Pins
#define flowSensorPin           3       // Interrupt GPIO pin used to determine flow rate of water using hall-effect sensor
#define municipalSensor         4       // Interrupt GPIO pin used to determine flow rate of water using municipal sensor
#define emergencyStop           5 
// Digital output pins for electric ball valve control circuit
#define valveClosePin           42      // Output signal sent to the valve to close
#define valveOpenPin            44      // Output signal sent to the valve to open
#define valveCloseToggle        38      // External toggle switch used to close valve 
#define valveOpenToggle         40      // External toggle switch used to open valve
// Define Relay control pins
#define ambientFans             49      // GPIO pin used for circulation fan control using relay
#define ambHeatingFans          45      // GPIO pin used for fans only in both heating fans
#define ambHeatingElem_set      50      // GPIO pin used for heating element set in heating fan module
#define ambHeatingElem_reset    51      // GPIO pin used for heating element reset in heating fan module
#define geyserPowerSet          46      // GPIO pin used for setting (on) the latching relay of the geyser element power 
#define geyserPowerReset        48      // GPIO pin used for resetting (off) the latching relay of the geyser element power
#define ventingPin              47      // GPIO pin used for venting fans using relay
// Define all DAC output pins
#define IWH_control_pin         67      // DAC (Digital to analog) pin used for instantaneous water heater control
// Define all analog pins used
#define currentReadPin          A0      // Analog ADC pin used to read current consumption of geyser heating element
#define voltageReadPin          A1      // Analog ADC pin used to geyser heating element voltage
#define geyserWaterTempPin      A2      // Analog ADC pin used to read NTC thermistor temperature value of thermostat
#define inletPressurePin        A3      // Analog ADC pin used to read inlet water pressure of geyser
#define currentVref             A4      // Reference voltage for current sensor
// Define parameters used by OLED screen
#define SCREEN_WIDTH            128     // OLED display width, in pixels
#define SCREEN_HEIGHT           64      // OLED display height, in pixels
#define OLED_RESET              -1      // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
U8G2_SH1106_128X32_VISIONOX_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
/** Declare all enumerations here**/
enum actuatorStates : int {Off, On, Closed = 0, Open = 1, NoOutput};
enum inletSystemStates : int {inletIdle, inletCooling, inletHeating, inletDischarging, tempSelect};
enum serialPortSelect : int {serialComputer, serialInlet};
enum timeStampSelect : uint8_t {FULL_TIME_STAMP, TIME_STAMP, DATE_STAMP};
enum setupDataOrder : int {setupCmdIndex, setupCheckIndex, samplingTimeIndex, setParamsIndex, inletEnergyInputIndex, waterScheduleIndex, powerScheduleIndex};
enum setParamsIndex : int {chamberSetTemp, geyserWaterSetTemp, geyserInletSetTemp, waterFlowRateSet, setParamsCount};
enum systemStateIndex : int {idleState, runState, setupState, debugState, shareState, viewState, errorState, emergencyState, mqttShare, systemStateCount}; 
enum chamberStateIndex : int {heatingFan, ventingFan, circulationFan, heatingFanElement, valveState, chamberStateCount};
enum geyserStateIndex : int {geyserElementPower, geyserHeating, geyserCooling, geyserTempReady, geyserStateCount};
enum autoControlIndex : int {chamberTempRegIndex, geyserTempRegIndex, inletTempRegIndex, flowRateControlIndex, waterScheduleControlIndex, geyserPowerControlIndex, autoControlIndexCount};
enum incomingCMDs : int {stopSystem, startSystem, setupSytem, resetSystem, shareData, viewData, debugSystem, OutletValveControl};
enum busDeviceCount{bus0DeviceCount = 9, bus1DeviceCount = 9, bus2DeviceCount = 9, bus3DeviceCount = 9, bus4DeviceCount = 6,\
                    bus5DeviceCount = 8, bus6DeviceCount = 8, bus7DeviceCount = 8};
enum externADCPins{currentPin, currentVrefPin, pressurePin, voltagePin};
/** Define general parameters used by source code **/
const int sensorErrorNum = DEVICE_DISCONNECTED_C;     // Value that will be displayed if temp sensors are disconnected
const double max12BitNum = 4095;
const double currentSensorRated = 20.0;
const double currentSensorRange = 30.0;
const uint32_t SerialBaudrate = 115200;  // Baud rate for serial communication
uint8_t tempDeviceCount[boilerProfileBusNumber] = {};   // Sensor count per bus
const uint8_t tempResolution = 11;    // Default resolution of the DS18B20 ADC output
String tempProfileStringArray[boilerProfileBusNumber] = {};
double chamberDataArray[3+numOfChamberTempSensors] = {};
int systemSetParams[setParamsIndex::setParamsCount] = {35, 60, 25, 5}; // Default temperature set values
String screenBuffer[10] = {};
const double geyserThermistorDisconnected = -1;
const int disconnectDS18B20 = -127;
volatile uint8_t geyserTempDelayTick = 0;
volatile int flowRateControlCount = 0;
volatile int systemAmbientUpdateCounter = 0;
volatile unsigned long flowControlCounter = 0;
double flowRateCorrectMargin = 0.0083333; // L/s
const uint32_t currentSampleBufferSize = 125;
volatile uint32_t currentACsignalBuffer[currentSampleBufferSize] = {};
const int PowerSamplingFreq = 1250;
volatile uint32_t currentSampleIndex = 0;
volatile bool currentBufferSampledFlag = false;
volatile uint32_t currentSqrtSampleSum = 0;
volatile uint32_t currentVrefSum = 0;
double primaryCurrent = 0.00;

/** Define all flags **/
bool systemStateFlags[systemStateIndex::systemStateCount] = {true, false, false, false, true, false, false, false, false};  // System state array to control state of system
bool chamberStateFlags[chamberStateIndex::chamberStateCount] = {Off, Off, Off, Off, Closed}; // Chamber state array for chamber state control
bool geyserStateFlags[geyserStateIndex::geyserStateCount] = {Off, false, false, false}; // geyser state array for geyser state control
bool autoControlFlags[autoControlIndex::autoControlIndexCount] = {false, true, false, false, false};
bool captureBoilerData = false;
bool sdCardSuccessFlag = false;
bool newFileFlag = true;
bool autoFlowControlFlag = false;
bool dataReadyFlag = false;
bool internalADCflag = false;
bool firstRequestChamberTemp = true;
bool firstRequestBoilerTemp = true;
bool chamberHeatCheckFlag = false;
volatile bool inletSetUpdate = false;
volatile bool systemUpdateFlag = false;
volatile bool sampleDataFlag = false;

/** Define all class instances **/
// OneWire instances needed for Dallas Temperature library
OneWire OneWireBusses[boilerProfileBusNumber] = {OneWire(oneWireBus0), OneWire(oneWireBus1), OneWire(oneWireBus2), OneWire(oneWireBus3), \
                            OneWire(oneWireBus4), OneWire(oneWireBus5), OneWire(oneWireBus6), OneWire(oneWireBus7)};
OneWire chamberControlTempBus(chamberControlBus);

// Temperature sensor dallasTemperature instances (Instantiated in the setup script)
DallasTemperature TempBusses[boilerProfileBusNumber] = {};
DallasTemperature chamberTempBus(&chamberControlTempBus);

// Define RTC instances
RTC_DS3231 sysRTC;
RTCDue dueRTC(XTAL);

//Define external ADC instance (ADS1115)
Adafruit_ADS1115 externADC(0x48);

struct polynomialCalParams
{
  double C0;
  double C1;
  double C2;
} voltageCalParams, currentCalParams;

struct PID_params
{
  double Kp;
  double Ki;
  double Kd;
  double e_sum;
  double e_prev;
}PIDout;
// Declare state machine states and flags
bool valveOpen = false;
bool ambientReady = false;
bool ambHeatingFlag = false;
bool ventingFlag = false;
bool geyserElementPowerAvailable = true;
bool geyserLatchFlag = false;
bool inDeadBand = false;
bool initialGeyserHeating = true;
bool valveOpenLatch = false;
bool initialHeating = true;
bool actuateValveFlag = false;
int inletEnergyInput = inletIdle;
volatile bool activeFlow = false;
volatile bool emergencyStateFlag = false;
// Declare counter variables
volatile uint32_t emergencyTick, flowCounter, municipalFlowCounter;
const uint32_t debounceTime = 40; // Button debounce time value
const unsigned long valveOpenStepTime = 1000; // ms
int PID_OutTime = 0;
const int flowControlUpdateTime = 5; // seconds
unsigned long prevValveOpenStepTick = 0;
unsigned long tempRequestTick = 0;
unsigned long latchTime = 0;
unsigned long prevWaterSampleTime = 0;
unsigned long prevDataSampleTick = 0;
unsigned long currentLoopTick = 0;
unsigned long prevSystemSampleTick = 0; 
int outletValvePosTime = 0;

// Set default DAQ parameters
int dataSamplingTime = 5;  // in seconds
const unsigned long systemUpdateTime = 1; // in seconds
double T_upper = 0.2;     // Define default valaue for upper temperature margin
double T_lower = 0.2;     // Define default valaue for lower temperature margin
double prevAmbientTemp = 20;    // Defines a place holder for previous sample to determine rate of temperature decay
double geyserSetTemp = 50.00;
const double kelvinToC_const = 273.15;
double deadBandMargin = 2;
double flowRateError = 0.00;
// Data sample variables
double inletWaterTemp, outletWaterTemp, sourceWaterTemp, outsideTemp, amb1Temp, amb2Temp, ambientTemp, ambError, geyserWaterTemp; 
double powerConsumed;
double AccumulatedEnergyPerDataSample, AccumulatedWaterConsumedPerDataSample;
double waterConsumed;
double waterEventTot;
String fileName = "";
String systemParamColNames =  "ChamberSetTemp,GeyserWaterSetTemp,InletWaterSetTemp,DesiredFlowRate,ChamberAirTempReg,GeyserWaterTempReg,\
                              InletWaterTempReg,FlowRateReg,WaterScheduleControl,PowerScheduleControl,\
                              ChamberHeatingFans,ChamberVentingFans,CirculationFans,ChamberHeatingElement, \
                              WaterValveState,GeyserHeatingFlag";
String dataColNamesChamber = "PowerConsumed,WaterConsumed, \
                              TotalWaterConsumed,GeyserWaterThermostatTemp,InletWaterTemp,\
                              OutletWaterTemp,TopGeyserSurfaceTemp,BotGeyserSurfaceTemp,LabTemp,\
                              ChamberTemp1,ChamberTemp2,ChamberTempMean";
String dataColNamesBoiler = "";
double flowMeterResolution = 2.425; // in mL

struct dueTimeAndDate
{
  uint16_t year_;
  uint8_t month_;
  uint8_t day_;
  uint8_t hour_;
  uint8_t minute_;
  uint8_t second_;
  String timeStamp;
};
bool externalRTCActive = false;
dueTimeAndDate currentLoopTime;
dueTimeAndDate dataSampleTime;

// Define schedules and alarms for geyser power and for water consumption
struct scheduleAlarm
{
  bool activeAlarm_;  // used to enable the schedule alarm
  bool elapsed_;      // used to check if alarm has finished
  bool running_;
  uint8_t hour_;      // 24-hour 
  uint8_t minute_;
  uint8_t duration_;  // Hours (Only applicable to power)
  double consumption;
};
const int maxNumOfAlarms = 10;  // Maximum number of alarms per schedule
scheduleAlarm waterEventSchedules[maxNumOfAlarms];
scheduleAlarm geyserPowerSchedules[maxNumOfAlarms];
int numberOfRequestedWaterSchedules;
int numberOfRequestedPowerSchedules;

/** Define all function prototypes **/
void oneWireSetup();
bool sdCardSetup();
void timerSetup();
String createTimeStamp(dueTimeAndDate *dateTime, uint8_t timeStampType = timeStampSelect::FULL_TIME_STAMP);
void setThermistorProperties(paramsThermistorNTC *thermistorStruct);
void setCurrentTime(dueTimeAndDate *currentLoopTime);
void setTemperatureRegulationFlags();
void sendDataToSD(String dataString);
void discoverOneWireDevices();
void requestAllTemperatureConversions();
void getGeyserTemperatures();
void getGeyserTemperatureInstance();
bool checkSensorCountOnBus(int busNumber, int sensorCountOnBus);
void stopAllActuators();
void printOutTemperatureMatrix();
void createTempProfileStringArray();
String createFinalDataString();
void configurePins();
void setupExperimentalParameters(String portMessage, char delimiter);
void sendDataToComputer(String dataString);
void sendDataToCloud();
void sendDiagnosticsToComputer();
void controlEnvironment();
void updateSystemParameters();
String sampleData();
void testLatchingRelays(bool which);
bool isDataSampleEvent();
void i2cScanner();
String createFileName(dueTimeAndDate *date_time, String extension = ".csv");
String createSystemParamAndStateString();
void sendInletControlParams();
void readIncomingSerialMessage(int SerialPort = serialPortSelect::serialComputer);
bool checkWifiMesgAvailable();
String getSubString(String data, char separator, int index);
void waitForResponse(long waitingTime);
void captureTemperatureData(bool captureBoilerData = false);
void actuateOutletValve(int valveState);
void actuateGeyserElement(bool powerAvailable, bool elementState);
void actuateHeatingFans(bool heatingElementState, bool fanState);
void actuateVentingFans(bool fanState);
void actuateAmbientFans(bool fanState);
double calculatePrimaryVoltage(float voltageReading, polynomialCalParams calParams);
void capture_AC_current();
double capture_AC_voltage();
double calculate_AC_power(double voltage, double current, bool kWHUnits = false, double pf = 1.00);
double captureWaterConsumption();
double mapDouble(double x, double in_min, double in_max, double out_min, double out_max);
String createChamberDataString();
String* createScreenBuffer();
void controlAmbTemp();
void controlSystemFlowRate();
bool isInPowerSchedule();
void controlGeyserElement();
void controlWaterFlow();
void controlGeyserInletTemp();
void setupSchedules();
void stopSys();
void displaySetup();
void printToOLED(String screenBuff[]);
void wifiSetup();
bool rtcSetup();
void resetMCU();
void configureInterrupts();
void configureADS1115(adsGain_t gain);
void emStopRoutine();
void flowSensorRoutine();
void getTempMargins();
bool isEmergency(DateTime time, uint32_t currentTick);
void municipalFlowSensorRoutine();
void startDataSampleTimer(Tc *tc, uint32_t channel, IRQn_Type irq, uint32_t frequency);
void startSystemUpdateTimer(Tc *tc, uint32_t channel, IRQn_Type irq, uint32_t frequency);
void startPowerSamplingTimer(Tc *tc, uint32_t channel, IRQn_Type irq, uint32_t frequency);
void updateDisplay();
int calcPIDoutput(double flowRateError);
#endif