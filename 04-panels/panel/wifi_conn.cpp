#include "wifi_conn.h"
#include "WiFi.h"


void connectWifi() {

   Serial.println("Attempt to connect to: assortimens");
   WiFi.disconnect(true, true);
   WiFi.mode(WIFI_STA);
   WiFi.begin(xxxxxxxx, xxxxxx);
  
  while (WiFi.status() != WL_CONNECTED) {
   
    Serial.print(".");
    
    delay(1000);
  }

  Serial.println("Wifi connected");
  Serial.print("IP adres: ");
  Serial.println(WiFi.localIP());
}