#include <Adafruit_NeoPixel.h>

#define pixelDataPin 6
#define numOfPixels 33

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numOfPixels, pixelDataPin, NEO_GRB + NEO_KHZ800);

const int numReadings = 5;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

int inputPin = A0;

void setup() {

  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  Serial.begin(115200);
  
  pixels.setBrightness(0);
  pixels.show();
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
  
  total = total - readings[readIndex];
  readings[readIndex] = analogRead(inputPin);
  total = total + readings[readIndex];
  readIndex = readIndex + 1;

  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  average = total / numReadings;

  int sensorMap = map(average, 0, 1023, 0, 255);


  for(int i=0;i<numOfPixels;i++){
    pixels.setPixelColor(i, pixels.Color(0,150,0));
    pixels.setBrightness(sensorMap);
    pixels.show();
    Serial.println(sensorMap);
  }  
  delay(1);
}
