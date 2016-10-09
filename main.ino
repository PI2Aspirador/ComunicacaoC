#include "threads.h"



void setup () {
  Serial.begin(9600);
  conect();
  // Inicializa o pino digital como uma saída.
  // Pin 13 tem um LED conectado na maioria das placas Arduino:
  pinMode (13, OUTPUT);
  digitalWrite(13, false);
  pinMode(12, OUTPUT);
  digitalWrite(12, false);
  
}

void loop () {
  check_print_red();
  check_print_green();
  check_sonar();
}



