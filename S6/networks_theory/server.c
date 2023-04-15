#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<stdbool.h>
#include<unistd.h>

#define PORT 3333
#define PAYLOAD_SIZE 1024

typedef struct {
	int type;
	int seq_no;
	char payload[PAYLOAD_SIZE];
	int checksum;
} packet;

int a_count = 0;
int b_count = 0;
float time_dur = 0;
packet pkt;

bool is_packet_valid(packet *pkt) {
    	int checksum = 0;
    	char *p = (char *)pkt;
	for (int i = 0; i < sizeof(packet); i++) {
        	checksum ^= *p;
        	p++;
    	}
	return (pkt->checksum == checksum);
}

void *check_errors() {
	struct sockaddr_in server, client;
	int sockfd;
	socklen_t client_addr_len = sizeof(client);

	sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0) {
		printf("Error creating socket");
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

	if(recvfrom(sockfd, (void *)&pkt, sizeof(packet), 0, (struct sockaddr *)&client, &client_addr_len) < 0) {
		printf("Error receiving packet\n");
		exit(1);
	}
	
	if(!is_packet_valid(&pkt)) {
		printf("Error Detected in packet %d of type %d\n", pkt.seq_no, pkt.type);
	}

	close(sockfd);
	pthread_exit(0);
}

void *handle_A() {
	a_count++;
	printf("Received Type 1 packet: seq_no=%d\n", pkt.seq_no);

	pthread_exit(0);
}

void *handle_B() {
        b_count++;
        printf("Received Type 2 packet: seq_no=%d\n", pkt.seq_no);

	pthread_exit(0);
}

void *print_count() {
	for(int i = 0; i < 20; i++) {
		sleep(0.3);
		printf("\ta_count=%d\tb_count=%d\n", a_count, b_count);
	}

	pthread_exit(0);
}

int main() {
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
	close(sockfd);
	
	

	pthread_t tid[4];

	pthread_create(&tid[0], 0, check_errors, 0);
	pthread_create(&tid[1], 0, handle_A, 0);
	pthread_create(&tid[2], 0, handle_B, 0);

	for(int i = 0; i < 3; i++) {
		pthread_join(tid[i], NULL);
	}
	
	pthread_create(&tid[3], 0, print_count, 0);
	pthread_join(tid[3], NULL);

	return 0;
}
