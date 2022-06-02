#include <Arduino.h>

#define BLUE_LED1 D4

void setup() {
  Serial.begin(115200);
  pinMode(BLUE_LED1,OUTPUT);
}

void loop() {
  Serial.println("Nyalakan LED");
  digitalWrite(BLUE_LED1,HIGH);
  delay(1000);
  Serial.println("Matikan LED");
  digitalWrite(BLUE_LED1,LOW);
  delay(1000);
}