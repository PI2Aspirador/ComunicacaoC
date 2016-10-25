#include <Ultrasonic.h>
#include "comunication.h"

#define pino_trigger_sonar 38
#define pino_echo_sonar 40

//Inicializando o sonar
Ultrasonic ultrasonic(pino_trigger_sonar, pino_echo_sonar);

void get_distance();

void get_distance() {
  Serial.println("Entrou no get_distance");
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  int len=0;
  char * mensagem;
  sprintf(mensagem, "%f", cmMsec);
  Serial.print("Enviando:");
  Serial.println(mensagem);
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  send_data("oi td bem?");
}
