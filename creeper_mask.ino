#include "Adafruit_NeoPixel.h"
#include "Ultrasonic.h"

Ultrasonic ultrasonic(2); 
int dist_cm = 0;

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            6
#define NUMPIXELS      22
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pixels.begin(); 
  pixels.setBrightness(250);
}

void loop() {
jj_monster(ultrasonic.MeasureInCentimeters()); 
}
/*****void jj_monster(uint8_t dist)*****/
void jj_monster(uint8_t dist) {
  uint8_t brightness,delaytime; 
  Serial.println(dist);
   if (dist >= 170) {
    brightness = 50;
    delaytime = 1;
    breath(delaytime,brightness);
  } 
  if (dist >= 70 && dist < 170) {
    brightness = 250;
    delaytime = 0;
    breath(delaytime,brightness);
  } 
  if (dist < 70 && dist > 2 ) {
    breath_red(0,250);
  }
}
/**************************************/
void breath(uint16_t delaytime, uint16_t brightness) {
    pixels.setBrightness(brightness);
    for(uint16_t i=0;i<512;i++){
      for(uint16_t j=0;j< pixels.numPixels();j++) {
        pixels.setPixelColor(j,triangular_color(i));
      }
    pixels.show();
    delay(delaytime);
  }
 }

void breath_red(uint16_t delaytime, uint16_t brightness) {
    pixels.setBrightness(brightness);
    for(uint16_t i=0;i<512;i++){
      for(uint16_t j=0;j< pixels.numPixels();j++) {
        pixels.setPixelColor(j,triangular_color_red(i));
      }
    pixels.show();
    delay(delaytime);
  }
 }


uint32_t triangular_color(uint32_t t) {
  uint32_t c = 0;
  if (t < 256) {
    c = pixels.Color(t, t, t);
  } else if (t < 512) {
    c = pixels.Color(511-t, 511-t, 511-t);
  }
  return c;
}

uint32_t triangular_color_red(uint32_t t) {
  uint32_t c = 0;
  if (t < 256) {
    c = pixels.Color(t, 0, 0);
  } else if (t < 512) {
    c = pixels.Color(511-t, 0, 0);
  }
  return c;
}
