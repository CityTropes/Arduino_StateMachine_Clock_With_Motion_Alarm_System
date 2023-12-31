// ***************************************************************************************** //
// ----------- OUTPUT CONTROLLER ----------------------------------------------------------- //
// ----------- functions to control screen, light & buzzer. -------------------------------- //
// ***************************************************************************************** //


void toggleAlarmSoundsiren() {
  static boolean alarmSoundToggle = true;

  if (alarmSoundToggle) {
    printAlarmSoundsirenStats();
    tone(BUZZER_PIN, 842, 250);
  } else {
    tone(BUZZER_PIN, 1160, 250);
  }
  alarmSoundToggle = !alarmSoundToggle;
}

void updateOutputControllerAlarmDisabled() {
  playTuneOne();
  analogWrite(RED_LED_PIN, 0);
  analogWrite(GREEN_LED_PIN, 255);
}


// todo: use sprintf-logic for lcd instead

void updateLcdAlarmAppIsRunning() {
  lcd.setCursor(0, 0);
  lcd.print("     ");
  lcd.setCursor(5, 0);
  lcd.print(F("-idle-"));
  lcd.setCursor(11, 0);
  lcd.print("    ");
  lcd.setCursor(15, 0);
  lcd.write(byte(0));
}

void updateLcdAlarmAppIsScanning() {
  lcd.setCursor(0, 0);
  lcd.print(F("scanning area  "));
  lcd.setCursor(14, 0);
  lcd.write(byte(2));
  lcd.setCursor(15, 0);
  lcd.write(byte(2));
}

void updateLcdAlarmIsTriggered() {
  lcd.clear();
  lcd.print(F("motion detected!"));
  lcd.setCursor(0, 1);
  lcd.print(F("enter code in "));
}

void updateLcdManageAlarmTrigger(byte &alarmTimerHalfSec) {
  lcd.setCursor(14, 1);
  lcd.print(alarmTimerHalfSec / 2);
  lcd.print("s");
}

void updateLcdCloseEyes() {
  lcd.setCursor(14, 0);
  lcd.write(byte(3));
  lcd.setCursor(15, 0);
  lcd.write(byte(3));
}

void updateLcdOpenEyes() {
  lcd.setCursor(14, 0);
  lcd.write(byte(2));
  lcd.setCursor(15, 0);
  lcd.write(byte(2));
}

void updateLcdDisableAlarm() {
  lcd.setCursor(0, 0);
  lcd.print("Passcode correct");
  lcd.setCursor(0, 1);
  lcd.print("Alarm disabled ");
}

void updateLcdIncorrectPassword() {
  lcd.print("Password incorrect");
  lcd.setCursor(0, 1);
  lcd.print("Alarm activated!");
}

void updateLcdSetClock() {
  lcd.clear();
  lcd.print(F("please set time:"));
  lcd.setCursor(0, 1);
  lcd.print(F("set hh:mm + C"));
}

void updateLcdSetCode() {
  lcd.clear();
  lcd.print(F("set 4-digit code"));
  lcd.setCursor(14, 1);
  lcd.print(F("+C"));
}

void toggleLight() {
  static boolean lightToggle = false;

  if (lightToggle) {
    analogWrite(GREEN_LED_PIN, 0);
    analogWrite(RED_LED_PIN, 255);
  } else {
    analogWrite(RED_LED_PIN, 0);
    analogWrite(GREEN_LED_PIN, 255);
  }
  lightToggle = !lightToggle;
}



// ------ methods below have delay() and will block the main loop & user clock (time slipping!) ------- //

void playTuneOne() {
  //play the 1Up noise
  tone(BUZZER_PIN, 1318, 150);   //E6
  delay(175);
  tone(BUZZER_PIN, 1567, 150);   //G6
  delay(175);
  tone(BUZZER_PIN, 2637, 150);   //E7
  delay(175);
  tone(BUZZER_PIN, 2093, 150);   //C7
  delay(175);
  tone(BUZZER_PIN, 2349, 150);   //D7
  delay(175);
  tone(BUZZER_PIN, 3135, 500);   //G7
  delay(500);
}

void playTuneTwoo() {
  //play the Losing noise
  tone(BUZZER_PIN, 130, 250);   //E6
  delay(275);
  tone(BUZZER_PIN, 73, 250);   //G6
  delay(275);
  tone(BUZZER_PIN, 65, 150);   //E7
  delay(175);
  tone(BUZZER_PIN, 98, 500);   //C7
  delay(500);
}
