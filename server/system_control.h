#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;

struct range{
	int front;
	int right;
	int left;
	int dright;
	int dleft;
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

// void * process_data(void * socket_cliente){
// 	char * msg;//mensagem de retorno ao robo
// 	int front;
// 	int right;
// 	int left;
// 	int dleft;//Estão com R mas são os da diagonal
// 	int dright;//Estão com R mas são os da diagonal
// 	int socket = *((int*) socket_cliente);
// 	msg = malloc(sizeof(char*));

// 	//Inicializando todos com 100
// 	pthread_mutex_lock (&mutex);
// 	range.front = 100;
// 	range.left = 100;
// 	range.right = 100;
// 	range.dright = 100;
// 	range.dleft = 100;
// 	pthread_mutex_unlock (&mutex);
// 	infos.status = 'R';
	

// 	do{
// 		//Pegando os dados das distâncias.
// 		pthread_mutex_lock (&mutex);
// 		front  = range.front;
// 		right = range.right;
// 		left = range.left;
// 		dleft = range.dleft;
// 		dright = range.dright;
// 		pthread_mutex_unlock (&mutex);

		//Printando informações
		//printf("Front =[%d], ", front);
		//printf("Right =[%d], ", right);
		//printf("Left =[%d]\n", left);
		// printf("Diag direita =[%d],", dright);
		// printf("Diag esquerda =[%d]\n", dleft);


// 		if(infos.status = 'R'){//Se ele está rodando pelo ambiente..
// 			// if(front <= 20 || dright <=15 || dleft <= 15){
// 			// 	printf("Entrou <15\n");
// 				if(dleft > dright && dleft != 100 && dright != 100){
// 					printf("Virando esquerda..\n");
// 					strcpy(msg, "L 90");
// 					//virar para esquerda
// 					if(send(socket, msg, sizeof(msg), 0) != sizeof(msg)){
// 						printf("Erro no envio - send()\n");
// 					}
// 				}else{
// 					printf("Virando direita..");
// 					strcpy(msg, "R 90");
// 					//printf("%s\n", msg);
// 					if(send(socket, msg, sizeof(msg), 0) != sizeof(msg)){
// 						printf("Erro no envio - send()\n");
// 					}
// 				}
// 			// }else{
// 			// 	printf(">15\n");
// 			// }
// 		}else{//se ele estiver voltando para base..
// 			//lógica para retorno a base
// 		}
// 		sleep(1);
// 	}while(infos.status != 'S');
// 	if(send(socket, "S", sizeof(char), 0) != sizeof(char)){
// 		printf("Erro no envio - send()\n");
// 	}
// 	free(msg);
// }


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