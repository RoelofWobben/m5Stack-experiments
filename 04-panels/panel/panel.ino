#include <M5Unified.h>

#include "pump_off.h"
#include "pump_on.h"
#include "window_closed.h"
#include "window_open.h"
#include "light_off.h"
#include "light_on.h"

struct RectButton {
  int x, y, w, h;
  const char* label;
};

struct Panel {
  int x, y, w, h;
  const char* label;
};

// drie panelen
Panel lightPanel = { 10, 10, 300, 100, "Light" };
Panel pompPanel = { 10, 130, 300, 100, "Pomp" };

// Licht status
bool lightStatus = false;
bool pompStatus = false;

uint16_t panelColor = 0x18E3;
uint16_t grey = 0x39C7;

void drawPanel(const Panel& panel, const uint16_t* icon, bool status) {
  M5.Display.fillRoundRect(panel.x, panel.y, panel.w, panel.h, 12, panelColor);

  // icon links in de titel rij
  M5.Display.setSwapBytes(true);
  M5.Display.pushImage(panel.x + 20, panel.y + 10, 32, 32, icon, 0xFFFF); 

  // Titel tekst opgeschoven naar rechts van het icoon
  M5.Display.setTextColor(WHITE, panelColor);
  M5.Display.setTextSize(2);
  M5.Display.setTextDatum(middle_left);
  M5.Display.drawString(panel.label, panel.x + 62, panel.y + 26);
}

void drawPanels() {
  drawPanel(lightPanel, lightStatus ? lightIcon : LightIconOff, lightStatus);
  drawPanel(pompPanel, pompStatus ? pumpIconOn : pumpIconOff, pompStatus);
}

void drawSingleButton(const RectButton& button, bool isActive) {
  M5.Display.fillRect(button.x - 2, button.y - 2, button.w - 4, button.h + 4, panelColor);

  uint16_t color = isActive ? GREEN : grey;
  M5.Display.fillRoundRect(button.x, button.y, button.w, button.h, 10, color);


  M5.Display.setTextColor(WHITE, color);
  M5.Display.setTextSize(2);
  M5.Display.setTextDatum(middle_center);
  M5.Display.drawString(button.label, button.x + button.w / 2, button.y + button.h / 2);
}


void drawButtons(const Panel& panel, bool status) {
  RectButton onButton(panel.x + 20, panel.y + 50, 120, 40, "ON");
  RectButton offButton(panel.x + 160, panel.y + 50, 120, 40, "OFF");

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
  return { panel.x + 20, panel.y + 50, 120, 40, "ON" };
}

RectButton getOffButton(const Panel& panel) {
  return { panel.x + 160, panel.y + 50, 120, 40, "OFF" };
}

void handlePanelTouch(const Panel& panel, bool& status) {

  if (!status && isButtonTouched(getOnButton(panel))) {
    status = true;
    drawButtons(panel, status);
  }

  if (status && isButtonTouched(getOffButton(panel))) {
    status = false;
    drawButtons(panel, status);
  }
}

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  M5.Display.fillScreen(BLACK);

  drawPanel(lightPanel);
  drawButtons(lightPanel, lightStatus);

  drawPanel(pompPanel);
  drawButtons(pompPanel, pompStatus);
}

void loop() {
  M5.update();

  handlePanelTouch(lightPanel, lightStatus);
  handlePanelTouch(pompPanel, pompStatus);
}
