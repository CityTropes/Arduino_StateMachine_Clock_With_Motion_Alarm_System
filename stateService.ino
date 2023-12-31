// ***************************************************************************************** //
// ----------- STATE SERVICE --------------------------------------------------------------- //
// ----------- functions to manage and switch the state of the application. ---------------- //
// ***************************************************************************************** //

long userCode = 0;

void setStateTo(alarmStateEnum alarmState) {

  alarmStateEnum oldAlarmState = *alarmState_p;
  *alarmState_p = alarmState;

  printAlarmStateChange(oldAlarmState, alarmState);

  //  if (oldAlarmState != SETUP && *alarmState_p == RUNNING) {
  // alarm disabled
  //  }

  switch (*alarmState_p) {
    case RUNNING:
      updateLcdAlarmAppIsRunning();
      scanningStatusStartTime = 0;
      isUserinputFlushRequested = true;
      break;
    case SCANNING:
      updateLcdAlarmAppIsScanning();
      isUserinputFlushRequested = true;
      *scanningStatusStartTime_p = millis();
      break;
    case TRIGGERED:
      updateLcdAlarmIsTriggered();
      alarmTimerHalfSec = 20;
      *scanningStatusStartTime_p = 0;
      // lcd update screen custom char
      break;
    case SIREN:
      // update lcd with custom char
      break;
    default:
      break;
  }

}

void disableAlarm() {
  wipeLcdMessageDisabledTime = millis() + 4000;
  updateLcdDisableAlarm();
  setStateTo(RUNNING);
  updateOutputControllerAlarmDisabled();
  //  updateLcdClockAll();
}

void enableAlarm() {
  setStateTo(SCANNING);
}

void initCode() {
  isUserinputFlushRequested = true;
  updateLcdSetCode();
  while (!isCodeSet) {
    manageKeypad();
  }
  lcd.clear();
}

void setCode(long code) {
  userCode = code;
  isCodeSet = true; // print
}

boolean checkCode(long code) {
  return userCode == code;
}
