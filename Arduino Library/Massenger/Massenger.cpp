

//ADDED FOR COMPATIBILITY WITH WIRING
extern "C" {
  #include <stdlib.h>
}

#include "Massenger.h"


/*
Massenger::Massenger()
{
	init(' ');
}
*/

Massenger::Massenger( Stream * _cereal , massengerCallbackFunction _callback )
{	
	serial = _cereal;
	callback = _callback;
	buffer[MASSENGERBUFFERLAST] = 0;
	reset();
	
}
/*
Massenger::Massenger(char separator)
{
	if (separator == 10 || separator == 13 || separator == 0)  separator = 32;
	init(separator);
}
*/




 void Massenger::send(char *string, int value) {
	serial->print(string);
	serial->write(32);
	serial->println(value);
 
 }

void Massenger::reset() {

        bufferIndex = 0;
		tail = buffer;
		/*
        messageState = 0;
        current = NULL;
        last = NULL;
        dumped = 1;*/
}


uint8_t Massenger::checkAddr(char *string) {
	
	return strcmp(string,buffer) == 0;
	
}

int Massenger::getInt() {

    return atoi(tail);
     
}

// Added based on a suggestion by G. Paolo Sanino
/*
long Massenger::readLong() {

	if (next()) {
		dumped = 1;
		return atol(current); // atol for long instead of atoi for int variables
	}
	return 0;

}

char Massenger::readChar() {

  if (next()) {
  	 dumped = 1;
  	 return current[0];
 }
  return 0;

}

double Massenger::readDouble() {
    if(next()) {
        dumped = 1;
        return atof(current);
    }
    return 0;
}

void Massenger::copyString(char *string, uint8_t size) {
	
	if (next()) {
		dumped = 1;
		strlcpy(string,current,size);
	} else {
		if ( size ) string[0] = '\0';
	}
}
*/




/*
uint8_t Massenger::next() {

  char * temppointer= NULL;
  switch (messageState) {
  case 0:
    return 0;
  case 1:
    temppointer = buffer;
    messageState = 2;
  default:
    if (dumped) current = strtok_r(temppointer,token,&last);
    if (current != NULL) {
    	dumped = 0;
    	return 1; 
	}
  }
  
  return 0;
}*/
/*
uint8_t Massenger::available() {
	
  return next();
  
}
*/

void Massenger::update() {
	

	 while ( serial->available( ) ) process( serial->read( ) );
	
}


void Massenger::process(int serialByte) {


    if (serialByte > 0) {

      switch (serialByte) {
      case 0: 
      	break;
      case 10: // LF
        break;
      case 13: // CR
        buffer[bufferIndex]=0;
        (*callback)();
        reset();
        break;
	  case 32:
	    buffer[bufferIndex]=0;
	    bufferIndex++;
		if (bufferIndex >= MASSENGERBUFFERSAFE) reset();
		tail = buffer+bufferIndex;
      default:
          buffer[bufferIndex]=serialByte;
          bufferIndex++;
           if (bufferIndex >= MASSENGERBUFFERSAFE) reset();
         }
      } 
	 
      
      //return messageState;
 }



