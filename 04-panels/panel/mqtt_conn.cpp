#include "mqtt_conn.h" 

const char* MQTT_SERVER = "mosquitto.local";
const int MQTT_PORT = 1883;
const char* MQTT_CLIENT_ID = "greenhouse-m5";

const char* MQTT_USER = "xxxxx";
const char* MQTT_PASS = "xxxxxx";

WiFiClient espClientM5; 
PubSubClient MqttClient(espClientM5); 

bool connectMqtt(){
  MqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  
  Serial.println("Verbinden met MQTT .....");

  if (MqttClient.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS)){
  
     Serial.println("MQTT verbonden");
     return true;
  } else {
    Serial.print("MQTT verbinden mislukt, state: ");
    Serial.println(MqttClient.state());
    return false;
  }
}

void ensureMqttConnected(){
  if (!MqttClient.connected()) {
    connectMqtt(); 
  }
  MqttClient.loop();
}