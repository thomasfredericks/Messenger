import processing.serial.*;
/*
Lorsque vous demarrez ce code, tout les ports
series s'affichent dans la fenetre de deboguage.
Changer la variable ''portName'' pour qu'elle
corresponde au nom du port serie qui correspond a
l'Arduino.

Sous Linux et OS X le nom du port ressemble a ceci :
String portName = "/dev/tty.usbmodem24121";

Sous Windows, il ressemble a ceci :
String portName = "COM4";
*/

String portName = "COM5";

// Declarer une instance de la classe Serial:
Serial serial;

int A0;

int debugLed;

Messenger messenger;

void setup() {
  size(512, 256);

  // Affiche les noms des ports.
  println(Serial.list());

  // Creer une instance de la classe Serial avec
  // une vitesse de 57600 baud:
  serial = new Serial(this, portName, 57600);

   messenger = new Messenger();
   messenger.attach(this,"messageReceived");

}

void messageReceived() {

  if ( messenger.checkString("A0") ) {
  
    A0 = messenger.readInt();
  }
  
}

void draw() {
  
  background(0);
  
   while ( serial.available( ) > 0 ) messenger.process( serial.read( ) );

  textAlign(CENTER, CENTER);
  text( "A0 : " + A0 , width * 0.5 , height * 0.5 - 20);
  text( "debugLed : " + debugLed , width * 0.5 , height * 0.5 + 20);

}

void mousePressed() {
  
  if ( debugLed == 0 ) debugLed = 1;
  else debugLed = 0;
  
  serial.write("led"+" "+debugLed+"\n");
  
}
