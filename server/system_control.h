#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

char verify_distance(int distance){
	if(distance < 15){
		return 'R';
	}else{
		return 'G';
	}
}


char * hash_data(char *texto){//Criando hash da mensagem:
	texto = crypt(texto, "ab");
    return texto;
}
