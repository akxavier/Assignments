#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>

struct NS {
	char name[50];
	int port;
	char nameserver[50];
};

struct NS nameservers[3] = {
	{
		"www.google.com",
		1238,
		"ns1.google.com",
	},
	{
		"www.yahoo.com",
		1239,
		"wg1.b.yahoo.com",
	},
	{
		"mail.google.com",
		1238,
		"ns1.google.com"
	},
};
int ns_count = 3;

int main() {
	int sockfd;
	struct sockaddr_in server, root, nserver;
	char query[50], response[50];

	// Create socket for DNS server
	sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1) {
		perror("socket");
		return 1;
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(1236);
	server.sin_addr.s_addr = INADDR_ANY;
	if(bind(sockfd, (struct sockaddr *)&server, sizeof server) < 0) {
		perror("bind");
		return 1;
	}

	printf("Running COM TLD Server...\n\n");

	// Create socket for TLD server
	int sock2 = socket(PF_INET, SOCK_DGRAM, 0);
	if(sock2 == -1) {
		perror("sock2");
		return 1;
	}

	while(1) {
		int len = sizeof root;
		memset(query, 0, sizeof query);
		int n = recvfrom(sockfd, query, sizeof query, 0, (struct sockaddr *)&root, &len);

		if(n < 0) {
			printf("Error receiving data from root server\n");
			return 1;
		}

		if(n == 0)
			break;
		//printf("\t%s\n", query);

		char *token = strtok(query, ":");
		// token now has url
		printf("Received query for %s ", token);

		char url[50];
		memset(url, 0, sizeof url);
		strcpy(url, token);

		token = strtok(NULL, ":");
		// token now has type
		printf("of type %s\n", token);

		int i;
		for(i = 0; i < ns_count; i++) {
			if(strcmp(url, nameservers[i].name) == 0) {
				break;
			}
		}

		if(i == ns_count) {
			printf("Record NOT FOUND\n");
			memset(response, 0, sizeof response);
			strcpy(response, "Record NOT FOUND");
		} 
		else if(strcmp(token, "ns") == 0) {
			printf("Name server found\n");
			memset(response, 0, sizeof response);
			strcpy(response, nameservers[i].nameserver);
		} 
		else if(strcmp(token, "a") == 0) {
			nserver.sin_addr.s_addr = inet_addr("127.0.0.1");
			nserver.sin_family = AF_INET;
			nserver.sin_port = htons(nameservers[i].port);

			printf("Sending query to %s nameserver...\n", nameservers[i].nameserver);

			if(sendto(sock2, query, n, 0, (struct sockaddr *)&nserver, sizeof nserver) < 0) {
				printf("Failed to send query to nameserver\n");
				return 1;
			}

			memset(response, 0, sizeof response);
			len = sizeof nserver;
			n = recvfrom(sock2, response, sizeof response, 0, (struct sockaddr *)&nserver, &len);

			if(n < 0) {
				printf("Failed to receive response from TLD server\n");
				return 1;
			}

			printf("Received response from nameserver\nSending response to root server...\n");
		}

		n = strlen(response) * sizeof (char);
		if(sendto(sockfd, response, n, 0, (struct sockaddr *)&root, sizeof root) < 0) {
			printf("Failed to send response to root server\n");
			return 1;
		}
		printf("Response Sent\n\n");
	}

	close(sockfd);
	close(sock2);
}
