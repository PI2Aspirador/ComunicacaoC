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
	int rright;
	int rleft;
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

void * process_data(void * socket_cliente){
	char * msg;//mensagem de retorno ao robo
	int front;
	int right;
	int left;
	int rleft;
	int rright;
	int socket = *((int*) socket_cliente);
	msg = malloc(sizeof(char*));
	pthread_mutex_lock (&mutex);
	range.front = 100;
	range.left = 100;
	range.right = 100;
	range.rright = 100;
	range.rleft = 100;
	pthread_mutex_unlock (&mutex);
	infos.status = 'R';
	printf("Entrou aqui\n");
	do{
		//Pegando os dados das distâncias.
		pthread_mutex_lock (&mutex);
		front  = range.front;
		right = range.right;
		left = range.left;
		rleft = range.rleft;
		rright = range.rright;
		pthread_mutex_unlock (&mutex);

		//Printando informações
		printf("Front =[%d], ", front);
		printf("Right =[%d], ", right);
		printf("Left =[%d]\n", left);
		//printf("Roda direita =[%d],", rright);
		//printf("Roda esquerda =[%d]\n", rleft);


		if(infos.status = 'R'){//Se ele está rodando pelo ambiente..
			if(front <= 15 || right <=15 || left <= 15){
				printf("Entrou <15\n");
				//printf("vaaaai\n");
				if(rleft > rright){
					printf("Virando esquerda..\n");
					strcpy(msg, "L 90");
					//virar para esquerda
					if(send(socket, msg, sizeof(msg), 0) != sizeof(msg)){
						printf("Erro no envio - send()\n");
					}
				}else{
					printf("Virando direita..");
					//msg = "R 90";
					//printf("%s\n", msg);
					if(send(socket, "R 90", sizeof(char*), 0) != sizeof(char*)){
						printf("Erro no envio - send()\n");
					}
				}
			}else{
				printf(">15\n");
			}
		}else{//se ele estiver voltando para base..
			//lógica para retorno a base
		}
		sleep(1);
	}while(infos.status != 'S');
	if(send(socket, "S", sizeof(char), 0) != sizeof(char)){
		printf("Erro no envio - send()\n");
	}
	free(msg);
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