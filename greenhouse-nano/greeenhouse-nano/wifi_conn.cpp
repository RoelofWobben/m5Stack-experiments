#include "Arduino.h"
#include "secrets.h"
#include "WiFiNINA.h"
#include "wifi_conn.h"

void connectWifi() {

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with  wifi module failed");
  }

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempt to connect to: ");
    Serial.println(WIFI_SSID);
    Serial.println(".");
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    delay(1000);
  }

  Serial.println("Wifi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void checkWifi() {
  if (WiFi.status()  != WL_CONNECTED) {
    Serial.println("Wifi lost! Reconnecting");
    connectWifi(); 
  }
}