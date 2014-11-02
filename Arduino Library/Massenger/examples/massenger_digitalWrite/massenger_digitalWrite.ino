#include <Massenger.h>

/*
Example on how to receive massages with Massenger.

Turn on/off a LED attached to pin 13 with ASCII massages :
To turn on the the LED : d13 1 
To turn off the LED :  d13 0
Always end massages with a carriage return.

*/
            
// Instantiate a Massenger object and
// link it to Serial and
// set a function to be called (massageReceived) when a massage is received.
Massenger massenger = Massenger( &Serial , massageReceived); 

void setup() {
  
  // Initiate serial communication.
  Serial.begin(57600); 
  
  // Setup pin 13 as a digital output.
  pinMode(13,OUTPUT);
  
}

void loop() {
  
   // Update massenger's input and process received massages. 
  massenger.update();
  
}

// Process received massages.
void massageReceived() {
  
  if ( massenger.checkAddr("d13") ) { // If the massage starts with "d13"...
     int value = massenger.getInt(); // ...read the value of the data as an int...
     digitalWrite(13,value); // ...and set the state of pin 13 to the value.
  }
  
}
