void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to ThingsBoard MQTT... ");

    if (client.connect("ESP8266", accessToken, NULL)) {
      Serial.println("Connected!");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Try again in 3 seconds...");
      delay(3000);
    }
  }
}

void sendTelementry(){
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if(isnan(temp) || isnan(hum)){
    Serial.println("Fail to read DHT");
    return;
  }

  String payload = 
  "{\"Temperature\":" + String(temp) +
  ",\"Humidity\":" + String(hum) +
  ",\"PM2.5\":" + SDS011_Return_MP10() +
  ",\"PM10\":" + SDS011_Return_MP25() +
  ",\"SW_Version\":" + String(FirmwareVer) +
  "}";
  client.publish("v1/devices/me/telemetry", payload.c_str());
}