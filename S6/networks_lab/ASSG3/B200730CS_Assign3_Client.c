#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

int main() {
	int sockfd;
	struct sockaddr_in dns;
	char url[50], query[50], response[50], type[10];

	// Create socket
	sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1) {
		perror("socket");
		return(1);
	}

	dns.sin_addr.s_addr = inet_addr("127.0.0.1");
	dns.sin_port = htons(1234);
	dns.sin_family = AF_INET;

	while(1) {
		printf("Enter URL: ");
		memset(url, 0, sizeof url);
		scanf("%s", url);

		if(strlen(url) == 0)
			break;

		printf("Enter record type: ");
		memset(type, 0, sizeof type);
		scanf("%s", type);

		if((strcmp(type, "a") != 0) && (strcmp(type, "ns") != 0)) {
			printf("ERR: Invalid type\n\n");
			continue;
		}

		memset(query, 0, sizeof query);
		strcpy(query, url);
		strcat(query, ":");
		strcat(query, type);

		if(sendto(sockfd, query, strlen(query)*sizeof(char), 0, (struct sockaddr *)&dns, sizeof dns) < 0) {
			perror("send");
			return 1;
		}

		socklen_t len = sizeof dns;
		memset(response, 0, sizeof response);

		if(recvfrom(sockfd,response, 100, 0, (struct sockaddr *)&dns, &len) < 0) {
			perror("recv");
			return 1;
		}

		if(strcmp(type, "a") == 0) {
			printf("\nName: %s\n", url);
			printf("Address: %s\n\n", response);
		} else if(strcmp(type, "ns") == 0) {
			printf("\nnameserver: %s\n\n", response);
		}
	}

	close(sockfd);
}

