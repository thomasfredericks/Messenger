/* 

  Control the debug led (pin 13 on Arduino) with the "led" ascii string
  followed by a 0 or 1.

  Thomas Ouellet Fredericks 
  2015/08/14

 */

// INCLUDE MESSENGER LIBRARY
// Download : https://github.com/thomasfredericks/Messenger/archive/master.zip
#include <Messenger.h>

// Instantiate a Messenger instance
Messenger message = Messenger(); 

void setup() {
  
  // Set pin 13 to OUTPUT mode
   pinMode(13, OUTPUT);
  
  // Initiate Serial Communication
  Serial.begin(57600); 
  // Attach a function that is called when a message is received
  message.attach(messageReceived);
}

void loop() {

  // Feed the serial data to Messenger
  while ( Serial.available( ) ) 
    message.process( Serial.read( ) );

}

// Function that is called when a message is received :
void messageReceived() {

  if ( message.checkString("led") ) {  // If the received message starts with led...
    int value = message.readInt(); // ...read the next element as an int...
     digitalWrite(13,value); // ...and set the state of pin 13 to the value.
  }
     
}
