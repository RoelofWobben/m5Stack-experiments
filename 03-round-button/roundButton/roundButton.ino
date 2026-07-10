#include <M5Unified.h>

struct roundButton {
  int x; 
  int y; 
  int radius; 
  bool status; 
}

roundButton lightButton = {160,120,50, true};  

void drawButtonCircle(bool state) {
  if (state) {
    M5.Display.fillCircle(lightButton.x, ightButton.y, lightButton.radius, GREEN); 
  } else {
    M5.Display.fillCircle(lightButton.x, lightButton.y, lightButton.radius, RED);
  }
}
/*
void drawButtonText(bool state) {
  M5.Display.setTextColor(WHITE);
  M5.Display.setTextSize(4);
  M5.Display.setTextDatum(MC_DATUM);
  
  if (state) {
    M5.Display.drawString("ON", buttonX, buttonY);
  } else{
    M5.Display.drawString("OFF", buttonX, buttonY);
  }
}

void drawButton() {
  M5.Display.fillScreen(BLACK);

  drawButtonCircle(buttonState);
  drawButtonText(buttonState);
}

bool isButtonTouched() {

  if(M5.Touch.getCount() == 0) {
    return false; 
  }

  auto detail = M5.Touch.getDetail(0);

  if (!detail.wasPressed()) {
    return false; 
  }

  int dx = detail.x - buttonX; 
  int dy = detail.y - buttonY; 

  int distanceSquared = (dx * dx) + (dy * dy);
  int radiusSquared = buttonRadius * buttonRadius; 

  return distanceSquared <= radiusSquared; 
}
*/

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);

  //drawButton();
}

void loop() {
  M5.update();

  //if (isButtonTouched()) {
  //  buttonState = !buttonState; 
  //  drawButton(); 
  //}   
}