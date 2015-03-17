
#ifndef Massenger_h
#define Massenger_h
#define MASSENGERBUFFERSIZE 128
#define MASSENGERBUFFERLAST 127
#define MASSENGERBUFFERSAFE 126

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif



extern "C" {
// callback function
    typedef void (*massengerCallbackFunction)(void);
}


class Massenger
{

public:

  Massenger(Stream * serial , massengerCallbackFunction callback); 

  void update();
  
  uint8_t checkAddr(char *string);
  int getInt();
  
  void send(char *string, int value);

  
private:
  void process(int serialByte);
  void reset();
  
  massengerCallbackFunction callback;
  
  char* tail; // Pointer to tail
  char* last;
  
  Stream* serial;
  
  char token[2];

  
  uint8_t bufferIndex; // Index where to write the data
  char buffer[MASSENGERBUFFERSIZE]; // Buffer that holds the data
};

#endif

