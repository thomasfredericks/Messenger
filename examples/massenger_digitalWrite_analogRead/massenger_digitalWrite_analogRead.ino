#include <Massenger.h>

/*
Example on how to receive and send massages with Massenger.

Turn on/off a LED attached to pin 13 with ASCII massages :
To turn on the the LED : d13 1 
To turn off the LED :  d13 0
Always end massages with a carriage return.

Each time the value of analogRead(0) changes, 
the value is sent as the following
ASCII massage where xxx is the new value:
a0 xxx
The massage always ends with a carriage return.

*/

// A few lines to make sure this sketch is compatible with Arduino and Wiring
#if !defined(WLED)
#define WLED 13
#endif

int debugLed = WLED;


// Instantiate a Massenger object, 
// link it to Serial 
// and set a function to be called when a massage is received.
Massenger massenger = Massenger( &Serial , massageReceived); 

// A variable to store the analog reading because we only want to send the value when it changes.
int value;

void setup() {
  
  // Initiate serial communication.
  Serial.begin(57600); 
    
  // Setup pin 13 as a digital output.
  pinMode(WLED,OUTPUT);
  
  
}

void loop() {
  
  // Update massenger's input and process received massages. 
 massenger.update();
 
 // Compare the previous reading with a new reading.
 int newValue = analogRead(0);
 if ( newValue != value ) {
   // If the value is different, send its new value.
     value = newValue;
     massenger.send("a0",value);
 }

  
}

// Process received massages.
void massageReceived() {
    
  if ( massenger.checkAddr("led") ) { // If the received message starts with d13...
     int value = massenger.getInt(); // ...read the next element as an int...
     digitalWrite(WLED,value); // ...and set the state of pin 13 to the value.
  }
  
}

