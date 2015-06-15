#include <Massenger.h>

/*
Example on how to receive massages with Massenger.

Control the PWM (analogWrite) of a LED connected to pin 9 with Massages :
To turn off the LED :  pwm9 0
To turn on the LED at half brightness : pwm9 127 
To turn on the LED at full brightness : pwm9 255 
Always end massages with a carriage return.

*/
            
// Instantiate a Massenger object and
// link it to Serial and
// set a function to be called (massageReceived) when a massage is received.
Massenger massenger = Massenger( &Serial , massageReceived); 

void setup() {
  
  // Initiate serial communication.
  Serial.begin(57600); 
  
  // Setup pin 9 as a digital output.
  pinMode(9,OUTPUT);
  
}

void loop() {
  
   // Update massenger's input and process received massages. 
  massenger.update();
  
}

// Process received massages.
void massageReceived() {
  
  if ( massenger.checkAddr("pwm9") ) { // If the massage starts with "pwm9"...
  
     int value = massenger.getInt(); // ...read the value of the data as an int...
     
     if ( value == 0 ) {
       digitalWrite(9,LOW); // ...and turn off pin 9.
     } else {                // ... or ...
       analogWrite(9,value); // ...and set the analogWrite of pin 9 to the value.
     }
     
  }
  
}
