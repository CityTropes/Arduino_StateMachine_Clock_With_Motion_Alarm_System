// ***************************************************************************************** //
// ----------- TEST SEQUENCES -------------------------------------------------------------- //
// ----------- functions to test & debug the hardware. ------------------------------------- //
// ***************************************************************************************** //


void testLcd() {
  lcd.setCursor(0, 0);
  lcd.print(F("Startup test(S)"));
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print(F("-testing screen-"));
  delay(1000);
  testAlarmCustomCharacters();
  testExtraCustomCharacters();
}

void testAlarmCustomCharacters() {

  setAlarmLcdCharacters();

  tone(BUZZER_PIN, 73, 75);   //E7 - short beep
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 0);
    lcd.write(byte(1));
  }
  delay(1000);
  tone(BUZZER_PIN, 73, 75);   //E7 - short beep
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 1);
    lcd.write(byte(0));
  }
  delay(1000);
  tone(BUZZER_PIN, 73, 75);   //E7 - short beep
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 1);
    lcd.write(byte(6));
  }
  delay(1000);
  lcd.clear();
}

void testExtraCustomCharacters() {
  setCustomLcdCharacters();

  lcd.write("Test LCD");
  delay(750);

  tone(BUZZER_PIN, 73, 75);   //E7 - short beep
  // house  (right)
  lcd.setCursor(14, 0);
  lcd.write(byte(4));
  lcd.setCursor(15, 0);
  lcd.write(byte(5));
  lcd.setCursor(14, 1);
  lcd.write(byte(2));
  lcd.setCursor(15, 1);
  lcd.write(byte(3));
  // car
  lcd.setCursor(12, 1);
  lcd.write(byte(6));
  lcd.setCursor(13, 1);
  lcd.write(byte(7));
  delay(1500);

  tone(BUZZER_PIN, 73, 75);   //E7 - short beep
  // text
  lcd.setCursor(0, 0);
  lcd.print(F("starting alarm"));
  delay(1500);
  lcd.clear();

  // text & car
  lcd.setCursor(12, 1);
  lcd.write(byte(6));
  lcd.setCursor(13, 1);
  lcd.write(byte(7));
  lcd.setCursor(5, 0);
  lcd.print(F("- GO -"));
  tone(BUZZER_PIN, 1800, 200);   //E7 - long beep
  delay(1000);
  lcd.setCursor(5, 0);
  lcd.print(F("          "));
  for (int i = 0; i < 15; i++) {
    lcd.scrollDisplayLeft();
    tone(BUZZER_PIN, 40, 50);
    delay(225);
  }
  // end car

  setAlarmLcdCharacters();
  lcd.clear();
}

void testBuzzer() {
  lcd.setCursor(0, 0);
  lcd.print(F("Startup test(B)"));
  lcd.setCursor(0, 1);
  lcd.print(F("Testing buzzer..."));
  delay(200);
  playTuneTwoo();   //  playTuneOne();
  delay(500);
  lcd.clear();
}

void testLight() {
  int value;
  lcd.print(F("Startup test(L)"));
  lcd.setCursor(0, 1);
  lcd.print(F("Testing light..."));
  for (value = 255; value > 0; value--)
  {
    analogWrite(RED_LED_PIN, value);
    analogWrite(GREEN_LED_PIN, 255 - value);
    delay(10);
  }
  delay(1000);
  for (value = 0; value < 255; value++)
  {
    analogWrite(RED_LED_PIN, value);
    analogWrite(GREEN_LED_PIN, 255 - value);
    delay(10);
  }
  analogWrite(RED_LED_PIN, 0);
  lcd.clear();
  delay(500);
}
