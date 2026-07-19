#pragma once

#include "WiFi.h"
#include <PubSubClient.h>
#include "secrets.h"

extern WiFiClient espClientM5; 
extern PubSubClient MqttClient; 

bool connectMqtt();
void ensureMqttConnected();
