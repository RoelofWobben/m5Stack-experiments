#include <M5Unified.h>

void display_Hello_World() {
  //Text op het scherm zetten
  M5.Display.setCursor(10, 20);
  M5.Display.print("Hello World");
}

void setup() {

  auto cfg = M5.config();
  M5.begin(cfg);
  display_Hello_World(); 
}

void loop() {}
