#include <M5Unified.h>

#include "pump_off.h"
#include "pump_on.h"
#include "window_closed.h"
#include "window_open.h"
#include "light_off.h"
#include "light_on.h"
#include "wifi_conn.h"
#include "mqtt_conn.h"
#include "panel.h"
#include "scroll.h"

// drie panelen
Panel lightPanel = { 10, 10, 300, 100, "Light", "On", "Off", "greenhouse/light/set" };
Panel pompPanel = { 10, 130, 300, 100, "Pomp", "On", "Off", nullptr };
Panel windowPanel = { 10, 250, 300, 100, "Window", "Open", "Closed", nullptr };

// Licht status
bool lightStatus = false;
bool pompStatus = false;
bool windowStatus = false;

uint16_t panelColor = 0x18E3;
uint16_t grey = 0x39C7;

M5Canvas canvas(&M5.Display);

void setup() {

  Serial.begin(115200);

  connectWifi();
  connectMqtt();

  auto cfg = M5.config();
  M5.begin(cfg);
  M5.Display.fillScreen(BLACK);

  canvas.setColorDepth(16);
  canvas.createSprite(M5.Display.width(), M5.Display.height());
  canvas.setSwapBytes(true);

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
