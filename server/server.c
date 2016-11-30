#include "system_control.h"

//gcc -o server server.c -dbg -lcrypt -lpthread

//Função utilizada para tratar toda a conexão com o cliente
void * get_distance(void * socket_cliente) {
	int tamanho_recebido, tamanho_envio, i=0, j=0;
	int socket = *((int*) socket_cliente);
	pthread_t work_data;
	char * msg;
	char *distance_right;
	char *distance_left;
	msg = malloc(sizeof(char*));
	distance_left = malloc(sizeof(char*));
	distance_right = malloc(sizeof(char*));
	char result;
	pthread_mutex_init(&mutex, NULL);

	//criando a thread que vai analisar e processar o conteudo recebido pelo arduino nesta conexão.
	// if(pthread_create(&work_data, NULL, process_data, (void *)&socket)!= 0){
	// 	printf("Erro ao criar a thread\n");
	// }

	do{
		if((tamanho_recebido = recv(socket, msg, 200, 0)) < 0){
			printf("Erro no recv()\n");
		}else{
			if((int)*msg < 0){
				//nothing to do
			}else{
				//msg[tamanho_recebido] = '\0';
				//printf("RECEBI MENSAGEM: %s\n", msg);
				i=0;
				while(msg[i] != ','){
					distance_right[i] = msg[i];
					i++;
				}
				i++;
				printf("DISTANCIA DIREITA: %d\n", atoi(distance_right));
				j=0;
				while(msg[i] != '\0'){
					distance_left[j] = msg[i];
					i++;
					j++;
				}
				distance_left[j] = '\0';

				printf("DISTANCIA ESQUERDA: %d\n", atoi(distance_left));

				if(atoi(distance_right) < atoi(distance_left)){
					printf("Virando esquerda..\n");
					strcpy(msg, "L 90");
					//virar para esquerda
					if(send(socket, msg, sizeof(msg), 0) != sizeof(msg)){
						printf("Erro no envio - send()\n");
					}
				} else{
					printf("Virando direita..");
					strcpy(msg, "R 90");
					//printf("%s\n", msg);
					if(send(socket, msg, sizeof(msg), 0) != sizeof(msg)){
						printf("Erro no envio - send()\n");
					}
				}
				
			}
		}
	}while(1);
	infos.status = 'S';
	free(msg);
	pthread_join(work_data, NULL);
	pthread_mutex_destroy(&mutex);
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