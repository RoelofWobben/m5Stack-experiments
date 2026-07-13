#include <M5Unified.h>

struct RectButton {
  int x, y, w, h;
  const char* label;
};

struct Panel{    
  int x, y, w, h;
  const char* label; 
};

// drie panelen
Panel lightPanel = {10,10,300,100, "Light"};
Panel pompPanel = {10,130,300,100, "Pomp"};



RectButton onButton = { panel.x + 20, panel.y + 50, 120, 40, "ON" };
RectButton offButton = { panel.x + 160, panel.y + 50, 120, 40, "OFF" };

// Licht status
bool lightStatus = false; 
bool pompStatus = false; 

uint16_t panelColor = 0x18E3;
uint16_t grey = 0x39C7;

void drawPanel(const Panel& panel) {
  M5.Display.fillRoundRect(panel.x, panel.y, panel.w, panel.h, 12, panelColor);

  M5.Display.setTextColor(WHITE, panelColor);
  M5.Display.setTextSize(2);
  M5.Display.setTextDatum(top_left);
  M5.Display.drawString(panel.label, panel.x + 20, panel.y + 15);
}

void drawPanels() {
  drawPanel(lightPanel);
  drawPanel(pompPanel); 
}

void drawSingleButton(const RectButton& button, bool isActive) {
  M5.Display.fillRect(button.x - 2, button.y - 2, button.w - 4, button.h + 4, panelColor);

  uint16_t color = isActive ? GREEN: grey;
  M5.Display.fillRoundRect(button.x, button.y, button.w, button.h, 10, color);
  

  M5.Display.setTextColor(WHITE, color);
  M5.Display.setTextSize(2);
  M5.Display.setTextDatum(middle_center);
  M5.Display.drawString(button.label, button.x + button.w / 2, button.y + button.h / 2);
}


void drawButtons() {
  //drawSingleButton(onButton, lightStatus == true);
  //drawSingleButton(offButton, lightStatus == false);
}

bool isButtonTouched(const RectButton& button) {

  if (M5.Touch.getCount() == 0) return false;

  auto detail = M5.Touch.getDetail(0);
  if (!detail.wasPressed()) return false;

  return (detail.x >= button.x && detail.x <= button.x + button.w && detail.y >= button.y && detail.y <= button.y + button.h);
}

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  M5.Display.fillScreen(BLACK);
  drawPanels();
  //drawButtons();
}

void loop() {
  M5.update();

  /*
  if (lightStatus != true && isButtonTouched(onButton)) {
    lightStatus = true;
    drawButtons();
  }

  if (lightStatus != false && isButtonTouched(offButton)) {
    lightStatus = false;
    drawButtons();
  }
  */
}
