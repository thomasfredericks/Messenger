#include <Massenger.h>

/*
Example on how to turn on/off a LED with ASCII massages.
 
 To turn on the the LED : "led 1" 
 To turn off the LED :  "led 0"
 
 Note : always end ASCII massages with a carriage return.
 
 Configure the following "debugLed" variable to the appropriate pin on
 your board.
 
 2014/03/18 by Thomas Ouellet FREDERICKS
 */
 
int debugLed = WLED;

// Instantiate and configure a Massenger object :
// link it to "Serial" and set a function to be called "massageReceived" when a massage is received.
Massenger massenger = Massenger( &Serial, massageReceived); 

void setup() {

  // Initiate serial communication.
  Serial.begin(57600); 

  // Setup pin debugLed as a digital output.
  pinMode(debugLed,OUTPUT);
}

void loop() {

  // Update massenger and process received massages. 
  massenger.update();
  
}

// Process received massages.
void massageReceived() {

  if ( massenger.checkAddr("led") ) { // If the massage starts with "led"
    int value = massenger.getInt(); // read the value of the data as an int
    digitalWrite(debugLed,value); // set the state of pin debugLed to the value.
  }
  
}

