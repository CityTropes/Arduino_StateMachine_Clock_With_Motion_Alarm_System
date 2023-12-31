
# Arduino StateMachine - Clock & Motion Alarm System

A basic clock that self-corrects when timeslipping is detected.
Also includes an alarm system that triggers a siren (after countdown) when motion is detected.
User enables/disables alarm via code.

- no libraries used for clock functions.
- no libraries used for custom made characters.
- extensive low memory log/debug methods included.


Sketch uses 17052 bytes (52%) of program storage space. Maximum is 32256 bytes.   
Global variables use 851 bytes (41%) of dynamic memory, leaving 1197 bytes for local variables. Maximum is 2048 bytes.


 
## Prototype circuit setup with PIR motion sensor, LCD screen, keypad & buzzer as main components:

![circuit_prototype](https://github.com/CityTropes/Arduino_StateMachine_Clock_With_Motion_Alarm_System/assets/84394352/6a16e0f8-705d-426d-9070-ce1cce13757e)


## Application states:

The application has 5 states:

0. SETUP: user sets the code for the alarm, user sets the time:
     
![setup_code](https://github.com/CityTropes/Arduino_StateMachine_Clock_With_Motion_Alarm_System/assets/84394352/ee954be5-41bf-41c2-a564-87dc30108f15)
![setup_time](https://github.com/CityTropes/Arduino_StateMachine_Clock_With_Motion_Alarm_System/assets/84394352/ba7f69a0-1a98-446c-8555-889f8c1bb998)


1. RUNNING: the clock is running & app is listening to keypad input (idle state).

 ![running_idle](https://github.com/CityTropes/Arduino_StateMachine_Clock_With_Motion_Alarm_System/assets/84394352/7364fa8b-6f09-4f49-85cf-1fb87e2e03af)


2. SCANNING : when the user inputs code + C, the motion alarm is set. The pir sensor will check for motion every 50ms.

![scanning](https://github.com/CityTropes/Arduino_StateMachine_Clock_With_Motion_Alarm_System/assets/84394352/e97ec30c-01c6-4498-bd50-ecb7c9d4bb08)


3. TRIGGERED: when motion is detected, the alarm switches state to TRIGGERED. A 10 sec countdown timer and prompt for code will be shown on display.

![triggered](https://github.com/CityTropes/Arduino_StateMachine_Clock_With_Motion_Alarm_System/assets/84394352/88a1d1ed-d424-4c74-9c97-f90577a4c9da)


4. SIREN: when the trigger timer reaches 0, or user inputs incorrect code, the state will change to SIREN. Code is needed to de-activate siren and alarm.

![running_disabled](https://github.com/CityTropes/Arduino_StateMachine_Clock_With_Motion_Alarm_System/assets/84394352/135762f7-4610-4dd3-bd75-e994f9e26a42)

When the alarm is disabled by the user, a confimation message appears for 4 seconds, after which the RUNNING-screen is shown again.
If there is time slipping detected, the clock will autocorrect.



## Motion Alarm Happy flow:

1. Display shows counting seconds, PIR is looking for motion.
   (Status light is green).
   
2. Motion sensor detects movement -> alarmTimer is triggered.
   (Status light toggles red/green every 500ms),

3. Display shows countdown alarmTimer (10 sec).
   (Status light keeps toggling during countdown).

4. User inputs **correct code** in time -> Alarm disabled.
   (Status light is green).

5. Display shows 'alarm disabled' for 4 seconds, then shows clock again.
   (Status light is green).


## Motion Alarm Unhappy flow:

1. Display shows counting seconds, PIR is looking for motion.
   (Status light is green).
   
2. Motion sensor detects movement -> alarmTimer is triggered.
   (Status light toggles red/green every 500ms),

3. Display shows countdown alarmTimer (10 sec).
   (Status light keeps toggling during countdown).

4. User inputs **wrong code** or **alarmTimer reaches 0** -> Siren starts.
   (Status light is red).

5. While siren sounds, user can still input correct code to disable alarm.
   (Status light is green).

6. Display shows 'alarm disabled' for 4 seconds, then shows clock again.
   (Status light is green).

   ![motion_detected_countdown](https://github.com/CityTropes/Arduino_Motion_Alarm_System/assets/84394352/172f0ab8-bd34-42bc-a554-9691d3ab465c)


## Testing & debugging:

When the alarm is connected to pc via usb it will automatically print output from included test- and debug-methods to the serial monitor.

![output](https://github.com/CityTropes/Arduino_StateMachine_Clock_With_Motion_Alarm_System/assets/84394352/a5dd2cc8-050e-4d47-885c-a92eaaff0c8d)


![output2 (2)](https://github.com/CityTropes/Arduino_StateMachine_Clock_With_Motion_Alarm_System/assets/84394352/5c971d27-5ce5-4e14-9745-cf442032387c)
