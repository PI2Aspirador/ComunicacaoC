#include <Servo.h> 

#define velocityA 6
#define velocityB 7

#define PortPin2  2    // Motor A
#define PortPin3  3    // Motor A
#define PortPin4  4    // Motor B
#define PortPin5  5    // Motor B

void config_motors(){
  pinMode(PortPin2, OUTPUT);
  pinMode(PortPin3, OUTPUT);
  pinMode(PortPin4, OUTPUT);
  pinMode(PortPin5, OUTPUT);
  pinMode(velocityA, OUTPUT);
  pinMode(velocityB, OUTPUT);
}

void turn_to_left() {          //função drive_esquerda
  digitalWrite(PortPin2, LOW);     //Motor 1
  digitalWrite(PortPin3, HIGH);    //Motor 2
  digitalWrite(PortPin4, HIGH);    //Motor 1
  digitalWrite(PortPin5, LOW);     //Motor 2
}

void turn_to_right() {            //função drive_direita
  digitalWrite(PortPin2, HIGH);     //Motor 1
  digitalWrite(PortPin3, LOW);      //Motor 1
  digitalWrite(PortPin4, LOW);      //Motor 2
  digitalWrite(PortPin5, HIGH);     //Motor 2
}

void drive_stop() {               //função drive_stop
  digitalWrite(PortPin2, LOW);      //Motor 1
  digitalWrite(PortPin4, LOW);      //Motor 2
  digitalWrite(PortPin3, LOW);      //Motor 1
  digitalWrite(PortPin5, LOW);      //Motor 2
}

void drive_re() {                 //função drive_re
  digitalWrite(PortPin2, HIGH);     //Motor 1
  digitalWrite(PortPin3, LOW);      //Motor 1
  digitalWrite(PortPin4, HIGH);     //Motor 2
  digitalWrite(PortPin5, LOW);      //Motor 2
}

void drive_frente() {             //função drive_frente
  digitalWrite(PortPin2, LOW);      //Motor 1
  digitalWrite(PortPin3, HIGH);     //Motor 1
  digitalWrite(PortPin4, LOW);      //Motor 2
  digitalWrite(PortPin5, HIGH);     //Motor 2
}
