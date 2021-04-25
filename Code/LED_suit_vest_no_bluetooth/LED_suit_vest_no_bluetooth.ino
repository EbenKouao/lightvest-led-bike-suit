/*
   Code: LightVest Remote enabled Vest
   Modified by Eben - smartbuilds.io
   Date: 22.02.21

   Description:
   LightVest to control the indicator lights (test code non-bluetooth). More info: smartbuilds.io

  Features:
  - Left
  - Right
  - Hazard
  - Rainbow

*/



// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip_back's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip_back's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip_back,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_BACK    5
#define LED_LEFT    4
#define LED_RIGHT   6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 52 // Define the number of LEDs in the strip

char state = 0; // Changes value from ASCII to char
int light_delay = 50; //How long to keep the LED on for (ms)


// Declare our NeoPixel strip_back object:
Adafruit_NeoPixel strip_back(LED_COUNT, LED_BACK, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_left(LED_COUNT, LED_LEFT, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_right(LED_COUNT, LED_RIGHT, NEO_GRB + NEO_KHZ800);


// Argument 1 = Number of pixels in NeoPixel strip_back
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


// setup() function -- runs once at startup --------------------------------

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip_back.begin();           // INITIALIZE NeoPixel strip_back object (REQUIRED)
  strip_back.show();            // Turn OFF all pixels ASAP
  strip_back.setBrightness(150); // Set BRIGHTNESS to about 1/5 (max = 255)

  strip_left.begin();           // INITIALIZE NeoPixel strip_back object (REQUIRED)
  strip_left.show();            // Turn OFF all pixels ASAP
  strip_left.setBrightness(150); // Set BRIGHTNESS to about 1/5 (max = 255)

  strip_right.begin();           // INITIALIZE NeoPixel strip_back object (REQUIRED)
  strip_right.show();            // Turn OFF all pixels ASAP
  strip_right.setBrightness(150); // Set BRIGHTNESS to about 1/5 (max = 255)

  Serial.begin(9600);
  delay(1000);
}


// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {

  //colorBlinkersLeft(strip_left.Color(255,   100,   0), 50); //Yellow
  //  colorBlinkersRight(strip_left.Color(255,   100,   0), 50); //Yellow
  //  delay(400);
  //  colorBlinkersRight(strip_left.Color(0,   0,   0), 25); //Yellow
  //  delay(300);


  rightBlink();
  delay(3000);

  leftBlink();
  delay(3000);

  sixNine();
  delay(3000);

  hazardBlink();
  delay(3000);

  //  colorWipeRight(strip_right.Color(255,   100,   0), 50); //Yellow

  //  colorWipeLeft(strip_left.Color(255,   100,   0), 50); //Yellow

}


// Some functions of our own for creating animated effects -----------------

// Fill strip_back pixels one after another with a color. strip_back is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip_back.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipeLeft(uint32_t color, int wait) {
  for (int i = 0; i < strip_left.numPixels(); i++) { // For each pixel in strip_back...
    strip_left.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip_left.show();                          //  Update strip_back to match
    delay(wait);                           //  Pause for a moment
    strip_left.clear();
  }
}

//void colorBlinkersLeft(uint32_t c, int wait) {
//  strip_left.setPixelColor(0, c);
//  strip_left.setPixelColor(1, c);
//  strip_left.setPixelColor(2, c);
//  strip_left.setPixelColor(3, c);
//  strip_left.setPixelColor(4, c);
//  strip_left.setPixelColor(5, c);
//  strip_left.setPixelColor(6, c);
//  strip_left.setPixelColor(7, c);
//
//  strip_left.show();
//  delay(wait);
//  strip_left.clear();
//}

void rightBlink() {

  for (int i = 0; i < 4; i++) { // For each pixel in strip_back...

    colorBlinkersRight(strip_left.Color(255,   100,   0), 50); //Yellow
    turnRight(strip_back.Color(255, 100, 0), 50);
    delay(400);
    colorBlinkersRight(strip_left.Color(0,   0,   0), 25); //Yellow
    turnRight(strip_back.Color(0, 0, 0), 50);
    delay(300);

  }
}

void colorBlinkersRight(uint32_t c, int wait) {

  strip_right.setPixelColor(0, c);
  strip_right.setPixelColor(1, c);
  strip_right.setPixelColor(2, c);
  strip_right.setPixelColor(3, c);
  strip_right.setPixelColor(4, c);
  strip_right.setPixelColor(5, c);
  strip_right.setPixelColor(6, c);
  strip_right.setPixelColor(7, c);
  strip_right.setPixelColor(8, c);
  strip_right.setPixelColor(9, c);
  strip_right.setPixelColor(10, c);
  strip_right.setPixelColor(11, c);
  strip_right.setPixelColor(12, c);
  strip_right.setPixelColor(13, c);
  strip_right.setPixelColor(14, c);
  strip_right.setPixelColor(15, c);
  strip_right.setPixelColor(16, c);
  strip_right.setPixelColor(17, c);
  strip_right.setPixelColor(18, c);
  strip_right.setPixelColor(19, c);
  strip_right.setPixelColor(20, c);
  strip_right.setPixelColor(21, c);
  strip_right.setPixelColor(22, c);
  strip_right.setPixelColor(23, c);
  strip_right.setPixelColor(24, c);
  strip_right.setPixelColor(25, c);
  strip_right.setPixelColor(26, c);
  strip_right.setPixelColor(27, c);
  strip_right.setPixelColor(28, c);

  strip_right.show();
  delay(wait);
  strip_right.clear();
  delay(wait);

}


void sixNine() {
  rainbow_back(10);
}


void hazardBlink() {

  for (int i = 0; i < 4; i++) { // For each pixel in strip_back...

    colorBlinkersLeft(strip_left.Color(255,   100,   0), 50); //Yellow
    colorBlinkersRight(strip_right.Color(255,   100,   0), 50); //Yellow
    colorBlinkersHazard(strip_back.Color(255, 100, 0), 50); //for back

    delay(400);
    colorBlinkersLeft(strip_left.Color(0,   0,   0), 25); //Yellow
    colorBlinkersRight(strip_right.Color(0,   0,   0), 50); //Yellow
    colorBlinkersHazard(strip_back.Color(0, 0, 0), 50); //for back


    delay(300);

  }
}


void leftBlink() {

  for (int i = 0; i < 4; i++) { // For each pixel in strip_back...

    colorBlinkersLeft(strip_left.Color(255,   100,   0), 50); //Yellow
    turnLeft(strip_back.Color(255, 100, 0), 50); //for back
    delay(400);
    colorBlinkersLeft(strip_left.Color(0,   0,   0), 25); //Yellow
    turnLeft(strip_back.Color(0, 0, 0), 50); //for back

    delay(300);

  }
}

void colorBlinkersLeft(uint32_t c, int wait) {



  strip_left.setPixelColor(0, c);
  strip_left.setPixelColor(1, c);
  strip_left.setPixelColor(2, c);
  strip_left.setPixelColor(3, c);
  strip_left.setPixelColor(4, c);
  strip_left.setPixelColor(5, c);
  strip_left.setPixelColor(6, c);
  strip_left.setPixelColor(7, c);
  strip_left.setPixelColor(8, c);
  strip_left.setPixelColor(9, c);
  strip_left.setPixelColor(10, c);
  strip_left.setPixelColor(11, c);
  strip_left.setPixelColor(12, c);
  strip_left.setPixelColor(13, c);
  strip_left.setPixelColor(14, c);
  strip_left.setPixelColor(15, c);
  strip_left.setPixelColor(16, c);
  strip_left.setPixelColor(17, c);
  strip_left.setPixelColor(18, c);
  strip_left.setPixelColor(19, c);
  strip_left.setPixelColor(20, c);
  strip_left.setPixelColor(21, c);
  strip_left.setPixelColor(22, c);
  strip_left.setPixelColor(23, c);
  strip_left.setPixelColor(24, c);
  strip_left.setPixelColor(25, c);
  strip_left.setPixelColor(26, c);
  strip_left.setPixelColor(27, c);
  strip_left.setPixelColor(28, c);

  strip_left.show();
  delay(wait);
  strip_left.clear();
  delay(wait);

}


void colorBlinkersHazard(uint32_t c, int wait) {

  strip_back.setPixelColor(0, c);
  strip_back.setPixelColor(1, c);
  strip_back.setPixelColor(2, c);
  strip_back.setPixelColor(3, c);
  strip_back.setPixelColor(4, c);
  strip_back.setPixelColor(5, c);
  strip_back.setPixelColor(6, c);
  strip_back.setPixelColor(7, c);

  strip_back.setPixelColor(24, c);
  strip_back.setPixelColor(25, c);
  strip_back.setPixelColor(26, c);
  strip_back.setPixelColor(27, c);
  strip_back.setPixelColor(28, c);
  strip_back.setPixelColor(29, c);
  strip_back.setPixelColor(30, c);
  strip_back.setPixelColor(31, c);


  strip_back.setPixelColor(32, c);
  strip_back.setPixelColor(33, c);
  strip_back.setPixelColor(34, c);
  strip_back.setPixelColor(35, c);
  strip_back.setPixelColor(36, c);
  strip_back.setPixelColor(37, c);
  strip_back.setPixelColor(38, c);
  strip_back.setPixelColor(39, c);
  strip_back.setPixelColor(40, c);
  strip_back.setPixelColor(41, c);
  strip_back.setPixelColor(42, c);
  strip_back.setPixelColor(43, c);
  strip_back.setPixelColor(44, c);

  strip_back.setPixelColor(8, c);
  strip_back.setPixelColor(9, c);
  strip_back.setPixelColor(10, c);
  strip_back.setPixelColor(11, c);
  strip_back.setPixelColor(12, c);
  strip_back.setPixelColor(13, c);
  strip_back.setPixelColor(14, c);
  strip_back.setPixelColor(15, c);

  strip_back.setPixelColor(16, c);
  strip_back.setPixelColor(17, c);
  strip_back.setPixelColor(18, c);
  strip_back.setPixelColor(19, c);
  strip_back.setPixelColor(20, c);
  strip_back.setPixelColor(21, c);
  strip_back.setPixelColor(22, c);
  strip_back.setPixelColor(23, c);


  strip_back.setPixelColor(32, c);
  strip_back.setPixelColor(33, c);
  strip_back.setPixelColor(34, c);
  strip_back.setPixelColor(35, c);
  strip_back.setPixelColor(36, c);
  strip_back.setPixelColor(37, c);
  strip_back.setPixelColor(38, c);
  strip_back.setPixelColor(39, c);
  strip_back.setPixelColor(40, c);
  strip_back.setPixelColor(41, c);
  strip_back.setPixelColor(42, c);
  strip_back.setPixelColor(43, c);
  strip_back.setPixelColor(44, c);



  strip_back.show();
  delay(wait);
  strip_back.clear();
  delay(wait);

}


void colorWipeRight(uint32_t color, int wait) {
  for (int i = 0; i < strip_right.numPixels(); i++) { // For each pixel in strip_back...
    strip_right.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip_right.show();                          //  Update strip_back to match
    delay(wait);                           //  Pause for a moment
    strip_right.clear();
  }
}


//1st - 0 - 7
//2nd - 8 - 15
//3rd - 16 - 23
//4th - 23 - 31
//long - 32 -44

// Fill the dots one after the other with a color
void turnRight(uint32_t c, uint8_t wait) {

  strip_back.setPixelColor(0, c);
  strip_back.setPixelColor(1, c);
  strip_back.setPixelColor(2, c);
  strip_back.setPixelColor(3, c);
  strip_back.setPixelColor(4, c);
  strip_back.setPixelColor(5, c);
  strip_back.setPixelColor(6, c);
  strip_back.setPixelColor(7, c);

  strip_back.setPixelColor(24, c);
  strip_back.setPixelColor(25, c);
  strip_back.setPixelColor(26, c);
  strip_back.setPixelColor(27, c);
  strip_back.setPixelColor(28, c);
  strip_back.setPixelColor(29, c);
  strip_back.setPixelColor(30, c);
  strip_back.setPixelColor(31, c);


  strip_back.setPixelColor(32, c);
  strip_back.setPixelColor(33, c);
  strip_back.setPixelColor(34, c);
  strip_back.setPixelColor(35, c);
  strip_back.setPixelColor(36, c);
  strip_back.setPixelColor(37, c);
  strip_back.setPixelColor(38, c);
  strip_back.setPixelColor(39, c);
  strip_back.setPixelColor(40, c);
  strip_back.setPixelColor(41, c);
  strip_back.setPixelColor(42, c);
  strip_back.setPixelColor(43, c);
  strip_back.setPixelColor(44, c);

  strip_back.show();
  delay(wait);
  strip_back.clear();


}


// Fill the dots one after the other with a color
void turnLeft(uint32_t c, uint8_t wait) {

  strip_back.setPixelColor(8, c);
  strip_back.setPixelColor(9, c);
  strip_back.setPixelColor(10, c);
  strip_back.setPixelColor(11, c);
  strip_back.setPixelColor(12, c);
  strip_back.setPixelColor(13, c);
  strip_back.setPixelColor(14, c);
  strip_back.setPixelColor(15, c);

  strip_back.setPixelColor(16, c);
  strip_back.setPixelColor(17, c);
  strip_back.setPixelColor(18, c);
  strip_back.setPixelColor(19, c);
  strip_back.setPixelColor(20, c);
  strip_back.setPixelColor(21, c);
  strip_back.setPixelColor(22, c);
  strip_back.setPixelColor(23, c);


  strip_back.setPixelColor(32, c);
  strip_back.setPixelColor(33, c);
  strip_back.setPixelColor(34, c);
  strip_back.setPixelColor(35, c);
  strip_back.setPixelColor(36, c);
  strip_back.setPixelColor(37, c);
  strip_back.setPixelColor(38, c);
  strip_back.setPixelColor(39, c);
  strip_back.setPixelColor(40, c);
  strip_back.setPixelColor(41, c);
  strip_back.setPixelColor(42, c);
  strip_back.setPixelColor(43, c);
  strip_back.setPixelColor(44, c);


  strip_back.show();
  delay(wait);
  strip_back.clear();


}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for (int a = 0; a < 30; a++) { // Repeat 30 times...
    for (int b = 0; b < 3; b++) { //  'b' counts from 0 to 2...
      strip_back.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip_back in increments of 3...
      for (int c = b; c < strip_back.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip_back (strip_back.numPixels() steps):
        int hue   = firstPixelHue + c * 65536L / strip_back.numPixels();
        uint32_t color = strip_back.gamma32(strip_back.ColorHSV(hue)); // hue -> RGB
        strip_back.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip_back.show();                // Update strip_back with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}


// Rainbow cycle along whole strip_back. Pass delay time (in ms) between frames.
void rainbow_back(int wait) {

  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < strip_back.numPixels(); i++) { // For each pixel in strip_back...

      int pixelHue = firstPixelHue + (i * 65536L / strip_back.numPixels());

      strip_back.setPixelColor(i, strip_back.gamma32(strip_back.ColorHSV(pixelHue)));
      strip_left.setPixelColor(i, strip_right.gamma32(strip_right.ColorHSV(pixelHue)));
      strip_right.setPixelColor(i, strip_right.gamma32(strip_right.ColorHSV(pixelHue)));


    }
    strip_back.show(); // Update strip_back with new contents
    strip_left.show(); // Update strip_back with new contents
    strip_right.show(); // Update strip_back with new contents


    delay(wait);  // Pause for a moment
  }
}


// Rainbow cycle along whole strip_back. Pass delay time (in ms) between frames.
void rainbow_left(int wait) {

  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < strip_left.numPixels(); i++) { // For each pixel in strip_back...

      int pixelHue = firstPixelHue + (i * 65536L / strip_back.numPixels());

      strip_left.setPixelColor(i, strip_left.gamma32(strip_left.ColorHSV(pixelHue)));
    }
    strip_left.show(); // Update strip_back with new contents
    delay(wait);  // Pause for a moment
  }
}


// Rainbow cycle along whole strip_back. Pass delay time (in ms) between frames.
void rainbow_right(int wait) {

  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < strip_right.numPixels(); i++) { // For each pixel in strip_back...

      int pixelHue = firstPixelHue + (i * 65536L / strip_right.numPixels());

      strip_right.setPixelColor(i, strip_right.gamma32(strip_right.ColorHSV(pixelHue)));
    }
    strip_right.show(); // Update strip_back with new contents
    delay(wait);  // Pause for a moment
  }
}


void colorShow(uint32_t color, int wait) {
  for (int i = 0; i < strip_back.numPixels(); i++) { // For each pixel in strip_back...
    strip_back.setPixelColor(i, color);         //  Set pixel's color (in RAM)
  }
  strip_back.show();                          //  Update strip_back to match
  //delay(wait);                           //  Pause for a moment
  strip_back.clear();

}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip_back.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for (int a = 0; a < 10; a++) { // Repeat 10 times...
    for (int b = 0; b < 3; b++) { //  'b' counts from 0 to 2...
      strip_back.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip_back in steps of 3...
      for (int c = b; c < strip_back.numPixels(); c += 3) {
        strip_back.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip_back.show(); // Update strip_back with new contents
      delay(wait);  // Pause for a moment
      strip_back.clear();

    }
  }
}

void clearLights() {
  strip_left.clear();
  strip_right.clear();
  strip_back.clear();
}
