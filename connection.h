#include <SPI.h>
#include <Ethernet.h>

//Assinaturas
void conect();
void send_data(void *msg);

//Definindo MAC, ip do cliente e ip do servidor
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 0, 110);

// IP do servidor:
IPAddress server(192, 168, 0, 195);

EthernetClient client;

//Abrindo conexão com a raspberry
void conect(){
  Ethernet.begin(mac, ip);
  while (!Serial) {
    ; // esperando uma conexão na porta serial
  }
  //Dando um tempo pro Ethernet shield iniciar:
  delay(1000);
  if (client.connect(server, 8080)) {
    Serial.println("Conectado");
  } else {
    // Se não conseguir conexão
    Serial.println("Falha na conexao");
    delay(100);
    exit(1);
  }
}

