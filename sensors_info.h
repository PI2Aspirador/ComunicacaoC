#include <Ultrasonic.h>
#include "util.h"
#include "comunication.h"

#define pino_trigger_sonar 4
#define pino_echo_sonar 5

//Inicializando o sonar
Ultrasonic ultrasonic(pino_trigger_sonar, pino_echo_sonar);

void get_distance();

void get_distance() {
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  int len=0;
  char * mensagem;
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  Serial.print("Enviando\n");
  send_data((int)cmMsec);
  
  if(cmMsec < 5){
    print_exit();
    exit(1);
  }
}
