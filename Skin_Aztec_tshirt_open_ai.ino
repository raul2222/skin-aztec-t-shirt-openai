#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Vector.h>
// Choose your prefered pixmap
//#include "heart24.h"
//#include "yellowsmiley24.h"
//#include "bluesmiley24.h"
#include "smileytongue24.h"
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif
#define PIN 4

#define BM32

#ifdef BM32
#include "google32.h"
// Anything with black does not look so good with the naked eye (better on pictures)
//#include "linux32.h"
#endif

const int ELEMENT_COUNT_MAX = 2000; //
typedef Vector<uint16_t> Elements;
const size_t DELAY = 180;
long randNumber;
Elements bitmap;
Elements vector;
int BRIGHTNESS = 4;

#define mw 32
#define mh 16
Adafruit_NeoMatrix *matrix = new Adafruit_NeoMatrix(32, 8, 
  1, 2, 
  PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
    NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG + 
// progressive vs zigzag makes no difference for a 4 arrays next to one another
    NEO_TILE_TOP + NEO_TILE_LEFT +  NEO_TILE_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800 );

#define LED_BLACK		0

#define LED_RED_VERYLOW 	(3 <<  11)
#define LED_RED_LOW 		(7 <<  11)
#define LED_RED_MEDIUM 		(15 << 11)
#define LED_RED_HIGH 		(31 << 11)

#define LED_GREEN_VERYLOW	(1 <<  5)   
#define LED_GREEN_LOW 		(15 << 5)  
#define LED_GREEN_MEDIUM 	(31 << 5)  
#define LED_GREEN_HIGH 		 (63 << 5) 

#define LED_BLUE_VERYLOW	3
#define LED_BLUE_LOW 		7
#define LED_BLUE_MEDIUM 	15
#define LED_BLUE_HIGH 		31

#define LED_ORANGE_VERYLOW	(LED_RED_VERYLOW + LED_GREEN_VERYLOW)
#define LED_ORANGE_LOW		(LED_RED_LOW     + LED_GREEN_LOW)
#define LED_ORANGE_MEDIUM	(LED_RED_MEDIUM  + LED_GREEN_MEDIUM)
#define LED_ORANGE_HIGH		(LED_RED_HIGH    + LED_GREEN_HIGH)

#define LED_PURPLE_VERYLOW	(LED_RED_VERYLOW + LED_BLUE_VERYLOW)
#define LED_PURPLE_LOW		(LED_RED_LOW     + LED_BLUE_LOW)
#define LED_PURPLE_MEDIUM	(LED_RED_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_PURPLE_HIGH		(LED_RED_HIGH    + LED_BLUE_HIGH)

#define LED_CYAN_VERYLOW	(LED_GREEN_VERYLOW + LED_BLUE_VERYLOW)
#define LED_CYAN_LOW		(LED_GREEN_LOW     + LED_BLUE_LOW)
#define LED_CYAN_MEDIUM		(LED_GREEN_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_CYAN_HIGH		(LED_GREEN_HIGH    + LED_BLUE_HIGH)

#define LED_WHITE_VERYLOW	(LED_RED_VERYLOW + LED_GREEN_VERYLOW + LED_BLUE_VERYLOW)
#define LED_WHITE_LOW		(LED_RED_LOW     + LED_GREEN_LOW     + LED_BLUE_LOW)
#define LED_WHITE_MEDIUM	(LED_RED_MEDIUM  + LED_GREEN_MEDIUM  + LED_BLUE_MEDIUM)

#define LED_WHITE_HIGH		(LED_RED_HIGH    + LED_GREEN_HIGH    + LED_BLUE_HIGH)


void loop() {
  
}


void linegen(){
  uint16_t storage_array[ELEMENT_COUNT_MAX];
  
  vector.setStorage(storage_array);
  int color = 1;
  int ant1 =0;
  int ant2 = 0;
 
  for (size_t i=0; i<vector.max_size()/2; ++i){
    randomSeed(analogRead(13));
    randNumber = random(1, 3);
    if(ant2 == ant1 and ant2 == randNumber){
      if (randNumber == 2){
        randNumber = 1;
      } else {
        randNumber = 2;
      }
    }
    ant2 = ant1;
    ant1 = randNumber;
    if(randNumber == 2) {
      color = LED_WHITE_HIGH;
    } else {
      color = 2016;
    }
    randomSeed(analogRead(13));
    randN umber = random(5, 15);

    for (int x=0; x<randNumber; x++){
      vector.push_back(color);
    }    
    randomSeed(analogRead(13));
    randNumber = random(2, 3);

    for (int x=0; x<randNumber; x++){
      vector.push_back(0);
    }    
  }

  uint16_t storage_array2[32*16];
  bitmap.setStorage(storage_array2);

  for (int x = 0; x< 1500 ; x++){
    static uint16_t *RGB_bmp_fixed = (uint16_t *) malloc( 32*16*2);
    for (int i = 0; i< 32 ; i++){
      RGB_bmp_fixed[i] =vector[i+x];   
    }
    for (int i = 32; i< 64 ; i++){
      RGB_bmp_fixed[i] =0;
      RGB_bmp_fixed[i+32] =0;
    }
    for (int i = 96; i< 128 ; i++){
      RGB_bmp_fixed[i] =vector[(x+166)-i];
    }
    for (int i = 128; i< 160 ; i++){
      RGB_bmp_fixed[i] =0;
      RGB_bmp_fixed[i+32] =0;
    }
    for (int i = 192; i< 224 ; i++){
      RGB_bmp_fixed[i] =vector[i+x];   
    }
    for (int i = 224; i< 256 ; i++){
      RGB_bmp_fixed[i] =0;
      RGB_bmp_fixed[i+32] =0;
    }
    for (int i = 288; i< 320 ; i++){ 
      RGB_bmp_fixed[i] =vector[(x+366)-i];
    }
    for (int i = 320; i< 352 ; i++){
      RGB_bmp_fixed[i] =0;
      RGB_bmp_fixed[i+32] =0;
    }
    for (int i = 384; i< 416 ; i++){
      RGB_bmp_fixed[i] =vector[i+x];
    }
    for (int i = 416; i< 448 ; i++){
      RGB_bmp_fixed[i] =0;
      RGB_bmp_fixed[i+32] =0;
    }
    for (int i = 480; i< 512 ; i++){
      RGB_bmp_fixed[i] =vector[(x+522)-i];
    }
    for (int i = 512; i< (32*16) ; i++){ 
      RGB_bmp_fixed[i] =0;
    }

    delay(DELAY);
    if (BRIGHTNESS < 40){ matrix->setBrightness(BRIGHTNESS++);}
    uint16_t xi = 0;
    uint16_t yi = 0;
    uint16_t w = 32;
    uint16_t h = 16;
    matrix->drawRGBBitmap(xi, yi,RGB_bmp_fixed, w, h);
    matrix->show();
  }
}

void printvector(){
  Serial.print("[");
  for (size_t i=0; i<vector.size(); ++i)
  {
    if (i != 0)
    {
      Serial.print(",");
    }
    Serial.print(vector[i]);
  }
  Serial.print("]");
}

void setup() {
  Serial.begin(115200);
  matrix->begin();
  matrix->setTextWrap(false);
  matrix->setBrightness(BRIGHTNESS);

  matrix->clear();
  linegen();
  matrix->clear();
  Serial.println("fin");
}


void display_boxes() {
    matrix->clear();
    matrix->drawRect(0,0, mw,mh, LED_BLUE_HIGH);
    matrix->drawRect(1,1, mw-2,mh-2, LED_GREEN_MEDIUM);
    matrix->fillRect(2,2, mw-4,mh-4, LED_RED_HIGH);
    matrix->fillRect(3,3, mw-6,mh-6, LED_ORANGE_MEDIUM);
    matrix->show();
}

void display_circles() {
    matrix->clear();
    matrix->drawCircle(mw/2,mh/2, 2, LED_RED_MEDIUM);
    matrix->drawCircle(mw/2-1-min(mw,mh)/8, mh/2-1-min(mw,mh)/8, min(mw,mh)/4, LED_BLUE_HIGH);
    matrix->drawCircle(mw/2+1+min(mw,mh)/8, mh/2+1+min(mw,mh)/8, min(mw,mh)/4-1, LED_ORANGE_MEDIUM);
    matrix->drawCircle(1,mh-2, 1, LED_GREEN_LOW);
    matrix->drawCircle(mw-2,1, 1, LED_GREEN_HIGH);
    if (min(mw,mh)>12) matrix->drawCircle(mw/2-1, mh/2-1, min(mh/2-1,mw/2-1), LED_CYAN_HIGH);
    matrix->show();
}
