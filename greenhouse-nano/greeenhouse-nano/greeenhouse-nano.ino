#include "wifi_conn.h"
#include "mqtt_conn.h"


void setup() {
  Serial.begin(9600);
  connectWifi(); 

  Serial.println("Setup completed");
}

void loop() {
  checkWifi(); 

  static unsigned long lastMqttAttempt = 0; 

  if (!mqttClient.connected() && millis() - lastMqttAttempt > 5000){
    lastMqttAttempt = millis(); 
    connectMqtt(); 
  }

  

}
