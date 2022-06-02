#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);// setbaudrate 115200
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello world");// menampilkan string ke serial monitor
  delay(1000);// jeda 1000 ms
}