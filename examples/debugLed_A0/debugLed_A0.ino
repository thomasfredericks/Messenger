// This example requires Chrono and Messenger
// Use the library manager to download them or
// get the latest versions here :
// https://github.com/thomasfredericks/Chrono
// https://github.com/thomasfredericks/Messenger

#include <Chrono.h>
#include <Messenger.h>

// Create a timer to control the speed 
// of the messages sent to the computer.
Chrono timer;

// Create a messenger to receive messages
// sent by the computer.
Messenger messenger;


void setup() {

   // Set pin 13 to OUTPUT mode :
   pinMode(13,OUTPUT);

  // start serial port at 57600 bps:
  Serial.begin(57600);
  
  // Run messageReceived when a message is received.
  // See messageReceived at the end of this sketch.
  messenger.attach(messageReceived);
}


void loop() {

  
   // Feed the serial data to Messenger
  while ( Serial.available( ) ) messenger.process( Serial.read( ) );
  
  // If 10 ms have passed :
  if ( timer.hasPassed(10) ) {
    // Restart the timer :
    timer.restart();

    // Send out the reading of analog pin 0
    Serial.print("A0"); // Start with the header "A0"
    Serial.print(" "); // Append a space
    Serial.print(analogRead(0)); // Send the value
    Serial.print('\n'); // End with a new line
    
  }

}

void messageReceived() {
  
   if ( messenger.checkString("led") ) {  // If the received message starts with led...
     int value = messenger.readInt(); // ...read the next element as an int...
     digitalWrite(13,value); // ...and set the state of pin 13 to the value.
  }
  
}
