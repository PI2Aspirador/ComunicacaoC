#include <Ultrasonic.h>
#include "comunication.h"

#define echopin_f  24  //Sensor ultrassônico da frente
#define trigerpin_f 22 //Sensor ultrassônico da frente
#define echopin_f2  28  //Sensor ultrassônico da frente de baixo
#define trigerpin_f2 26 //Sensor ultrassônico da frente de baixo
#define echopin_r 45  //Sensor ultrassônico da direita 32
#define trigerpin_r 43 //Sensor ultrassônico da direita 30
#define echopin_l 36 //Sensor ultrassônico da esquerda 36
#define trigerpin_l 34 //Sensor ultrassônico da esquerda 34
#define echopin_dr 44  //Sensor ultrassônico da roda direita
#define trigerpin_dr 42  //Sensor ultrassônico da roda direita
#define echopin_dl 40  //Sensor ultrassônico da roda esquerda
#define trigerpin_dl 38  //Sensor ultrassônico da roda esquerda

//INVERTER.. DIAGONAL ESQUERDA VIRANDO ESQUERDA!!!! 

//Inicializando o sonar
Ultrasonic sonar_front(trigerpin_f, echopin_f);
Ultrasonic sonar_front2(trigerpin_f2, echopin_f2);
Ultrasonic sonar_right(trigerpin_r, echopin_r);
Ultrasonic sonar_left(trigerpin_l, echopin_l);
Ultrasonic sonar_dleft(trigerpin_dl, echopin_dl);
Ultrasonic sonar_dright(trigerpin_dr, echopin_dr);

int get_distance_front();
int get_distance_front2();
int get_distance_dleft();
int get_distance_dright();

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

void get_distance(){
   float cmMsec;
   char mensagem[8];
   char * command;
   long microsec;

    microsec = sonar_left.timing();
    cmMsec = sonar_left.convert(microsec, Ultrasonic::CM); 
    Serial.print(".");
   if(cmMsec > 100){
    cmMsec = 90;
   }

   command = malloc(sizeof(cmMsec+2));
   sprintf(mensagem, "%d", (int) cmMsec);
   strcpy(command, mensagem);

    microsec = sonar_right.timing();
    cmMsec = sonar_right.convert(microsec, Ultrasonic::CM); 
    Serial.print("*");
   if(cmMsec > 100){
    cmMsec = 90;
   }

   Serial.println("EITA FI 3");
   
   strcat(command, ",");
   sprintf(mensagem, "%d", (int) cmMsec);
   strcat(command, mensagem);
   Serial.print("COMANDO: ");
   Serial.println(command);
   send_data(command);
   free(command);
}

//Função que pega a distância do sonar da frente (cima)
int get_distance_front() {
  float cmMsec;
  do{
    long microsec = sonar_front.timing();
  
    cmMsec = sonar_front.convert(microsec, Ultrasonic::CM);
  }while(cmMsec < 2);
  
  Serial.print("FRENTE1: ");
  Serial.println((int)cmMsec);
  return (int) cmMsec;
}

//Função que pega a distância do sonar da frente (baixo)
int get_distance_front2() {
  float cmMsec;
  do{
    long microsec = sonar_front.timing();
  
    cmMsec = sonar_front.convert(microsec, Ultrasonic::CM);
  }while(cmMsec < 2);
  
  Serial.print("FRENTE2: ");
  Serial.println((int)cmMsec);
  return (int) cmMsec;
}

//Função que pega a distância do sonar da diagonal esquerda
int get_distance_dleft(){
  float cmMsec;
  do{
    long microsec = sonar_dleft.timing();
    cmMsec = sonar_dleft.convert(microsec, Ultrasonic::CM);
    
  }while(cmMsec < 2 || cmMsec > 500);
  Serial.print("D ESQUERDA: ");
  Serial.println((int)cmMsec);
  return (int) cmMsec;
 }

//Função que pega a distância do sonar da diagonal direita
int get_distance_dright(){
  float cmMsec;
  //do{
     Serial.print(".");
    long microsec = sonar_dright.timing();
    cmMsec = sonar_dright.convert(microsec, Ultrasonic::CM);
  //}while(cmMsec < 2 || cmMsec > 500);
  
  Serial.print("D DIREITA: ");
  Serial.println((int)cmMsec);
  return (int) cmMsec;
}
