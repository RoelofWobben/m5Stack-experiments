#include "mqtt_conn.h"
#include <Adafruit_NeoPixel.h>
#include "leds.h"
#include "constants.h" 

extern PubSubClient mqttClient; 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);


void initLeds(){
  
  strip.setBrightness(255);
  strip.begin();
  strip.show();
  Serial.println("LEDS initialized");
}

void turnLightOn(){
  
  for(int i = 0; i < NUM_PIXELS; i++) {
    strip.setPixelColor(i, strip.Color(255,0,0));
    
  }
  strip.show();
  mqttClient.publish("greenhouse/light/status", "ON");
}


void turnLightOff() {
  
  for(int i = 0; i < NUM_PIXELS; i++) {
    strip.setPixelColor(i, strip.Color(0,0,0));
  }
  strip.show(); 
  mqttClient.publish("greenhouse/light/status", "OFF");
}
