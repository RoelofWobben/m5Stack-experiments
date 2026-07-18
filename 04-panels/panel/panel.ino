#include <M5Unified.h>

#include "pump_off.h"
#include "pump_on.h"
#include "window_closed.h"
#include "window_open.h"
#include "light_off.h"
#include "light_on.h"
#include "wifi_conn.h"
#include "mqtt_conn.h"

struct RectButton {
  int x, y, w, h;
  const char* label;
};

struct Panel {
  int x, y, w, h;
  const char* label;
  const char* textOn;
  const char* textOff;
  const char* mqttTopic; 
};

// drie panelen
Panel lightPanel = { 10, 10, 300, 100, "Light", "On", "Off", "greenhouse/light/set" };
Panel pompPanel = { 10, 130, 300, 100, "Pomp", "On", "Off", nullptr };
Panel windowPanel = { 10, 250, 300, 100, "Window", "Open", "Closed", nullptr};

// Licht status
bool lightStatus = false;
bool pompStatus = false;
bool windowStatus = false;

uint16_t panelColor = 0x18E3;
uint16_t grey = 0x39C7;

int scrollOffSet = 0;

// voor swipe detectie
int touchStartY = 0;
int scrollStartOffSet = 0;
bool isDragging = false;

// grenzen waarbinnen je mag scrollen
int minScrollOffSet = 0;
int maxScrollOffSet = 110;

M5Canvas canvas(&M5.Display);

void flush() {
  canvas.pushSprite(0, 0);
}


void handleScroll() {

  if (M5.Touch.getCount() == 0) {
    isDragging = false;
    return;
  }

  auto detail = M5.Touch.getDetail(0);

  if (detail.wasPressed()) {
    touchStartY = detail.y;
    scrollStartOffSet = scrollOffSet;
    isDragging = true;
  }

  if (isDragging && detail.isDragging()) {
    int deltaY = detail.y - touchStartY;
    int newOffSet = scrollStartOffSet - deltaY;
    newOffSet = constrain(newOffSet, minScrollOffSet, maxScrollOffSet);

    if (newOffSet != scrollOffSet) {
      scrollOffSet = newOffSet;
      drawPanels();
    }
  }
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

void drawSingleButton(const RectButton& button, bool isActive) {
  canvas.fillRect(button.x - 2, button.y - 2, button.w - 4, button.h + 4, panelColor);

  uint16_t color = isActive ? GREEN : grey;
  canvas.fillRoundRect(button.x, button.y, button.w, button.h, 10, color);

  canvas.setTextColor(WHITE, color);
  canvas.setTextSize(2);
  canvas.setTextDatum(middle_center);
  canvas.drawString(button.label, button.x + button.w / 2, button.y + button.h / 2);
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

RectButton getOnButton(const Panel& panel) {
  return { panel.x, panel.y + 50 - scrollOffSet, 120, 40, panel.textOn };
}

RectButton getOffButton(const Panel& panel) {
  return { panel.x + 160, panel.y + 50 - scrollOffSet, 120, 40, panel.textOff };
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

void setup() {

   Serial.begin(115200);
   
  connectWifi(); 

  auto cfg = M5.config();
  M5.begin(cfg);
  M5.Display.fillScreen(BLACK);

  canvas.setColorDepth(16);
  canvas.createSprite(M5.Display.width(), M5.Display.height());
  canvas.setSwapBytes(true);

  Serial.begin(115200);

  connectWifi(); 
  connectMqtt(); 

  drawPanels();
}

void loop() {
  M5.update();

  ensureMqttConnected(); 

  handleScroll();

  handlePanelTouch(lightPanel, lightStatus, lightIconOn, lightIcon);
  handlePanelTouch(pompPanel, pompStatus, pumpIconOn, pumpIconOff);
  handlePanelTouch(windowPanel, windowStatus, windowIconOpen, windowIconClosed);
}
