#include <FastLED.h>

#define LED_PIN     6
#define NUM_LEDS    6
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType currentBlending;

const int piezoPin = A0;
const int lowThresholdPin = A1;
const int highThresholdPin = A2;
const int sustainPin = A3;
const int buttonPin = 2;

const int pixelGroup1[] = {1, 2, 5, 6};
const int pixelGroup3[] = {1, 2, 3, 4, 5, 6};

int switchState = 0;
int switchCount = 0;

uint8_t piezoValue = (analogRead(piezoPin) / 2);
uint8_t lowTheshold = (analogRead(lowThresholdPin) / 4);
uint8_t highThreshold = (analogRead(highThresholdPin) / 4);
uint8_t sustainValue = (analogRead(sustainPin) / 4);

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(0);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {

  if(piezoValue > lowTheshold){
    ledsOn(pixelGroup1);
  }
  else if(piezoValue > highThreshold){
    currentEffect();
    ledsOn(pixelGroup3);
  }
  else{
    sustainFade();
    midiWrite();
  }
}

void ledsOn(int pixelGroup[]){
  for(int i=0; i<sizeof(pixelGroup); i++){
    FastLED.setBrightness(piezoValue);
    sustainFade();
    delay(1);
  }
  midiWrite();
}


void sustainFade(){
  while(piezoValue > 0){
    FastLED.setBrightness(piezoValue - sustainValue);
    delay(sustainValue);
  }
  midiWrite();
}

void currentEffect(){
  switchState = digitalRead(buttonPin);
  if(switchState == LOW){
    switchCount++;
  }

  switch(switchCount){
    case 0:
      for(int i=0; i<sizeof(pixelGroup3); i++){
        FastLED.setBrightness(0);
        }
        delay(1);
      break;
    case 1:
      for(int i=0; i<sizeof(pixelGroup3); i++){
        FastLED.setBrightness(0);
        leds[i] = CRGB( 100, 0, 0);
        }
        delay(1);
      break;
    case 2:
      for(int i=0; i<sizeof(pixelGroup3); i++){
        FastLED.setBrightness(0);
        leds[i] = CRGB( 0, 100, 0);
        }
        delay(1);
      break;
    case 3:
      for(int i=0; i<sizeof(pixelGroup3); i++){
        FastLED.setBrightness(0);
        leds[i] = CRGB( 0, 0, 100);
        }
        delay(1);
      break;
  }
  delay(1);
}

void midiRead(){
}

void midiWrite(){
}
