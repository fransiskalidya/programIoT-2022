#include <Arduino.h>

// LDR
// #define sensorLDR A0
// int nilaiSensor;

// void setup()
// {
//   Serial.begin(115200);
//   Serial.println("Contoh Penggunaan Sensor LDR");
//   delay(3000);
// }

// void loop()
// {
//   nilaiSensor = analogRead(sensorLDR);
//   Serial.print("Nilai Sensor : ");
//   Serial.println(nilaiSensor);
//   delay(1000);
// }

// SENSOR ULTRASONIC
// #define triggerPin D6
// #define echoPin D5

// void setup() {
//    Serial.begin (115200);
//    pinMode(triggerPin, OUTPUT);
//    pinMode(echoPin, INPUT);
//    pinMode(BUILTIN_LED, OUTPUT);
// }

// void loop() {
//    long duration, jarak;
//    digitalWrite(triggerPin, LOW);
//    delayMicroseconds(2);
//    digitalWrite(triggerPin, HIGH);
//    delayMicroseconds(10);
//    digitalWrite(triggerPin, LOW);
//    duration = pulseIn(echoPin, HIGH);
//    jarak = duration * 0.034 / 2;
//    Serial.print(jarak);
//    Serial.println(" cm");
//    delay(2000);
// }

// tugas 1
#include <SimpleDHT.h>

#define pinDHT 1 // SD3 pin signal sensor DHT
#define RED_LED D5
#define GREEN_LED D6
#define BLUE_LED D7
#define sensorLDR A0
int nilaiSensor;

byte temperature = 0;
byte humidity = 0;
SimpleDHT11 dht11(D1);
void setup()
{
  Serial.begin(115200);
  Serial.println("sensor suhu dan cahaya");
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  delay(1000);
}


void loop()
{

  int err = SimpleDHTErrSuccess;

  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess)
  {
    Serial.print("Pembacaan DHT11 gagal, err=");
    Serial.println(err);
    delay(1000);
    return;
  }
  nilaiSensor = analogRead(sensorLDR);
  Serial.print("Sample OK: ");
  Serial.print((int)temperature);
  Serial.print(" *C, ");
  Serial.print("Nilai Sensor : ");
  Serial.println(nilaiSensor);

  if (temperature < 27 && nilaiSensor > 800)
  {
    Serial.print(" suhu dingin dan cahaya redup ");
    for (int i = 0; i < 3; i++)
    {
      digitalWrite(BLUE_LED, HIGH);
      Serial.print((int)temperature);
      Serial.print(" *C, ");
      Serial.print("Nilai Sensor : ");
      Serial.println(nilaiSensor);
      delay(1000);
      digitalWrite(BLUE_LED, LOW);
      Serial.print((int)temperature);
      Serial.print(" *C, ");
      Serial.print("Nilai Sensor : ");
      Serial.println(nilaiSensor);
      delay(1000);
    }
    digitalWrite(RED_LED, LOW);
  }

  else if (temperature >= 28 && nilaiSensor < 400)
  {
    Serial.print(" suhu panas dan cahaya terang ");
    digitalWrite(RED_LED, HIGH);
    Serial.print((int)temperature);
    Serial.print(" *C, ");
    Serial.print("Nilai Sensor : ");
    Serial.println(nilaiSensor);
    delay(1000);
    digitalWrite(RED_LED, LOW);
    Serial.print((int)temperature);
    Serial.print(" *C, ");
    Serial.print("Nilai Sensor : ");
    Serial.println(nilaiSensor);
  }
  // digitalWrite(BLUE_LED, LOW);

  delay(1500);
}

// tugas 2

// #define RED_LED D1
// #define GREEN_LED D2
// #define BLUE_LED D3
// #define triggerPin D6
// #define echoPin D5

// void setup()
// {
//   Serial.begin(115200);
//   pinMode(triggerPin, OUTPUT);
//   pinMode(echoPin, INPUT);
//   pinMode(BUILTIN_LED, OUTPUT);
//   pinMode(BLUE_LED, OUTPUT);
//   pinMode(RED_LED, OUTPUT);
//   pinMode(GREEN_LED, OUTPUT);
// }

// void rgbLED()
// {
//   digitalWrite(RED_LED, HIGH);
//   digitalWrite(GREEN_LED, LOW);
//   digitalWrite(BLUE_LED, LOW);
//   delay(1000);

//   digitalWrite(RED_LED, LOW);
//   digitalWrite(GREEN_LED, HIGH);
//   digitalWrite(BLUE_LED, LOW);
//   delay(1000);

//   digitalWrite(RED_LED, LOW);
//   digitalWrite(GREEN_LED, LOW);
//   digitalWrite(BLUE_LED, HIGH);
//   delay(1000);
// }

// void loop()
// {
//   long duration, jarak;
//   digitalWrite(triggerPin, LOW);
//   delayMicroseconds(2);
//   digitalWrite(triggerPin, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(triggerPin, LOW);
//   duration = pulseIn(echoPin, HIGH);
//   jarak = duration * 0.034 / 2;
//   Serial.print(jarak);
//   Serial.println(" cm");

//   if (jarak == 1)
//   {
//     Serial.print(jarak);
//     Serial.println(" cm");
//     digitalWrite(BLUE_LED, HIGH);
//     digitalWrite(RED_LED, LOW);
//     digitalWrite(GREEN_LED, LOW);
//   }
//   else if (jarak == 2)
//   {
//     Serial.print(jarak);
//     Serial.println(" cm");
//     digitalWrite(GREEN_LED, HIGH);
//     digitalWrite(RED_LED, LOW);
//     digitalWrite(BLUE_LED, LOW);
//   }
//   else if (jarak == 3)
//   {
//     Serial.print(jarak);
//     Serial.println(" cm");
//     digitalWrite(RED_LED, HIGH);
//     digitalWrite(BLUE_LED, LOW);
//     digitalWrite(GREEN_LED, LOW);
//   }
//   else if (jarak > 3)
//   {
//     rgbLED();
//   }
//   delay(2000);
// }