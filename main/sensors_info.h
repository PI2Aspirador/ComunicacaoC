#include <Ultrasonic.h>
#include "comunication.h"

#define echopin_f 24
#define trigerpin_f 22
#define echopin_r 28
#define trigerpin_r 26
#define echopin_l 32
#define trigerpin_l 30

//Inicializando o sonar
Ultrasonic sonar_front(trigerpin_f, echopin_f);
Ultrasonic sonar_right(trigerpin_r, echopin_r);
Ultrasonic sonar_left(trigerpin_l, echopin_l);

void config_sonar(){
  pinMode(echopin_f, INPUT);
  pinMode(trigerpin_f, OUTPUT);
  pinMode(echopin_r, INPUT);
  pinMode(trigerpin_r, OUTPUT);
  pinMode(echopin_l, INPUT);
  pinMode(trigerpin_l, OUTPUT);
}

//L = left
//R = Right
//F = Front

void get_distance_front() {
  //Serial.println("Frente");
  float cmMsec;
  long microsec = sonar_front.timing();
  char mensagem[8];
  char * command;
  cmMsec = sonar_front.convert(microsec, Ultrasonic::CM);

  command = malloc(sizeof(cmMsec+2));
  sprintf(mensagem, "%d", (int) cmMsec);
  strcpy(command, "F ");
  strcat(command, mensagem);
  Serial.println(command);
  
  send_data(command);

  //free(mensagem);
  //free(command);
}

void get_distance_right(){
  //Serial.println("Direita");
  float cmMsec;
  long microsec = sonar_right.timing();
  char * mensagem;
  char * command;
  sprintf(mensagem, "%f", cmMsec);
  //Serial.print("Enviando:");
  //Serial.println(mensagem);
  strcpy(command, "R ");
  strcat(command, mensagem);
  Serial.print("olha:");
  Serial.println(command);
  cmMsec = sonar_right.convert(microsec, Ultrasonic::CM);
  send_data(command);
  free(mensagem);
  free(command);
}

void get_distance_left(){
  //Serial.println("Esquerda");
  float cmMsec;
  long microsec = sonar_left.timing();
  char * mensagem;
  char * command;
  sprintf(mensagem, "%f", cmMsec);
  //Serial.print("Enviando:");
  //Serial.println(mensagem);
  strcpy(command, "L ");
  strcat(command, mensagem);
  Serial.print("olha:");
  Serial.println(command);
  cmMsec = sonar_left.convert(microsec, Ultrasonic::CM);
  send_data(command);

  free(mensagem);
  free(command);
}


