#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc, char *argv[]) {
	int sockfd, client_sock, read_len, c;
	struct sockaddr_in server, client;
	char client_msg[100];

	//Create socket
	sockfd = socket(PF_INET, SOCK_STREAM, 0);

	if(sockfd == -1) {
		printf("Could not create socket\n");
		return 1;
	}
	printf("Socket created\n");

	//Prepare sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(9876);

	//Bind
	if(bind(sockfd, (struct sockaddr *) &server, sizeof(server)) < 0) {
		perror("Bind failed\n");
		return 1;
	}
	printf("Bind success\n\n");

	//Listen for incoming connections
	listen(sockfd, 5);

	printf("Waiting for incoming connections...\n\n");
	c = sizeof(struct sockaddr_in);

	//Accept an incoming connection
	client_sock = accept(sockfd, (struct sockaddr *) &client, (socklen_t *) &c);
	if(client_sock < 0) {
		perror("Accept failed\n");
		return 1;
	}

	printf("Connection established\n\n");

	//Reading from client
	while((read_len = recv(client_sock, client_msg, 100, 0)) > 0) {
		printf("Text received from client: %s\n", client_msg);

		int n = strlen(client_msg);
		for(int i = 0, j = n - 1; i < j; i++, j--) {
			char temp = client_msg[i];
			client_msg[i] = client_msg[j];
			client_msg[j] = temp;
		}

		printf("Reversed text: %s\n\n", client_msg);
		send(client_sock, client_msg, 100, 0);
		memset(client_msg, 0, sizeof client_msg);
	}

	if(read_len == 0) {
		printf("\nClient disconnected\n");
	}
	else if(read_len == -1) {
		perror("recv failed\n");
		return 1;
	}

	return 0;
}
