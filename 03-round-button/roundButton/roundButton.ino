#include <M5Unified.h>

struct RoundButton {
  int x; 
  int y; 
  int radius; 
  bool status; 
};

RoundButton lightButton = {160,120,50, true};  

void drawButtonCircle(const RoundButton& button) {
  if (button.status) {
    M5.Display.fillCircle(button.x, button.y, button.radius, GREEN); 
  } else {
    M5.Display.fillCircle(button.x, button.y, button.radius, RED);
  }
}

void drawButtonText(const RoundButton& button) {
  M5.Display.setTextColor(WHITE);
  M5.Display.setTextSize(4);
  M5.Display.setTextDatum(MC_DATUM);
  
  if (button.status) {
    M5.Display.drawString("ON", button.x, button.y);
  } else{
    M5.Display.drawString("OFF", button.x, button.y);
  }
}

void drawButton(const RoundButton& button) {
  M5.Display.fillScreen(BLACK);

  drawButtonCircle(button);
  drawButtonText(button);
}

bool isButtonTouched(const RoundButton& button) {

  if(M5.Touch.getCount() == 0) {
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