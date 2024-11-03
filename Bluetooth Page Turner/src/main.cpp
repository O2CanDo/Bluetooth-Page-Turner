/**
 * current issues:
 * - reconnect ignores new device if previous device has bluetooth on
 * - return values for customDisconnect/Reconnect only placeholder
 * - pairing input button usually pressed over multiple cycles -> input issues
 */

#include <Arduino.h>
#include <BleKeyboard.h>

#include <NimBLEDevice.h>

// pin alias defines
#define INPUT_LEFT 16
#define INPUT_RIGHT 17
#define INPUT_PAIRING 26


BleKeyboard devicePageShift;


void customDisconnect()
{
  // get pointer to server
  NimBLEServer* pServer =  NimBLEDevice::getServer();
      

  // get pointer to client and connID
  NimBLEDevice::getClientListSize();
  //std::list<NimBLEDevice*>* pClientList = (devicePageShift.hid->getClientList());   // get client list
  //NimBLEClient* pClient = nullptr;    // placeholder, assign client from list or else ESP panics
  //uint16_t connID = pClient->getConnId();
  uint16_t connID = 0;    // hard coded id for first connection, replace with code above ^

 /* 
 =======================
 Disconnection procedure
 =======================
 */
      
 // Attempt to disconnect first, then stop advertising
 pServer->disconnect(connID);
 Serial.println("# Attempting to disconnect #");

 // Optional short delay to ensure disconnection completes before stopping advertising [to do: determine best value]
 delay(100);

 // Check if still connected after disconnect attempt
 if (devicePageShift.isConnected()) 
 { 
  Serial.println("Warning: Device still connected after disconnect attempt.");
 } 
 else 
 {
  Serial.println("# Device disconnected successfully #");
 }

 // Now stop advertising after confirming disconnection
 pServer->stopAdvertising();
 Serial.println("# Stopped advertising #");
}

void customReconnect()
{
  NimBLEServer* pServer =  NimBLEDevice::getServer();
  pServer->startAdvertising();
  Serial.println("## Started advertising... ##");
}


void setup() {

  // pin setup
  pinMode(INPUT_LEFT, INPUT_PULLUP);
  pinMode(INPUT_RIGHT, INPUT_PULLUP);
  pinMode(INPUT_PAIRING, INPUT_PULLUP);

  // serial setup
  Serial.begin(115200);

  // bluetooth setup
  devicePageShift.setName("LS PageShift");
  devicePageShift.begin();
  
  // setup feedback
  Serial.println("\n\n ### Setup successful ###\n");
}

void loop() 
{
  if(devicePageShift.isConnected()) 
  {
    
    //Serial.println("connection successful");

    if(digitalRead(INPUT_LEFT) == LOW) 
    {
      Serial.println("left pressed");
      devicePageShift.write(KEY_LEFT_ARROW);
    }
    if (digitalRead(INPUT_RIGHT) == LOW) 
    {
      Serial.println("right pressed");
      devicePageShift.write(KEY_RIGHT_ARROW);
    }
    // disconnect device
    if (digitalRead(INPUT_PAIRING) == LOW) 
    {
      customDisconnect();
    }
  }

  // Reconnect to a device
  else if (digitalRead(INPUT_PAIRING) == LOW)
  {
    customReconnect();
  }
  
  
  


  
  
  

 
  
}
  



