// ***************************************************************************************** //
// ----------- MOTION ALARM AND CLOCK ------------------------------------------------------ //
// ----------- defining I/O pins, including libraries, declaring key variables. ------------ //
// ***************************************************************************************** //

#include <Key.h>
#include <Keypad.h>
#include <MFRC522.h>
#include <SPI.h>
#include <LiquidCrystal.h>
#include <stdio.h>

#define RED_LED_PIN 10
#define GREEN_LED_PIN 11
#define PIR_MOTION_PIN A0
#define BUZZER_PIN 9

const byte rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const unsigned long eventInterval = 50;           // optional
unsigned long previousTime, mainLoopCounter = 0;  // optional

enum alarmStateEnum {SETUP, RUNNING, SCANNING, TRIGGERED, SIREN};
alarmStateEnum alarmState = SETUP;
alarmStateEnum *alarmState_p = &alarmState;


// ***************************************************************************************** //
// ----------- MOTION ALARM AND CLOCK - START ---------------------------------------------- //
// ----------- setup() and loop(): startup and managing the clock & alarm state. ----------- //
// ***************************************************************************************** //

void setup() {
  arduinoSetup();
  alarmAppSetup();
}

void loop() {

  unsigned long currentTime = millis();
  if (currentTime - previousTime >= eventInterval) {

    updateAppClockTime();
    manageKeypad();

    switch (*alarmState_p) {
      case SETUP:
        initCode();
        setAlarmClock();
        setStateTo(RUNNING);
        break;
      case RUNNING:
        // clock is updating, also listening to keypad
        break;
      case SCANNING:
        scanForMotion();
        break;
      case TRIGGERED:
        manageAlarmTriggerTimer();
        break;
      case SIREN:
        manageAlarmTriggerTimer();
        break;
    }

    previousTime = currentTime;
    mainLoopCounter > 99999 ? mainLoopCounter = 0 : mainLoopCounter++;
  }
}
