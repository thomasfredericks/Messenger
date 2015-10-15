#include <Messenger.h>
#include <Servo.h> 
 
Messenger message = Messenger();

Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards

void setup() {

        Serial.begin(57600);

        message.attach(messageReceived);

        myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
}

void loop() {

        while ( Serial.available( ) > 0 ) {
                message.process( Serial.read( ) );
        }
}

void messageReceived() {

        if ( message.checkString("servo") ) {  // If the received message starts with "servo"...
                int value = message.readInt(); // ...read the next element as an int...
                myservo.writeMicroseconds(value)  ;     // ...tell servo to go to position set by variable 'value' 
                // value should be between 500 and 2500
                Serial.println("Ok");
        } else {
             Serial.print("What? ");
             Serial.println(message.received());
          
        }

}