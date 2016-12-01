#include "ESP8266.h"
#include "parser_network_info.h"


#define DEBUG true
#define SSID "r2-pi2"
#define PASS "12345678"
#define DST_IP "192.168.0.19"

ESP8266 wifi(Serial1);

//Assinaturas
void conect();
void send_data_wifi(String command, const int timeout, boolean debug);

void send_data_wifi(String command, const int timeout, boolean debug){
  // Envio dos comandos AT para o modulo
  String response = "";
  Serial1.print(command);
  long int time = millis();
  while ( (time + timeout) > millis()){
    while (Serial1.available()){
      // The esp has data so display its output to the serial window
      char c = Serial1.read(); // read the next character.
      response += c;
    }
  }
  if (debug){
    Serial.print(response);
  }
}

//Abrindo conexão com a raspberry
void conect(){
  uint32_t port = 8090;
  //char *msg;
  //char * rssi;
  send_data_wifi("AT+RST\r\n", 2000, DEBUG);
  send_data_wifi("AT+CIOBAUD=19200\r\n", 2000, DEBUG);
  Serial.print("Versao de Firmware ESP8266: ");
    //A funcao wifi.getVersion() retorna a versao de firmware informada pelo modulo no inicio da comunicacao
    send_data_wifi("AT+GMR\r\n", 2000, DEBUG);
      
    //Vamos setar o modulo para operar em modo Station (conecta em WiFi) e modo AP (é um ponto de WiFi tambem)
    if (wifi.setOprToStationSoftAP()) {
        Serial.println("Station e AP OK.");
    } else {
        Serial.println("Erro em setar Station e AP.");
    }

    Serial.println("Conectando na rede..");
    //Agora vamos conectar no ponto de WiFi informado no inicio do codigo, e ver se corre tudo certo
    if (wifi.joinAP(SSID, PASS)) {
        Serial.println("Conectado com Sucesso.");
        //Serial.println("IP: ");
        //rotina wifi.getLocalIP() retorna o IP usado na conexao com AP conectada.
        send_data_wifi("AT+CIFSR\r\n", 2000, DEBUG);    
    } else {
        Serial.println("Falha na conexao AP.");
        delay(200);
        exit(1);
    }
  
    if (wifi.disableMUX()) {
        Serial.print("single ok\r\n");
    } else {
        Serial.print("single err\r\n");
    }
    
    Serial.println("Criando conexao TCP");
    
     while(!wifi.createTCP(DST_IP, port)) {
        Serial.print("Erro ao criar conexao TCP\r\n");
        //delay(200);
        //exit(1);
    }
    Serial.print("Conexao TCP ok!\r\n");
    //rssi = get_rssi(send_data_wifi("AT+CWLAP\r\n", 5000, DEBUG));
    
}

double get_rssi(){
  double rssi;

  return rssi;
}

void desconect(){
 if (wifi.releaseTCP()) {
        Serial.print("release tcp ok\r\n");
    } else {
        Serial.print("release tcp err\r\n");
    }
    delay(2000);
}
 

