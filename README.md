
# Arduino StateMachine - Clock & Motion Alarm System

A basic clock with alarm system that triggers a siren -after countdown- when motion is detected.
User disables siren & alarm via code.


## Prototype circuit setup with PIR motion sensor, LCD screen, keypad & buzzer as main components:

![circuit_prototype](https://github.com/CityTropes/Arduino_StateMachine_Clock_With_Motion_Alarm_System/assets/84394352/6a16e0f8-705d-426d-9070-ce1cce13757e)


## Happy flow:

1. Display shows counting seconds, PIR is looking for motion.
   (Status light is green).
   
2. Motion sensor detects movement -> alarmTimer is triggered.
   (Status light toggles red/green every 500ms),

3. Display shows countdown alarmTimer (10 sec).
   (Status light keeps toggling during countdown).

4. User inputs **correct code** in time -> Alarm disabled.
   (Status light is green).


## Unhappy flow:

1. Display shows counting seconds, PIR is looking for motion.
   (Status light is green).
   
2. Motion sensor detects movement -> alarmTimer is triggered.
   (Status light toggles red/green every 500ms),

3. Display shows countdown alarmTimer (10 sec).
   (Status light keeps toggling during countdown).

4. User inputs **wrong code** or **alarmTimer reaches 0** -> Siren starts.
   (Status light is red).

5. While siren sounds, user can still input correct code to disable alarm.
   (Status light is green)

   ![motion_detected_countdown](https://github.com/CityTropes/Arduino_Motion_Alarm_System/assets/84394352/172f0ab8-bd34-42bc-a554-9691d3ab465c)


## Testing & debugging:

When the alarm is connected to pc via usb it will automatically print output from included test- and debug-methods to the serial monitor.

