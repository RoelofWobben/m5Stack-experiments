#include <M5Unified.h>

const int buttonX = 160;
const int buttonY = 120;
const int buttonRadius = 50;

void drawButton(const int color) {
  M5.Display.fillScreen(BLACK);
  M5.Display.fillCircle(buttonX, buttonY, buttonRadius, color);
}

void drawButtonText(char* text) {
  M5.Display.setCursor(135, 100);
  M5.Display.setTextColor(WHITE);
  M5.Display.setTextSize(4);
  M5.Display.print(text);
}

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);

  drawButton(GREEN);
  drawButtonText("ON");
}

void loop() {
  M5.update();

  if (M5.Touch.getCount() > 0) {
    auto detail = M5.Touch.getDetail(0);

    if (detail.isPressed()) {
      int touchX = detail.x;
      int touchY = detail.y;

      int dx = touchX - buttonX;
      int dy = touchY - buttonY;

      int distanceSquared = (dx * dx) + (dy * dy);
      int radiusSquared = buttonRadius * buttonRadius;

      if (distanceSquared <= radiusSquared) {
        drawButton(RED);
        drawButtonText("OFF");
      }
    }
  }
}
