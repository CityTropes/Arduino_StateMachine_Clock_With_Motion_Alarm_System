// ***************************************************************************************** //
// ----------- TO SERIAL OUTPUT ------------------------------------------------------------ //
// ----------- functions to test & debug code, logging (if serial monitor is connected). --- //
// ***************************************************************************************** //

// avoiding string concat to save memory


void printKeyPress(char key) {
  if (Serial) {
    Serial.print(F("key Pressed : "));
    Serial.println(key);
  }
}

void printInputIsFlushed() {
  if (Serial) {
    Serial.println(F("[i] --> userinput is flushed!"));
  }
}

void printClockCorrectionSeconds(int &seconds) {
  if (Serial) {
    Serial.print(F("[!] --> clock correction seconds! Corrected seconds: "));
    Serial.println(seconds);
  }
}

void printClockCalibrationInfo(int &hour, int &minute, int &sec, unsigned long reCalibratedSeconds) {
  Serial.print(F("[i] --> seconds since clockStartTime (userTime + userSurplus): "));
  Serial.println(reCalibratedSeconds);
  Serial.print("    --> int hour: ");
  Serial.print(hour);
  Serial.print(", int minute: ");
  Serial.print(minute);
  Serial.print(", int sec");
  Serial.println(sec);
}

void printSetUserTime(int &hour, int &minute, int &sec, unsigned long &userSurplusTime) {
  if (Serial) {
    Serial.print(F("[i] --> user set the clock time to: "));
    Serial.print(hour);
    Serial.print(minute);
    Serial.println(sec);
    Serial.print(F("    --- stored userSurplusTime converted to ms: "));
    Serial.print(userSurplusTime);
  }
}

void printSecStats(int &elapsedSecondsCounter) {
  if (Serial) {
    Serial.print(F("[i] --> 1000ms interval (clock update sec): "));
    Serial.println(elapsedSecondsCounter);
    Serial.print(F("[i] --- number of main loops in total: "));
    Serial.println(mainLoopCounter);
  }
}

void printMinStats(int &hour, int &minute, int &second) {
  if (Serial) {
    Serial.print(F("[i] --> 1 min interval (clock update hh:mm:ss): "));
    Serial.print(hour);
    Serial.print(F("h "));
    Serial.print(minute);
    Serial.print(F("m "));
    Serial.print(second);
    Serial.println(F("s "));
  }
}

void printAlarmTriggerInfo() {
  Serial.print(F("[i] --> alarmtriggerTimer (500ms interval): "));
  if (*alarmState_p == TRIGGERED) {
    Serial.println (F("    --- triggered = true. Waiting for code."));
  } else {
    Serial.println (F("    --- triggered = false."));
  }
}

void printAlarmSoundsirenStats() {
  if (Serial) {
    Serial.print(F("[i] --> alarm Sound siren is ON."));
  }
}

void printPirInfo(unsigned long &alarmTriggerTime) {
  if (Serial) {
    Serial.print(F("[i] --> Motion detected at: "));
    Serial.print(alarmTriggerTime);
    Serial.println(F(" ms (since startup)."));    // todo: convert to real user time
  }
}

void printPirInfo() {
  if (Serial) {
    Serial.println(F("[i] --> scanning: no motion"));
  }
}

void printAlarmStateChange(alarmStateEnum &oldAlarmState, alarmStateEnum &alarmState) {
  if (Serial) {
    Serial.print(F("[i] --> alarmState has changed from: "));
    Serial.print(oldAlarmState);
    printAlarmStateAsString(oldAlarmState);
    Serial.print( F(" to: "));
    Serial.print(alarmState);
    printAlarmStateAsString(alarmState);
    Serial.println(F("."));

  }
}

void printAlarmStateAsString(int state) {
  String stateString = "";
  switch (state) {
    case 0: stateString = " (SETUP) ";
      break;
    case 1: stateString = " (RUNNING) ";
      break;
    case 2: stateString = " (SCANNING) ";
      break;
    case 3: stateString = " (TRIGGERED) ";
      break;
    case 4: stateString = " (SIREN) ";
      break;
  }
  Serial.print(stateString);
}
