// ***************************************************************************************** //
// ----------- CLOCK SERVICE --------------------------------------------------------------- //
// ----------- functions for user clock setting, alarm timers & time keeping. -------------- //
// ***************************************************************************************** //


unsigned long *clockStartTime_p = &clockStartTime;
unsigned long *userTimeCounter_p = &userTimeCounter;
unsigned long *userSurplusTime_p = &userSurplusTime;

unsigned long wipeLcdMessageDisabledTime, scanningStatusStartTime = 0;
unsigned long *scanningStatusStartTime_p = &scanningStatusStartTime;
int elapsedSecondsCounter = 0;
int *elapsedSecondsCounter_p = &elapsedSecondsCounter;
byte alarmTimerHalfSec = 20;
boolean isUserinputFlushRequested = false;

// todo: refactor

void setAlarmClock() {
  updateLcdSetClock();
  *userSurplusTime_p = 0;
  isUserinputFlushRequested = true;
  while (*userSurplusTime_p < 1) {
    manageKeypad();
  }
  *clockStartTime_p = millis();
  *userTimeCounter_p = millis();
  updateLcdClockAll(); // todo: not needed here?

  int hour = (*userSurplusTime_p / 1000) / 3600L;
  int minute = ((*userSurplusTime_p / 1000) - 3600UL * hour) / 60UL;

  char buf[10];
  sprintf(buf, "%02d:%02d:", hour, minute);
  lcd.setCursor(0, 1);
  lcd.print(F("time: "));
  lcd.setCursor(8, 1);
  lcd.print(buf);
}

void setUserTime(char userinput[]) {
  int hourInt = ((String)userinput[0] + (String)userinput[1]).toInt();
  int minInt = ((String)userinput[2] + (String)userinput[3]).toInt();
  int secInt = ((String)userinput[4] + (String)userinput[5]).toInt();   // set seconds not included atm.

  hourInt > 23 ? hourInt = 0 : hourInt = hourInt;
  minInt > 59 ? minInt = 0 : minInt = minInt;
  secInt > 59 ? secInt = 0 : secInt = secInt;

  *userSurplusTime_p = (unsigned long)((hourInt * 3600000) + (minInt * 60000) + 1); // +1 ms to break while-loop if user inputs 00:00

  printSetUserTime(hourInt, minInt, secInt, userSurplusTime);
  lcd.clear();
}


void updateAppClockTime() {
  unsigned long timeNow = millis();

  if (timeNow > wipeLcdMessageDisabledTime &&  wipeLcdMessageDisabledTime  > 0) {
    Serial.println("inside wipemessage");
    wipeLcdMessageDisabledTime = 0;
    updateLcdAlarmAppIsRunning();
    updateLcdClockAll();
  }

  if (millis() - *userTimeCounter_p >= 1000) {
    *userTimeCounter_p += (millis() - *userTimeCounter_p);
    elapsedSecondsCounter++;

    if (*elapsedSecondsCounter_p < 60) {
      updateLcdClockSeconds(elapsedSecondsCounter);
    } else {
      updateLcdClockAll();
    }
    if (*alarmState_p == SCANNING) {
      manageBlinkingEyesLcd();
    }
  }
}


void updateLcdClockAll() {
  long reCalibratedSeconds = (millis() - *clockStartTime_p) / 1000;

  reCalibratedSeconds = reCalibratedSeconds + (*userSurplusTime_p / 1000);

  int hour = reCalibratedSeconds / 3600L;
  int minute = (reCalibratedSeconds - 3600UL * hour) / 60UL;
  int second = reCalibratedSeconds - (3600UL * hour) - (60UL * minute);

  hour = hour % 24 == 0 ? 0 : hour;

  printClockCalibrationInfo(hour, minute, second, reCalibratedSeconds);

  if ((*alarmState_p == RUNNING || *alarmState_p == SCANNING) && (millis() > wipeLcdMessageDisabledTime)) {
    char buf[10];
    sprintf(buf, "%02d:%02d:%02d", hour, minute, second);
    lcd.setCursor(0, 1);
    lcd.print(F("time:   "));
    lcd.setCursor(8, 1);
    lcd.print(buf);
  }

  *elapsedSecondsCounter_p = second;
  if (second != 0) {
    printClockCorrectionSeconds(second);
  } else {
    printMinStats(hour, minute, second);          // check to just print buf
  }
}

void updateLcdClockSeconds(int &elapsedSecondsCounter) {
  if (millis() > wipeLcdMessageDisabledTime && (*alarmState_p == RUNNING || *alarmState_p == SCANNING)) {
    lcd.setCursor(14, 1);
    if (elapsedSecondsCounter < 10) {
      lcd.print(F("0"));                         // use sprintf instead
    }
    lcd.print(elapsedSecondsCounter);
  }
  printSecStats(elapsedSecondsCounter);
}


void manageAlarmTriggerTimer() {                // managing alarm sounds, lights & countdown timer (in sec)
  if (millis() - alarmTriggerTime >= 500) {
    alarmTriggerTime += (millis() - alarmTriggerTime);

    if (*alarmState_p == SIREN) {
      toggleAlarmSoundsiren();
    } else if (*alarmState_p == TRIGGERED) {
      if (alarmTimerHalfSec > 0) {
        toggleLight();
        tone(BUZZER_PIN, 73, 75);   //E7 - short beep

        alarmTimerHalfSec = alarmTimerHalfSec - 1;

        if (alarmTimerHalfSec % 2 == 0) {
          updateLcdManageAlarmTrigger(alarmTimerHalfSec);
        }
      } else {
        alarmTimerHalfSec = 20;
        setStateTo(SIREN);
      }
    }
    printAlarmTriggerInfo();
  }
}

void manageBlinkingEyesLcd() {
  if (millis() >= *scanningStatusStartTime_p) {
    updateLcdCloseEyes();
    *scanningStatusStartTime_p += 12000;
  } else {
    updateLcdOpenEyes();
  }
}
