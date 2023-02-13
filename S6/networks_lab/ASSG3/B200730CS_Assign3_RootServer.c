#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>

struct TLD {
	char domain[10];
	int port;
};

struct TLD tld_servers[3] = {
	{
		"com",
		1236,
	},
	{
		"org",
		1237,
	}
};
int tld_count = 2;

int main() {
	int sockfd;
	struct sockaddr_in server, dns, tld;
	char query[50], response[50];

	// Create socket for DNS server
	sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1) {
		perror("socket");
		return 1;
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(1235);
	server.sin_addr.s_addr = INADDR_ANY;
	if(bind(sockfd, (struct sockaddr *)&server, sizeof server) < 0) {
		perror("bind");
		return 1;
	}

	printf("Running Root Server...\n\n");

	// Create socket for TLD server
	int sock2 = socket(PF_INET, SOCK_DGRAM, 0);
	if(sock2 == -1) {
		perror("sock2");
		return 1;
	}

	while(1) {
		int len = sizeof dns;
		memset(query, 0, sizeof query);
		int n = recvfrom(sockfd, query, sizeof query, 0, (struct sockaddr *)&dns, &len);

		if(n < 0) {
			printf("Error receiving data from DNS server\n");
			return 1;
		}

		if(n == 0)
			break;

		char dupl[50];
		strcpy(dupl, query);
		char *token = strtok(dupl, ":");

		printf("Received query for %s\n", token);

		char url[50];
		memset(url, 0, sizeof url);
		strcpy(url, token);

		char *prev = NULL;
		token = strtok(url, ".");
		while(token != NULL) {
			prev = token;
			token = strtok(NULL, ".");
		}
		// 'prev' holds the top-level domain name now

		tld.sin_addr.s_addr = inet_addr("127.0.0.1");
		tld.sin_family = AF_INET;

		//printf("\t%s\n", query);
		int i;
		for(i = 0; i < tld_count; i++) {
			if(strcmp(prev, tld_servers[i].domain) == 0) {
				tld.sin_port = htons(tld_servers[i].port);
				break;
			}
		}

		// if TLD name wasn't found
		if(i == tld_count) {
			printf("Domain NOT FOUND!\nExiting...\n");
			return 1;
		}

		printf("Sending query to %s TLD server...\n", prev);

		if(sendto(sock2, query, n, 0, (struct sockaddr *)&tld, sizeof tld) < 0) {
			printf("Failed to send query to TLD server\n");
			return 1;
		}

		memset(response, 0, sizeof response);
		len = sizeof tld;
		n = recvfrom(sock2, response, sizeof response, 0, (struct sockaddr *)&tld, &len);	

		if(n < 0) {
			printf("Failed to receive response from TLD server\n");
			return 1;
		}

		printf("Received response from TLD server\nSending response to DNS server...\n");

		if(sendto(sockfd, response, n, 0, (struct sockaddr *)&dns, sizeof dns) < 0) {
			printf("Failed to send response to DNS server\n");
			return 1;
		}
		printf("Response Sent\n\n");
	}

	close(sockfd);
	close(sock2);
}
