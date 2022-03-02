/**************************************************************************/
/*! Source code overview and description
  @section Source code overview

  This software serves as a control algorithm for a geyser boiler temperature data acquisition system. 
  The temperature sensor that will be used mainly is the DS18B20. 
  
  The DS18B20 is best suited based on the following: 

    1. Rated accuracy is +- 0.5 C (It is different for every temperature region)
    2. Can read temperatures between -10 C and +85 C
    3. All sensors can be connected on a single bus thanks to the OneWire protocol implemented
    4. The DS18B20 has a built-in ADC which provides temperature readings with a resolution up to 12-bit (9-bit lowest)
    5. Each DS18B20 sensor has a 8-byte ROM address that can be used to reference a specific sensor on the bus. It also 
        allows for many, many devices to be connected on a single bus.
    6. The sensor version used is a waterproof (To some extent) version with a stainless steel probe cover - making it ideal
        for a submerged water usage. 

  This project forms part of a master's thesis at Stellenbosch University's Electrical and Electronic Engineering department. 
  
  This source code will be used to control a microcontroller (Arduino Due) device to capture temperature data points at 
  specific regions of a typical geyser boiler. This is to identify the thermal profile based on water usage data such as 
  volume used and water usasge schedules. It will also be used to verify the work of the "Two-node" geyser model and possibly
  improve it.

  @section Peripherals used and set up.

  @author Daniel van Schalkwyk
          Student number: 19891334
*/
/**************************************************************************/

// Include all header files
#include "geyser_daq_controller.h"

void setup() 
{ 
  Serial.begin(SerialBaudrate);
  inletWaterComms.begin(SerialBaudrate);
  configurePins();
  stopAllActuators(); // Ensure that all actuators are switched off before loop starts (Safety reasons)
  oneWireSetup();
  displaySetup();
  externalRTCActive = rtcSetup();
  sdCardSuccessFlag = sdCardSetup(); 
  setThermistorProperties(&geyserWiseThermistorMain);
  configureADS1115(GAIN_ONE);
  wifiSetup();
  timerSetup();
  Serial.print("Setup Complete");
}

void loop() 
{
  
  setCurrentTime(&currentLoopTime);
  currentLoopTick = millis();
  checkWifiMesgAvailable();
  if(Serial.available() > 0)  // Check if there is any incoming commands 
  { 
    Serial.println("<- Incoming message detected ->");
    readIncomingSerialMessage(serialPortSelect::serialComputer);  // Read in command from serial port and set system accordingly
  }
  else if(inletWaterComms.available() > 0)  // Check if inlet controller is requesting a parameter update for its temperature control
  {
    // Serial.println("<- Incoming message from inlet controller: ->");
    String portMessage = inletWaterComms.readStringUntil(0x10);
    // Serial.println(portMessage);
    if(portMessage.startsWith("R") || portMessage.startsWith("r"))  { sendInletControlParams(); }
  }
  else if(systemStateFlags[runState])  // Continue with regular program sequence
  {
    updateSystemParameters(); // Update system control parameters
    controlEnvironment(); // Control system based on updated system parameters
    if(sampleDataFlag)
    {
      sampleDataFlag = false;
      String dataString = sampleData();
      if(sdCardSuccessFlag) sendDataToSD(dataString);
      if(systemStateFlags[systemStateIndex::shareState])  sendDataToComputer(dataString);
      if(systemStateFlags[systemStateIndex::mqttShare])   sendDataToCloud();
    }
  }
  else if(systemStateFlags[debugState])
  {
    sendDiagnosticsToComputer();
    systemStateFlags[debugState] = false;
    systemStateFlags[idleState] = true;
  }
  updateDisplay(); // Update parameters on the OLED screen
}

/*! Function description
  @brief   
*/
void sendDataToCloud()
{
  // Still need to complete this after I get the Wifi working
}

/*! Function description
  @brief  This function is used to configure a few of the Arduino Due's timers for 
          data actuisition and actuation timing control within the control script
*/
void timerSetup()
{
  // It is important to use the TC1 timer counter because the three channels connected to this 
  // counter is not connected to any of the due pins.
  startDataSampleTimer(TC1, 1, TC4_IRQn, dataSamplingTime);  // Interrupt timer will execute every 5 seconds (0.2 Hz)
  startSystemUpdateTimer(TC1, 0, TC3_IRQn, systemUpdateTime); // Interrupt timer will execute every 1 seconds (1 Hz)
  startPowerSamplingTimer(TC1, 2, TC5_IRQn, PowerSamplingFreq); // Interrupt timer will execute at 1.25 kHz
}

void i2cScanner()
{
  byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16) { Serial.print("0");  }
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
  delay(5000);
}

/*! Function description
  @brief  This function is used to generate the column names for the sampled dataset that is 
          is sent to the SD card. The column names include the variables from the chamber parameter
          variables and the internal boiler DAQ system. 
  \return The string of delimited column parameter names.
*/
String generateColumnHeaders()
{
  String finalColumnHeaders = "Timestamp";
  finalColumnHeaders += ",";
  finalColumnHeaders += systemParamColNames;
  finalColumnHeaders += ",";
  finalColumnHeaders += dataColNamesChamber;
  finalColumnHeaders += ",";
  for(int i = 0; i < boilerProfileBusNumber; i++)
  {
    for(int j = 0; j < maxSensorsPerBus; j++)
    {
      finalColumnHeaders += "B";
      finalColumnHeaders += String(i);
      finalColumnHeaders += "-T";
      finalColumnHeaders += String(j);
      finalColumnHeaders += ",";
    }
  }
  return finalColumnHeaders;
}

/*! Function description
  @brief  This function is used to send the system diagnostics of the microcontroller to the UI computer. 
          This information includes any system errors, number of sensors connected, and any other meta data available.
*/
void sendDiagnosticsToComputer()
{
  // Test the function
  Serial.println("Sending Diagnostics of System {TEST}");
  delay(500);
  Serial.println("Done");
}

/*! Function description
  @brief  This function is used to set the time parameters of a time structure variable passed 
          to the function. 
  \param  *requestedTime A predefined time structure type pointer variable   
*/
void setCurrentTime(dueTimeAndDate *requestedTime)
{
  requestedTime->year_ = dueRTC.getYear();
  requestedTime->month_ = dueRTC.getMonth();
  requestedTime->day_ = dueRTC.getDay();
  requestedTime->hour_ = dueRTC.getHours();
  requestedTime->minute_ = dueRTC.getMinutes();
  requestedTime->second_ = dueRTC.getSeconds();
}

/*! Function description
  @brief  This function is used to send a copy of the data sent to the SD card to the computer over the serial port.
  \param  dataString This variable contains the system data string to be sent over serial to the UI computer
*/
void sendDataToComputer(String dataString) 
{
  Serial.println("Sharing all data with computer:");
  Serial.println(dataString);
  Serial.println("Done");
  Serial.flush();
  // printOutTemperatureMatrix();
}

/*! Function description
  @brief  This is a setup function and is used to configure all the onewire sensors in the system
          It instantiates an array of DallasTemperature objects and configures all elements to the
          same specifications. 
          It sets the resolution of the DS18B20 sensors, sets the "wait for convesion" flag to false 
          and checks that all sensors are connected to their busses - otherwise it will display an error message.
 */
void oneWireSetup() 
{
  // Initialise temperature bus for chamber control
  chamberTempBus.begin();
  chamberTempBus.setResolution(tempResolution);
  chamberTempBus.setWaitForConversion(false);
  // Initialise all temperature busses in boiler DAQ
  for (int i = 0; i < boilerProfileBusNumber; i++)
    {
      /* Temperature bus array description:
        // TempBusses[0] : Full vertical sensor assembly furthest from element
        // TempBusses[1] : Full vertical sensor assembly next to TempBus0 closer to element
        // TempBusses[2] : Full vertical sensor assembly next to TempBus1 closer to element
        // TempBusses[3] : Full vertical sensor assembly closest to boiler element
        // TempBusses[4] : Two short/vertical sensor assemblies above and below element
        // TempBusses[5] : Top-side (left) sensor assembly 
        // TempBusses[6] : Top-side (right) sensor assembly 
        // TempBusses[7] : This bus includes both Bottom-side sensor assemblies of the system
        */
      TempBusses[i] = DallasTemperature(&OneWireBusses[i]);
      TempBusses[i].begin();  //  Initialise all DS18B20 sensors on all busses
      tempDeviceCount[i] = TempBusses[i].getDeviceCount();  //  Get the sensor count of each bus
      TempBusses[i].setResolution(tempResolution);  // Set the temperature resolution of all busses
      TempBusses[i].setWaitForConversion(false);  // Ensure that the MCU knows not to wait for any conversion to alleviate blocking
      if(!checkSensorCountOnBus(i, tempDeviceCount[i]))   // Check that all sensors are connected on each bus
        Serial.println("Disconnected sensors on bus: " + String(i));
    }
}

/** Function description
 * \brief This function is used to update the parameters on the provided OLED screen on the controller.
 */
void updateDisplay()
{
  screenBuffer[0] = createTimeStamp(&currentLoopTime);
  screenBuffer[1] = (systemStateFlags[runState]) ? "System State: RUN" : "System State: IDLE";
  screenBuffer[2] = "Geyser Temp: " + String(geyserWaterTemp) + " C";
  screenBuffer[3] = (geyserLatchFlag) ? "Geyser elem: On" : "Geyser elem: Off";
  screenBuffer[4] = "Water draw: " + String((int)waterConsumed) + " mL";
  printToOLED(screenBuffer);
}

bool checkWifiMesgAvailable()
{
  bool wifiMesgAvailable = false;
  if(wifiPort.available() > 0)
  {
    // Then there is a message in the wifi RX buffer that needs to be read.
    wifiMesgAvailable = true;
    String wifiMesg = wifiPort.readStringUntil(0x10); // Reads the string until newline character --> "\n"
  }
  return wifiMesgAvailable;
} 

void wifiSetup()  // TO:DO !!
{

}

/** Function Ddscription
 * \brief This is a setup function for the SD card functionality. 
 * \return sdCardSuccess - a flag to indicate if the SD card initialisation was successful
 */
bool sdCardSetup()  
{
  bool sdCardSuccess = false;
  // See if the card is present and can be initialized:
  if (!SD.begin(sd_CS)) 
  {
    Serial.println("SD Card failed or is not present -> Data will not be saved");
    sdCardSuccess = false;
  }
  else
  {
    Serial.println("SD card Successfully Initialized");
    sdCardSuccess = true;
  }
  return sdCardSuccess;
}

/** Function Ddscription
 * \brief This function is used to create a filename for the SD card data set file 
 * \return fileName - The name of the file to use
 */
String createFileName(dueTimeAndDate *date_time, String extension)
{
  if(!(extension == ".csv" || extension == ".txt"))
  {
    Serial.println("file extension not supported. Default to .csv");
    extension = ".csv";
  }
  String fileName = String(date_time->hour_);
  fileName += "_";
  fileName += String(date_time->minute_);
  fileName += "_";
  fileName += String(date_time->second_);
  fileName += extension;
  return fileName;
}

/** Function Ddscription
 * \brief This function is called when data needs to be streamed to the available SD card
 * \param dataString  The string of data that needs to be sent to the SD card as an data entry.
 */
void sendDataToSD(String dataString) 
{
  if(newFileFlag)
  {
    fileName = createFileName(&dataSampleTime);
    File dataFile = SD.open(fileName, FILE_WRITE);
    delay(1);
    if (dataFile) 
    {
      dataFile.println(generateColumnHeaders());
      dataFile.close();
    }
    else
    {
      Serial.print("File creation failed");
    }
    newFileFlag = false;
  }
  File dataFile = SD.open(fileName, FILE_WRITE );
  // if the file is available, write to it:
  if (dataFile)
  {
    if(dataReadyFlag) 
    {
      // Send data to SD card
      dataFile.println(dataString);
      dataReadyFlag = false; 
    }
    dataFile.close();
  }
  // if the file isn't open, pop up an error:
  else 
  {
    Serial.println("Error opening file");
  }
}

/** Function Ddscription
 * \brief This function is used to check if all the DS18B20 temperature sensors are connected on the specified bus.
 * \param busNumber The DS18B20 bus number to check if all sensors are connected.
 * \param sensorCountOnBus  The number of sensors detected 
 * \return AllSensorsConnectedFlag - a flag used to indicate that all sensors are connected on the provided bus number
 */
bool checkSensorCountOnBus(int busNumber, int sensorCountOnBus)
{
  bool allSensorsConnected = false;
  switch(busNumber)
  {
    case 0:
    case 1:
    case 2:
    case 3: 
      if(sensorCountOnBus == bus3DeviceCount) allSensorsConnected = true;
      break;
    case 4:
      if(sensorCountOnBus == bus4DeviceCount) allSensorsConnected = true;
      break;
    case 5:
    case 6:
    case 7:
      if(sensorCountOnBus == bus7DeviceCount) allSensorsConnected = true;
      break;
  }
  return allSensorsConnected;
}

/** Function Ddscription
 * \brief This function is used to find all oneWire device addresses on all DS18B20 sensor buses.
 *        The function will print out all the device addresses of every sensor on all buses.
 */
void discoverOneWireDevices()
{
  // Open-source code used to easily find the OneWire Addresses of sensors 
  byte addr[8];
  
  Serial.print("Looking for 1-Wire devices...\n\r");
  for (int j = 0; j < boilerProfileBusNumber; j++)  // Iterate over all temperature busses
  {
    while(OneWireBusses[j].search(addr)) 
    {
      Serial.print("\n\rFound \'1-Wire\' device/s with address/es shown on bus: " + String(j) + ":\n\r");
      for(byte i = 0; i < 8; i++) 
      {
        Serial.print("0x");
        if (addr[i] < 16) {
          Serial.print('0');
        }
        Serial.print(addr[i], HEX);
        if (i < 7) {
          Serial.print(", ");
        }
      }
      if ( OneWire::crc8( addr, 7) != addr[7]) {
          Serial.print("CRC is not valid!\n");
          return;
      }
    }
    Serial.print("\n\r\n\rThat's it.\r\n");
    OneWireBusses[j].reset_search();
  }
  return;
}

/** Function Ddscription
 * \brief This function is used separate a string variable using delimeters
 * \param data  The entire string to be separated
 * \param separator The character delimiter used to split the data string
 * \param index The location of the string to be extracted from the data string
 * \return The indexed string delimited by the separator paramter
 */
String getSubString(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
      if (data.charAt(i) == separator || i == maxIndex) {
          found++;
          strIndex[0] = strIndex[1] + 1;
          strIndex[1] = (i == maxIndex) ? i+1 : i;
      }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

/** Function description
 * \brief This function is used to block the code and wait for a user input.
 * \param waitingTime The amount of time to wait for a response before the program continues.
 */
void waitForResponse(long waitingTime)  
{
  // This function is used to block code while waiting for a response
  double timeOutVal = millis();
  while(!Serial.available())
  {
    // Wait for response 
    if(millis() - (unsigned long)timeOutVal >= (unsigned long)(waitingTime*1000))
    {
      break;
    }
  }
}

/** Function description
 * \brief This function is used to send inlet control parameters to the inlet controller
 */
void sendInletControlParams()
{
  String inletParamsPacket = String(autoControlFlags[inletTempRegIndex]);
  inletParamsPacket += ":";
  inletParamsPacket += systemSetParams[setParamsIndex::geyserInletSetTemp];
  inletParamsPacket += ":";
  inletParamsPacket += inletEnergyInput;
  inletWaterComms.print(inletParamsPacket);
  inletWaterComms.flush();
  Serial.println("Params sent.");
}

/** Function description
 * \brief This function responsible for reading commands from the serial port and then configuring the system to be in the correct state
 */
void readIncomingSerialMessage(int serialPort) 
{
  String portMessage = Serial.readStringUntil(0x10);
  if(getSubString(portMessage, ':', 0).equalsIgnoreCase("V"))
  {
    valveOpen = (bool)getSubString(portMessage, ':', 1).toInt();
    if(systemStateFlags[systemStateIndex::runState])
    {
      if(valveOpen)
      {
        Serial.print("Opening system water valve ");
        if(getSubString(portMessage, ':', 2).startsWith("1") || getSubString(portMessage, ':', 2).startsWith("True"))
          Serial.println("WITH flow regulation");
        else
          Serial.println("WITHOUT flow regulation");
      }
      else 
        Serial.println("Closing system water valve...");
    }
    else {Serial.println("System not in \"Run\" State: Valve won't actuate...");}
  }
  else if(getSubString(portMessage, ':', 0).equalsIgnoreCase("SVP")) // if Outlet Servo Valve Position is received
  {
    inletWaterComms.println("SVP:" + String(getSubString(portMessage, ':', 1).toInt()));
    inletWaterComms.flush();
  }
  else if(getSubString(portMessage, ':', 0).equalsIgnoreCase("OVP"))  // if Outlet Valve Position is received
  {
    outletValvePosTime = getSubString(portMessage, ':', 1).toDouble();
  }
  else
  {
    int messageCMD = getSubString(portMessage, ':', 0).toInt();
    switch (messageCMD)
    {
      case incomingCMDs::startSystem:
      {
        if(getSubString(portMessage, ':', 1).toInt())
        {
          systemStateFlags[runState] = true;
          systemStateFlags[idleState] = false;
          systemStateFlags[setupState] = false;
          Serial.println("System in RUN state");
        }
        else
        {
          systemStateFlags[runState] = false;
          systemStateFlags[idleState] = true;
        }
        break;
      }
      case incomingCMDs::stopSystem:
      {
        stopSys();
        if(getSubString(portMessage, ':', 1).toInt()) // If the stop command is reliable from UI (double check)
        {
          systemStateFlags[runState] = false;
          systemStateFlags[idleState] = true;
          Serial.println("System in IDLE state");
        }
        break;
      }
      case incomingCMDs::setupSytem:
      {
        if(getSubString(portMessage, ':', 1).toInt()) // If the setup command and info is reliable from UI (double check)
        {
          systemStateFlags[runState] = false;
          systemStateFlags[idleState] = true;
          systemStateFlags[setupSytem] = true;
          Serial.println("System in SETUP state");
          setupExperimentalParameters(portMessage, ':');
          setTemperatureRegulationFlags();  // Determine if temperature regulation is requested by the UI 
        }
        break;
      }
      case incomingCMDs::resetSystem:
      {
        resetMCU();  // Microcontroller will reset script
        Serial.println("System reset failed..."); // This shouldn't execute, but iof it does the reset isn't working.
        systemStateFlags[idleState] = true;
        break;
      }
      case incomingCMDs::shareData:
      {
        systemStateFlags[shareState] = (getSubString(portMessage, ':', 1).toInt()) ? true : false;
        break;
      }
      case incomingCMDs::viewData:
      {
        systemStateFlags[viewState] = (getSubString(portMessage, ':', 1).toInt()) ? true : false;
        break;
      }
      case incomingCMDs::debugSystem:
      {
        if(getSubString(portMessage, ':', 1).toInt())
        {
          systemStateFlags[debugState] = true;
          systemStateFlags[runState] = false;
        }
        break;
      }
      case incomingCMDs::OutletValveControl:
      {
        valveOpen = (getSubString(portMessage, ':', 1).toInt()) ? Open : Closed;
        break;
      }
      default:
        Serial.println("Error occured: Command from UI not recognised...");
        break;
    }
  }
}

/*! Function description
  @brief  This function is used to set the system temperature regulation flags. These flags are used to check if temperature regulation for either 
          the geyser water, chamber air temp or inlet water temperature is required for the specific experiment. These system temp regulation flags 
          are set inside the "setupExperimentalParameters" function where it receives the command from the serial port. They are then checked in the 
          "controlEnvironment" function. 
          --
          If these flags are set low, then the temperatures will not be regulated (heaters will not switch on).
*/
void setTemperatureRegulationFlags()
{
  autoControlFlags[autoControlIndex::chamberTempRegIndex] = (systemSetParams[setParamsIndex::chamberSetTemp] != 0) ? true : false;
  autoControlFlags[autoControlIndex::geyserTempRegIndex] = (systemSetParams[setParamsIndex::geyserWaterSetTemp] != 0) ? true : false;
  autoControlFlags[autoControlIndex::inletTempRegIndex] = (systemSetParams[setParamsIndex::geyserInletSetTemp] != 0) ? true : false;
  autoControlFlags[autoControlIndex::flowRateControlIndex] = (systemSetParams[setParamsIndex::waterFlowRateSet] != 0) ? true : false;
}

/*! Function description
  @brief  This function is used to setup the exerimental parameters for the environment to be regulated and for 
          the datasets that will be produced. These parameters include set temperatures, sampling periods, water usage
          schedules and power availability schedules.
  \param portMessage This is the data packet transmitted over the serial port from the User Interface
  \param delimiters The delimiter used to separate the parameters from one another (Usually ":")
*/
void setupExperimentalParameters(String portMessage, char delimiter)
{
  // Separate the portMessage into the different information sections
  dataSamplingTime = getSubString(portMessage, delimiter, setupDataOrder::samplingTimeIndex).toInt(); // Set the sampling period of the captured data
    startDataSampleTimer(TC1, 1, TC4_IRQn, dataSamplingTime);
  String setTempsMsg = getSubString(portMessage, delimiter, setupDataOrder::setParamsIndex);
  inletEnergyInput = getSubString(portMessage, delimiter, setupDataOrder::inletEnergyInputIndex).toInt();
  String waterEventScheduleMsg = getSubString(portMessage, delimiter, setupDataOrder::waterScheduleIndex);
  String powerAvailScheduleMsg = getSubString(portMessage, delimiter, setupDataOrder::powerScheduleIndex);
  // Set all set temperatures from temperature message section
  for(int i = 0; i < setParamsIndex::setParamsCount; i++)
  {
    systemSetParams[i] = getSubString(setTempsMsg, ',', i).toInt();
  }
  // Setup all schedules for water events and consumption volumes
  numberOfRequestedWaterSchedules = getSubString(waterEventScheduleMsg, ',', 0).toInt();
  if(numberOfRequestedWaterSchedules <= maxNumOfAlarms)  // Check for max number of alarms allowed
  {
    for (int i = 0; i < numberOfRequestedWaterSchedules; i++)
    {
      waterEventSchedules[i].activeAlarm_ = true;
      waterEventSchedules[i].running_ = false;
      waterEventSchedules[i].hour_ = getSubString(getSubString(waterEventScheduleMsg, ',', 1 + i*2), 'h', 0).toInt(); // Gets the hour from the string
      waterEventSchedules[i].minute_ = getSubString(getSubString(waterEventScheduleMsg, ',', 1 + i*2), 'h', 1).toInt(); // Gets the minute 
      waterEventSchedules[i].consumption = getSubString(waterEventScheduleMsg, ',', 2 + i*2).toDouble();
    }
  }
 // Setup all schedules for power availability
 numberOfRequestedPowerSchedules = getSubString(powerAvailScheduleMsg, ',', 0).toInt();
 if(numberOfRequestedPowerSchedules <= maxNumOfAlarms)  // Check for max number of alarms allowed
 {
   for (int i = 0; i < numberOfRequestedPowerSchedules; i++)
  {
    geyserPowerSchedules[i].activeAlarm_ = true;
    geyserPowerSchedules[i].running_ = false;
    geyserPowerSchedules[i].hour_ = getSubString(getSubString(powerAvailScheduleMsg, ',', 1 + i*2), 'h', 0).toInt();
    geyserPowerSchedules[i].minute_ = getSubString(getSubString(powerAvailScheduleMsg, ',', 1 + i*2), 'h', 1).toInt();
    geyserPowerSchedules[i].duration_ = getSubString(powerAvailScheduleMsg, ',', 2 + i*2).toDouble();
  }
 }
}

/*! Function description
  @brief This function is used to print out the temperature matrix onto a serial port for debugging purposes
  @returns A serial printout of the temperature matrix
*/
void printOutTemperatureMatrix()  
{   
  createTempProfileStringArray();
  for (int i = 0; i < boilerProfileBusNumber; i++)
  {
    Serial.println(tempProfileStringArray[i]);
  }
  Serial.println("** --------------------------- **");
}

/*! Function description
  @brief Captures a temperature profile instance in time and stores the profile data in a matrix variable
*/
void getGeyserTemperatureInstance()  
{
  // This function is used to capture all the temperature measurements from the system
  // Most of the temperature sensors will be on the oneWire bus, but additional analog
  // Sensors can also be added or used 

  // Extract temperature measurements from the onewire sensors
  if (firstRequestBoilerTemp) 
  {
    requestAllTemperatureConversions();
    firstRequestBoilerTemp = false;
  }
  else    
  {
    getGeyserTemperatures();  // Fetch the temperature data from sensor scratch pads and stores it in a matrix of doubles
    requestAllTemperatureConversions(); // Sends a Skip ROM command to communicate with all sensor simultaneously to do a ADC conversion
  }
}

void testLatchingRelays(bool which)
{
  if(which)
  {
    actuateGeyserElement(true, Off);
    Serial.println("Geyser element state: " + String(geyserLatchFlag));
    delay(50);
    actuateGeyserElement(true, On);
    Serial.println("Geyser element state: " + String(geyserLatchFlag));
    delay(50);
  }
  else
  {
    actuateHeatingFans(On, On);
    Serial.println("Air heater state: " + String(chamberStateFlags[chamberStateIndex::heatingFanElement]));
    delay(50);
    actuateHeatingFans(Off, On);
    Serial.println("Air heater state: " + String(chamberStateFlags[chamberStateIndex::heatingFanElement]));
    delay(50);
  }
}

/*! Function description
  @brief Captures the thermistor temperature reading of the geyserWise thermistor
  \return The bulk water temperature of the geyser water measured by the geyserWise thermistor
*/
double getGeyserThermistorTemp()
{
  analogReadResolution(12);
  double thermistorVoltageReading = (double)analogRead(geyserWaterTempPin);
  geyserWiseThermistorMain.thermistorResistance = geyserWiseThermistorMain.voltDividerR*(max12BitNum/thermistorVoltageReading - 1);
  double thermR = geyserWiseThermistorMain.thermistorResistance;
  geyserWaterTemp = 1.0/(geyserWiseThermistorMain.a2 + geyserWiseThermistorMain.b2*log(thermR) \
                    + geyserWiseThermistorMain.c2*(log(thermR))*(log(thermR))*(log(thermR))) - kelvinToC_const;
  if(geyserWaterTemp < 0) { geyserWaterTemp = geyserThermistorDisconnected; }  // geyser thermostat not connected
  return geyserWaterTemp;
}

/*! Function description
  @brief Captures the thermistor temperature reading of the geyserWise thermistor
  \param  thermistorStruct The thermistor paramater structure to that you want to set
*/
void setThermistorProperties(paramsThermistorNTC *thermistorStruct)
{
  // Set the geyserWise thermistor properties
  thermistorStruct->voltDividerR = 10050.00;
  thermistorStruct->thermistorResistance = 12000.00;
  thermistorStruct->a2 = 1.6746923000E-03;
  thermistorStruct->b2 = 1.3466670000E-04;
  thermistorStruct->c2 = 5.7660617403E-07;
}

/*! Function description
  @brief This function is called when a "Skip ROM" and temperature request command needs to be sent to all sensors simultaneously.
         If an updated temperature profile is required, this function needs to be called to clear sensor memory and 
         to repopulate with new data. 
*/
void requestAllTemperatureConversions() 
{
  // This function is used to send a skip ROM and temperature read command to all DS18B20 busses
  for (int i = 0; i < boilerProfileBusNumber; i++)
  {
    TempBusses[i].requestTemperatures();
  }
}

/*! Function description
  @brief This function is used explicitly to retrieve sensor data from all sensors sequentially and to 
         store the data in a dedicated temperature profile 2-D array.
  @returns void, but populates a global variable 2-D array
*/
void getGeyserTemperatures()  
{
  for(int i = 0; i < boilerProfileBusNumber; i++) // Iterate rows
  {
    for(int j = 0; j < maxSensorsPerBus; j++) // Iterate columns
    {
      boilerProfileTempArray[i][j] = TempBusses[i].getTempC(boilerProfileTempReg[i][j]);  // Fetch temperature from sensor 'ScratchPad' and populate temperature matrix
    }
  }
}

/** Function Ddscription
 * \brief This function is called to make a string array of the boiler temperature data. This is used to simplify the
 *        data transfer to the SD card and or the computer. The string array is a globally declared variable.
 */
void createTempProfileStringArray() 
{
  String temporaryString;
  for(int i = 0; i < boilerProfileBusNumber; i++)
  {
    for(int j = 0; j < maxSensorsPerBus; j++)
    {
      temporaryString += String(boilerProfileTempArray[i][j], 3);
      if(j != maxSensorsPerBus - 1) temporaryString += ",";
    }
    tempProfileStringArray[i] = temporaryString;
    temporaryString = "";
  }
}

/** Function Ddscription
 * \brief This function is used to create the ultimate string, containing all important system paramters and measurement data. 
 * \return finalDataString - The data entry sent to the dataset on the SD card and or the PC
 */
String createFinalDataString()
{
  int numberOfBoilerTempArrayElements = sizeof(tempProfileStringArray)/sizeof(tempProfileStringArray[0]);
  String finalDataString = createTimeStamp(&dataSampleTime);
  finalDataString += ",";
  finalDataString += createSystemParamAndStateString();
  finalDataString += ",";
  finalDataString += createChamberDataString();
  finalDataString += ",";
  createTempProfileStringArray();
  for(int i = 0; i < numberOfBoilerTempArrayElements; i++)
  {
    finalDataString += tempProfileStringArray[i];
    if(i != numberOfBoilerTempArrayElements - 1)  finalDataString += ",";
  }
  return finalDataString;
}

/*! Function description
  @brief  This function is responsible for ensuring that the environment of the EWH unit 
          remains at the desireable parameters and that the geyser schedule is followed.
          Different climatic chamber functions
          1. Ambient Temperature
            1.1. Venting environment when too hot
            1.2. Heating environment when too cold
          2. Geyser internal temperature
            2.1. Switching off element when higher than set point
            2.2. Switching on element when lower than set point 
          3. Schedule for on and off time of the geyser
            3.1. Switch system on according to schedule
            3.2. Swicth system off according to schedule
          4. Control electric ball valve to allow flow of water
            4.1. Open valve to enable flow of water [scheduled or manual]
            4.2. Close vale to disable flow of water [after consumption goal or manual]
          5. Regulate geyser inlet water temperature
            5.1. Send inlet water temperature control parameters to inlet controller
          */
void controlEnvironment() 
{
  if(autoControlFlags[autoControlIndex::geyserPowerControlIndex]) geyserElementPowerAvailable = isInPowerSchedule();
  if(autoControlFlags[autoControlIndex::chamberTempRegIndex])  controlAmbTemp(); 
  if(autoControlFlags[autoControlIndex::geyserTempRegIndex])  controlGeyserElement();
  if(autoControlFlags[autoControlIndex::inletTempRegIndex])  controlGeyserInletTemp();
  controlWaterFlow();
  capture_AC_current();
}

/*! Function description
  @brief  This function is used to communicate between the main controller 
          and the inlet water control unit
*/
void controlGeyserInletTemp()
{
  if(inletWaterComms.available())
  {
    // Do something with received message
    readIncomingSerialMessage(serialPortSelect::serialInlet);  // Read in command from serial port 
  }
}

/*! Function description
  @brief  This function is used to update control parameters for chamber environment control. 
          This data is not shared to an SD card or over a serial monitor, it is only to regulate 
          certain chamber conditions.
*/
void updateSystemParameters()
{
  if(systemUpdateFlag)
  {
    systemUpdateFlag = false; // reset the timer flag
    captureTemperatureData(false);  // Retrieves all temperature data except the inside boiler data
    // Save accumulated information during a time step for data sample event
    AccumulatedEnergyPerDataSample += calculate_AC_power(capture_AC_voltage(), primaryCurrent, true);
    AccumulatedWaterConsumedPerDataSample += captureWaterConsumption();   // Capture current water consumption levels and accumulated consuption per data sampling period
  }
}

/** Function Ddscription
 * \brief This function is used to create a string of the current system states. These states include 
 *        actuator states, set temperatures provided and which temperature regulation regimes are activated.
 * \return SystemStateString - A string containing set temperatures and system states
 */
String createSystemParamAndStateString()
{
  String systemStateString = "";
  // Set temperature parameters
  for (int i = 0; i < setParamsIndex::setParamsCount; i++)
  {
    systemStateString += String(systemSetParams[i]);
    systemStateString += ",";
  }
  // System regulation states
  for (int i = 0; i < autoControlIndex::autoControlIndexCount; i++)
  {
    systemStateString += String(autoControlFlags[i]);
    systemStateString += ",";
  }
  // System actuator states
  for (int i = 0; i < chamberStateIndex::chamberStateCount; i++)
  {
    systemStateString += String(chamberStateFlags[i]);
    systemStateString += ",";
  }
  systemStateString += String(geyserLatchFlag);
  return systemStateString;
}

/*! Function description
  @brief  This function is used to update control parameters for chamber environment control. 
          This data is not shared to an SD card or over a serial monitor, it is only to regulate 
          certain chamber conditions.
*/
String sampleData() 
{
  String dataString = "";
  setCurrentTime(&dataSampleTime);
  // Serial.println("Timestamp: " + createTimeStamp(&dataSampleTime));
  captureTemperatureData(true); // Capture all temperatures including the boiler data - populates a bunch of temperature arrays.
  // Populate the chamber data array for data sampling
  chamberDataArray[0] = AccumulatedEnergyPerDataSample;
  chamberDataArray[1] = AccumulatedWaterConsumedPerDataSample;
  chamberDataArray[2] = waterEventTot;
  AccumulatedEnergyPerDataSample = 0.00;
  AccumulatedWaterConsumedPerDataSample = 0.00;
  waterEventTot = 0.00;
  for(int i = 0; i < numOfChamberTempSensors; i++)
  {
    chamberDataArray[i+3] = climaticChamberTempArray[i];
  }
  dataReadyFlag = true;
  dataString = createFinalDataString();
  return dataString;
}

/*! Function description
  @brief    This function is responsible for capturing all temperature parameters. This includes the
            internal boiler temp data, the thermistor temp data and the external chamber temperature data.
  \param    captureBoilerData Flag used to indicate whether internal boiler temp data needs to be captured.
*/
void captureTemperatureData(bool captureBoilerData)  
{
  if(captureBoilerData)
    getGeyserTemperatureInstance(); // Captures an instance of the Boiler DAQ temp profile

  // Get temperatures of chamber system
  if (firstRequestChamberTemp) 
  {
    chamberTempBus.requestTemperatures();    // send the command to get temperatures
    firstRequestChamberTemp = false;
  }
  prevAmbientTemp = ambientTemp;
  geyserWaterTemp = getGeyserThermistorTemp();
  climaticChamberTempArray[0] = geyserWaterTemp;
  if (!firstRequestChamberTemp)     
  {
    for(int i = 1; i < numOfChamberTempSensors; i++)
    {
      climaticChamberTempArray[i] = chamberTempBus.getTempC(climaticChamberTempReg[i]);
    }
    chamberTempBus.requestTemperatures(); 
  }
  ambientTemp = (climaticChamberTempArray[amb1TempAddress] + climaticChamberTempArray[amb1TempAddress]) / 2;
  ambError = systemSetParams[chamberSetTemp] - ambientTemp;
}

/** Function Ddscription
 * \brief This function is used to sample the current consumption of the geyser heating element at an instance of time. 
 * \return currentConsumption(double) - The current consumption of the geyser heating element
 */
void capture_AC_current()  
{
  // This function is used to measure the AC current that is consumed by the geyser
  // A current transducer circuit is necessary for the function to read the accurate 
  // analog voltage. This voltage should be tested before connected to the Arduino
  // to ensure that the voltage levels do not exceed 3.3V (Arduino Due) or 5V (Arduino Mega)
  if(currentBufferSampledFlag)
  {
    currentBufferSampledFlag = false; 
    double currentMean = (double)currentSqrtSampleSum/(double)currentSampleBufferSize; 
    currentSqrtSampleSum = 0;
    double currentVrefMean = (double)currentVrefSum/(double)currentSampleBufferSize;
    currentVrefSum = 0;
    double rmsCurrentMean = sqrt(currentMean);
    double primaryCurrentVoltage = mapDouble(rmsCurrentMean, 0, max12BitNum, 0, 3.30);
    primaryCurrent = (primaryCurrentVoltage)/(0.625) * currentSensorRated;
  }
  // Cap the current to zero if the output value is unrealistic
  if (primaryCurrent <= 0.1)  {primaryCurrent = 0;}
}

/** Function Ddscription
 * \brief This function is used to sample the operating voltage of the geyser heating element at an instance of time. 
 *        It will most probably be close to 230V (RMS)
 * \return geyserVoltage(double) - The operating voltage of the geyser heating element.
 */
double capture_AC_voltage() 
{
  // This function is used to measure the AC voltage of the Eskom power supply
  // that is used to supply the geyser with power
  analogReadResolution(12);
  double primaryVoltage;
  if(internalADCflag)
  {
    double voltageReading = mapDouble((double)analogRead(voltageReadPin), 0.00, max12BitNum, 0.00, 3.30);
    // Cap the voltage to zero if the output value is unrealistic
    primaryVoltage = calculatePrimaryVoltage(voltageReading, voltageCalParams);
    if (voltageReading <= 0.1)  { primaryVoltage = 0; }
  }
  else
  {
    double voltageReading = mapDouble((double)externADC.readADC_SingleEnded(externADCPins::voltagePin), 0.00, pow(2, 15)-1, 0.00, 3.30);
    primaryVoltage = calculatePrimaryVoltage(voltageReading, voltageCalParams);
    if (voltageReading <= 0.1)  { primaryVoltage = 0; }
  }
  return 240.0; // Temporary
}

double calculatePrimaryVoltage(float voltageReading, polynomialCalParams calParams)
{
  // Implement calibration curve as determined from excel data
  return -7.6484*pow((double)voltageReading, 2) + 89.79*(double)voltageReading + 1.8238;  // Fitted characteristic curve
  // return calParams.C2*pow((double)voltageReading, 2) + calParams.C1*(double)voltageReading + calParams.C0;  // Fitted characteristic curve
}

/** Function Ddscription
 * \brief This function is called when a power calculation is required of an instance in time.
 * \param voltage The sampled operating voltage of the device
 * \param current The sampled current consumption of the device
 * \param pf  The power factor of the device (approximated) 
 * \return currentConsumption(double) - The current consumption of the geyser heating element
 */
double calculate_AC_power(double voltage, double current, bool kWhUnits, double pf) 
{ 
  powerConsumed = voltage*current*pf;
  if (geyserLatchFlag == false) { powerConsumed = 0.00; }
  
  if(kWhUnits)
  {
    // Calculate power in Wh - the energy consumed per sampling time
    powerConsumed *= 0.000277778;
  }
  return powerConsumed;
}

/*! Function description
  @brief  This function is called for when a water consumption sample is required. 
          It uses the volatile current flowCounter variable value in the flow sensor ISR 
          and multiplies it with the resolution value of the sensor to get the water consumption
          per sampled time. The flowCounter variable is then reset back to zero.
  \returns The amount of water consumed (in mL) for every sampled time
*/
double captureWaterConsumption()  
{
  if(activeFlow) 
  {
    waterConsumed = flowCounter*flowMeterResolution;      // This will output consumption in millilters
    flowCounter = 0;
    if(waterConsumed <= 2*flowMeterResolution)  // if no more water is recorded, then reset flag to indicate no flow
    {
      activeFlow = false;
      waterConsumed = 0;
    }
  }
  return waterConsumed;
}

/*! Function description
  @brief  This function is called when the parameters and measurements of the chamber system needs to be 
          converted to a string format
*/
String createChamberDataString()  
{ 
  int numOfDataArrayElements = sizeof(chamberDataArray)/sizeof(chamberDataArray[0]);
  String dataString = "";
  for(int i = 0; i < numOfDataArrayElements; i++)
  {
    dataString += String(chamberDataArray[i], 3);
    dataString += ",";
  }
  dataString += String(ambientTemp, 3);
  return dataString;
}

/*! Function description
  @brief  This function is exclusively used to control the internal climatic chamber temperature of the system.
          It is used to control the heating fans and the venting fans 
          of the geyser environment based on the temperature reading of the environment
*/
void controlAmbTemp() 
{ 
  if(systemAmbientUpdateCounter >= 2)
  {
    systemAmbientUpdateCounter = false;
    double outsideTemp = climaticChamberTempArray[outsideTempAddress];
    double ambSetTemp = systemSetParams[chamberSetTemp];
    getTempMargins();
    systemStateFlags[errorState] = false;
    // Check if the set ambient temperature is achievable
    if(outsideTemp > ambSetTemp)  
    {
      systemStateFlags[errorState] = true;
      Serial.println("ERROR: -> Set temperature for geyser environment cannot be lower than outside lab temperature:");
    }
    else
    {
      systemStateFlags[errorState] = false;
    }
    if(climaticChamberTempArray[amb1TempAddress] == sensorErrorNum || climaticChamberTempArray[amb2TempAddress] == sensorErrorNum)
    {
      systemStateFlags[errorState] = true;
      actuateHeatingFans(Off, On);  // Turn heating fan elements off for safety
      Serial.println("ERROR: -> One or more of the chamber temperature sensors are faulty or disconnected");
    }
    else
    {
      systemStateFlags[errorState] = false;
    }
    // If there is no error, continue with program
    if(!systemStateFlags[errorState])
    {
      actuateAmbientFans(On);   // Turn on the ambient fans
      if(ambSetTemp <= ambientTemp)
      {
        initialHeating = false;
      }
      // Check if the ambient temperature is equal to or higher than the set ambient temperature
      //  if((ambSetTemp + T_upper >= ambientTemp) && (ambientTemp - prevAmbientTemp <= 0)) // The environment does not need heating
      if((ambSetTemp + T_upper <= ambientTemp))
      {
        //Serial.println("Cooling loop activated");
        ambientReady = true;
        actuateHeatingFans(Off, On);  // Fans for element remain on to cool off element to prevent damage
        if(ambientTemp - ambSetTemp >= 0.30)
        {
          actuateVentingFans(On);
          actuateAmbientFans(On);
        }
        else
        {
          actuateVentingFans(Off);   // Turn off the venting fans
        }
      }
      // else if((ambSetTemp - T_lower <= ambientTemp) && (ambientTemp - prevAmbientTemp >= 0) || initialHeating) // Environment needs to be heated
      else if((ambSetTemp - T_lower >= ambientTemp))
      {
        ambientReady = false;   // ambient is not ready for testing
        actuateHeatingFans(On, On);   // Both heating fans start heating up the chamber
        Serial.println("Heaters actuated"); // temp debugging tool
        actuateVentingFans(Off);     // Turn off the venting fans
      }
      double tempDiff = amb1Temp-amb2Temp;
      if(abs(tempDiff) <= 1.00)
      {
        if(!ventingFlag)
          actuateAmbientFans(Off);  // Turn off the ambient fans
      }
      else
        actuateAmbientFans(On);  // Turn on the ambient fans 
    }
  }
  
}

void getTempMargins() 
{ 
  // This function is used to determine the upper and lower switching temperatures 
  // for the ambient temperature control function.
  double T_des = 50;      // Defines the design temperature
  double upperBC = 0.4;   // Defines the upper temperature boundary condition
  double lowerBC = 0.4;   // Defines the lower temperature boundary condition
  double outsideTemp = climaticChamberTempArray[outsideTempAddress];
  if (outsideTemp <= 0)
    outsideTemp = 22;   // if the sensor is faulty then assign a default value

  double C1 = - (upperBC)/(T_des-outsideTemp)*outsideTemp;
  double C2 = (lowerBC)/(T_des-outsideTemp)*outsideTemp + lowerBC;
  T_upper = (upperBC)/(T_des-outsideTemp)*systemSetParams[chamberSetTemp] + C1;
  T_lower = -(lowerBC)/(T_des-outsideTemp)*systemSetParams[chamberSetTemp] + C2;
}

/*! Function description
  @brief  This function is responsible for controlling the power delivered 
          to the element of the geyser. This function is used to check if the geyser element is scheduled to have power, that being said, 
          whether it should respond to the set temperature reading of the water or whether it 
          should remain off.
  \returns A boolean flag indicating whether there is scheduled power availability
*/
bool isInPowerSchedule() 
{   
  bool geyserElementPowerAvailable = false;
  for(int i = 0; i < numberOfRequestedPowerSchedules; i++)
  {
    uint8_t scheduledDurationHours = geyserPowerSchedules[i].duration_ / 60;
    uint8_t scheduledDurationMin = geyserPowerSchedules[i].duration_ % 60;
    // If the current time is at the start of the "Power available" period
    if(geyserPowerSchedules[i].activeAlarm_ && !geyserPowerSchedules[i].running_\
      && geyserPowerSchedules[i].hour_ == (uint8_t)currentLoopTime.hour_\
      && geyserPowerSchedules[i].minute_ == (uint8_t)currentLoopTime.minute_ && !geyserPowerSchedules[i].elapsed_)
    {
      geyserPowerSchedules[i].elapsed_ = false;
      geyserPowerSchedules[i].running_ = true;
      geyserElementPowerAvailable = true;
    }
    // Else if it is in the scheduled "Power available" period
    else if(geyserPowerSchedules[i].running_ && !geyserPowerSchedules[i].elapsed_)
    {
      // Check if the "Power available" period has elapsed
      if(currentLoopTime.hour_ - geyserPowerSchedules[i].hour_ == scheduledDurationHours\
        && currentLoopTime.minute_ - geyserPowerSchedules[i].minute_ == scheduledDurationMin)
      {
        geyserPowerSchedules[i].elapsed_ = true;
        geyserPowerSchedules[i].running_ = false;
        geyserElementPowerAvailable = false;
      }
    }
  }
  return geyserElementPowerAvailable;
}

/*! Function description
  @brief  This function is responsible for controlling the power delivered 
          to the element of the geyser. The power will switch between ON and OFF
          based on the temperature reading of the internal geyser water.
*/
void controlGeyserElement()  
{
  if(geyserTempDelayTick >= 5)  // Update geyser element state every 5 seconds 
  {
    geyserTempDelayTick = 0;
    double geyserSetTemp = systemSetParams[setParamsIndex::geyserWaterSetTemp];
    double deadBandBottom = geyserSetTemp - deadBandMargin/2;
    double deadBandTop = geyserSetTemp + deadBandMargin/2;
    // Check if the water temperature is below the set temperature
    if(geyserWaterTemp < deadBandBottom )
    {
      inDeadBand = false;
      // Geyser element should switch on and make sure that temp sensors are not faulty
      if  (!geyserLatchFlag && (geyserWaterTemp != geyserThermistorDisconnected) && \
          !(boilerProfileTempArray[3][4] >= deadBandTop + 5) && !(boilerProfileTempArray[2][4] >= deadBandTop + 5)) // Check if other DS18B20 sensors are sensing a higher tank temperature than thermistor (Protection)
        actuateGeyserElement(geyserElementPowerAvailable, On);
    }
    // Check if the water temperature is above the set temperature
    else if(geyserWaterTemp >= deadBandTop)
    {
      // Geyser element should switch off
      if(geyserLatchFlag)   
        actuateGeyserElement(geyserElementPowerAvailable, Off);
    }
    // Check if the water temperature is in the defined deadband zone
    else if((geyserWaterTemp >= deadBandBottom) && (geyserWaterTemp <= deadBandTop))
    {
      inDeadBand = true;
    }
    else  // Water temperature is not in deadband region
    {
      inDeadBand = false;
    }
  }
}

/*! Function description
  @brief  This function is responsible for controlling the flow rate of the DC valve at the exit.
  \param  flowRateError The calculated error of the set point top the measured flow rate
  \returns The PID output based on the current and historic error
*/
int calcPIDoutput(double flowRateError)
{
  PIDout.Kp = 50;
  PIDout.Ki = 0.01;
  // PIDout.Kd = 0.05;
  flowRateError *= 60;  // Convert flowRateError from L/s to L/min
  double errorDiff = PIDout.e_prev - flowRateError;
  int PID_out = 0.00;
  // Calculate the PID output based on the error
  PID_out = PIDout.Kp*flowRateError + PIDout.Ki*PIDout.e_sum + PIDout.Kd*errorDiff;
  if(PID_out >= 1000) PID_out = 1000;
  else if(PID_out <= -1000) PID_out = -1000;
  // Collect the sum of the errors and set the new error value for next iteration
  PIDout.e_sum += flowRateError;
  if(PIDout.e_sum >= 10) {PIDout.e_sum = 10;}
  else if(PIDout.e_sum <= -10)  {PIDout.e_sum = -10;}
  PIDout.e_prev = flowRateError;
  return PID_out;
}

/*! Function description
  @brief  This function is responsible for controlling the water flow rate 
          of the system based on user set input.
*/
void controlSystemFlowRate()
{
  if(flowRateControlCount >= flowControlUpdateTime) // This if statement is triggered every 4 seconds second
  {
    flowRateControlCount = 0;
    double flowRateSetPerSecond = systemSetParams[setParamsIndex::waterFlowRateSet]/60.00; // Convert /min to /sec
    double actualFlowRatePerSecond = (double)flowControlCounter*flowMeterResolution/(flowControlUpdateTime*1000.00); // Convert from mL to L
    flowRateError = flowRateSetPerSecond - actualFlowRatePerSecond;
    PID_OutTime = calcPIDoutput(flowRateError); // Calculate the output time in milliseconds to actuate
    flowControlCounter = 0;
    actuateValveFlag = true;
    prevValveOpenStepTick = millis();
  }
  // Actual actuation of valve
  if(actuateValveFlag)
  {
    if(PID_OutTime > 0) // If the PID output is positive then ball vale should open more
    {
      actuateOutletValve(Open);
    }
    else if (PID_OutTime < 0) // If the PID output is negative then ball vale should close
    {
      actuateOutletValve(Closed);
    }
    // Actuate the valve until set point is reached
    if(millis() - prevValveOpenStepTick > abs(PID_OutTime))  // Reset flags to stop actuation
    {
      actuateValveFlag = false;
      actuateOutletValve(NoOutput);
    } 
  }
}

/*! Function description
  @brief  This function is used to control the outlet electric ball valve to enable 
          and disable water flow from or into the geyser.
          The electric ball valve should be able to be opened manually via a physical toggle switch
          or after a scheduled time has passed.
          The electric ball valve should be closed after a specified amount of water has been recorded 
          or by manually toggling a physical toggle switch
*/
void controlWaterFlow() 
{
  // Check if the valve is currently supposed to be open
  int waterScheduleNum = 0;
  if(valveOpen)
  {
    if(autoControlFlags[autoControlIndex::flowRateControlIndex])
    {
      controlSystemFlowRate();
    }
    else
    {
      actuateOutletValve(Open); // Open outlet valve
      // Check if water consumption target has been reached for specific water event
      if(autoControlFlags[autoControlIndex::waterScheduleControlIndex] && waterEventSchedules[waterScheduleNum].running_ && (waterEventTot >= waterEventSchedules[waterScheduleNum].consumption - 1.5e3))
      {
        actuateOutletValve(Closed); // Close outlet valve
        valveOpen = false;
        waterEventSchedules[waterScheduleNum].running_ = false;
      }
    }
  }
  else  
  {
    actuateOutletValve(Closed);
    // Check if any of the scheduled events are triggered 
    if(autoControlFlags[autoControlIndex::waterScheduleControlIndex])
    {
      for(int i = 0; i < numberOfRequestedWaterSchedules; i++)
      {
        if(waterEventSchedules[i].activeAlarm_ && waterEventSchedules[i].hour_ == (uint8_t)currentLoopTime.hour_ \
          && waterEventSchedules[i].minute_ == (uint8_t)currentLoopTime.minute_ && !waterEventSchedules[i].elapsed_)
        {
          valveOpen = true;
          waterEventSchedules[i].elapsed_ = true;
          waterEventSchedules[i].running_ = true;
          waterScheduleNum = i;
        }
      }
    }
  }
}

/*! Function description
  @brief  This function is used to toggle the state (open or close) of the outlet electric ball valve.
  \param valveState determines whether the ball valve opens or closes. If true, the valve opens and vice versa.
*/
void actuateOutletValve(int valveState)
{
  if(valveState == Open)
  {
    chamberStateFlags[chamberStateIndex::valveState] = Open;
    digitalWrite(valveClosePin, LOW);
    digitalWrite(valveOpenPin, HIGH);
  }
  else if(valveState == Closed)
  {
    chamberStateFlags[chamberStateIndex::valveState] = Closed;
    digitalWrite(valveClosePin, HIGH);
    digitalWrite(valveOpenPin, LOW);
  }
  else if(valveState == NoOutput)
  {
    digitalWrite(valveClosePin, LOW);
    digitalWrite(valveOpenPin, LOW);
  }
}

/*! Function description
  @brief  This function is used to toggle the state of the heating fans' fans and heating elements.
  \param heatingElementState determines whether the heating element in the heating fan should switch on. If true, element turns on and vice versa.
  \param fanState determines whether the fan of the heating fans should switch on. If true, fans will switch on and vice versa
*/
void actuateHeatingFans(bool heatingElementState, bool fanState)
{
  chamberStateFlags[chamberStateIndex::heatingFan] = fanState;
  digitalWrite(ambHeatingFans, fanState);
  if(heatingElementState)
  {
    // Engage latching relay to set state
    chamberStateFlags[chamberStateIndex::heatingFanElement] = On;
    digitalWrite(ambHeatingElem_set, On);
    digitalWrite(ambHeatingElem_reset, Off);
    delay(5);
    digitalWrite(ambHeatingElem_set, Off);
    ambHeatingFlag = true;
  }
  else
  {
    // Engage latching relay to to reset state
    chamberStateFlags[chamberStateIndex::heatingFanElement] = Off;
    digitalWrite(ambHeatingElem_set, Off);
    digitalWrite(ambHeatingElem_reset, On);
    delay(5);
    digitalWrite(ambHeatingElem_reset, Off);
    ambHeatingFlag = false;
  }
}

/*! Function description
  @brief  This function is used to toggle the state (open or close) of the geyser heating element.
  \param elementState determines whether the heating element switches on or off. If true, the element switches ON and vice versa.
*/
void actuateGeyserElement(bool powerAvailable, bool elementState)
{
  if(powerAvailable)
  {
    if(elementState)
    {
      geyserLatchFlag = On;
      digitalWrite(geyserPowerReset, LOW);
      digitalWrite(geyserPowerSet, HIGH);
      delay(50);
      digitalWrite(geyserPowerSet, LOW);
    }
    else
    {
      geyserLatchFlag = Off;
      digitalWrite(geyserPowerReset, HIGH);
      digitalWrite(geyserPowerSet, LOW);
      delay(50);
      digitalWrite(geyserPowerReset, LOW);
    }
  }
  else
  {
    geyserLatchFlag = Off;
    digitalWrite(geyserPowerReset, HIGH);
    digitalWrite(geyserPowerSet, LOW);
    delay(50);
    digitalWrite(geyserPowerReset, LOW);
  }
}

/*! Function description
  @brief  This function is used to turn on / turn off the venting fans to cool down the chamber
  \param fanState determines whether the venting fans switch on or off. If true, the fans turn ON and vice versa.
*/
void actuateVentingFans(bool fanState)
{
  chamberStateFlags[chamberStateIndex::ventingFan] = fanState;
  digitalWrite(ventingPin, fanState);
  ventingFlag = fanState;
} 

/*! Function description
  @brief  This function is used to turn on / turn off the circulation fans to homogenise the chamber temperature
  \param fanState determines whether the circulation fans switch on or off. If true, the fans turn ON and vice versa.
*/
void actuateAmbientFans(bool fanState)
{
  chamberStateFlags[chamberStateIndex::circulationFan] = fanState;
  digitalWrite(ambientFans, fanState);
}

/*! Function description
  @brief  This function is used to switch off all actuators and to put the system in IDLE state
*/
void stopSys() 
{
  stopAllActuators();
  systemStateFlags[idleState] = true;
  systemStateFlags[shareState] = true;
  newFileFlag = true;
}

/*! Function description
  @brief  This function is explicitly used to switch off all actuators
*/
void stopAllActuators() 
{
  actuateGeyserElement(Off, Off);
  actuateHeatingFans(Off, Off);
  actuateAmbientFans(Off);
  actuateVentingFans(Off);
}

/** Description
 * \brief Responisible for configuring the ADS1115 modules to specified parameters for pressure sensors
 * \param gain The PGA value for amplification. 
 *        GAIN_TWOTHIRDS, GAIN_ONE, GAIN_TWO, GAIN_FOUR, GAIN_EIGHT, GAIN_SIXTEEN
 */
void configureADS1115(adsGain_t gain) 
{
  externADC.begin();
  externADC.setGain(gain);
}

/*! Function description
  @brief  This function is used to configure and set the RTCs of the system.
          For now, the DS3231 RTC is used, but later the Due's own RTC will be incorporated.
*/
bool rtcSetup() 
{
  bool externalRTCActive = false;
  if (!sysRTC.begin()) 
  {
    externalRTCActive = false;
    Serial.println("Couldn't find RTC");
    Serial.flush();
  }
  else
  {
    externalRTCActive = true;
    sysRTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  if (sysRTC.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    externalRTCActive = false;
    sysRTC.adjust(DateTime(F(__DATE__), F(__TIME__)));

    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  // Configure the internal RTC of the Arduino Due
  dueRTC.begin();
  if(externalRTCActive)
  {
    DateTime externalRTC = sysRTC.now();
    dueRTC.setYear(externalRTC.year());
    dueRTC.setMonth(externalRTC.month());
    dueRTC.setDay(externalRTC.day());
    dueRTC.setHours(externalRTC.hour());
    dueRTC.setMinutes(externalRTC.minute());
    dueRTC.setSeconds(externalRTC.second());
  }
  else
  {
    dueRTC.setClock(__DATE__, __TIME__);
  }
  return externalRTCActive;
}

/*! Function description
  @brief  This function is used create a string of a received reference to a time-based struct variable. 
  An example of the default output timestamp is: "2021-05-28T14:02:09" (YYYY-MM-DDTHH:mm:ss).
  \param  *dateTime a pointer to a dueTimeAndDate variable of type Struct
  \param  timeStampType Determines that type of timestamp requested. FullTimeStamp = 0 (Default), TimeOnly = 1, DateOnly = 2.
*/
String createTimeStamp(dueTimeAndDate *dateTime, uint8_t timeStampType)
{
  String dueTimeStamp = "";
  switch (timeStampType)
  {
    case FULL_TIME_STAMP:
    {
      dueTimeStamp = createTimeStamp(dateTime, DATE_STAMP);
      dueTimeStamp += "T";
      dueTimeStamp += createTimeStamp(dateTime, TIME_STAMP);
      break;
    }
    case TIME_STAMP: // if only Time is requested
    {
      if(dateTime->hour_ < 10) dueTimeStamp += "0";
      dueTimeStamp += String(dateTime->hour_);
      dueTimeStamp += ":";
      if(dateTime->minute_ < 10) dueTimeStamp += "0";
      dueTimeStamp += String(dateTime->minute_);
      dueTimeStamp += ":";
      if(dateTime->second_ < 10) dueTimeStamp += "0";
      dueTimeStamp += String(dateTime->second_);
      break;
    }
    case DATE_STAMP: // if only Date is requested
    {
      dueTimeStamp = String(dateTime->year_);
      dueTimeStamp += "-";
      if(dateTime->month_ < 10) dueTimeStamp += "0";
      dueTimeStamp += String(dateTime->month_);
      dueTimeStamp += "-";
      if(dateTime->day_ < 10) dueTimeStamp += "0";
      dueTimeStamp += String(dateTime->day_);
      break;
    }
    default:
      break;
  }
  
  return dueTimeStamp;
}

/*! Function description
  @brief  This function is used exclusively when the MCU and peripherals need to be resetted. 
          A software reset is implemented. 
*/
void resetMCU()
{
  RSTC->RSTC_CR = 0xA5000005; // Reset processor and internal peripherals
}

/*! Function description
  @brief  This function is used to configure the appropriate interrupt pins of the overall system.
*/
void configureInterrupts() 
{
  pinMode(emergencyStop, INPUT);
  pinMode(flowSensorPin, INPUT);
  pinMode(municipalSensor, INPUT);
  // attachInterrupt(digitalPinToInterrupt(emergencyStop), emStopRoutine, FALLING);
  attachInterrupt(digitalPinToInterrupt(flowSensorPin), flowSensorRoutine, FALLING);
  // attachInterrupt(digitalPinToInterrupt(municipalSensor), municipalFlowSensorRoutine, FALLING);
}

/*! Function description
  @brief  
*/
void displaySetup()
{
  if(u8g2.begin())
  {
    u8g2.clearDisplay();
    u8g2.setFont(u8g2_font_6x10_tr);
    u8g2.firstPage();
    do 
    {
      u8g2.setCursor(0, 20);
      u8g2.print(F("Welcome!"));
    } 
    while ( u8g2.nextPage() );
  }
  
  if(display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  { 
   // Clear the buffer
    display.clearDisplay();
    delay(1);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    // Display static text
    display.println("OLED screen ready!");
    display.setCursor(0, 10);
    display.println("Current State: IDLE");
    display.display();
    delay(1);
  }
}

/*! Function description
  @brief  
*/
void printToOLED(String screenBuff[])
{
  uint8_t xScreenPos = 0;
  uint8_t yScreenPos = 0;
  display.clearDisplay();
  delay(1);
  for(int i = 0; i < 10; i++)
  {
    display.setCursor(xScreenPos, yScreenPos);
    display.println(screenBuff[i]);
    yScreenPos += 11;
  }
  display.display();
  delay(1);
}

String* createScreenBuffer()
{
  String* screenBuffer = new String[6];
  screenBuffer[0] = createTimeStamp(&currentLoopTime);

  return screenBuffer;
}

/*! Function description
  @brief  This function is used to configure all pins used in the overall system.
*/
void configurePins()
{
  // Configure all OUTPUT pins (Default is INPUT)
  pinMode(sd_CS, OUTPUT);
  pinMode(valveClosePin, OUTPUT);   digitalWrite(valveClosePin, LOW);
  pinMode(valveOpenPin, OUTPUT);    digitalWrite(valveOpenPin, LOW);
  pinMode(ambientFans, OUTPUT);     digitalWrite(ambientFans, LOW);
  pinMode(ventingPin, OUTPUT);      digitalWrite(ventingPin, LOW);
  pinMode(ambHeatingFans, OUTPUT);  digitalWrite(ambHeatingFans, LOW);
  pinMode(ambHeatingElem_set, OUTPUT);    digitalWrite(ambHeatingElem_set, LOW);
  pinMode(ambHeatingElem_reset, OUTPUT);  digitalWrite(ambHeatingElem_reset, LOW);
  pinMode(geyserPowerSet, OUTPUT);    digitalWrite(geyserPowerSet, LOW);
  pinMode(geyserPowerReset, OUTPUT);  digitalWrite(geyserPowerReset, LOW);
    // pinMode(IWH_control_pin, OUTPUT);   digitalWrite(IWH_control_pin, LOW);
  //Configure all interrupts
  configureInterrupts();
  analogReadResolution(12); // Set analgue pin resolution to 12 bits
}

/*! Function description
  @brief  This function is used to check if an emergency stop event has been triggered. 
          If it has, then it disables all actuators and resets system to IDLE state.
  \param  time The current time when the emergency event was triggered.
  \param  currentTick The current millis() value to check for debouncing if necessary
  \returns The boolean flag for if an emergency event was triggered. If true, then yes and vice versa.
*/
bool isEmergency(dueTimeAndDate time, uint32_t currentTick) 
{
  bool isEmergency = emergencyStateFlag;
  if(emergencyStateFlag && (currentTick - emergencyTick > debounceTime))  
  {
    systemStateFlags[emergencyState] = true;
    stopSys();
    newFileFlag = HIGH;
    Serial.println("Emergency State activated at: " + createTimeStamp(&time));
    // Reset Emergency state 
    emergencyStateFlag = false;
    systemStateFlags[emergencyState] = false;
    delay(1000);
  }
  return isEmergency;
}

/*! ISR description
  @brief  This is the interrupt service routine (ISR) of the emergency stop EXTI line
          The millis() value is recorded for debouncing and a flag is triggered high to 
          be used in the main loop.
*/
void emStopRoutine() 
{  // This is the ISR for the emergency state
  emergencyTick = millis();
  emergencyStateFlag = true;
}

/*! ISR description
  @brief  This is the interrupt service routine (ISR) of the hall-effect flow sensor EXTI line.
          When the routine is triggered, a flag indicating active flow is triggered and a flow pulse
          counter is incremented and inspected in the main loop.
*/
void flowSensorRoutine()  
{
  activeFlow = true;
  flowCounter++;
  flowControlCounter++;
  // Serial.println(flowCounter);
}

/*! ISR description
  @brief  This is the interrupt service routine (ISR) of the ...
*/
void municipalFlowSensorRoutine() 
{
  municipalFlowCounter++;
}

double mapDouble(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Timer stuff
void startDataSampleTimer(Tc *tc, uint32_t channel, IRQn_Type irq, uint32_t frequency) {
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk((uint32_t)irq);
  TC_Configure(tc, channel, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);
  uint32_t rc = VARIANT_MCK/128*frequency; // 128 because we selected TIMER_CLOCK4 above
  TC_SetRA(tc, channel, rc/2); // 50% high, 50% low
  TC_SetRC(tc, channel, rc);
  TC_Start(tc, channel);
  tc->TC_CHANNEL[channel].TC_IER = TC_IER_CPCS;
  tc->TC_CHANNEL[channel].TC_IDR =~ TC_IER_CPCS;
  NVIC_EnableIRQ(irq);
}

void startSystemUpdateTimer(Tc *tc, uint32_t channel, IRQn_Type irq, uint32_t frequency) {
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk((uint32_t)irq);
  TC_Configure(tc, channel, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);
  uint32_t rc = VARIANT_MCK/128/frequency; //128 because we selected TIMER_CLOCK4 above
  TC_SetRA(tc, channel, rc/2); //50% high, 50% low
  TC_SetRC(tc, channel, rc);
  TC_Start(tc, channel);
  tc->TC_CHANNEL[channel].TC_IER = TC_IER_CPCS;
  tc->TC_CHANNEL[channel].TC_IDR =~ TC_IER_CPCS;
  NVIC_EnableIRQ(irq);
}

void startPowerSamplingTimer(Tc *tc, uint32_t channel, IRQn_Type irq, uint32_t frequency)
{
  startSystemUpdateTimer(tc, channel, irq, frequency);
}

// This function is called every 1s
void TC3_Handler()
{
  // You must do TC_GetStatus to "accept" interrupt
  // As parameters use the first two parameters used in startTimer (TC1, 0 in this case)
  TC_GetStatus(TC1, 0);
  // Serial.println(String(millis()) + " : Timer works");
  systemUpdateFlag = true;
  systemAmbientUpdateCounter++;
  geyserTempDelayTick++;
  flowRateControlCount++;
}

// This function is called every 5s
void TC4_Handler()
{
  // You must do TC_GetStatus to "accept" interrupt
  // As parameters use the first two parameters used in startTimer (TC1, 1 in this case)
  TC_GetStatus(TC1, 1);
  // Serial.println(String(millis()) + " : Second Timer works");
  sampleDataFlag = true;
}

// This function is called every 800us -> 1.25kHz for current sampling
void TC5_Handler()
{
  // You must do TC_GetStatus to "accept" interrupt
  TC_GetStatus(TC1, 2);
  currentACsignalBuffer[currentSampleIndex] = analogRead(currentReadPin) - analogRead(currentVref);
  // currentACsignalBuffer[currentSampleIndex] = analogRead(currentReadPin);
  currentSqrtSampleSum += sq(currentACsignalBuffer[currentSampleIndex]);
  currentVrefSum += analogRead(currentVref);
  currentSampleIndex++; 
  if(currentSampleIndex == currentSampleBufferSize) { currentSampleIndex = 0; currentBufferSampledFlag = true;}
}