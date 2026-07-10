
#include <M5Unified.h>

// --- Lamp icoon (32x32, mono 1-bit) ---
const int lightIcon_width = 32;
const int lightIcon_height = 32;
const unsigned char lightIcon[] PROGMEM = {
  0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9f, 0x3f, 0x7f, 0xff,
  0xff, 0xff, 0xff, 0x7f, 0x61,
  0x61, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x9f, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x00, 0x00,
  0x00, 0x00, 0xff, 0xbf, 0xbf, 0xbf, 0xbf, 0xff, 0xff, 0x0f, 0x63,
  0xd9, 0xc4, 0xf2, 0xfa, 0xfa,
  0xfe, 0xfe, 0xfe, 0xfc, 0xf9, 0xe3, 0x0f, 0xff, 0xff, 0xbf, 0xbf,
  0xbf, 0xbf, 0xff, 0x00, 0x00,
  0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x9f, 0xce, 0xf8,
  0xf3, 0x87, 0x1f, 0x7f, 0x7f,
  0x7f, 0x7f, 0x3f, 0x0f, 0xf3, 0xf8, 0xce, 0x9f, 0x3f, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x00, 0x00,
  0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xf5, 0xd5, 0x95,
  0x95, 0xd5, 0xf5, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0x00, 0x00
};

struct RoundButton {
  int x;
  int y;
  int radius;
  bool status;
};

RoundButton lightButton = { 160, 120, 60, true };

void drawButtonCircle(const RoundButton& button) {
  if (button.status) {
    M5.Display.fillCircle(button.x, button.y, button.radius, GREEN);
  } else {
    M5.Display.fillCircle(button.x, button.y, button.radius, RED);
  }
}

void drawButtonIcon(const RoundButton& button) {
  // icoon iets links van het midden, verticaal gecentreerd
  int iconX = button.x - 20;
  int iconY = button.y - (lightIcon_height / 2);

  M5.Display.drawBitmap(iconX, iconY, lightIcon, lightIcon_width,
                        lightIcon_height, WHITE);
}

void drawButtonText(const RoundButton& button) {
  M5.Display.setTextColor(WHITE);
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
