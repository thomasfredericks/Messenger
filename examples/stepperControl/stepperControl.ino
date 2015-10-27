#include <Stepper.h>
#include <Chrono.h>
#include <Messenger.h>

// CREER UNE INSTANCE DE Messenger POUR RECEVOIR LES MESSAGES
Messenger messenger = Messenger();

/* LES  MESSAGES
 *   "pasA α" :  α EST UN ENTIER ENTRE -32768 ET 32767  QUI DETERMINE LE NOMBRE DE PAS A FAIRE DANS UNE DIRECTION
 *   "pauseA β" :  β EST UN ENTIER PLUS GRAND QUE 3 QUI DETERMINE LE TEMPS DE PAUSE EN MS ENTRE CHAQUE PAS
 */

int pas_par_rotationA = 513; // A TROUVER SUR LA FICHE TECHNIQUE DU MOTEUR

int broche_in_1A = 2; // BROCHE RELIEE PAR LE ULN2803A A LA PHASE 1
int broche_in_2A = 3; // BROCHE RELIEE PAR LE ULN2803A A LA PHASE 2
int broche_in_3A = 4; // BROCHE RELIEE PAR LE ULN2803A A LA PHASE 3
int broche_in_4A = 5; // BROCHE RELIEE PAR LE ULN2803A A LA PHASE 4

Stepper stepperA( pas_par_rotationA ,  broche_in_1A , broche_in_2A, broche_in_3A, broche_in_4A);

int pasA = 0; // LE NOMBRE DE PAS A EFFECTUER PAR LE STEPPER A

int pauseA = 4; // UN TEMPS D'ATTENTE EN MS ENTRE CHAQUE PAS DU STEPPER A
Chrono pause_chronoA; // UN CHRONOMETRE POUR LA PAUSE DES PAS DU STEPPER A


void setup() {

  // La DEL de debogage sera allumee lorsque
  // le stepper change de direction,
  // donc la mettre en mode sortie :
  pinMode(13, OUTPUT);

  Serial.begin(57600);  // INITIALISER LA COMMUNICATION SERIE

  messenger.attach(messageReceived);  // LANCER messageReceived LORSQU'UN MESSAGE EST RECU

}

void loop() {


  if ( pasA != 0 ) { // SI IL FAUT FAIRE DES PAS
    if ( pause_chronoA.hasPassed(pauseA) ) { // EST-CE QUE LE TEMPS DE PAUSE EST PASSE?...
      pause_chronoA.restart(); // ... OUI : ALORS REDEMARRER LE CHRONOMETRE
      // FAIRE UN PAS DANS LA BONNE DIRECTION
      if ( pasA > 0 ) {
        stepperA.step(1);
        pasA--;
      } else {
        stepperA.step(-1);
        pasA++;
      }
    }
  }

  while ( Serial.available( ) > 0 ) {
    messenger.process( Serial.read( ) ); // FOURNIR LES DONNEES SERIES RECUES A L'INSTANCE DE Messenger
  }
}

void messageReceived() {

  if ( messenger.checkString("pasA") ) {   // SI LE MESSAGE COMMENCE AVEC "pasA"...
    
    pasA = messenger.readInt(); // ...LIRE LA PROCHAINE DONNEE EN TANT QU'ENTIER (int)
    Serial.println("Ok");
    
  } else if ( messenger.checkString("pauseA")) {  // SI LE MESSAGE COMMENCE AVEC "pauseA"...
    
    pauseA = messenger.readInt();  // ...LIRE LA PROCHAINE DONNEE EN TANT QU'ENTIER (int)
    Serial.println("Ok");
    
  } else {
    Serial.println("What?");  // IMPRIMER "What?" SI LE MESSAGE N'EST PAS RECONNU

  }

}
