#include <M5Unified.h>

void setup() {

  auto cfg = M5.config(); 
  M5.begin(cfg);

  // Achtergrond kleur van het screen aanpassen
  M5.Display.fillScreen(BLACK);

  // Textkleur instellen
  M5.Display.setTextColor(RED, BLACK);

  // TextGrootte instellen 
  M5.Display.setTextSize(4);

  //Text op het scherm zetten 
  M5.Display.setCursor(10,20);
  M5.Display.print("Hello World");

}

void loop() {
  M5.update();

}
