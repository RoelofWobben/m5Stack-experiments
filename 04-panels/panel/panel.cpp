#include "panel.h"
#include "mqtt_conn.h"
#include "pump_off.h"
#include "pump_on.h"
#include "window_closed.h"
#include "window_open.h"
#include "light_off.h"
#include "light_on.h"

extern Panel lightPanel; 
extern bool lightStatus; 
extern Panel pompPanel; 
extern bool pompStatus; 
extern Panel windowPanel;
extern bool windowStatus;  

void flush() {
  canvas.pushSprite(0, 0);
}

void drawPanel(const Panel& panel, const uint16_t* icon, bool status) {
  canvas.fillRoundRect(panel.x, panel.y - scrollOffSet, panel.w, panel.h, 12, panelColor);

  canvas.pushImage(panel.x + 20, panel.y + 10 - scrollOffSet, 32, 32, icon, 0xFFFF);

  // Titel tekst opgeschoven naar rechts van het icoon
  canvas.setTextColor(WHITE, panelColor);
  canvas.setTextSize(2);
  canvas.setTextDatum(middle_left);
  canvas.drawString(panel.label, panel.x + 62, panel.y + 26 - scrollOffSet);
}

void drawSingleButton(const RectButton& button, bool isActive) {
  canvas.fillRect(button.x - 2, button.y - 2, button.w - 4, button.h + 4, panelColor);

  uint16_t color = isActive ? GREEN : grey;
  canvas.fillRoundRect(button.x, button.y, button.w, button.h, 10, color);

  canvas.setTextColor(WHITE, color);
  canvas.setTextSize(2);
  canvas.setTextDatum(middle_center);
  canvas.drawString(button.label, button.x + button.w / 2, button.y + button.h / 2);
}

RectButton getOnButton(const Panel& panel) {
  return { panel.x, panel.y + 50 - scrollOffSet, 120, 40, panel.textOn };
}

RectButton getOffButton(const Panel& panel) {
  return { panel.x + 160, panel.y + 50 - scrollOffSet, 120, 40, panel.textOff };
}

void drawButtons(const Panel& panel, bool status) {
  RectButton onButton = getOnButton(panel);
  RectButton offButton = getOffButton(panel);

  drawSingleButton(onButton, status);
  drawSingleButton(offButton, !status);
}

bool isButtonTouched(const RectButton& button) {

  if (M5.Touch.getCount() == 0) return false;

  auto detail = M5.Touch.getDetail(0);
  if (!detail.wasPressed()) return false;

  return (detail.x >= button.x && detail.x <= button.x + button.w && detail.y >= button.y && detail.y <= button.y + button.h);
}

void handlePanelTouch(const Panel& panel, bool& status, const uint16_t* iconOn, const uint16_t* iconOff) {

  if (!status && isButtonTouched(getOnButton(panel))) {
    status = true;
    drawPanel(panel, status ? iconOn : iconOff, status);
    drawButtons(panel, status);
    flush();
    publishStatus(panel, status);
  }

  if (status && isButtonTouched(getOffButton(panel))) {
    status = false;
    drawPanel(panel, status ? iconOn : iconOff, status);
    drawButtons(panel, status);
    flush();
    publishStatus(panel, status);
  }
}

void publishStatus(const Panel& panel, bool status) {

  if (panel.mqttTopic == nullptr) return;

  const char* payload = status ? "ON" : "OFF";
  MqttClient.publish(panel.mqttTopic, payload);

  Serial.print(panel.label);
  Serial.print(" -> ");
  Serial.println(payload);
}

void drawPanels() {

  canvas.fillScreen(BLACK);

  drawPanel(lightPanel, lightStatus ? lightIconOn : lightIcon, lightStatus);
  drawButtons(lightPanel, lightStatus);

  drawPanel(pompPanel, pompStatus ? pumpIconOn : pumpIconOff, pompStatus);
  drawButtons(pompPanel, pompStatus);

  drawPanel(windowPanel, windowStatus ? windowIconOpen : windowIconClosed, windowStatus);
  drawButtons(windowPanel, windowStatus);

  flush();
}

void mqttCallBack(char* topic, byte* payload, unsigned int length){
  String message; 
  for (unsigned int i = 0; i < length; i++) {
    message += (char) payload[i];
  }

  Serial.print("M5 ontving op  ");
  Serial.print(topic);
  Serial.print(": ");
  Serial.print(message);
}

