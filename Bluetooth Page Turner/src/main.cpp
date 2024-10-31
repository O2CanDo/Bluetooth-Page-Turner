


#include <Arduino.h>
#include <BleKeyboard.h>

const int INPUT_LEFT = 16;
const int INPUT_RIGHT = 17;


BleKeyboard blePageTurner;



void setup() {
  pinMode(INPUT_LEFT, INPUT_PULLUP);
  pinMode(INPUT_RIGHT, INPUT_PULLUP);

  Serial.begin(115200);
  blePageTurner.begin();
  Serial.print("\nSetup successful for version: V1 ");
 
}

void loop() {
  
  if(blePageTurner.isConnected()) {
    Serial.println("connection successful");

    if(digitalRead(INPUT_LEFT) == LOW){
      Serial.println("left pressed");
      blePageTurner.write(KEY_LEFT_ARROW);
    }
    if (digitalRead(INPUT_RIGHT) == LOW) {
      Serial.println("right pressed");
      blePageTurner.write(KEY_RIGHT_ARROW);
    }
  }
  delay(500);
}
  



