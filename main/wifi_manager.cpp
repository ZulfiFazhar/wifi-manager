#include "wifi_manager.h"

const char* ap_ssid = "ESP32_AP";
const char* ap_password = "esp32mantap";

String wifi_ssid = "YourWiFiSSID";
String wifi_password = "YourWiFiPassword";

WiFiServer server(80);
String header;
int mode = 0;

void setupAPMode() {
  Serial.println("Setting up Access Point (AP)...");
  WiFi.softAP(ap_ssid, ap_password);
  IPAddress AP_IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(AP_IP);
}

void setupStationMode() {
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(wifi_ssid);
  WiFi.begin(wifi_ssid.c_str(), wifi_password.c_str());

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Wi-Fi connected!");
  Serial.print("Station IP Address: ");
  Serial.println(WiFi.localIP());
}

void saveWiFiCredentials(String ssid, String password) {
  for (int i = 0; i < 32; i++) {
    EEPROM.write(i, i < ssid.length() ? ssid[i] : 0);
    EEPROM.write(32 + i, i < password.length() ? password[i] : 0);
  }
  EEPROM.commit();
}

void loadWiFiCredentials() {
  char ssid[33];
  char password[33];
  
  for (int i = 0; i < 32; i++) {
    ssid[i] = EEPROM.read(i);
    password[i] = EEPROM.read(32 + i);
  }
  ssid[32] = '\0';
  password[32] = '\0';

  wifi_ssid = String(ssid);
  wifi_password = String(password);

  if (wifi_ssid.length() == 0 || wifi_password.length() == 0) {
    wifi_ssid = "YourWiFiSSID";
    wifi_password = "YourWiFiPassword";
  }
}
