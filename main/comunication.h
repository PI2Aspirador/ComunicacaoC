#include "connection.h"
#include "util.h"
#include "motors.h"

char read_data();

//Envia dados a raspberry
void send_data(char * msg){
    strcat(msg, "\0");
    wifi.send((const uint8_t*)msg, strlen(msg));
}

//Escuta informações da raspberry
void listen_infos(){
  uint8_t buffer[128] = {0};
  uint32_t len = wifi.recv(buffer, sizeof(buffer), 1000);
    if (len > 0) {
        Serial.print("Recebido:[");
        for(uint32_t i = 0; i < len; i++) {
            Serial.print((char)buffer[i]);
        }
        Serial.print("]\r\n");
        if(buffer[0] == 'L'){
            drive_stop();
            delay(1000);
            turn_to_left();
            delay(1200);
            //drive_frente();
        }else{
            if(buffer[0] == 'R'){
                drive_stop();
                delay(1000);
                turn_to_right();
                delay(1200);
                //drive_frente();
            }
            if(buffer[0] == 'S'){
                drive_stop();
            }
        }
    }
}

