#include <Utility.h>
#include <TimedAction.h>
#include <Ultrasonic.h>
#include <SPI.h>
#include <Ethernet.h>
#include <stdio.h>
//#include "conection.h"
#include <stdlib.h>

#define pino_trigger_sonar 4
#define pino_echo_sonar 5
#define pino_red 13
#define pino_green 12

void print_red();
void print_green();
void get_distance();

//Inicializando o sonar
Ultrasonic ultrasonic(pino_trigger_sonar, pino_echo_sonar);

//Criando as threads
TimedAction thread2 = TimedAction(300, print_green);
TimedAction thread1 = TimedAction(300, print_red);
TimedAction thread_sonar = TimedAction(200, get_distance);


void print_red() {
  digitalWrite(pino_red, HIGH);
  delay(100);
  thread_sonar.check();
  digitalWrite(pino_red, LOW);
  delay(100);
  thread_sonar.check();
  digitalWrite(pino_red, HIGH);
  delay(100);
  thread_sonar.check();
  digitalWrite(pino_red, LOW);
}

void print_green() {
  digitalWrite(pino_green, HIGH);
  delay(100);
  thread_sonar.check();
  digitalWrite(pino_green, LOW);
  delay(100);
  thread_sonar.check();
  digitalWrite(pino_green, HIGH);
  delay(100);
  
  digitalWrite(pino_green, LOW);
}

void get_distance() {
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  int len=0;
  char * mensagem;
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  Serial.print("Distancia em cm: ");
  Serial.print(cmMsec);
  Serial.print("\n");
  //len = asprintf(&mensagem, "%g", cmMsec);
  //if (len == -1)
   // fprintf(stderr, "Erro ao converter float\n");
  
 // send_info("192.168.0.26", "8080", mensagem);
  if(cmMsec < 5){
    Serial.print("Saindo...\n");
    digitalWrite(pino_green, LOW);
    digitalWrite(pino_red, LOW);
    delay(200);
    exit(1);
  }
}


void setup () {
  Serial.begin(9600);
  Serial.println("Lendo dados do sensor...");
  // Inicializa o pino digital como uma saída.
  // Pin 13 tem um LED conectado na maioria das placas Arduino:
  pinMode (13, OUTPUT);
  digitalWrite(13, false);
  pinMode(12, OUTPUT);
  digitalWrite(12, false);
  //Rede:
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Saiu do while..");
  //Dando um tempo pro Ethernet shield iniciar:
  delay(1000);
  Serial.println("Conectando...");
  if (client.connect(server, 8080)) {
    Serial.println("connected");
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop () {
  int i=0;
  char myVar[100];
  strcpy(myVar, "Oi amigo, vamos conversar?");
  thread2.check();
  thread1.check();
  thread_sonar.check();
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  Serial.print("Enviando.. ");
    if (client.connected()) {
      client.print(myVar); 
    }
 
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    delay(1000);
  }
}



