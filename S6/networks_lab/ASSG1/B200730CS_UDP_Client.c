#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in server;
    char message[1000], server_reply[2000];

    // Create socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
        printf("Could not create socket");
    }
    puts("Socket created\n");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(9876);

    // Send some data
    while(1) {
		printf("Enter Text: ");
		scanf("%s", message);
			
		if (sendto(sock, message, strlen(message), 0, (struct sockaddr *)&server, sizeof(server)) < 0) {
		    puts("Send failed");
		    return 1;
		}
		printf("Data sent: %s\n", message);

		if(strcmp(message, "exit()") == 0)
			break;
			
		// Receive a reply from the server
		int len = sizeof(server);
		memset(server_reply, 0, sizeof server_reply);
		if (recvfrom(sock, server_reply, 2000, 0, (struct sockaddr *)&server, &len) < 0) {
		    puts("recv failed");
		}
		printf("Reply received: %s\n\n", server_reply);
	}
    close(sock);
    return 0;
}

