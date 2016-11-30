#include <Ultrasonic.h>
#include "comunication.h"

#define echopin_f  24  //Sensor ultrassônico da frente
#define trigerpin_f 22 //Sensor ultrassônico da frente
#define echopin_f2  28  //Sensor ultrassônico da frente de baixo
#define trigerpin_f2 26 //Sensor ultrassônico da frente de baixo
#define echopin_r 32  //Sensor ultrassônico da direita 32
#define trigerpin_r 30 //Sensor ultrassônico da direita 30
#define echopin_l 36 //Sensor ultrassônico da esquerda 36
#define trigerpin_l 34 //Sensor ultrassônico da esquerda 34
#define echopin_dr 40  //Sensor ultrassônico da roda esquerda
#define trigerpin_dr 38  //Sensor ultrassônico da roda esquerda
#define echopin_dl 40  //Sensor ultrassônico da roda esquerda
#define trigerpin_dl 38  //Sensor ultrassônico da roda esquerda

//Inicializando o sonar
Ultrasonic sonar_front(trigerpin_f, echopin_f);
Ultrasonic sonar_right(trigerpin_r, echopin_r);
Ultrasonic sonar_left(trigerpin_l, echopin_l);
Ultrasonic sonar_rleft(trigerpin_dl, echopin_dl);
Ultrasonic sonar_rright(trigerpin_dr, echopin_dr);

void get_distance_front();
void get_distance_front2();
void get_distance_right();
void get_distance_left();
void get_distance_dleft();
void get_distance_dright();

void config_sonar(){
  pinMode(echopin_f, INPUT);
  pinMode(trigerpin_f, OUTPUT);
  pinMode(echopin_f2, INPUT);
  pinMode(trigerpin_f2, OUTPUT);
  pinMode(echopin_dr, INPUT);
  pinMode(trigerpin_dr, OUTPUT);
  pinMode(echopin_dl, INPUT);
  pinMode(trigerpin_dl, OUTPUT);
  pinMode(echopin_l, INPUT);
  pinMode(trigerpin_l, OUTPUT);
  pinMode(echopin_r, INPUT);
  pinMode(trigerpin_r, OUTPUT);
}

//L = left
//R = Right
//F = Front

//Função que pega a distância do sonar da frente (cima)
void get_distance_front() {
  float cmMsec;
  long microsec = sonar_front.timing();
  char mensagem[8];
  char * command;
  cmMsec = sonar_front.convert(microsec, Ultrasonic::CM);

  command = malloc(sizeof(cmMsec+2));
  sprintf(mensagem, "%d", (int) cmMsec);
  strcpy(command, "F ");
  strcat(command, mensagem);

  //Enviando comando pra rasp
  send_data(command);
  //Fazendo o mesmo com a frente 2 (de baixo)
  get_distance_front2();
  free(command);
}

//Função que pega a distância do sonar da frente (baixo)
void get_distance_front2() {
  float cmMsec;
  long microsec = sonar_front.timing();
  char mensagem[8];
  char * command;
  cmMsec = sonar_front.convert(microsec, Ultrasonic::CM);

  command = malloc(sizeof(cmMsec+2));
  sprintf(mensagem, "%d", (int) cmMsec);
  strcpy(command, "F ");
  strcat(command, mensagem);
  //Serial.println(command);
  
  send_data(command);
  //Fazendo o mesmo com a direita
  get_distance_right();
  free(command);
}

//Função que pega a distância do sonar da direita
void get_distance_right(){
  float cmMsec;
  long microsec = sonar_right.timing();
  char mensagem[8];
  char * command;
  cmMsec = sonar_right.convert(microsec, Ultrasonic::CM);

  command = malloc(sizeof(cmMsec+2));
  sprintf(mensagem, "%d", (int) cmMsec);
  strcpy(command, "D ");
  strcat(command, mensagem);
  //Serial.println(command);
  
  send_data(command);
  get_distance_left();

  free(command);
}

//Função que pega a distância do sonar da esquerda
void get_distance_left(){
  float cmMsec;
  long microsec = sonar_left.timing();
  char mensagem[8];
  char * command;
  cmMsec = sonar_left.convert(microsec, Ultrasonic::CM);

  command = malloc(sizeof(cmMsec+2));
  sprintf(mensagem, "%d", (int) cmMsec);
  strcpy(command, "E ");
  strcat(command, mensagem);
  //Serial.println(command);
  
  send_data(command);

  get_distance_dleft();
  free(command);
}

//Função que pega a distância do sonar da diagonal esquerda
void get_distance_dleft(){
   float cmMsec;
   long microsec = sonar_rleft.timing();
   char mensagem[8];
   char * command;
   cmMsec = sonar_rleft.convert(microsec, Ultrasonic::CM);

   command = malloc(sizeof(cmMsec+2));
   sprintf(mensagem, "%d", (int) cmMsec);
   strcpy(command, "E ");
   strcat(command, mensagem);
  
   send_data(command);

   get_distance_dright();

   free(command);
 }

//Função que pega a distância do sonar da diagonal direita
void get_distance_dright(){
   float cmMsec;
   long microsec = sonar_rright.timing();
   char mensagem[8];
   char * command;
   cmMsec = sonar_rright.convert(microsec, Ultrasonic::CM);

   command = malloc(sizeof(cmMsec+2));
   sprintf(mensagem, "%d", (int) cmMsec);
   strcpy(command, "D ");
   strcat(command, mensagem);
 
   send_data(command);

   free(command);
}
