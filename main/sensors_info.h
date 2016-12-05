#include <Ultrasonic.h>
#include "comunication.h"

#define echopin_f  26  //Sensor ultrassônico da frente
#define trigerpin_f 27 //Sensor ultrassônico da frente
#define echopin_r 24  //Sensor ultrassônico da direita 32
#define trigerpin_r 25 //Sensor ultrassônico da direita 30
#define echopin_l 30 //Sensor ultrassônico da esquerda 36
#define trigerpin_l 31 //Sensor ultrassônico da esquerda 34
#define echopin_dr 22  //Sensor ultrassônico da roda direita
#define trigerpin_dr 23  //Sensor ultrassônico da roda direita
#define echopin_dl 28  //Sensor ultrassônico da roda esquerda
#define trigerpin_dl 29  //Sensor ultrassônico da roda esquerda

//INVERTER.. DIAGONAL ESQUERDA VIRANDO DIREITA!!!! 

//Inicializando o sonar
Ultrasonic sonar_front(trigerpin_f, echopin_f);
Ultrasonic sonar_right(trigerpin_r, echopin_r);
Ultrasonic sonar_left(trigerpin_l, echopin_l);
Ultrasonic sonar_dleft(trigerpin_dl, echopin_dl);
Ultrasonic sonar_dright(trigerpin_dr, echopin_dr);

int get_distance_front();
int get_distance_dleft();
int get_distance_dright();

void config_sonar(){
  pinMode(echopin_f, INPUT);
  pinMode(trigerpin_f, OUTPUT);
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
   char * mensagem;
   char * command;
   long  microsec;
   int i;
   float soma=0;
    for(i=0 ; i<5 ; i++){
      microsec = sonar_dleft.timing();//É a direita
      cmMsec = sonar_dleft.convert(microsec, Ultrasonic::CM); 
      if(cmMsec > 100){
        cmMsec = 90;
      }  
      soma += cmMsec;
    }

    soma = soma/5;
    

    command = malloc(sizeof(char*));
    mensagem = malloc(sizeof(char*));
    sprintf(mensagem, "%d", (int) soma);
    strcpy(command, mensagem);

    soma = 0;
    for(i=0 ; i<5 ; i++){
      microsec = sonar_left.timing();//É a esquerda
      cmMsec = sonar_left.convert(microsec, Ultrasonic::CM); 
      if(cmMsec > 100){
        cmMsec = 90;
      }
      soma += cmMsec;
    }

    soma = soma/5;
  
   strcat(command, ",");
   sprintf(mensagem, "%d", (int) soma);
   strcat(command, mensagem);
   Serial.print("DADOS: ");
   Serial.println(command);
   send_data(command);
   free(command);
   free(mensagem);
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
