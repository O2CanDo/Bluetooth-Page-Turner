/**
 * current issues:
 * - reconnect ignores new device if previous device has bluetooth on
 * - return values for customDisconnect/Reconnect only placeholder
 * - pairing input button usually pressed over multiple cycles -> input issues
 * - connID for disconnect hardcoded
 */

#include <Arduino.h>
#include <BleKeyboard.h>

#include <NimBLEDevice.h>




// pin alias defines
#define INPUT_LEFT 27
#define INPUT_RIGHT 26
#define INPUT_DISCONNECT 25
#define INPUT_RECONNECT 32
#define INPUT_PLACEHOLDER1 16
#define INPUT_PLACEHOLDER2 17


BleKeyboard devicePageShift;


void customDisconnect()
{
  // get pointer to server
  NimBLEServer* pServer =  NimBLEDevice::getServer();
      

  // get pointer to client and connID  [to do: fix hardcoding]
  // [if no clients are created, how are connIDs handled???]
  //Serial.print("getClientListSize(): ");
  //Serial.println(NimBLEDevice::getClientListSize());
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

  // to do: add delay and status confirmation??
}


void setup() 
{
  // pin setup
  pinMode(INPUT_LEFT, INPUT_PULLUP);
  pinMode(INPUT_RIGHT, INPUT_PULLUP);
  pinMode(INPUT_DISCONNECT, INPUT_PULLUP);
  pinMode(INPUT_RECONNECT, INPUT_PULLUP);
  pinMode(INPUT_PLACEHOLDER1, INPUT_PULLUP);
  pinMode(INPUT_PLACEHOLDER2, INPUT_PULLUP);

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
    if (digitalRead(INPUT_DISCONNECT) == LOW) 
    {
      Serial.println("Disconnect pressed");
      customDisconnect();

      // remove bonds from here in the future?
    }
  }

  // Reconnect to a device
  /*else*/ if (digitalRead(INPUT_RECONNECT) == LOW)
  {
    Serial.println("Reconnect pressed");
    customReconnect();
  }
  if (digitalRead(INPUT_PLACEHOLDER1) == LOW)
  {
    Serial.println("Deleting all bonds");
    NimBLEDevice::deleteAllBonds();
  }
  if (digitalRead(INPUT_PLACEHOLDER2) == LOW)
  {
    // [Client List seems useless for now, don't think they are created from BleKeyboard]
    //Serial.print("getClientListSize(): ");
    //Serial.println(NimBLEDevice::getClientListSize());
    Serial.print("getNumBonds(): ");
    Serial.println(NimBLEDevice::getNumBonds());
  }

  

}
  



