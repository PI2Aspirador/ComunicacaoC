#include <Ultrasonic.h>
#include "comunication.h"

#define echopin_f  24  //Sensor ultrassônico da frente
#define trigerpin_f 22 //Sensor ultrassônico da frente
#define echopin_f2  28  //Sensor ultrassônico da frente de baixo
#define trigerpin_f2 26 //Sensor ultrassônico da frente de baixo
#define echopin_r 32  //Sensor ultrassônico da direita 28
#define trigerpin_r 30 //Sensor ultrassônico da direita 26
#define echopin_l 36 //Sensor ultrassônico da esquerda 32
#define trigerpin_l 34 //Sensor ultrassônico da esquerda 30
// #define echopin_rd 40  //Sensor ultrassônico da roda esquerda
// #define trigerpin_rd 38  //Sensor ultrassônico da roda esquerda
// #define echopin_rl 36  //Sensor ultrassônico da roda esquerda
// #define trigerpin_rl 34  //Sensor ultrassônico da roda esquerda

//Inicializando o sonar
Ultrasonic sonar_front(trigerpin_f, echopin_f);
Ultrasonic sonar_right(trigerpin_r, echopin_r);
Ultrasonic sonar_left(trigerpin_l, echopin_l);
// Ultrasonic sonar_rleft(trigerpin_rl, echopin_rl);
// Ultrasonic sonar_rright(trigerpin_rd, echopin_rd);

void get_distance_front();
void get_distance_front2();
void get_distance_right();
void get_distance_left();
// void get_distance_rleft();
// void get_distance_rright();

void config_sonar(){
  pinMode(echopin_f, INPUT);
  pinMode(trigerpin_f, OUTPUT);
  pinMode(echopin_f2, INPUT);
  pinMode(trigerpin_f2, OUTPUT);
  // pinMode(echopin_rd, INPUT);
  // pinMode(trigerpin_rd, OUTPUT);
  // pinMode(echopin_rl, INPUT);
  // pinMode(trigerpin_rl, OUTPUT);
  pinMode(echopin_l, INPUT);
  pinMode(trigerpin_l, OUTPUT);
  pinMode(echopin_r, INPUT);
  pinMode(trigerpin_r, OUTPUT);
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
  //Serial.println(command);
  
  send_data(command);
  //get_distance_right();//Fazendo o mesmo com a direita
  get_distance_front2();
  free(command);
}

void get_distance_front2() {
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
  //Serial.println(command);
  
  send_data(command);
  //get_distance_right();//Fazendo o mesmo com a direita
  get_distance_right();
  free(command);
}

void get_distance_right(){
 //Serial.println("Frente");
  float cmMsec;
  long microsec = sonar_right.timing();
  char mensagem[8];
  char * command;
  cmMsec = sonar_right.convert(microsec, Ultrasonic::CM);

  command = malloc(sizeof(cmMsec+2));
  sprintf(mensagem, "%d", (int) cmMsec);
  strcpy(command, "R ");
  strcat(command, mensagem);
  //Serial.println(command);
  
  send_data(command);
  get_distance_left();

  free(command);
}

void get_distance_left(){
  //Serial.println("Frente");
  float cmMsec;
  long microsec = sonar_left.timing();
  char mensagem[8];
  char * command;
  cmMsec = sonar_left.convert(microsec, Ultrasonic::CM);

  command = malloc(sizeof(cmMsec+2));
  sprintf(mensagem, "%d", (int) cmMsec);
  strcpy(command, "L ");
  strcat(command, mensagem);
  //Serial.println(command);
  
  send_data(command);

  //get_distance_rleft();
  free(command);
}

// void get_distance_rleft(){
//   //Serial.println("Frente");
//   float cmMsec;
//   long microsec = sonar_rleft.timing();
//   char mensagem[8];
//   char * command;
//   cmMsec = sonar_rleft.convert(microsec, Ultrasonic::CM);

//   command = malloc(sizeof(cmMsec+2));
//   sprintf(mensagem, "%d", (int) cmMsec);
//   strcpy(command, "E ");
//   strcat(command, mensagem);
//   //Serial.println(command);
  
//   send_data(command);

//   get_distance_rright();

//   free(command);
// }

// void get_distance_rright(){
//   //Serial.println("Frente");
//   float cmMsec;
//   long microsec = sonar_rright.timing();
//   char mensagem[8];
//   char * command;
//   cmMsec = sonar_rright.convert(microsec, Ultrasonic::CM);

//   command = malloc(sizeof(cmMsec+2));
//   sprintf(mensagem, "%d", (int) cmMsec);
//   strcpy(command, "D ");
//   strcat(command, mensagem);
//   //Serial.println(command);
  
//   send_data(command);

//   free(command);
// }
