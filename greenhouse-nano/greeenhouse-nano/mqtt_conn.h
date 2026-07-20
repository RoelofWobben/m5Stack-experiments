#pragma once 

#include <PubSubClient.h>

extern PubSubClient mqttClient; 

bool connectMqtt();
void MqttCallBack(char* topic, byte* payload, unsigned int length); 