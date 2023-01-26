#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sockfd;
    struct sockaddr_in server, client;
    char buffer[1024];
    int n;

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        printf("Error creating socket.\n");
        return 1;
    }
    printf("Socket created.\n");

    // Bind socket to address and port
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(9876);
    if (bind(sockfd, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Error binding socket.\n");
        return 1;
    }
    printf("Bind Success\n\n");

    // Receive data from client
    while(1) {
		int len = sizeof(client);
		memset(buffer, 0, sizeof buffer);
		n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &client, &len);
		
		if(strcmp(buffer, "exit()") == 0)
			break;
			
		if (n < 0) {
		    printf("Error receiving data from client.\n");
		    return 1;
		}
		
		printf("Received from client: %s\n", buffer);

		// Reverse string
		int i, j;
		char temp;
		for (i = 0, j = strlen(buffer) - 1; i < j; i++, j--) {
		    temp = buffer[i];
		    buffer[i] = buffer[j];
		    buffer[j] = temp;
		}

		// Send reversed string to client
		n = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *) &client, sizeof(client));
		if (n < 0) {
		    printf("Error sending reversed string to client.\n");
		    return 1;
		}
		printf("Sent to client: %s\n", buffer);
	}

    // Close socket
    close(sockfd);
    return 0;
}
