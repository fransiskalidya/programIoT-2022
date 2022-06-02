#include <Arduino.h>
#include <SimpleDHT.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <Wire.h>

#define pinDHT 0 // SD3 pin signal sensor DHT
#define RED_LED D5
#define GREEN_LED D6
#define BLUE_LED D7

byte temperature = 0;
byte humidity = 0;
SimpleDHT11 dht11(D0);

#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char *ssid = "Alohomora";
const char *password = "pasangwifi2021";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void setup()
{
  // SETUP LCD
  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.clear();
  lcd.home();

  Serial.begin(115200);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  timeClient.begin();
  // mengatur timezone
  timeClient.setTimeOffset(28800);
  delay(1000);
}

void loop()
{
  lcd.home();
  timeClient.update();

  time_t epochTime = timeClient.getEpochTime();
  String formattedTime = timeClient.getFormattedTime();
  struct tm *ptm = gmtime((time_t *)&epochTime);

  int monthDay = ptm->tm_mday;
  Serial.print("Month day: ");
  Serial.println(monthDay);

  int currentMonth = ptm->tm_mon + 1;
  Serial.print("Month: ");
  Serial.println(currentMonth);

  int currentYear = ptm->tm_year + 1900;
  Serial.print("Year: ");
  Serial.println(currentYear);
  String currentDate = String(monthDay) + "-" + String(currentMonth) + "-" + String(currentYear);

  int err = SimpleDHTErrSuccess;

  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess)
  {
    
    delay(1000);
    return;
  }

  Serial.print((int)temperature);
  Serial.print(" *C, ");
  float fahren = 1.8 * temperature;
  Serial.print((float)fahren);
  Serial.print(" *F, ");
  Serial.print(currentDate);

  if (temperature <= 20)
  {
    for (int i = 0; i < 3; i++)
    {
      Serial.print(" dingin ");
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(BLUE_LED, LOW);
      digitalWrite(RED_LED, LOW);
    }
    lcd.setCursor(0,0); //dimulai dari kolom ke -0, baris ke-0
    lcd.print(temperature);
    lcd.print(" *C, ");
    lcd.setCursor(7,0); //dimulai dari kolom ke -7, baris ke-0
    lcd.print(fahren);
    lcd.print(" *F, ");
    lcd.setCursor(0, 1); //dimulai dari kolom ke -0, baris ke-1
    lcd.print(currentDate);
    lcd.setCursor(10, 1); //dimulai dari kolom ke -10, baris ke-1
    lcd.print(formattedTime);
  }
  else if (20 < temperature < 30)
  {
    for (int i = 0; i < 3; i++)
    {
      Serial.print(" normal ");
      digitalWrite(BLUE_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, LOW);
    }
     lcd.setCursor(0,0);
    lcd.print(temperature);
    lcd.print(" *C, ");
    lcd.setCursor(7,0);
    lcd.print(fahren);
    lcd.print(" *F, ");
    lcd.setCursor(0, 1);
    lcd.print(currentDate);
    lcd.setCursor(10, 1);
    lcd.print(formattedTime);
  }
  else if (temperature >= 30)
  {
    for (int i = 0; i < 3; i++)
    {
      Serial.print(" panas ");
      digitalWrite(RED_LED, HIGH);
      digitalWrite(BLUE_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
    }
     lcd.setCursor(0,0);
    lcd.print(temperature);
    lcd.print(" *C, ");
    lcd.setCursor(7,0);
    lcd.print(fahren);
    lcd.print(" *F, ");
    lcd.setCursor(0, 1);
    lcd.print(currentDate);
    lcd.setCursor(10, 1);
    lcd.print(formattedTime);
  }
}