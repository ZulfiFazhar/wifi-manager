#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include <EEPROM.h>

#define EEPROM_SIZE 96  // 32 bytes for SSID, 32 bytes for password

extern const char* ap_ssid;
extern const char* ap_password;

extern String wifi_ssid;
extern String wifi_password;

extern WiFiServer server;
extern String header;
extern int mode;

void setupAPMode();
void setupStationMode();
void saveWiFiCredentials(String ssid, String password);
void loadWiFiCredentials();

#endif // WIFI_MANAGER_H
