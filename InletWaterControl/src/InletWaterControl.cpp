#include <declarations.h>

void setup() {
  // Setup code
  Serial.begin(serialSpeed);
  mainControllerChannel.begin(serialSpeed);
  configurePins();
  oneWireSetup();
  servoMotorSetup();
  startTimer(servoUpdateFrequency);
  displaySetup();
  // connectToWifi();
  previousStateCLK = digitalRead(encoderClkPin);
  Serial.print("Setup Complete");
  requestInletControllerParams();
  actuateServo(0, 90.00); // Open valve to be fully supplied by source water side
}

void loop() {
  // Loop code

  double angleCurr = getServoAngle();
  Serial.println(String(angleCurr) + " : " + String(ServoPwmTick));
  calibrateServos();
  if(mainControllerChannel.available() > 0) // If there is a message from the main controller
  {
    String message = mainControllerChannel.readStringUntil('\n');
    readSerialMessage(message);
    // mainControllerChannel.println("You sent: " + message);
  }
  else if(Serial.available() > 0) // If there is a message from the computer via USB
  {
    // Do something here
    readSerialMessage(Serial.readStringUntil('\n'));
    // Serial.println("Message received from Computer");
    // Serial.flush();
  }
  else
  {
    controlInletEnvironment(inletSetTemp);
    // Check if encoder is in use
    if(encoderSwFlag && (millis() - encoderSwTick >= 50)) // Include debounce for switch
    {
      menuLatch = !menuLatch;
      encoderSwFlag = false;
      Serial.println("Switch triggered...");
      systemState = systemStates::tempSelect;
      setTemperatureMenu();
    }
    updateDisplay(); // Update display
  }
}

/** Function description
 * \brief This function is used to ...
 */
void readSerialMessage(String serialMessage)
{
  if(getSubString(serialMessage, ':', 0).equalsIgnoreCase("SVP"))
  {
    regulationFlag = false;
    actuateServo(servoChannel, getSubString(serialMessage, ':', 1).toDouble());
  }
  else if(getSubString(serialMessage, ':', 0).equalsIgnoreCase("get") || getSubString(serialMessage, ':', 0).equalsIgnoreCase("set"))
  {
    readGetSetCommand(serialMessage);
  }
  else
  {
    regulationFlag = (getSubString(serialMessage, ':', 0).toInt());
    inletSetTemp = getSubString(serialMessage, ':', 1).toDouble();
    systemState = getSubString(serialMessage, ':', 2).toInt();
    mainControllerChannel.println("systemState is = " + String(systemState));
  }
  // Send confirmation response to main controller
  // mainControllerChannel.println("Confirming received inlet controller parameters:");
  // mainControllerChannel.println("Regulation: " + String(regulationFlag));
  // mainControllerChannel.println("Inlet set temp: " + String(inletSetTemp));
  // mainControllerChannel.print("Energy input: ");
  // if(systemState == (int)cooling) { mainControllerChannel.println("Cooling"); }
  // else if (systemState == (int)heating) { mainControllerChannel.println("Heating"); }
  // else if (systemState == (int)idle)  {mainControllerChannel.println("Idle");} 
  // else { mainControllerChannel.println("Eish, something is wrong."); }
  // mainControllerChannel.flush();
}

/*! Function description
  @brief  This function is used to respond to API commands from a computer. Thes commands are get and set commands. 
          The get commands are for sensor measurements.
          The set commands are used to configure parameters and control system actuators;
  \param  getSetCommand The command string sent from the computer and interface program
*/
void readGetSetCommand(String getSetCommand)
{
  String getResponse = "gr:";
  String setResponse = "sr:";
  if(getSubString(getSetCommand, ':', 0).equalsIgnoreCase("get"))
  {
    switch(getSubString(getSetCommand, ':', 0).toInt())
    {
      case (int)GetCommandsIndex::inletWaterTempIdx:  // "get:10:"
      {
        getResponse += String((int)inletWaterTempIdx) + ":";
        getResponse += String(inletTempMeas, 3);  // "gr:10:inletWatertemp"
      }
      case (int)GetCommandsIndex::freezerTemp:  // "get:11:"
      {
        getResponse += String((int)freezerTemp) + ":";
        getResponse += String(freezerChamberTemp, 3); // "gr:11:freezerTemp"
      }
      case (int)GetCommandsIndex::inletTankTemp:  // "get:12:"
      {
        getResponse += String((int)inletTankTemp) + ":";
        getResponse += String(geyserWaterTemp, 3);  // "gr:12:geyserWaterTemp"
      }
      case (int)GetCommandsIndex::inletValvePositionIdx:  // "get:13:"
      {
        getResponse += String((int)inletValvePositionIdx) + ":";
        getResponse += String(getServoAngle(), 3);  // "gr:13:servoAngle"
      }
    }
    mainControllerChannel.println(getResponse + ":");
  }
  else if(getSubString(getSetCommand, ':', 0).equalsIgnoreCase("set"))
  {
    switch(getSubString(getSetCommand, ':', 1).toInt())
    {
      case SetCommandsIndex::inletTempSet:  // "set:1:setTemp:"
      {
        inletSetTemp = getSubString(getSetCommand, ':', 2).toDouble();
        setResponse += String((int)inletTempSet) + ":" + String(inletSetTemp);  // "sr:1:inletSetTemp"
      }
      case SetCommandsIndex::inletValvePosition: // "set:3:valPos:"
      {
        regulationFlag = false;
        double valvePosition = getSubString(getSetCommand, ':', 2).toDouble();
        actuateServo(servoChannel, valvePosition);
        setResponse += String((int)inletValvePosition) + ":" + String(valvePosition); // "sr:3:valvePosition"
      }
      case SetCommandsIndex::inletTankTempSet:  // "set:6:setTankTemp:"
      {
        geyserSetTemp = getSubString(getSetCommand, ':', 2).toDouble();
        setResponse += String((int)inletTankTempSet) + ":" + String(geyserSetTemp); // "sr:6:inletTankSetTemp"
      }
      case SetCommandsIndex::freezerPower:  // "set:7:state(bool):"
      {
        bool state = getSubString(getSetCommand, ':', 2).toInt();
        actuatePower(state, highPowerLoad::freezer);
        if(state) {actuatePower(!state, highPowerLoad::geyser);}
        setResponse += String((int)freezerPower) + ":" + String(state); // "sr:7:freezerState"
      }
      case SetCommandsIndex::inletTankElementPower: // "set:8:state(bool):"
      {
        bool state = getSubString(getSetCommand, ':', 2).toInt();
        actuatePower(state, highPowerLoad::geyser);
        if(state) { actuatePower(!state, highPowerLoad::freezer); }
        setResponse += String((int)inletTankElementPower) + ":" + String(state);  // "sr:8:geyserState"
      }
    }
    mainControllerChannel.println(setResponse + ":");
  }
}

/*! Function description
  @brief  This function is used to call the necessary parameters 
          from the main controller in order to regulate the inlet temperature
*/
void requestInletControllerParams()
{
  mainControllerChannel.println("Request");
  mainControllerChannel.flush();
}

/** Function description
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

/*! Function description
  @brief  This function is used to toggle the state (open or close) of the geyser heating element.
  \param elementState determines whether the heating element switches on or off. If true, the element switches ON and vice versa.
*/
void actuatePower(bool loadState, bool loadType)
{
  switch(loadType)
  {
    case geyser:
    {
      if(loadState)
      {
        geyserLatchFlag = On;
        digitalWrite(geyserPowerResetPin, LOW);
        digitalWrite(geyserPowerSetPin, HIGH);
        delay(10);
        digitalWrite(geyserPowerSetPin, LOW);
      }
      else
      {
        geyserLatchFlag = Off;
        digitalWrite(geyserPowerResetPin, HIGH);
        digitalWrite(geyserPowerSetPin, LOW);
        delay(10);
        digitalWrite(geyserPowerResetPin, LOW);
      }
      break;
    }
    case freezer:
    {
      if(loadState)
      {
        freezerLatchFlag = On;
        digitalWrite(freezerResetPin, LOW);
        digitalWrite(freezerSetPin, HIGH);
        delay(10);
        digitalWrite(freezerSetPin, LOW);
      }
      else
      {
        freezerLatchFlag = Off;
        digitalWrite(freezerResetPin, HIGH);
        digitalWrite(freezerSetPin, LOW);
        delay(10);
        digitalWrite(freezerResetPin, LOW);
      }
      break;
    } 
  }
}

/*! Function description
  @brief  This function is responsible for capturing all temperature data of the inlet controller
*/
void getAllTemperatures()
{
  if(firstTempRequest)
  {
    systemTempBus.requestTemperatures();
    firstTempRequest = false;
  }
  else if (timerSampleCounter >= 1) // Temperature will be requested every 200ms
  {
    inletTempMeas = systemTempBus.getTempC(mainInletWaterSensorAddress);
    localOutletTemp = systemTempBus.getTempC(localOutletSensorAddress);
    freezerChamberTemp = systemTempBus.getTempC(freezerTempSensorAddress);
    systemTempBus.requestTemperatures();
  }
  geyserWaterTemp = getGeyserThermistorTemp();
}

/*! Function description
  @brief  This function is responsible for controlling the power delivered 
          to the element of the geyser. The power will switch between ON and OFF
          based on the temperature reading of the internal geyser water.
*/
void controlGeyserElement(double geyserWaterTemp, double geyserSetTemp)  
{
  if(geyserTempUpdateCounter >= (5*20) && systemState == systemStates::heating)  // Update geyser element state every 5 seconds 
  {
    geyserTempUpdateCounter = 0;
    float deadBandBottom = geyserSetTemp - geyserWaterDeadband;
    float deadBandTop = geyserSetTemp + geyserWaterDeadband;
    if(geyserWaterTemp < 0) { geyserWaterTemp = geyserThermistorDisconnected; }  // geyser thermostat not connected
    // Check if the water temperature is below the set temperature
    if(geyserWaterTemp < geyserSetTemp)
    {
      // Geyser element should switch on
      if(!geyserLatchFlag && (geyserWaterTemp != geyserThermistorDisconnected)) 
      { 
        actuatePower(On, highPowerLoad::geyser); 
        Serial.println("Switching on Geyser element");
        actuatePower(Off, highPowerLoad::freezer);
      }
    }
    // Check if the water temperature is above the set temperature
    else if(geyserWaterTemp >= geyserSetTemp && geyserLatchFlag)  
    { 
      actuatePower(Off, highPowerLoad::geyser); 
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
  else if(systemState == systemStates::cooling || systemState == systemStates::idle) 
  {
    actuatePower(Off, highPowerLoad::geyser); 
  }
}

/** Function description
 * \brief This function is used to ...
 */
void controlServoValve()
{
  if((inletTempMeas != disconnectDS18B20 || inletTempMeas != 0) && timerSampleCounter >= 1)  // Only regulate if values make sense
  {
    double currentServoAngle = getServoAngle();
    Serial.println(currentServoAngle);
    double inletTempError = inletSetTemp - inletTempCal;
    double PID_out = calcPIDoutput(inletTempError, angle_);
    if(abs(inletTempError) > tempAccuracyMargin)
    {
      actuateServo(geyserValve, PID_out); // 
    }
    else
    {
      // The measured inlet temperature is within the temperature margin and is ready
    }
  }
}

void controlChestFreezerPower()
{
  if(systemState == systemStates::cooling && freezerTempUpdateCounter >= (5*20))
  {
    freezerTempUpdateCounter = 0;
    if(freezerChamberTemp > 1.00) // Turn freezer on to decrease temperature in freezer chamber
    {
      actuatePower(On, highPowerLoad::freezer);
      actuatePower(Off, highPowerLoad::geyser);
    }
    else if(systemState == systemStates::heating || systemState == systemStates::idle) // Turn freezer off before it reaches dangerously low temperature
    {
      actuatePower(Off, highPowerLoad::freezer);
    }
  }
}

/** Function description
 * \brief This function is used to regulate the inlet temperature of the 150L geyser water if this is required.
 */
void controlInletEnvironment(double MainInletSetTemp)
{
  if(paramsRequestTick >= (150)) // Request parameter update from main controller every 30 sec
  {
    paramsRequestTick = 0;
    requestInletControllerParams();
  }
  if(regulationFlag)
  {
    // Serial.println("Regulation on:");
    timerSampleCounter = 0;
    // systemState = setSystemState();
    controlGeyserElement(geyserWaterTemp, geyserSetTemp); // Control geyser temp
    controlChestFreezerPower(); // Ensure that freezer temperature does not go lower than 1*C
    controlServoValve();  // Control flow of water through servo valve
  }
  getAllTemperatures(); // Capture state temperatures
}

/** Function description
 * \brief This function is used to ...
 */
void updateDisplay()
{
  if(updateDisplayTick >= 3)
  {
    updateDisplayTick = 0;
    u8g2.clearDisplay();
    u8g2.setFont(u8g2_font_6x10_tr);
    u8g2.firstPage();
    do 
    {
      u8g2.setCursor(0, 10);
      u8g2.print("Temperature: " + String(inletTempMeas));
      u8g2.setCursor(0, 20);
      u8g2.println("GeyserTemp: " + String(geyserWaterTemp));
      u8g2.setCursor(0, 30);
      u8g2.println("Freezer: " + String(freezerChamberTemp));
    } 
    while ( u8g2.nextPage() );
  }
}

/** Function description
 * \brief This function is used to ...
 */
double calcPIDoutput(double inletTempError, bool typeOut)
{
  servoPIDout.Kp = 2;
  servoPIDout.Ki = 0.1;
  servoPIDout.Kd = 0;
  double errorDiff = servoPIDout.e_prev - inletTempError;
  double PID_out = 0.00;
  if(angle_)
  {
    PID_out = servoPIDout.Kp*inletTempError + servoPIDout.Ki*servoPIDout.e_sum + servoPIDout.Kd*errorDiff;
    if(PID_out >= 90) PID_out = 90;
    else if(PID_out <= 0) PID_out = 0;
  }
  else
  {
    if(PID_out >= MAX_GV_servo) PID_out = MAX_GV_servo;
    else if(PID_out <= MIN_GV_servo) PID_out = MIN_GV_servo;
  }
  servoPIDout.e_sum += inletTempError;
  if(servoPIDout.e_sum >= 40) servoPIDout.e_sum = 40;
  else if(servoPIDout.e_sum <= -40) servoPIDout.e_sum = -40;
  servoPIDout.e_prev = inletTempError;
  return PID_out;
}

/** Function description
 * \brief This is a setup function and is used to configure all the onewire sensors in the system
 *        It instantiates an array of DallasTemperature objects and configures all elements to the
 *        same specifications. 
 *        It sets the resolution of the DS18B20 sensors, sets the "wait for convesion" flag to false 
 *        and checks that all sensors are connected to their busses - otherwise it will display an error message.
 */
void oneWireSetup() 
{
  // Initialise temperature bus for inlet water control
  systemTempBus.begin();
  systemTempBus.setResolution(tempResolution);
  systemTempBus.setWaitForConversion(false);
  // Initialise calibration temperature bus for inlet water control
  calTempBus.begin();
  calTempBus.setResolution(tempResolution);
  calTempBus.setWaitForConversion(false);
}

/** Function description
 * \brief This function is used to ...
 */
void calibrateServos()
{
  if(ServoPwmTick >= MIN_GV_servo && ServoPwmTick < MAX_GV_servo && dirFlag)
  {
    dirFlag = true;
    ServoPwmTick += 2;
  }
  else
  {
    dirFlag = false;
    if(ServoPwmTick <= MIN_GV_servo)
      dirFlag = true;
    else  
      ServoPwmTick -= 2;
  }
  delay(200);
  servoPWM.setPWM(0, 0, ServoPwmTick);
  // double angleCurr = getServoAngle();
  // Serial.println(String(angleCurr) + " : " + String(ServoPwmTick));
}

/** Function description
 * \brief This function is used to ...
 */
double getServoAngle()
{
  analogReadResolution(12);
  double adcInServo = analogRead(servoPosFeedbackPin);
  adcInServo *= 3.30/max12BitNum;
  return mapDouble(adcInServo, feedback0, feedback90, 0, 90);
}

/** Function description
 * \brief This function is used to ...
 */
void actuateServo(int valveNum, double servoAngle)
{
  if(servoAngle < 0) {servoAngle = 0.00;} // Ensure that servo lower limits are not reched
  if(servoAngle > 90) {servoAngle = 90.00;} // Ensure that servo upper limits are not reached.
  servoPWM.setPWM(valveNum, 0, getServoPulsePeriod(valveNum, servoAngle));
}

/** Description
 * \brief This function is used to convert the required angle into a PWM pulse width
 *        that can be used by the servo shield library
 * \param servo The enumerated servo name / channel on the PWM shield.
 * \param angle The required anglar position the servo needs to actuate to.
 * \return The unint16_t 12-bit pulse value required by the PWM servo motor object.
 */
uint16_t getServoPulsePeriod(int servo, int angle) 
{
  uint16_t servo_max = 0; 
  uint16_t servo_min = 0;
  uint16_t pulsePeriod;
  // Cap the angle to prevent servo damage
  if(angle > 90 && servo != PreInletValve)  angle = 90; else if(angle < 0)  angle = 0;
  // Start the switch statement for various servos
  servo_max = MAX_GV_servo;
  servo_min = MIN_GV_servo;
  pulsePeriod = (uint16_t)mapDouble((double)angle, (double)0, (double)90, (double)servo_min, (double)servo_max);
  return pulsePeriod;
}

void setTimerFrequency(int frequencyHz) {
  int compareValue = (CPU_HZ / (TIMER_PRESCALER_DIV * frequencyHz)) - 1;
  TcCount16* TC = (TcCount16*) TC3;
  // Make sure the count is in a proportional position to where it was
  // to prevent any jitter or disconnect when changing the compare value.
  TC->COUNT.reg = map(TC->COUNT.reg, 0, TC->CC[0].reg, 0, compareValue);
  TC->CC[0].reg = compareValue;
  // Serial.println(TC->COUNT.reg);
  // Serial.println(TC->CC[0].reg);
  while (TC->STATUS.bit.SYNCBUSY == 1);
}

void startTimer(int frequencyHz) {
  REG_GCLK_CLKCTRL = (uint16_t) (GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID_TCC2_TC3) ;
  while ( GCLK->STATUS.bit.SYNCBUSY == 1 ); // wait for sync
  TcCount16* TC = (TcCount16*) TC3;
  TC->CTRLA.reg &= ~TC_CTRLA_ENABLE;
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync
  // Use the 16-bit timer
  TC->CTRLA.reg |= TC_CTRLA_MODE_COUNT16;
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync
  // Use match mode so that the timer counter resets when the count matches the compare register
  TC->CTRLA.reg |= TC_CTRLA_WAVEGEN_MFRQ;
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync
  // Set prescaler to 1024
  TC->CTRLA.reg |= TC_CTRLA_PRESCALER_DIV1024;
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync
  setTimerFrequency(frequencyHz);
  // Enable the compare interrupt
  TC->INTENSET.reg = 0;
  TC->INTENSET.bit.MC0 = 1;
  NVIC_EnableIRQ(TC3_IRQn);
  TC->CTRLA.reg |= TC_CTRLA_ENABLE;
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync
}

void TC3_Handler() {
  TcCount16* TC = (TcCount16*) TC3;
  // If this interrupt is due to the compare register matching the timer count
  if (TC->INTFLAG.bit.MC0 == 1) 
  {
    TC->INTFLAG.bit.MC0 = 1;
    // Write callback here!!!
    timerSampleCounter++;
    geyserTempUpdateCounter++;
    freezerTempUpdateCounter++;
    paramsRequestTick++;
    updateDisplayTick++;
  }
}

/*! Function description
  @brief  
*/
void displaySetup()
{
  if(u8g2.begin())
  {
    u8g2.clearDisplay();
    u8g2.setFont(u8g2_font_5x8_tr);
    u8g2.firstPage();
    do 
    {
      u8g2.setCursor(45, 10);
      u8g2.print("Welcome!");
      u8g2.setCursor(0, 20);
      u8g2.println("Inlet water controller :)");
    } 
    while ( u8g2.nextPage() );
  }
}

uint8_t findOneWireDevices(int pin)
{
  OneWire ow(pin);
  uint8_t address[8];
  uint8_t count = 0;
  if (ow.search(address))
  {
    Serial.print("\nuint8_t pin");
    Serial.print(pin, DEC);
    Serial.println("[][8] = {");
    do {
      count++;
      Serial.println("  {");
      for (uint8_t i = 0; i < 8; i++)
      {
        Serial.print("0x");
        if (address[i] < 0x10) Serial.print("0");
        Serial.print(address[i], HEX);
        if (i < 7) Serial.print(", ");
      }
      Serial.println("  },");
    } while (ow.search(address));

    Serial.println("};");
    Serial.print("// nr devices found: ");
    Serial.println(count);
  }
  else{
    Serial.println("Nothing found");
  }
  return count;
}

/*! Function description
  @brief Captures the thermistor temperature reading of the geyserWise thermistor
  \return The bulk water temperature of the geyser water measured by the geyserWise thermistor
*/
double getGeyserThermistorTemp()
{
  analogWriteResolution(12);
  setThermistorProperties(&geyserWiseThermistorMain);
  geyserWiseThermistorMain.thermistorResistance = geyserWiseThermistorMain.voltDividerR*((max12BitNum)/(double)analogRead(geyserWaterTempPin) - 1);
  double thermR = geyserWiseThermistorMain.thermistorResistance;
  double temp = (1.0/(geyserWiseThermistorMain.a2 + geyserWiseThermistorMain.b2*log(thermR) + geyserWiseThermistorMain.c2*(log(thermR))*(log(thermR))*(log(thermR))) - kelvinToC_const);
  return temp;
}

/*! Function description
  @brief Captures the thermistor temperature reading of the geyserWise thermistor
  \param  thermistorStruct The thermistor paramater structure to that you want to set
*/
void setThermistorProperties(paramsThermistorNTC *thermistorStruct)
{
  // Set the geyserWise thermistor properties
  thermistorStruct->voltDividerR = 9610.00;
  thermistorStruct->thermistorResistance = 12000.00;
  thermistorStruct->a2 = 0.0008544974;
  thermistorStruct->b2 = 0.0002882289;
  thermistorStruct->c2 = -1.8781118715e-7;
}

double mapDouble(double x, double in_min, double in_max, double out_min, double out_max) 
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/*! Function description
  @brief 
*/
void connectToMQTTbroker()
{
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  // set the message receive callback
  mqttClient.onMessage(receivedMqttMessage);

  Serial.print("Subscribing to topic: ");
  Serial.println(topicReceive);
  Serial.println();
  // subscribe to a topic
  mqttClient.subscribe(topicReceive);
  Serial.print("Topic: ");
  Serial.println(topicReceive);
  Serial.println();
}

/*! Function description
  @brief 
*/
void connectToWifi()
{
  // attempt to connect to Wi-Fi network:
  while (status != WL_CONNECTED) 
  {
    Serial.print("Attempting to connect to network: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
    // wait 5 seconds for connection:
    delay(5000);
  }
  // you're connected now, so print out the data:
  Serial.println("Device connected to " + String(ssid));
  Serial.println("---------------------------------------");
}

/*! Function description
  @brief Callback function for when a Wifi message is received 
  \param  messageSize
*/
void receivedMqttMessage(int messageSize)
{
  // we received a message, print out the topic and contents
  Serial.println("Received a message with topic '");
  Serial.print(mqttClient.messageTopic());
  Serial.print("', length ");
  Serial.print(messageSize);
  Serial.println(" bytes:");

  // use the Stream interface to print the contents
  while (mqttClient.available()) {
    mqttReceivedMessage += (char)mqttClient.read();
  }
  Serial.println(mqttReceivedMessage);
  Serial.println();
  Serial.println();
}

uint8_t checkEncoderDirection()
{
  uint8_t direction = still;
  // Read the current state of inputCLK
  bool currentStateCLK = digitalRead(encoderClkPin);
  // If the previous and the current state of the inputCLK are different then a pulse has occured
  if (currentStateCLK != previousStateCLK)
  { 
    // If the inputDT state is different than the inputCLK state then 
    // the encoder is rotating counterclockwise
    if (digitalRead(encoderDtPin) != currentStateCLK) { 
      encoderCounter--;
      direction = CCW;
      
    } else {
      // Encoder is rotating clockwise
      encoderCounter++;
      direction = CW;
    }
  } 
  // Update previousStateCLK with the current state
  previousStateCLK = currentStateCLK;
  return direction;
}

void setTemperatureMenu()
{
  while(menuLatch)
  {
    if(encoderClkFlag && (millis() - encoderClkTick >= 1))
    {
      encoderClkFlag = false;
      if(digitalRead(encoderDtPin) != digitalRead(encoderClkPin)) 
      { 
        encoderCounter++;
      } 
      else // Encoder is rotating clockwise
      {
        encoderCounter--;
      }
    }
    u8g2.clearDisplay();
    u8g2.setFont(u8g2_font_5x8_tr);
    u8g2.firstPage();
    do 
    {
      u8g2.setCursor(0, 10);
      u8g2.print("Adjust inlet set temp:");
      u8g2.setCursor(0, 30);
      u8g2.println("Inlet Temp: " + String(encoderCounter) + " degC");
    } 
    while ( u8g2.nextPage() );
    
    if(encoderSwFlag) 
    {
      menuLatch = !menuLatch; 
      encoderSwFlag = false;
    }
  }
}

/*! Function description
  @brief  This function is used to configure all pins used in the overall system.
*/
void configurePins()
{
  // Configure all OUTPUT pins (Default is INPUT)
  pinMode(geyserPowerSetPin, OUTPUT);
  pinMode(geyserPowerResetPin, OUTPUT);
  pinMode(freezerSetPin, OUTPUT);
  pinMode(freezerResetPin, OUTPUT);
  // pinMode(geyserValveFeedbackPin, INPUT);
  pinMode(mainWaterValveFeedbackPin, INPUT);
  // pinMode(preInletValveFeedbackPin, INPUT);
  pinMode(servoPosFeedbackPin, INPUT);
  analogReadResolution(12); // Set analgue pin resolution to 12 bits
  configureInterrupts();
}

/*! Function description
  @brief  This function is used to configure the appropriate interrupt pins of the overall system.
*/
void configureInterrupts() 
{
  pinMode(encoderClkPin, INPUT);
  pinMode(encoderDtPin, INPUT);
  pinMode(encoderSwPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoderSwPin), encoderSwHandler, FALLING);
  attachInterrupt(digitalPinToInterrupt(encoderDtPin), encoderDtHandler, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderClkPin), encoderClkHandler, CHANGE);
}

/*! Function description
  @brief  This function is used to configure all pins used in the overall system.
*/
void servoMotorSetup()
{
  servoPWM.begin();
  servoPWM.setPWMFreq(servoFREQUENCY);
}

void encoderClkHandler()
{
  encoderClkFlag = true;
  encoderClkTick = millis();
}

void encoderDtHandler()
{
  encoderDtFlag = true;
}

void encoderSwHandler()
{
  encoderSwFlag = true;
  encoderSwTick = millis();
}
