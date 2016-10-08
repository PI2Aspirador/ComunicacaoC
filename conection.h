#include <SPI.h>
#include <Ethernet.h>

  //Definindo MAC, ip do cliente e ip do servidor
  byte mac[] = {
    0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
  };
  IPAddress ip(192, 168, 0, 110);
  
  // IP do servidor:
  IPAddress server(192, 168, 0, 195);
  
  EthernetClient client;


