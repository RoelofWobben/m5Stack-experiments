
#include <M5Unified.h>
#include "light_off.h"
#include "light_on.h"

const int lightIcon_width  = 32;
const int lightIcon_height = 32;

struct RoundButton {
  int x;
  int y;
  int radius;
  bool status;
};

RoundButton lightButton = { 160, 120, 40, true };

void drawButtonCircle(const RoundButton& button) {
  if (button.status) {
    M5.Display.fillCircle(button.x, button.y, button.radius, GREEN);
  } else {
    M5.Display.fillCircle(button.x, button.y, button.radius, RED);
  }
}

void drawButtonIcon(const RoundButton& button) {
  // icoon iets links van het midden, verticaal gecentreerd
  
   M5.Display.setSwapBytes(true); 
   M5.Display.pushImage(120,100,32,32,lightIcon, 0xFFFF);
}

void drawButtonText(const RoundButton& button) {
  M5.Display.setTextColor(BLACK);
  M5.Display.setTextSize(2);
  M5.Display.setTextDatum(MC_DATUM);

  // tekst iets rechts van het midden, naast het icoon
  int textX = button.x + 15;

  if (button.status) {
    M5.Display.drawString("ON", textX, button.y);
  } else {
    M5.Display.drawString("OFF", textX, button.y);
  }
}

void drawButton(const RoundButton& button) {
  M5.Display.fillScreen(BLACK);

  drawButtonCircle(button);
  drawButtonIcon(button);
  drawButtonText(button);
}



void drawButtonIcon(const RoundButton& button) {
  M5.Display.setSwapBytes(true);
  if (button.status) {
    M5.Display.pushImage(120, 100, 32, 32, lightIconOn, 0xFFFF);
  } else {
    M5.Display.pushImage(120, 100, 32, 32, lightIcon, 0xFFFF);
  }
}

bool isButtonTouched(const RoundButton& button) {

  if (M5.Touch.getCount() == 0) {
    return false;
  }

  auto detail = M5.Touch.getDetail(0);

  if (!detail.wasPressed()) {
    return false;
  }

  int dx = detail.x - button.x;
  int dy = detail.y - button.y;

  int distanceSquared = (dx * dx) + (dy * dy);
  int radiusSquared = button.radius * button.radius;

  return distanceSquared <= radiusSquared;
}


void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);

  drawButton(lightButton);
}

void loop() {
  M5.update();

  if (isButtonTouched(lightButton)) {
    lightButton.status = !lightButton.status;
    drawButton(lightButton);
  }
}
