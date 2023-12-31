// ***************************************************************************************** //
// ----------- INPUT CONTROLLER ------------------------------------------------------------ //
// ----------- functions to setup & manage membrane keypad & motion sensor input. ---------- //
// ***************************************************************************************** //

// todo: refactor & expand clock options

byte rowPins[4] = {A5, A4, A3, A2};
byte colPins[4] = {A1, 8, 12, 13};
char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);


void scanForMotion() {
  if (digitalRead(PIR_MOTION_PIN) == HIGH) {
    alarmTriggerTime = millis();
    setStateTo(TRIGGERED);
    printPirInfo(alarmTriggerTime);
  } else {
    printPirInfo();
  }
}

void manageKeypad() {
  static char userinput[5];
  static int count = 0;
  char key = keypad.getKey();

  if (key != NO_KEY)
  {
    printKeyPress(key);

    if (alarmState != SIREN) {
      tone(BUZZER_PIN, 130, 150);   //E6
    }
    if ((*alarmState_p == TRIGGERED || *alarmState_p == SIREN) && count == 0) {
      lcd.setCursor(0, 0);
      lcd.print("                ");
    }
  }

  switch (key)
  {
    case NO_KEY:
      if (isUserinputFlushRequested) {
        memset(userinput, 0, sizeof(userinput));
        count = 0;
        isUserinputFlushRequested = false;
        printInputIsFlushed();
      }
      break;

    case '#':
      // todo: scroll help
      break;

    case '*':
      // todo clear sceen and go to main?
      break;

    case 'A':   // activate motion alarm

      if (*alarmState_p == RUNNING) {
        if (checkCode(scrambleUserInput(userinput))) {
          enableAlarm();
        }
        memset(userinput, 0, sizeof(userinput));
        count = 0;
      }
      break;

    case 'B':
      // todo - sound
      break;

    case 'C':     // code & clock functions  // manage clock // set clock // todo: set wake up alarm // set timer

      if (*alarmState_p == SETUP) { // todo: refactor
        if (isCodeSet) {
          setUserTime(userinput);
        } else if (count == 4) {
          setCode(scrambleUserInput(userinput));
        } else {
          lcd.setCursor(0,1);
          lcd.print("               ");
        }

      }
      memset(userinput, 0, sizeof(userinput));
      count = 0;
      break;

    case 'D':      // disable alarm and/or siren with correct code, enables siren with wrong code

      if (*alarmState_p == TRIGGERED || *alarmState_p == SIREN || *alarmState_p == SCANNING) {
        lcd.clear();
        if (checkCode(scrambleUserInput(userinput))) {
          disableAlarm();
        } else {
          updateLcdIncorrectPassword();
          setStateTo(SIREN);
        }
      }
      memset(userinput, 0, sizeof(userinput));
      count = 0;
      break;

    default:
      // todo: refactor, change logic to switch?
    
      if (isCodeSet && *alarmState_p == SETUP && count < 2) {          // set hour in correct place (hh)
        lcd.setCursor((4 + count), 1);
        lcd.print(key);
      } else if (isCodeSet && *alarmState_p == SETUP && count < 4) {
        lcd.setCursor((5 + count), 1);                                // set min in correct place (mm)
        lcd.print(key);
      }
      else if (*alarmState_p != RUNNING && count < 5) {
        lcd.setCursor(6 + count, 1);                                  // set pw in correct place
        lcd.print("*");
      }
      userinput[count++] = key;
      break;
  }
}

int userInputToNumber(char userinput[]) {
  return ((String)userinput[0] + (String)userinput[1] + (String)userinput[2] + (String)userinput[3]).toInt();
}

long scrambleUserInput(char userinput[]) {

  String string = (String)userinput[0] + (String)userinput[1] + (String)userinput[2] + (String)userinput[3];
  char buffer[5];
  string.toCharArray(buffer, 4);

  int myNumber = userInputToNumber(buffer);
  int c = ((String)userinput[0]).toInt();
  int o = ((String)userinput[1]).toInt();
  int d = ((String)userinput[2]).toInt();
  int e = ((String)userinput[3]).toInt();
  int myInt[] = {c, o, d, e};

  for (int i = 0; i < 3 ; i++) {
    myInt[i] = (myInt[i] == 9) ? 0 : (myInt[i] + 1);
  }

  Serial.println("app start time: "); // todo: print methods
  Serial.println(appStartTime);
  Serial.println("my number: ");
  long myLong = (1111 + myInt[1] + (myNumber * appStartTime) + (myInt[2] * 2));
  for (int i = 0; i < 3 ; i++) {
    myLong += (myInt[i] * 3);
  }
  long testlong = myLong - c - o - d - e;
  Serial.println("scrambled input: ");
  Serial.println(testlong);
  return myLong - c - o - d - e;
}
