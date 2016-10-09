#include "connection.h"

//Envia dados a raspberry
void send_data(int distance){
    if (client.connected()) {
      Serial.println(distance);
      client.print(distance);//Envia distancia 
    }
 
  if (!client.connected()) {
    Serial.println();
    Serial.println("ERRO! Servidor desconectado.");
    client.stop();
    delay(200);
    exit(1);
  }
}

char * read_data(){
  char *c;
  if (client.available()) {
    c = client.read();
    Serial.print(c);
  }
  return c;
}
