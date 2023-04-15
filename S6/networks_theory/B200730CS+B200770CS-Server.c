#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<stdbool.h>
#include<unistd.h>
#include<semaphore.h>

#define PORT 3333
#define PAYLOAD_SIZE 1024

typedef struct {
	int type;
	int seq_no;
	char payload[PAYLOAD_SIZE];
	int checksum;
} packet;

struct node {
	packet pkt;
	struct node *next;
};

typedef struct node *node;

struct queue {
	node front;
	node back;
};

struct queue *Q;

int a_count = 0;
int b_count = 0;

//variables that show which type is at the front of queue
int flagA = 0;
int flagB = 0;
packet pkt;

//keep count of packets processed
int count = 0;

sem_t mutex, cnsole;

bool is_packet_valid(packet *pkt) {
    	int checksum = 0;
    	char *p = (char *)pkt->payload;
	for (int i = 0; i < sizeof(pkt->payload); i++) {
        	checksum ^= *p;
        	p++;
    	}
	return (pkt->checksum == checksum);
}

void *check_errors() {
	while(count++ < 20) {
		//printf("\tcount: %d\n", count);
		
		while(Q->front == NULL)
			;
		sem_wait(&mutex);
		
		packet x = Q->front->pkt;
		
		if(!is_packet_valid(&x)) {
			sem_wait(&cnsole);
			printf("Error Detected in Type %d packet: seq_no=%d\n", x.type, x.seq_no);
			sem_post(&cnsole);
			
			if(Q->front == NULL) {
				printf("BREAK\n");
				break;
			}
			
			node x = Q->front;
			Q->front = x->next;
			if(Q-> front == NULL)
				Q->back = NULL;
			sem_post(&mutex);
			
			free(x);
		} else {
			/*sem_wait(&cnsole);
			printf("%d: Error-Free\n", count);
			sem_post(&cnsole);*/
			//sem_wait(&mutex);
			if(x.type == 1) {
				flagA = 1;
			} else {
				flagB = 1;
			}
		}
	}
	
	sem_wait(&cnsole);
	printf("\tExiting Error Function\n");
	sem_post(&cnsole);
	pthread_exit(0);
}

void *handle_A() {
	while(count < 20) {
		while(flagA != 1)
			if(count >= 20)
				break;
		node x = Q->front;
		Q->front = x->next;
		if(Q->front == NULL)
			Q->back = NULL;
		flagA = 0;
		sem_post(&mutex);
		
		packet y = x->pkt;
		free(x);	
		a_count++;
		
		sem_wait(&cnsole);
		printf("Received Type 1 packet: seq_no=%d\n", y.seq_no);
		sem_post(&cnsole);
	}

	pthread_exit(0);
}

void *handle_B() {
        while(count < 20) {
		while(flagB != 1)
			if(count >= 20)
				break;
		node x = Q->front;
		Q->front = x->next;
		if(Q->front == NULL)
			Q->back = NULL;
		flagB = 0;
		sem_post(&mutex);
		
		packet y = x->pkt;
		free(x);	
		b_count++;
		
		sem_wait(&cnsole);
		printf("Received Type 2 packet: seq_no=%d\n", y.seq_no);
		sem_post(&cnsole);
	}
	
	pthread_exit(0);
}

void *print_count() {
	int i = 0;
	while(i < 20) {
		while(i == count && count < 20)
			;
		
		sleep(0.3);
		sem_wait(&cnsole);
		printf("\ta_count=%d\tb_count=%d\n", a_count, b_count);
		sem_post(&cnsole);
		
		i++;
	}

	sem_wait(&cnsole);
	printf("\tExiting print_count function\n");
	sem_post(&cnsole);
	pthread_exit(0);
}

node Create_Node(packet x) {
	node y = (node) malloc (sizeof(struct node));
	y->pkt = x;
	y->next = NULL;

	return y;
}

int main() {
	//initialize queue
	Q = (struct queue *) malloc (sizeof(struct queue));
	Q->front = NULL;
	Q->back = NULL;
	
	struct sockaddr_in server, client;
	socklen_t client_addr_len = sizeof client;

	int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1) {
		printf("Error creating socket\n");
		exit(1);
	}
	
	int yes = 1;
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1) {
		perror("setsockopt");
		exit(1);
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = INADDR_ANY;
	if(bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
		printf("Error binding socket\n");
		exit(1);
	}

	char msg[10];
	if(recvfrom(sockfd, msg, sizeof msg, 0, (struct sockaddr *)&client, &client_addr_len) < 0) {
		printf("Error receiving initialization\n");
		exit(1);
	}
	printf("Receiving Packets from Client...\n\n");	
	
	//Initialise the mutex
	sem_init(&mutex, 0, 1);
	sem_init(&cnsole, 0, 1);

	pthread_t tid[4];
	
	pthread_create(&tid[0], 0, check_errors, 0);
	pthread_create(&tid[1], 0, handle_A, 0);
	pthread_create(&tid[2], 0, handle_B, 0);
	pthread_create(&tid[3], 0, print_count, 0);

	for(int i = 0; i < 20; i++) {
		if(recvfrom(sockfd, (void *)&pkt, sizeof(packet), 0, (struct sockaddr *)&client, &client_addr_len) < 0) {
			printf("Error receiving packet\n");
			exit(1);
		}
		
		node x = Create_Node(pkt);
		if(Q->front == NULL) {
			sem_wait(&mutex);
			Q->front = Q->back = x;
			sem_post(&mutex);
		} else {
			sem_wait(&mutex);
			Q->back->next = x;
			Q->back = x;
			sem_post(&mutex);
		}
	}
	
	for(int i = 0; i < 4; i++) {
		pthread_join(tid[i], NULL);
	}

	sem_destroy(&mutex);
	sem_destroy(&cnsole);
	free(Q);
	return 0;
}
