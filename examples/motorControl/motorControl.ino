#include <Messenger.h>

// CREER UNE INSTANCE DE Messenger POUR RECEVOIR LES MESSAGES
Messenger messenger = Messenger();

/* LES  MESSAGES
 *   "vitesseA α" :  α EST UN ENTIER ENTRE 0 ET 255 QUI DETERMINE LA VITESSE DU MOTEUR A
 *   "directionA β" :  β EST UN ENTIER ENTRE 0 ET 1 QUI DETERMINE LA DIRECTION DU MOTEUR A
 */

int broche_vitesseA = 9; // LA BROCHE RELIEE AU CONTROLE DE LA VITESSE : 12EN
int broche_direction1A = 8; // LA BROCHE RELIEE AU PREMIER DE LA PAIRE POUR LA DIRECTION : 1A
int broche_direction2A = 7; // LA BROCHE RELIEE AU DEUXIEME DE LA PAIRE POUR LA DIRECTION : 2A

int vitesseA = 255; // LA VALEUR INITIALE QUI SERA APPLIQUEE A LA VITESSE DU MOTEUR
int directionA = 0; // LA VALEUR INITIALE QUI SERA APPLIQUEE A LA DIRECTION DU MOTEUR

void setup() {

  Serial.begin(57600);  // INITIALISER LA COMMUNICATION SERIE

  messenger.attach(messageReceived);   // LANCER messageReceived LORSQU'UN MESSAGE EST RECU

  // CONFIGURER LES BROCHES DU MOTEUR
  pinMode( broche_vitesseA , OUTPUT );
  pinMode( broche_direction1A , OUTPUT );
  pinMode( broche_direction2A , OUTPUT );

  // APPLIQUER LES VALEURS INITIALES
  analogWrite(broche_vitesseA,vitesseA);
  if ( directionA == 0 ) {
    digitalWrite( broche_direction1A , LOW );
    digitalWrite( broche_direction2A , HIGH );
  } else {
    digitalWrite( broche_direction1A , HIGH );
    digitalWrite( broche_direction2A , LOW );
  }
  
}

void loop() {

  while ( Serial.available( ) > 0 ) {
    messenger.process( Serial.read( ) ); // FOURNIR LES DONNEES SERIES RECUES A L'INSTANCE DE Messenger
  }
}

void messageReceived() {

  if ( messenger.checkString("vitesseA") ) {  // SI LE MESSAGE COMMENCE AVEC "vitesseA"...

    vitesseA = messenger.readInt(); // ...LIRE LA PROCHAINE DONNEE EN TANT QU'ENTIER (int)
    analogWrite(broche_vitesseA,vitesseA);    // APPLIQUER LA VALEUR AU MOTEUR
    
    Serial.println("Ok");

  } else  if ( messenger.checkString("directionA") ) {   // SI LE MESSAGE COMMENCE AVEC "directionA"...


    directionA = messenger.readInt(); // ...LIRE LA PROCHAINE DONNEE EN TANT QU'ENTIER (int)
    if ( directionA == 0 ) {  // APPLIQUER LA VALEUR AU MOTEUR
    digitalWrite( broche_direction1A , LOW );
    digitalWrite( broche_direction2A , HIGH );
  } else {
    digitalWrite( broche_direction1A , HIGH );
    digitalWrite( broche_direction2A , LOW );
  }   
    Serial.println("Ok");
    
  } else {

    Serial.println("What?"); // IMPRIMER "What?" SI LE MESSAGE N'EST PAS RECONNU

  }

}
