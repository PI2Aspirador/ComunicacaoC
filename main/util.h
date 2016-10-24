#define pino_red 12
#define pino_green 12
#include <Utility.h>

void print_red();
void print_green();

void print_red() {
  Serial.println("Eita que entrou RED");
  digitalWrite(pino_green, LOW);
  delay(50);
  digitalWrite(pino_red, HIGH);
}

void print_green() {
  Serial.println("Eita que entrou GREEN");
  //digitalWrite(pino_red, LOW);
  //delay(50);
  digitalWrite(pino_green, HIGH);
}

void low_green(){
  digitalWrite(pino_green, LOW);
}

void print_exit(){
  Serial.print("Saindo...\n");
  digitalWrite(pino_green, HIGH);
  digitalWrite(pino_red, HIGH);
  delay(2000);
  digitalWrite(pino_green, LOW);
  digitalWrite(pino_red, LOW);
}

