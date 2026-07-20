#include "secrets.h"
#include <WiFi.h>
#include "mqtt_conn.h"
#include <PubSubClient.h>

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
  Serial.print("Topic: ");
  Serial.println(topic); 
}