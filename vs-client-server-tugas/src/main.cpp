#include <Arduino.h>
#include <ESP8266WiFi.h>

#define RED_LED D5   // led warna merah
#define GREEN_LED D6 // led warna hijau
#define BLUE_LED D7  // led warnah biru

const char *ssid = "JTI-POLINEMA";   // nama SSID untuk koneksi Anda
const char *password = "jtifast!";   // password akses point WIFI Anda
const uint16_t port = 2004;          // diganti dengan port serve Anda
const char *host = "192.168.67.147"; // diganti dengan host server Anda, bisa ip ataupun domain

#include <SimpleDHT.h>

#define pinDHT 1 // SD3 pin signal sensor DHT

byte temperature = 0;
byte humidity = 0;

SimpleDHT11 dht11(D1); // instan sensor dht11

// untuk pembacaan sensor cahaya
#define sensorLDR A0
int nilaiSensor;

void connect_wifi()
{
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
}

void connect_server()
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
  Serial.print("Nilai Sensor : ");
  Serial.println(nilaiSensor);
  delay(1000);

  WiFiClient client;

  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, port))
  {
    Serial.println("connected]");

    Serial.println("[Sending a request]");
    client.print("Hai from ESP8266");

    // pembacaan suhu dan kelembapan
    client.print((int)temperature);

    client.print(" *C, ");
    client.print((int)humidity);
    client.println(" H");

    // pembacaan sensor cahaya
    client.println("nilai sensor : ,");
    client.println(nilaiSensor);
    if (nilaiSensor > 500)
    {
      digitalWrite(GREEN_LED, HIGH);
      client.println("Sudah malam, Lampu menyala");
      delay(1000);
    }
    else if (nilaiSensor <= 500)
    {
      digitalWrite(GREEN_LED, LOW);
      client.println("Lampu mati");
      delay(1000);
    }

    Serial.println("[Response:]");
    String line = client.readStringUntil('\n');
    Serial.println(line);
    client.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("connection failed!]");
    client.stop();
  }
  delay(3000);
}

void setup()
{
  Serial.begin(115200);
  pinMode(RED_LED, OUTPUT); // atur pin-pin digital sebagai output
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  connect_wifi();

  delay(1000);
}

void loop()
{
  connect_server();
}