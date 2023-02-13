#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>

int main() {
	int sockfd;
	struct sockaddr_in server, client, root;
	char query[50], response[50];

	// Create socket for client
	sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1) {
		perror("socket");
		return 1;
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(1234);
	server.sin_addr.s_addr = INADDR_ANY;
	if(bind(sockfd, (struct sockaddr *)&server, sizeof server) < 0) {
		perror("bind");
		return 1;
	}

	printf("Running DNS Server...\n\n");

	// Create socket for root server
	int sock2 = socket(PF_INET, SOCK_DGRAM, 0);
	if(sock2 == -1) {
		perror("sock2");
		return 1;
	}

	root.sin_family = AF_INET;
	root.sin_port = htons(1235);
	root.sin_addr.s_addr = inet_addr("127.0.0.1");

	while(1) {
		int len = sizeof client;
		memset(query, 0, sizeof query);
		int n = recvfrom(sockfd, query, sizeof query, 0, (struct sockaddr *)&client, &len);

		if(n < 0) {
			printf("Error receiving data from client\n");
			return 1;
		}

		if(n == 0)
			break;

		char dupl[50];
		strcpy(dupl, query);
		char *token = strtok(dupl, ":");
		printf("Received DNS query for %s\n", token);

		printf("Sending query to root server...\n");

		//printf("\t%s\n", query);
		if(sendto(sock2, query, n, 0, (struct sockaddr *)&root, sizeof root) < 0) {
			printf("Failed to send query to root server\n");
			return 1;
		}

		memset(response, 0, sizeof response);
		len = sizeof root;
		n = recvfrom(sock2, response, sizeof response, 0, (struct sockaddr *)&root, &len);	

		if(n < 0) {
			printf("Failed to receive response from root server\n");
			return 1;
		}

		printf("Received response from root server\nSending response to client...\n");

		if(sendto(sockfd, response, n, 0, (struct sockaddr *)&client, sizeof client) < 0) {
			printf("Failed to send response to client\n");
			return 1;
		}
		printf("Response Sent\n\n");
	}

	close(sockfd);
	close(sock2);
}
