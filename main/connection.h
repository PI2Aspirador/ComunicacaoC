#include "ESP8266.h"
#include "parser_network_info.h"

#define DEBUG true
#define SSID "r2-pi2"
#define PASS "12345678"
#define DST_IP "182.168.0.26"

ESP8266 wifi(Serial1);

//Assinaturas
void conect();
void send_data(void *msg);

String sendData(String command, const int timeout, boolean debug)
{
  // Envio dos comandos AT para o modulo
  String response = "";
  Serial1.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (Serial1.available())
    {
      // The esp has data so display its output to the serial window
      char c = Serial1.read(); // read the next character.
      response += c;
    }
  }
  if (debug)
  {
    //Serial.print(response);
  }
  return response;
}

//Abrindo conexão com a raspberry
void conect(){
  char *msg;
  char * rssi;
  Serial.print("Versao de Firmware ESP8266: ");
    //A funcao wifi.getVersion() retorna a versao de firmware informada pelo modulo no inicio da comunicacao

    sendData("AT+GMR\r\n", 2000, DEBUG);
    
    //Vamos setar o modulo para operar em modo Station (conecta em WiFi) e modo AP (é um ponto de WiFi tambem)
    if (wifi.setOprToStationSoftAP()) {
        Serial.println("Station e AP OK.");
    } else {
        Serial.println("Erro em setar Station e AP.");
    }
 
    //Agora vamos conectar no ponto de WiFi informado no inicio do codigo, e ver se corre tudo certo
    if (wifi.joinAP(SSID, PASS)) {
        Serial.println("Conectado com Sucesso.");
        Serial.println("IP: ");
        //rotina wifi.getLocalIP() retorna o IP usado na conexao com AP conectada.
        sendData("AT+CIFSR\r\n", 2000, DEBUG);    
    } else {
        Serial.println("Falha na conexao AP.");
    }
    
    //Agora vamos habiliar a funcionalidade MUX, que permite a realizacao de varias conexoes TCP/UDP
    if (wifi.enableMUX()) {
        Serial.println("Multiplas conexoes OK.");
    } else {
        Serial.println("Erro ao setar multiplas conexoes.");
    }
    
    //Inicia servidor TCP na porta 8090 (veja depois a funcao "startServer(numero_porta)", que serve para UDP!
    if (wifi.startTCPServer(8090)) {
        Serial.println("Servidor iniciado com sucesso.");
    } else {
        Serial.println("Erro ao iniciar servidor.");
    }    
    rssi = get_rssi(sendData("AT+CWLAP\r\n", 5000, DEBUG));
    Serial.println("Setup finalizado!");
    Serial.println(rssi);
}

double get_rssi(){
  double rssi;

  return rssi;
}

