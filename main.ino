#include "threads.h"



void setup () {
  Serial.begin(9600);
  conect();
  // Inicializa o pino digital como uma saída.
  // Pin 13 tem um LED conectado na maioria das placas Arduino:
  //pinMode (pino_red, OUTPUT);
  //digitalWrite(pino_red, false);
  pinMode(pino_green, OUTPUT);
  digitalWrite(pino_green, false);
  
}

void loop () {
  //check_print_red();
  //check_print_green();
  check_sonar();
  check_instructions();
}



