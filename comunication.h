#include "connection.h"
#include "util.h"

char read_data();

//Envia dados a raspberry
void send_data(int distance){
    if (client.connected()) {
      Serial.println(distance);
      client.print((char)distance);//Envia distancia 
    }
 
  if (!client.connected()) {
    Serial.println();
    Serial.println("ERRO! Servidor desconectado.");
    client.stop();
    delay(200);
    print_exit();
    exit(1);
  }
}

//Escuta informações da raspberry
void listen_infos(){
  char msg = read_data();
  Serial.print("Entrou no listen: ");
  delay(25);
  Serial.println(msg);
  if(msg == 'R'){
    Serial.print("Identificou R\n");
    low_green();
  }else if(msg == 'G'){
    Serial.print("Identificou G\n");
    //delay(50);
    print_green();
  }else{
    Serial.print("Caractere desconhecido!!");
  }
}

char read_data(){
  char c;
  if (client.available()) {
    c = client.read();
    Serial.print(c);
  }
  return c;
}
