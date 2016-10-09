#define pino_red 13
#define pino_green 12
#include <Utility.h>

void print_red();
void print_green();

void print_red() {
  digitalWrite(pino_red, HIGH);
  delay(100);
  digitalWrite(pino_red, LOW);
  delay(100);
  digitalWrite(pino_red, HIGH);
  delay(100);
  digitalWrite(pino_red, LOW);
}

void print_green() {
  digitalWrite(pino_green, HIGH);
  delay(100);
  digitalWrite(pino_green, LOW);
  delay(100);
  digitalWrite(pino_green, HIGH);
  delay(100);
  
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

