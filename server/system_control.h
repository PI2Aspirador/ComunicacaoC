#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

struct range{
	int front;
	int right;
	int left;
};

struct info{
	char status;//R para running, B para Back.
	int socket;
};

struct range range;
struct info infos;


char verify_distance(int distance){
	if(distance < 15){
		return 'R';
	}else{
		return 'G';
	}
}

void * process_data(){
	char * msg;//mensagem de retorno ao robo
	range.front = 100;
	range.left = 100;
	range.right = 100;
	infos.status = 'R';
	printf("Entrou aqui\n");
	do{
		printf("Front =[%d], ", range.front);
		printf("Right =[%d], ", range.right);
		printf("Left =[%d]\n", range.left);
		if(infos.status = 'R'){//Se ele está rodando pelo ambiente..
			if(range.front <= 15){
				printf("Entrou <15\n");
				if(range.left > range.right){
					printf("Virando esquerda..");
					//virar para esquerda
					msg = "L 90";
					if(send(infos.socket, msg, sizeof(msg), 0) != sizeof(msg)){
						printf("Erro no envio - send()\n");
					}
				}else{
					printf("Virando direita..");
					msg = "R 90";
					if(send(infos.socket, msg, sizeof(msg), 0) != sizeof(msg)){
						printf("Erro no envio - send()\n");
					}
				}
			}else{
				printf(">15\n");
			}
		}else{//se ele estiver voltando para base..
			//lógica para retorno a base
		}
	}while(infos.status != 'S');
}


// char * hash_data(char *texto){//Criando hash da mensagem:
// 	texto = crypt(texto, "ab");
//     return texto;
// }

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