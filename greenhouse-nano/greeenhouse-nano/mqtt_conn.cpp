#include "secrets.h"
#include <WiFi.h>
#include "mqtt_conn.h"
#include <PubSubClient.h>
#include "leds.h"

const char* MQTT_SERVER = "mosquitto.local";
const int MQTT_PORT = 1883;
const char* MQTT_CLIENT_ID = "greenhouse-nano";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

bool connectMqtt() {
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(MqttCallBack);

  Serial.println("Connecting to MQTT");

  if (mqttClient.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS)) {
    Serial.println("MQTT Connected");
    mqttClient.subscribe("greenhouse/#");
    return true;
  } else {
    Serial.print("MQTT failed: ");
    Serial.println(mqttClient.state());
    return false; 

  } 
}

void MqttCallBack(char* topic, byte* payload, unsigned int length) {
  String message; 
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i]; 
  }

  Serial.print("Bericht ontvangen op ");
  Serial.print(topic);
  Serial.print(": ");
  Serial.println(message);

  if (String(topic) == "greenhouse/light/set"){
    if (message == "ON") {
      turnLightOn();
    } else if (message == "OFF") {
      turnLightOff();
    }
  }
}