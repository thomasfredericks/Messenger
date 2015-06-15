
class Massenger {

  java.lang.reflect.Method callback;
  byte[] receivedDataArray = new byte[1024];
  int receivedDataIndex = 0;
  Serial serial;
  Object instance;
  String callbackName;
  boolean ready = false;
  String massageAddr;
  int massageData;


  Massenger( Object instance, Serial serial, String callbackName ) {
    this.serial = serial;
    this.instance = instance;
    this.callbackName = callbackName;
    try {
      callback = instance.getClass().getMethod(callbackName );
    } 
    catch (ReflectiveOperationException e) {
      print("Could not find massage received callback called "+callbackName+".");

      throw new RuntimeException(e);
    }
  }

  void update() {
    while ( this.serial.available () > 0 ) {

      if ( receivedDataIndex > 1023 ) {
        receivedDataIndex = 0;
      }

      int data = this.serial.read();
      if ( data == 13 ) {

        String rawMassage = new String(receivedDataArray, 0, receivedDataIndex);
        String[] tableauDeChaines = splitTokens(rawMassage);
        if ( tableauDeChaines.length == 2 ) {
           massageAddr = tableauDeChaines[0];
           massageData = int(tableauDeChaines[1]);
         
          ready = true;
          try {
            callback.invoke(instance);
          } 
          catch (ReflectiveOperationException e) {
            print("Could not find massage received callback called "+callbackName+".");

            throw new RuntimeException(e);
          }
        }
        receivedDataIndex = 0;
        ready = false;
        
      } else if ( data > 10 && data < 128) {
        receivedDataArray[receivedDataIndex] = byte(data);
        receivedDataIndex++;
      }
    }
  }

  boolean checkAddr( String addr) {
    if ( ready &&  massageAddr.equals(addr) ) {
      return true;
    }
   return false;
  }
  
  int getInt() {
   
   return massageData;
  }
  
  void send(String addr, int value) {
    
   String massage = addr+" "+value+"\r"; // "\r" indique un retour de chariot
   serial.write(massage);
  }
  
  
}


