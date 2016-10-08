#include <SPI.h>
#include <Ethernet.h>

void conect();
void send_data(void *msg);
char * read_data();

  //Definindo MAC, ip do cliente e ip do servidor
  byte mac[] = {
    0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
  };
  IPAddress ip(192, 168, 0, 110);
  
  // IP do servidor:
  IPAddress server(192, 168, 0, 195);
  
  EthernetClient client;

void conect(){
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  //Dando um tempo pro Ethernet shield iniciar:
  delay(1000);
  if (client.connect(server, 8080)) {
    Serial.println("Conectado");
  } else {
    // if you didn't get a connection to the server:
    Serial.println("Falha na conexão");
    delay(500);
  }
}

void send_data(void *msg){
  conect();
  char * mensagem = "D: ";
  char *distancia = *(char*)msg;
  strcat(mensagem, distancia);
  Serial.println("Enviando olha.. ");
  Serial.println(mensagem);
  
    if (client.connected()) {
      client.print(mensagem); 
    }
 
  if (!client.connected()) {
    Serial.println();
    Serial.println("Servidor desconectado.");
    client.stop();
    delay(1000);
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

