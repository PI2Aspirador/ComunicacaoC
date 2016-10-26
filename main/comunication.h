#include "connection.h"
#include "util.h"
#include "motors.h"

char read_data();

//Envia dados a raspberry
void send_data(char * msg){
    //Serial.print("Send Data:");
    //Serial.println(msg);
    wifi.send((const uint8_t*)msg, strlen(msg));
}

//Escuta informações da raspberry
void listen_infos(){
  uint8_t buffer[128] = {0};
  uint32_t len = wifi.recv(buffer, sizeof(buffer), 1000);
    if (len > 0) {
        Serial.print("Received:[");
        for(uint32_t i = 0; i < len; i++) {
            Serial.print((char)buffer[i]);
        }
        Serial.print("]\r\n");
    }
}

