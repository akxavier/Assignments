#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<poll.h>

#define PORT 9034

int main(int argc, char *argv[]) {
	int sockfd;
	struct sockaddr_in server;
	char msg[100], server_msg[100];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1) {
		printf("Error creating socket\n");
		return 1;
	}

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(9034);

	if(connect(sockfd, (struct sockaddr *) &server, sizeof server) < 0) {
		printf("Connection failed\n");
		return 1;
	}
	printf("Connected to server...\n\n");

	struct pollfd pfds[2];

	pfds[0].fd = 0;
	pfds[0].events = POLLIN;

	pfds[1].fd = sockfd;
	pfds[1].events = POLLIN;

	while(1) {
		int n = poll(pfds, 2, -1);

		if(pfds[0].revents & POLLIN) {
			// if stdin is ready to read

			memset(msg, 0, sizeof msg);
		
			scanf("%[^\n]%*c", msg);
			//scanf("%s", msg);
			//fgets(msg, 100, stdin);

			if(strcmp(msg, "/exit") == 0 || strcmp(msg, "/quit") == 0 || strcmp(msg, "/part") == 0)
				break;

			int len = strlen(msg) * sizeof(char);
			if(send(sockfd, msg, len, 0) < 0) {
				printf("Failed to send message\n");
				return 1;
			}
		}

		if(pfds[1].revents & POLLIN) {
			//socket is ready to read
			memset(server_msg, 0, sizeof server_msg);

			if(recv(sockfd, server_msg, 100, 0) < 0) {
				printf("recv failed\n");
				return 1;
			}

			puts(server_msg);
		}
	}

	close(sockfd);

	printf("Disconnected from server\n");
	return 0;
}
