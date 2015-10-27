#include <Messenger.h>
#include <Servo.h>

// CREER UNE INSTANCE DE Messenger POUR RECEVOIR LES MESSAGES
Messenger messenger = Messenger();

/* LES  MESSAGES
 *   "servoA α" :  α EST UN ENTIER ENTRE 500 ET 2500 QUI DETERMINE LA ROTATION DU SERVO A
 */

// CREER UNE INSTANCE DE Servo POUR CONTROLER UN SERVOMOTEUR
// IL FAUT UNE INSTANCE PAR SERVOMOTEUR
Servo servoA;

int broche_servoA = 9; // LA BROCHE RELIEE AU SERVOMOTEUR

int rotation_servoA = 1500; // LA VALEUR INITIALE QUI SERA APPLIQUEE AU SERVOMOTEUR

void setup() {

  Serial.begin(57600);  // INITIALISER LA COMMUNICATION SERIE

  messenger.attach(messageReceived);   // LANCER messageReceived LORSQU'UN MESSAGE EST RECU

  servoA.attach(broche_servoA);   // INDIQUER A L'INSTANCE DE Servo QU'ELLE CONTROLE LA BROCHE  9

  servoA.writeMicroseconds(rotation_servoA); // APPLIQUER LA VALEUR AU SERVOMOTEUR
}

void loop() {

  while ( Serial.available( ) > 0 ) {
    messenger.process( Serial.read( ) ); // FOURNIR LES DONNEES SERIES RECUES A L'INSTANCE DE Messenger
  }
}

void messageReceived() {

  if ( messenger.checkString("servoA") ) {  // SI LE MESSAGE COMMENCE AVEC "servoA"...

    rotation_servoA = messenger.readInt(); // ...LIRE LA PROCHAINE DONNEE EN TANT QU'ENTIER (int)
    servoA.writeMicroseconds(rotation_servoA)  ;    // APPLIQUER LA VALEUR AU SERVOMOTEUR
    Serial.println("Ok");

  } else {

    Serial.println("What?"); // IMPRIMER "What?" SI LE MESSAGE N'EST PAS RECONNU

  }

}
