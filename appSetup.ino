// ***************************************************************************************** //
// ----------- APPLICATION SETUP ----------------------------------------------------------- //
// ----------- setup funtions for arduino & alarm app, for main setup(). ------------------- //
// ***************************************************************************************** //


unsigned long appStartTime, clockStartTime, userSurplusTime, userTimeCounter, alarmTriggerTime = 0;
boolean isCodeSet = false;

void arduinoSetup() {
  pinMode(PIR_MOTION_PIN, INPUT_PULLUP);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  lcd.begin(16, 2);
}

void alarmAppSetup() {
  buildCustomCharacters();
  setAlarmLcdCharacters();

  // testLight();
  testBuzzer();
  testLcd();

  analogWrite(RED_LED_PIN, 0);
  userTimeCounter, appStartTime = millis();
}
