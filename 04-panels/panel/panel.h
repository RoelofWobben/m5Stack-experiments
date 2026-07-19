#pragma once 

#include <M5Unified.h>

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

extern M5Canvas canvas;
extern int scrollOffSet;
extern uint16_t panelColor; 
extern uint16_t grey;

void drawPanel(const Panel& panel, const uint16_t* icon, bool status);
void drawSingleButton(const RectButton& button, bool isActive);
void drawButtons(const Panel& panel, bool status);
bool isButtonTouched(const RectButton& button);
void handlePanelTouch(const Panel& panel, bool& status, const uint16_t* iconOn, const uint16_t* iconOff);
void publishStatus(const Panel& panel, bool status);
void drawPanels();
void flush();