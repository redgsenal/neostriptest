#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

uint32_t WHITE = strip.Color(255, 255, 255);
int c = 0;

void setup() {  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

/** 
 void loop() {
  // Some example procedures showing how to display to the pixels:
  //colorWipe(strip.Color(255, 0, 0), 1); // Red
  //colorWipe(strip.Color(0, 255, 0), 50); // Green
  //colorWipe(strip.Color(0, 0, 255), 50); // Blue
  //rainbow(20);
  //rainbowCycle(1);  
}*/

void loop() {
  clear();
  //if (c++ > 5)
  //  stopLights();
 
  starLights();
  clear();
  fiveColors();
  clear();
  kitEyes(1, 20);
  clear();
  lightAll();  
}

void stopLights(){
  clear();
  while(true){      
  }
}

void lightAll(){  
  uint32_t c = getRandomColor();
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  fadeIn();
  fadeOut();
}

void fadeOut(){
  for(uint16_t i=255; i>1; i--){
    strip.setBrightness(i);
    strip.show();
    delay(5);
  }
}

void fadeIn(){  
  for(uint16_t i=1; i<255; i++){
    strip.setBrightness(i);    
    strip.show();
    delay(5);
  }
}

void starLights(){
  uint32_t c1 = getRandomColor();
  
  for(uint16_t i=0; i<12; i++) {
    strip.setPixelColor(i, c1);
    strip.setPixelColor(i + 12, c1);
    strip.setPixelColor(i + 24, c1);
    strip.setPixelColor(i + 36, c1);
    strip.setPixelColor(i + 48, c1);
    delay(100);
    strip.show();
  }
  
  c1 = getRandomColor();
  for(uint16_t i=0; i<12; i++) {
    strip.setPixelColor(strip.numPixels() - i, c1);
    strip.setPixelColor(strip.numPixels() - (12 + i), c1);
    strip.setPixelColor(strip.numPixels() - (24 + i), c1);
    strip.setPixelColor(strip.numPixels() - (36 + i), c1);
    strip.setPixelColor(strip.numPixels() - (48 + i), c1);
    delay(100);
    strip.show();
  }
}

uint32_t getRandomColor(){
  return strip.Color(random(0, 255), random(0, 255), random(0, 255));
}

void kitEyes(uint16_t s, uint8_t wait){
  if (s < 0 || s > 5)
    s = 5;
    
  uint32_t c1 = getRandomColor();
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c1);

    uint16_t g = i - s;
    g = g < 0 ? i: g;
    strip.setPixelColor(g, 0);
    delay(wait);
    strip.show();
  }

  c1 = getRandomColor();
   for(uint16_t i=strip.numPixels(); i>0; i--) {
    strip.setPixelColor(i, c1);

    uint16_t g = i + s;
    g = g < 0 ? i: g;
    strip.setPixelColor(g, 0);
    delay(wait);
    strip.show();
  }
}
void fiveColors(){
  delay(500);
  lightStrip(0, 12, getRandomColor(), 500);
  lightStrip(12, 24, getRandomColor(), 500);
  lightStrip(24, 36, getRandomColor(), 500);
  lightStrip(36, 48, getRandomColor(), 500);
  lightStrip(48, 60, getRandomColor(), 500);
  delay(500);
  clear();
}

void clear(){
  strip.setBrightness(255);
  for(uint16_t i=0; i<strip.numPixels() ; i++) {
      strip.setPixelColor(i, 0);      
  }
  strip.show();
}

void lightStrip(uint16_t startPos, uint16_t endPos, uint32_t c, uint8_t wait){   
  endPos = (endPos > strip.numPixels()) ? strip.numPixels() : endPos;
  for(uint16_t i=startPos; i<endPos; i++) {
      strip.setPixelColor(i, c);      
  }
  strip.show();
  delay(wait);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }    
    delay(wait);
    strip.show();
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

