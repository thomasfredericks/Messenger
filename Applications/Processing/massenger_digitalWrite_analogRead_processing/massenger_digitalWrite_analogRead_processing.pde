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
String portName = "COM4";

// Declarer une instance de la classe Serial:
Serial serial;

int a0;

int d13;

Massenger massenger;

void setup() {
  size(512, 256);

  // Affiche les noms des ports.
  println(Serial.list());

  // Creer une instance de la classe Serial avec
  // une vitesse de 57600 baud:
  serial = new Serial(this, portName, 57600);

   massenger = new Massenger(this, serial, "massageReceived");

}

void massageReceived() {
  
  if ( massenger.checkAddr("a0") ) {
    
    a0 = massenger.getInt();
  }
  
}

void draw() {
  background(0);
  
  massenger.update();

  textAlign(CENTER, CENTER);
  text( "a0 : " + a0 , width * 0.5 , height * 0.5 - 20);
  text( "d13 : " + d13 , width * 0.5 , height * 0.5 + 20);

}

void mousePressed() {
  
  if ( d13 == 0 ) d13 = 1;
  else d13 = 0;
  massenger.send("led", d13);
  
  //println(byteArray);
  //serial.write(byteArray);
  
}
