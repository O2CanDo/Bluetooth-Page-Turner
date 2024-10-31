
#include <Arduino.h>
#include <BleKeyboard.h>

// to do: define pins

BleKeyboard blePageTurner;

void setup() {
  Serial.begin(115200);
  blePageTurner.begin();
  Serial.println("Setup successful.");
}

void loop() {
  
}


