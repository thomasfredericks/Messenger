import processing.serial.*;
/*
Lorsque vous demarrez ce code, tout les ports
 series s'affichent dans la fenetre de deboguage.
 Changer la variable ''portName'' pour qu'elle
 corresponde au nom du port serie qui correspond a
 la plaquette Arduino ou Wiring.
 
 Sous Linux et OS X le nom du port ressemble a ceci :
 String port = "/dev/tty.usbmodem24121";
 
 Sous Windows, il ressemble a ceci :
 String port = "COM4";
 
 */
String port = "COM4";

// Declarer une instance de la classe Serial :
Serial serial;

// Declarer une instance de la classe Massenger :
Massenger massenger;

// Une variable pour l'etat voulu de la DEL :
int led = 0;

// BLOC D'INITIALISATION.
void setup() {
  size(512, 256);

  // Affiche les noms des ports pour identifier celui de 
  // la plaquette Arduino ou Wiring :
  println(Serial.list());

  // Creer une instance de la classe "Serial" avec
  // une vitesse de 57600 baud:
  serial = new Serial(this, portName, 57600);

  // Initialiser une instance de Massenger qui porte le nom "massenger"
  // et la lier avec ce sketch, le port serie et la fonction "massageReceived".
  massenger = new Massenger(this, serial, "massageReceived");
}

// Cette fonction est execute lorsqu'un Massage est recu.
void massageReceived() {
  // Dans cet exemple, Processing ne recoit rien de l'Arduino.
  // mais cela peut servir lorsque le code sera developpe davantage.
}

// BLOC D'EXECUTION EN BOUCLE.
void draw() {

  // Indique a l'instance "massenger" de traiter les Massages entrants.
  // Ce qui n'est pas necessaire pour cet exemple, mais qui peut servir
  // lorsque le code sera developpe davantage.
  massenger.update();

  // Le "if ... else if" suivant effectue cette operation :
  // Si la valeur de "led" est 0, afficher un fond noir.
  // Sinon si la valeur de "led" est 1, afficher un fond blanc.
  if ( led == 0 ) {
    background(0);
  } else if ( led == 1 ) {
    background(255);
  }
}

// BLOC DE CODE EXECUTE LORSQUE LE BOUTON DE LA SOURIS EST APPUYE
void mousePressed() {

  // Le "if ... else if" suivant effectue cette operation :
  // Si la valeur de "led" est 0, changer la valeur de "led" a 1.
  // Sinon si la valeur de "led" est 1, changer la valeur de "led" a 0.
  if ( led == 0 ) {
    led = 1;
  } else if ( led == 1 ) {
    led = 0;
  }

  // Envoyer un Massage avec l'adresse "led" et une valeur.
  massenger.send("led", led);
}

