#define _XOPEN_SOURCE
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

//gcc -o server server.c -dbg -lcrypt -lpthread

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
		printf("404 Not Found");
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

//Função utilizada para tratar toda a conexão com o cliente
void * get_distance(void * socket_cliente) {
	int tamanho_recebido, tamanho_envio, i=0;
	int socket = *((int*) socket_cliente);
	char * distance;
	distance = malloc(sizeof(char*));
	float limit = 5;

	//pega a info, retornando o tamanho dessa info
	printf("get_distance\n");
	do{
		printf("I = %d\n", i);
		if((tamanho_recebido = recv(socket, distance, sizeof(distance), 0)) < 0){
			printf("Erro no recv()\n");
		}else{
			if((int)*distance < 0){
				//nothing to do
			}else{
				printf("D = %d\n", *distance);
				printf("%d redebidos\n", tamanho_recebido);
			}
		}
		i++;
	}while(i<10);
	printf("Fim da funcao\n");
}


int main(int argc, char *argv[]) {
	pthread_t *thread;
	int socket_servidor;
	int socket_cliente;
	struct sockaddr_in servidorAddr;
	struct sockaddr_in clienteAddr;
	unsigned short servidorPorta;
	unsigned int cliente_length;

	thread = malloc(sizeof(pthread_t));
	if (argc != 2) { //Caso não tenha entrado com os parâmetros certos
		printf("Uso: %s <Porta>\n", argv[0]);
		exit(1);
	}
	servidorPorta = atoi(argv[1]);
	// Abrir Socket
	if((socket_servidor = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) //Gerando um socket tcp
		printf("falha no socket do Servidor\n");
	
	// Montando a estrutura sockaddr_in
	memset(&servidorAddr, 0, sizeof(servidorAddr)); // Zerando a estrutura de dados
	servidorAddr.sin_family = AF_INET;
	servidorAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servidorAddr.sin_port = htons(servidorPorta); //definindo a porta

	// Bind
	if(bind(socket_servidor, (struct sockaddr *) &servidorAddr, sizeof(servidorAddr)) < 0)
		printf("Falha no Bind\n");
	// Listen
	if(listen(socket_servidor, 10) < 0) //definindo uma fila máxima de 10 clientes aguardando
		printf("Falha no Listen\n");		
		cliente_length = sizeof(clienteAddr);
		if((socket_cliente = accept(socket_servidor, 
			                      (struct sockaddr *) &clienteAddr, 
			                      &cliente_length)) < 0){
			printf("Falha no Accept\n");
		}else{
			printf("Conexão do Cliente %s\n", inet_ntoa(clienteAddr.sin_addr));
			//Criando uma thread para gerenciar a conexão com o cliente
			//Possibilitando a conexão simultânea de diversos clientes.
			if(pthread_create(thread, NULL, get_distance, (void *)&socket_cliente)!= 0){
				printf("Erro ao criar a thread\n");
			}
			pthread_join(*thread, NULL);
		}	
		
		
	close(socket_cliente);
	close(socket_servidor);
}