#pragma once

#include "WiFi.h"
#include <PubSubClient.h>

extern WiFiClient espClientM5; 
extern PubSubClient MqttClient(espClientM5); 

bool connectMqtt();
void ensureMqttConnected();
