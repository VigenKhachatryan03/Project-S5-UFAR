// #include <Send_To_ThingsBoard>
// #include <OTA.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <WiFiClientSecure.h>
#include <time.h>
#include <PubSubClient.h>
#include <DHT.h>

//SDS011 nova sensor
#include "SdsDustSensor.h"

int rxPin = D5;
int txPin = D6;
SdsDustSensor sds(rxPin, txPin);

//DHT sensor
#define DHTPIN D1
#define DHTTYPE DHT22

// Time and Led
unsigned long lastCheck = 0;
unsigned long lastBlink = 0;
bool ledState = false;

//Send Data WiFi Client
WiFiClient wifiClient;
PubSubClient client(wifiClient);

const char* mqttServer = "thingsboard.cloud";
const int mqttPort = 1883;
const char* accessToken = "bvbQjmvxNWZy3wioAQ7m";

DHT dht(DHTPIN, DHTTYPE);

// ---------------- WIFI ----------------
const char* ssid = "Ucom8350_2.4G"; //no android WiFi
const char* password = "10433091";

//delay for sending data
unsigned long lastReadingTime = 0;
unsigned long interval = 5000;


void setup() {
  Serial.begin(115200);
  sds.begin();
  delay(2000);
  
  //OTA
  WiFi.mode(WIFI_STA);

  //WiFi
  connect_wifi();
  
  setClock();
  
  //Send Data to Server
  client.setServer(mqttServer, mqttPort);

  //Project
  dht.begin();
  pinMode(LED_BUILTIN, OUTPUT);

  //Check SDS011
  SDS011_Setup();
}

void loop() {
  //Update firmware if available
  if (millis() - lastCheck > 60000) {  
    lastCheck = millis();
    FirmwareUpdate();
  }
  //If WiFi is not connected, it reconnects 
  if (WiFi.status() != WL_CONNECTED) {
    connect_wifi();
  }
  //Server reconnect
  if (!client.connected()) {
    reconnect();
  }
  ledFlash(0);
  client.loop();

  if (millis() - lastReadingTime > interval) {
    lastReadingTime = millis();
    sendTelementry();
  }

  // Serial.println("New Version: 1.2");
  delay(3000);
}