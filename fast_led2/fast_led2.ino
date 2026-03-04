#include <FastLED.h>
#define NUM_LEDS 8
#define DATA_PIN 6
#define BRIGHTNESS 64

int red = 0;
int green = 0;
int blue = 0;
CRGB leds[NUM_LEDS];


void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  for (int j = 0; j < 256 * 5; j++)
  {
    for (int i = 0; i < 8; i++)
    {
      Wheel(((i * 256 / 8) + j)%255);
      leds[i] = CRGB(red, green, blue);
    }
    FastLED.show();
    delay(10);
  }
}


void Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    red = 255 - WheelPos * 3;
    green = 0;
    blue = WheelPos * 3;
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    red = 0;
    green = WheelPos * 3;
    blue = 255 - WheelPos * 3;
  }
  else {
    WheelPos -= 170;
    red = WheelPos * 3;
    green = 255 - WheelPos * 3;
    blue = 0;
  }
}