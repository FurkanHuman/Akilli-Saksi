/*
 * Bu kod, Furkan Bozkurt tarafından OpenAI ile geliştirilen ChatGPT AI modeli kullanılarak yazılmıştır.
 * Bu model, dil üretim işlemleri yapmak için kullanılır ve yapay zeka teknolojilerini
 * kullanarak insan dilini anlamaya ve yanıt vermeye çalışır.
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD I2C adresi
#define I2C_ADDR 0x27

// LCD ekranı tanımla
LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2);

// Zaman aralıkları (6 saat ve 10 dakika)
#define INTERVAL 2160000
#define MOTOR_INTERVAL 360000
#define PUMP_INTERVAL 2160000
#define RAIN_INTERVAL 300000

unsigned long previousMillis = 0;

// Pin tanımlamaları
#define SOIL_PIN A0
#define MOTOR_PIN 3
#define PUMP_PIN 4
#define RAIN_PIN 2

bool isRaining = false;
unsigned long rainStartTime = 0;
unsigned long motorStartTime = 0;

void setup()
{
    // Seri port hızını ayarla
    Serial.begin(9600);

    // LCD ekranını başlat
    lcd.begin();
    lcd.backlight();

    // Motor, pompa ve yağmur sensörü pinlerini çıkış olarak ayarla
    pinMode(MOTOR_PIN, OUTPUT);
    pinMode(PUMP_PIN, OUTPUT);
    pinMode(RAIN_PIN, INPUT);

    // Başlangıç mesajı
    lcd.clear();
    lcd.print("Akıllı Saksı");
    lcd.setCursor(0, 1);
    lcd.print("Başlatılıyor...");
    delay(2000);
}

void loop()
{
    // Toprak nem sensörü değerini oku
    int soil = map(analogRead(SOIL_PIN), 0, 1023, 0, 100);

    // LCD ekrana değerleri yaz
    lcd.clear();
    lcd.print("Toprak Nemi: ");
    lcd.print(soil);
    lcd.print("%");

    // Geçerli millis değerini al
    unsigned long currentMillis = millis();

    // aralık geçip geçmediğini kontrol et
    if (currentMillis - previousMillis > INTERVAL)
    {

        previousMillis = currentMillis;
        // Toprak nemi %70 veya daha az ise motor ve pompayı çalıştır
        if (soil < 70)
        {
            if (motorStartTime == 0)
            {
                motorStartTime = millis();
                digitalWrite(MOTOR_PIN, HIGH);
                digitalWrite(PUMP_PIN, HIGH);
                lcd.setCursor(0, 1);
                lcd.print("Motor: AKTIF");
                lcd.print(" ");
                lcd.print("Pompa: AKTIF");
            }
            // Motor ve pompa çalışma süresi sonunda pasifleştirilir.
            else if (millis() - motorStartTime >= MOTOR_INTERVAL)
            {
                digitalWrite(MOTOR_PIN, LOW);
                digitalWrite(PUMP_PIN, LOW);
                lcd.setCursor(0, 1);
                lcd.print("Motor: PASIF");
                lcd.print(" ");
                lcd.print("Pompa: PASIF");
                motorStartTime = 0;
            }
        }
        // Toprak nemi %70 veya daha fazla ise sadece motor çalışır.
        else if (millis() - previousMillis >= PUMP_INTERVAL)
        {

            digitalWrite(MOTOR_PIN, HIGH);
            lcd.setCursor(0, 1);
            lcd.print("Motor: AKTIF");
            previousMillis = millis();
        }
        else
        {
            digitalWrite(MOTOR_PIN, LOW);
            lcd.setCursor(0, 1);
            lcd.print("Motor: PASIF");
            motorStartTime = 0;
        }
    }

    // Yağmur sensörünü kontrol et
    int rainValue = digitalRead(RAIN_PIN);
    if (rainValue == HIGH && !isRaining)
    {
        // Yağmur algılandı
        isRaining = true;
        rainStartTime = millis();
        lcd.setCursor(0, 1);
        lcd.print("Yagmur: AKTIF");
    }
    else if (isRaining && millis() - rainStartTime >= RAIN_INTERVAL)
    {
        // Yağmur bitti
        isRaining = false;
        digitalWrite(PUMP_PIN, LOW);
        lcd.setCursor(0, 1);
        lcd.print("Yagmur: PASIF");
        delay(600000);
    }
}
