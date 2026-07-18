void PublishStatus(const Panel& panel, bool status) {

  if (panel.mqttTopic == nullptr) return; 

  const char* payload = status? "ON" : "OFF";
  mqttClient.publish(panel.mqttTopic, payload);

  Serial.print(panel.label);
  Serial.print(" -> ");
  Serial.println(payload);
}