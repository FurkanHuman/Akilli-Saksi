/*
  Lezzetli Robot Tarifleri
   VİDEO >>> https://lezzetlirobottarifleri.com/arduino-ve-i2c-ile-4x20-2x16-lcd-ekran-kullanimi
*/
 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.begin();
}

void loop() {
  lcd.home();
  lcd.print("      TOPLA");
  lcd.setCursor(4, 1);
  lcd.print("  FURKAN");
}