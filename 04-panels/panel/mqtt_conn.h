#pragma once

#include "WiFi.h"
#include <PubSubClient.h>

WiFiClient espClientM5; 
PubSubClient mqttClient(espClientM5); 


bool connectMqtt();
void ensureMqttConnected();
void PublishStatus(const Panel& panel, bool status); 
