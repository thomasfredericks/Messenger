#include <Messenger.h>
#include <Servo.h>

// CREER UNE INSTANCE DE Messenger POUR RECEVOIR LES MESSAGES
Messenger messenger = Messenger();

/* LES  MESSAGES
 *   "relaisA α" :  α EST UN ENTIER ENTRE 0 ET 1 QUI DETERMINE L'ETAT DU RELAIS
 */

int broche_relaisA = 2; // LA BROCHE RELIEE AU RELAIS

int etat_relaisA = 0; // LA VALEUR INITIALE QUI SERA APPLIQUEE AU RELAIS

void setup() {

  Serial.begin(57600);  // INITIALISER LA COMMUNICATION SERIE

  messenger.attach(messageReceived);   // LANCER messageReceived LORSQU'UN MESSAGE EST RECU

  // CONFIGURER LA BROCHE RELIEE AU RELAIS
  pinMode( broche_relaisA ,  OUTPUT );   
  digitalWrite(  broche_relaisA ,  etat_relaisA );   
}

void loop() { 

  // FOURNIR LES DONNEES SERIES RECUES A L'INSTANCE DE Messenger
  while ( Serial.available( ) > 0 ) {
    messenger.process( Serial.read( ) ); 
  }
}

void messageReceived() {

  if ( messenger.checkString("relaisA") ) {  // SI LE MESSAGE COMMENCE AVEC "relaisA"...

    etat_relaisA = messenger.readInt(); // ...LIRE LA PROCHAINE DONNEE EN TANT QU'ENTIER (int)
    digitalWrite(  broche_relaisA ,  etat_relaisA );    // APPLIQUER LA VALEUR AU RELAIS
    Serial.println("Ok");

  } else {

    Serial.println("What?"); // IMPRIMER "What?" SI LE MESSAGE N'EST PAS RECONNU

  }

}
