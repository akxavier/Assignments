#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>

#define PORT 3333

typedef struct {
	int type;
	int seq_no;
	char payload[1024];
	char checksum;
}packet;

sem_t mutex;

//clock_t t1, t2;

int calc_checksum(packet *pkt) {
	int checksum = 0;
	char *p = (char *) pkt;

	for(int i = 0; i < sizeof (packet); i++) {
		checksum ^= *p;
		p++;
	}

	return checksum;
}

void *send_A() {
	int sockfd;
	struct sockaddr_in server;
	
	sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1) {
		puts("Socket creation failed");
		exit(1);
	}
	printf("Socket Created For Type A Packets...\n\n");
	sleep(3);

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);

	packet pkt;

	for(int i = 0; i < 10; i++) {
		sleep(0.1);
		
		pkt.type = 1;
		pkt.seq_no = i;
		memset(pkt.payload, 'A', 1024);
		pkt.checksum = calc_checksum(&pkt);

		sem_wait(&mutex);
		//t2 = clock();
		sendto(sockfd, (void *)&pkt, sizeof pkt, 0, (struct sockaddr *)&server, sizeof server);
		printf("Packet 1 Sent: seq_no=%d\n", i);
		sem_post(&mutex);
	}

	close(sockfd);
	pthread_exit(NULL);
}

void *send_B() {
	sleep(0.1);
        int sockfd;
        struct sockaddr_in server;

        sockfd = socket(PF_INET, SOCK_DGRAM, 0);
        if(sockfd == -1) {
                puts("Socket creation failed");
                exit(1);
        }
        printf("Socket Created For Type B Packets...\n\n");
        sleep(3);

        server.sin_addr.s_addr = inet_addr("127.0.0.1");
        server.sin_family = AF_INET;
        server.sin_port = htons(PORT);

        packet pkt;

        for(int i = 0; i < 10; i++) {
        	sleep(0.15);
        	
                pkt.type = 2;
                pkt.seq_no = i;
                memset(pkt.payload, 'B', 1024);
                pkt.checksum = calc_checksum(&pkt);

		sem_wait(&mutex);
		//t2 = clock();
                sendto(sockfd, (void *)&pkt, sizeof pkt, 0, (struct sockaddr *)&server, sizeof server);
                printf("\tPacket 2 Sent: seq_no=%d\n", i);
                sem_post(&mutex);
        }

        close(sockfd);
        pthread_exit(NULL);
}

int main() {
	sem_init(&mutex, 0, 1);
	struct sockaddr_in server;
	
	int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1) {
		puts("Socket creation failed");
		exit(1);
	}
	char msg[] = "Hello";
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	
	sendto(sockfd, msg, sizeof(msg), 0, (struct sockaddr *)&server, sizeof server);
	printf("Sending Packets to Server\n");
	pthread_t sender[2];

	//t1 = clock();
	
	pthread_create(&sender[0], 0, send_A, 0);
	pthread_create(&sender[1], 0, send_B, 0);
	pthread_join(sender[0], NULL);
	pthread_join(sender[1], NULL);
	
	sem_destroy(&mutex);
}
