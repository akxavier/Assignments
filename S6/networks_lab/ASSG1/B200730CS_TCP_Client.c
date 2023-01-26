#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in server;
    char msg[100], server_msg[100];

    // Create socket
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Could not create socket");
	return 1;
    }
    puts("Socket created\n");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(9876);

    // Connect to remote server
    if(connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connection failed\n");
        return 1;
    }

    puts("Connection established\n");

    // Send message to server
    while(1) {
	 	 printf("Enter message: ");
         scanf("%s", msg);
         
         if(strcmp(msg, "exit()") == 0)
         	break;
         if(send(sockfd, msg, strlen(msg), 0) < 0) {
		    puts("Send failed");
		    return 1;
		}
    	printf("Sent message to server: %s\n", msg);

		// Receive a reply from the server
		if (recv(sockfd, server_msg, 100, 0) < 0)
		{
		    puts("recv failed");
		}
		printf("Server reply: %s\n\n", server_msg);
    }

    close(sockfd);

    printf("\nConnection closed\n");
    return 0;
}

