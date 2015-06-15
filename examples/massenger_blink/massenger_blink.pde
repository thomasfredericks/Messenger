#include <Massenger.h>

/*
 DESCRIPTION:
 Example on how to turn on/off the a LED with a Massage.
 
 CIRCUIT :
 Connect a LED and resistor to a digital pin or 
 use the board's debug LED.
 For Arduino, the debug LED is on pin 13.
 For Wiring, the debug LED is determined by WLED.
 
 USAGE :
 Send the following Massages through the serial port :
 
 * To turn on the the LED : "led 1" 
 * To turn off the LED :  "led 0"
 Note : always end Massages with a carriage return.
 
 2014/03/18 by Thomas Ouellet FREDERICKS
 */

// A few lines to make sure this sketch is compatible with Arduino and Wiring :
#if defined(ARDUINO)
#define DEBUG_LED 13
#else
#define DEBUG_LED WLED
#endif


// Instantiate and configure a Massenger object :
// link it to "Serial" and set a function to be called "massageReceived" when a massage is received.
Massenger massenger = Massenger( &Serial, massageReceived); 

void setup() {

  // Initiate serial communication.
    Serial.begin(57600); 

  // Setup pin debugLed as a digital output.
  pinMode(DEBUG_LED,OUTPUT);
}

void loop() {

  // Update massenger and process received massages. 
  massenger.update();
}

// Process received massages.
void massageReceived() {

  if ( massenger.checkAddr("led") ) { // If the massage starts with "led"
    int value = massenger.getInt(); // read the value of the data as an int
    digitalWrite(DEBUG_LED,value); // set the state of pin debugLed to the value.
  }
}

