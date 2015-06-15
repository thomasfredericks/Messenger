/*
 DESCRIPTION:
 Allumer et eteindre la DEL de debogage avec un Massage.
 
 CIRCUIT :
 Aucun.
 
 UTILISATION :
 Envoyer les Massages suivantes par port serie :
 
 "led 1" : allume la DEL de debogage.
 
 "led 0" : eteint la DEL de debogage.
 
 Note : ne pas oublier de terminer les Massages avec
 des retours a la ligne (carriage return).
 
 2014/03/18 by Thomas Ouellet FREDERICKS
 */

// DEBUG_LED
// Bloc de code qui permet d'identifier DEBUG_LED,
// i.e. la broche qui correspond a la DEL de debogage.
// Pour Arduino, DEBUG_LED correspond a la broche 13.
// Pour Wiring, DEBUG_LED est identifie par WLED.
#if defined(ARDUINO)
#define DEBUG_LED 13
#else
#define DEBUG_LED WLED
#endif

// Inclure la logitheque Massenger :
#include <Massenger.h>

// Initialiser une instance de Massenger qui porte le nom "massenger"
// et la lier avec le port serie et la fonction "massageReceived".
Massenger massenger = Massenger( &Serial, massageReceived); 

void setup() {

  // Initialiser la communication serie a une vitesse de 57600 :
  Serial.begin(57600);

  // Configurer la broche en tant que sortie,
  // c'est a dire qu'elle peut controler le flux de courant. 
  pinMode(DEBUG_LED,OUTPUT);
}

void loop() {

  // Indique a l'instance "massenger" de traiter les Massages entrants.
  massenger.update();
}

 // Cette fonction est execute lorsqu'un Massage est recu.
void massageReceived() {
  // Verifie si l'adresse du Massage correspond a l'adresse "led".
  if ( massenger.checkAddr("led") ) { 
    // Recupere la valeur du Massage.
    int valeur = massenger.getInt();

    // Le "if ... else if" suivant effectue cette operation :
    // Si la valeur est 0, eteindre la DEL.
    // Sinon si la valeur est 1, allumer la DEL.
    if ( valeur == 0 ) {
      // Envoyer 0V (ce qui eteint la DEL) :
      digitalWrite(DEBUG_LED, LOW);
    } else if ( valeur == 1) {
      // Envoyer 5V (ce qui allume la DEL) :
      digitalWrite(DEBUG_LED, HIGH);
    }
  }
}

