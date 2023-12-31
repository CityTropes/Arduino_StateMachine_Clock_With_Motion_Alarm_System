// ***************************************************************************************** //
// ----------- CUSTOM CHARACTER BUILDER ---------------------------------------------------- //
// ----------- functions for building & managing custom made characters for lcd. ----------- //
// ***************************************************************************************** //


byte lock[8], lockOpen[8], eyeOpen[8], eyeClosed[8], star[8], houseLD[8], houseRD[8], houseLU[8], houseRU[8], carFront[8], carBack[8], heart[8], bell[8];

void setAlarmLcdCharacters() {
  lcd.createChar(0, heart);
  lcd.createChar(1, bell);
  lcd.createChar(2, eyeOpen);
  lcd.createChar(3, eyeClosed);
  lcd.createChar(4, carFront);
  lcd.createChar(5, carBack);
  lcd.createChar(6, lock);
  lcd.createChar(7, lockOpen);
}

void setCustomLcdCharacters() {
  lcd.createChar(0, star);
  lcd.createChar(1, lock);
  lcd.createChar(2, houseLD);
  lcd.createChar(3, houseRD);
  lcd.createChar(4, houseLU);
  lcd.createChar(5, houseRU);
  lcd.createChar(6, carFront);
  lcd.createChar(7, carBack);
}

void buildCustomCharacters() {
  eyeOpen[0] = 0b00000;
  eyeOpen[1] = 0b00000;
  eyeOpen[2] = 0b01110;
  eyeOpen[3] = 0b10001;
  eyeOpen[4] = 0b10101;
  eyeOpen[5] = 0b01110;
  eyeOpen[6] = 0b00000;
  eyeOpen[7] = 0b00000;

  eyeClosed[0] = 0b00000;
  eyeClosed[1] = 0b00000;
  eyeClosed[2] = 0b01110;
  eyeClosed[3] = 0b11111;
  eyeClosed[4] = 0b11111;
  eyeClosed[5] = 0b01110;
  eyeClosed[6] = 0b00000;
  eyeClosed[7] = 0b00000;

  houseLD[0] = 0b11111;
  houseLD[1] = 0b11111;
  houseLD[2] = 0b11000;
  houseLD[3] = 0b11000;
  houseLD[4] = 0b11000;
  houseLD[5] = 0b11000;
  houseLD[6] = 0b11000;
  houseLD[7] = 0b11000;

  houseRD[0] = 0b11111;
  houseRD[1] = 0b11111;
  houseRD[2] = 0b10001;
  houseRD[3] = 0b10001;
  houseRD[4] = 0b10001;
  houseRD[5] = 0b11111;
  houseRD[6] = 0b11111;
  houseRD[7] = 0b11111;

  houseLU[0] = 0b00001;
  houseLU[1] = 0b00011;
  houseLU[2] = 0b00011;
  houseLU[3] = 0b00111;
  houseLU[4] = 0b00111;
  houseLU[5] = 0b01111;
  houseLU[6] = 0b01111;
  houseLU[7] = 0b11111;

  houseRU[0] = 0b10010;
  houseRU[1] = 0b11010;
  houseRU[2] = 0b11010;
  houseRU[3] = 0b11110;
  houseRU[4] = 0b11110;
  houseRU[5] = 0b11110;
  houseRU[6] = 0b11110;
  houseRU[7] = 0b11111;

  heart[0] =  B00000;
  heart[1] =  B01010;
  heart[2] =  B11111;
  heart[3] =  B11111;
  heart[4] =  B01110;
  heart[5] =  B00100;
  heart[6] =  B00000;
  heart[7] =  B00000;

  bell[0] = B00100;
  bell[1] = B01110;
  bell[2] = B01110;
  bell[3] = B01110;
  bell[4] = B11111;
  bell[5] = B00000;
  bell[6] = B00100;
  bell[7] = B00000;

  star[0] = 0b00000;
  star[1] = 0b00100;
  star[2] = 0b10001;
  star[3] = 0b00100;
  star[4] = 0b01110;
  star[5] = 0b00100;
  star[6] = 0b10001;
  star[7] = 0b00100;

  carFront[0] = 0b00000;
  carFront[1] = 0b00001;
  carFront[2] = 0b00011;
  carFront[3] = 0b11111;
  carFront[4] = 0b10000;
  carFront[5] = 0b11111;
  carFront[6] = 0b00110;
  carFront[7] = 0b00110;

  carBack[0] = 0b11100;
  carBack[1] = 0b00010;
  carBack[2] = 0b00010;
  carBack[3] = 0b00001;
  carBack[4] = 0b00001;
  carBack[5] = 0b11110;
  carBack[6] = 0b01100;
  carBack[7] = 0b01100;

  lock[0] = 0b01110;
  lock[1] = 0b10001;
  lock[2] = 0b10001;
  lock[3] = 0b11111;
  lock[4] = 0b11011;
  lock[5] = 0b11011;
  lock[6] = 0b11011;
  lock[7] = 0b11111;

  lockOpen[0] = 0b01110;
  lockOpen[1] = 0b10000;
  lockOpen[2] = 0b10000;
  lockOpen[3] = 0b11111;
  lockOpen[4] = 0b11011;
  lockOpen[5] = 0b11011;
  lockOpen[6] = 0b11011;
  lockOpen[7] = 0b11111;
}
