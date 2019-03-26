#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define led 13
#define peizo A0
#define threshold 1000
#define pixelDataPin 6
#define numOfPixels 16
#define redButton 2
#define greenButton 3
#define blueButton 4

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numOfPixels, pixelDataPin, NEO_GRB + NEO_KHZ800);

int peizoValue = 0;
int ledState = LOW;
int redButtonState = LOW;
int greenButtonState = LOW;
int blueButtonState = LOW;

int delayval = 500;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(redButton, INPUT_PULLUP);
  pinMode(greenButton, INPUT_PULLUP);
  pinMode(blueButton, INPUT_PULLUP);
  Serial.begin(9600);
  pixels.begin();
  
}

void loop() {
  peizoValue = analogRead(peizo);
  redButtonState = digitalRead(redButton);
  greenButtonState = digitalRead(greenButton);
  blueButtonState = digitalRead(blueButtonState);
  
  if(peizoValue >= threshold) {
    ledState = HIGH;
    digitalWrite(led, ledState);
    Serial.println("Knock " + String(peizoValue));
    for(int i=0;i<numOfPixels;i++){
        pixels.currentColor();
        pixels.show();
        delay(delayval);
     }
   }
}

void currentColor() {
  if (redButtonState = HIGH){
    for(int i=0;i<numOfPixels;i++){
        pixel.setPixelColor(i, pixel.Color(150, 0, 0)); 
    }
    strip.show();
    delay(wait);
  }
  else if (greenButtonState = HIGH){
    for(int i=0;i<numOfPixels;i++){
        pixel.setPixelColor(i, pixel.Color(0, 150, 0)); 
    }
    strip.show();
    delay(wait);
  }
  else (blueButtonState = HIGH){
    for(int i=0;i<numOfPixels;i++){
        pixel.setPixelColor(i, pixel.Color(0, 0, 150)); 
    }
    strip.show();
    delay(wait);
  }
}

void beatFade(){
  if(peizoValue > threshold){
    pixel.setBrightness(threshold);
    strip.show();
    delay(wait);
  }
  else{
    pixel.setBrightness(0);
    strip.show();
    delay(wait);
  }
}
