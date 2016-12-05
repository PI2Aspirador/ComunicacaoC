#include "threads.h"

#define pin1 52
#define pin2 50
#define pin3 48
#define pin4 53
#define pin5 49
#define pin6 51

void setup () {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  pinMode(pin4, OUTPUT);
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, HIGH);
  digitalWrite(pin5, HIGH);
  digitalWrite(pin6, HIGH);
  
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
  analogWrite(velocityA, 75);
  analogWrite(velocityB, 75);
}

void loop () {
  //check_print_red();
  //check_print_green();
  drive_frente();
 

  if(get_distance_front() <= 15){
    drive_stop(); 
    get_distance();
    if(turn_to() == 1){
      turn_to_left();
    }else{
      if(turn_to() == 2){
        turn_to_right();
      }else{
        exit(1); // Sai do código (deliga o robo).
      }
    }
  }
}



