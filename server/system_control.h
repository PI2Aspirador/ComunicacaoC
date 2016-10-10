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

//Função para pegar a informação presente no arquivo demandado pelo cliente.
char * get_data(char *texto){
	char * data;
	char * texto_completo;
	FILE *fp;

	fp = fopen(texto, "r");//abrindo arquivo somente para leitura
	if(fp == NULL){//Caso não encontre o arquivo
		printf("\n404 Not Found\n");
		return "404 Not Found\n";
	}

	data = malloc(sizeof(char*));
	texto_completo = malloc(sizeof(char*));

	while(fgets(data, 100, (FILE*)fp) != NULL){//Enquanto não chegar ao fim do arquivo
		strcat(texto_completo, data);//concatenando cada linha do arquivo para gerar o texto completo
	}

	fclose(fp);
	return texto_completo;//Retorna o conteudo do arquivo
}