#include <Messenger.h>

// Turn on/off a LED attached to pin 13 with the following ASCII messages :
//
// turn on the LED 
//                   d13 1     
//
// turn off the LED
//                   d13 0

// Instantiate a Messenger object.
Messenger messenger = Messenger(); 

void setup() {
  
  // Initiate serial communication.
  Serial.begin(57600); 
  
  // Attach a function that is executed when a message is received.
  messenger.attach(messageReceived);
  
  // Setup pin 13 as a digital output.
  pinMode(13,OUTPUT);
  
}

void loop() {
  
  // The following line effectively feeds the serial data to the Messenger instance.
  while ( Serial.available( ) ) messenger.process( Serial.read( ) );
  
}

void messageReceived() {
  
  if ( messenger.checkString("d13") ) { // If the received message starts with d13...
     int value = messenger.readInt(); // ...read the next element as an int...
     digitalWrite(13,value); // ...and set the state of pin 13 to the value.
  }
  
}
