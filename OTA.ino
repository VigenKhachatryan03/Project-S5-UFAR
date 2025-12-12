
// ---------------- FIRMWARE SETTINGS ----------------
const String FirmwareVer = "1.6";

#define URL_fw_Version "https://raw.githubusercontent.com/VigenKhachatryan03/ESP8266ex-air-monitoring-project-S5/main/FirmwareVersion.txt"
#define URL_fw_Bin     "https://raw.githubusercontent.com/VigenKhachatryan03/ESP8266ex-air-monitoring-project-S5/main/OTA_Send_ThingsBoard.ino.bin"


// ---------------- TIME (TLS REQUIRED) ----------------
void setClock() {
  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.print("Syncing time ");
  time_t now = time(nullptr);

  while (now < 1510644967) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println(" done.");
}



// ---------------- OTA UPDATE ----------------
void FirmwareUpdate() {
  WiFiClientSecure client;
  client.setInsecure();
  // client.setTrustAnchors(&cert);

  HTTPClient https;
  if (!https.begin(client, URL_fw_Version)) {
    Serial.println("Error opening version URL");
    return;
  }

  int httpCode = https.GET();
  if (httpCode != HTTP_CODE_OK) {
    Serial.println("Version check failed");
    return;
  }

  String newVersion = https.getString();
  newVersion.trim();

  Serial.print("Remote FW version: ");
  Serial.println(newVersion);

  if (newVersion == FirmwareVer) {
    Serial.println("Already latest firmware.");
    return;
  }

  Serial.println("New firmware available! Updating...");

  ESPhttpUpdate.setLedPin(LED_BUILTIN, HIGH);
  t_httpUpdate_return ret = ESPhttpUpdate.update(client, URL_fw_Bin);

  if (ret == HTTP_UPDATE_OK)
    Serial.println("UPDATE SUCCESS!");
  else {
    Serial.printf("UPDATE ERROR (%d): %s\n",
                  ESPhttpUpdate.getLastError(),
                  ESPhttpUpdate.getLastErrorString().c_str());
  }
}