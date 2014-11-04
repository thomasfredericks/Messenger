import processing.serial.*;

// Lorsque vous demarrez ce code, tout les ports
// series sont affiche dans la fenetre de deboguage.
// Changer la chaine suivante pour qu'elle
// corresponde au nom de votre port serie.

// Sous Linux et OS X le nom du port ressemble a ceci :
//String portName = "/dev/tty.usbmodem24121";
// Sous Windows, il ressemble a ceci :
String portName = "COM5";

// Declarer une instance de la classe Serial:
Serial serial;

int a0;

int d13;

void setup() {
  size(512, 256);

  // Affiche les noms des ports.
  println(Serial.list());

  // Creer une instance de la classe Serial avec
  // une vitesse de 57600 baud:
  serial = new Serial(this, portName, 57600);

  // Indiquer a l'instance serial de lancer la fonction serialEvent()
  // lorsque l'octet 13 est recu. L'octet 13 est envoye par
  // l'Arduino pour indiquer la fin du message
  serial.bufferUntil(13);
}

// Definir une fonction pour recevoir les donnees du port serie:
void serialEvent(Serial p) {

  // Lire le message.
  String chaine = p.readString();

  // Separer les elements du message
  // selon les espaces:
  String[] tableauDeChaines = splitTokens(chaine);

  // S'assurer qu'il y a bien deux mots
  // dans le message et les appliquer aux variables :
  if ( tableauDeChaines.length == 2 ) {
    String premier = tableauDeChaines[0];
    int deuxieme = int(tableauDeChaines[1]);
    // On peut "router" les messages en comparant le premier element :
    if ( premier.equals("a0")) {
      a0 = deuxieme;

      
    }
  }
}

void draw() {
  background(0);

  textAlign(CENTER, CENTER);
  text( "a0 : " + a0 , width * 0.5 , height * 0.5 - 20);
  text( "d13 : " + d13 , width * 0.5 , height * 0.5 + 20);

}

void mousePressed() {
  
  if ( d13 == 0 ) d13 = 1;
  else d13 = 0;
  
  String massage = "d13 "+d13+"\r"; // "\r" indique un retour de chariot
  byte[] byteArray = massage.getBytes();
  println(byteArray);
  serial.write(byteArray);
  
}
