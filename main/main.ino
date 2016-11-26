#include "threads.h"

#define pin52 52
#define pin58 58
#define pin54 54


void setup () {
  digitalWrite(pin52, HIGH);
  digitalWrite(pin58, HIGH);
  digitalWrite(pin54, HIGH);
  
  Serial.begin(9600);
  Serial1.begin(19200);
  Serial.println("Configurando Conexao");
  config_motors();
  config_sonar();
  conect();
  
  // Inicializa o pino digital como uma saída.
  // Pin 13 tem um LED conectado na maioria das placas Arduino:
  //pinMode (pino_red, OUTPUT);
  //digitalWrite(pino_red, false);
  //pinMode(pino_green, OUTPUT);
  //digitalWrite(pino_green, false);
  
}

void loop () {
  //check_print_red();
  //check_print_green();
  drive_frente();
  check_sonar1();
  check_instructions();
  //delay(250);
  //desconect();
  
}



