#include <Messenger.h>
#include <Servo.h>

// CREER UNE INSTANCE DE Messenger POUR RECEVOIR LES MESSAGES
Messenger messenger = Messenger();

/* LES  MESSAGES
 *   "solenoideA α" :  α EST UN ENTIER ENTRE 0 ET 1 QUI DETERMINE L'ETAT DU SOLENOIDE
 */

int broche_solenoideA = 9; // LA BROCHE RELIEE AU SOLENOIDE

int etat_solenoideA = 0; // LA VALEUR INITIALE QUI SERA APPLIQUEE AU SOLENOIDE

void setup() {

  Serial.begin(57600);  // INITIALISER LA COMMUNICATION SERIE

  messenger.attach(messageReceived);   // LANCER messageReceived LORSQU'UN MESSAGE EST RECU

  // CONFIGURER LA BROCHE RELIEE AU SOLENOIDE
  pinMode( broche_solenoideA ,  OUTPUT );   
  digitalWrite(  broche_solenoideA ,  etat_solenoideA );   
}

void loop() { 

  // FOURNIR LES DONNEES SERIES RECUES A L'INSTANCE DE Messenger
  while ( Serial.available( ) > 0 ) {
    messenger.process( Serial.read( ) ); 
  }
}

void messageReceived() {

  if ( messenger.checkString("solenoideA") ) {  // SI LE MESSAGE COMMENCE AVEC "solenoideA"...

    etat_solenoideA = messenger.readInt(); // ...LIRE LA PROCHAINE DONNEE EN TANT QU'ENTIER (int)
    digitalWrite(  broche_solenoideA ,  etat_solenoideA );    // APPLIQUER LA VALEUR AU SOLENOIDE
    Serial.println("Ok");

  } else {

    Serial.println("What?"); // IMPRIMER "What?" SI LE MESSAGE N'EST PAS RECONNU

  }

}
