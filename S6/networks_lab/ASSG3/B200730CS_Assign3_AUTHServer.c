#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

struct AR {
	char name[50];
	char addr[50];
};

struct AR addrs[5] = {
	{
		"www.google.com",
		"192.168.5.60",
	},
	{
		"mail.google.com",
		"192.8.1.100",
	}
};

int addr_count = 2;

int main() {
	int sockfd;
	struct sockaddr_in server, tld;
	char query[50], response[50];

	sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1) {
		perror("socket");
		return 1;
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(1238);
	server.sin_addr.s_addr = INADDR_ANY;
	if(bind(sockfd, (struct sockaddr *)&server, sizeof server) < 0) {
		perror("bind");
		return 1;
	}

	printf("Running ns1 nameserver...\n\n");

	while(1) {
		int len = sizeof tld;
		memset(query, 0, sizeof query);
		int n = recvfrom(sockfd, query, sizeof query, 0, (struct sockaddr *)&tld, &len);

		if(n < 0) {
			printf("Error receiving data from TLD server\n");
			return 1;
		}

		if(n == 0)
			break;
		//printf("\t%s\n", query);

		char *token = strtok(query, ":");
		// token now has url
		printf("Received query for %s\n", token);

		char url[50];
		memset(url, 0, sizeof url);
		strcpy(url, token);

		int i;
		for(i = 0; i < addr_count; i++) {
			if(strcmp(url, addrs[i].name) == 0) {
				break;
			}
		}

		if(i == addr_count) {
			printf("Record NOT FOUND\n");
			memset(response, 0, sizeof response);
			strcpy(response, "Record NOT FOUND");
		}
		else {
			memset(response, 0, sizeof response);
			strcpy(response, addrs[i].addr);
		}

		n = strlen(response) * sizeof (char);
		if(sendto(sockfd, response, n, 0, (struct sockaddr *)&tld, sizeof tld) < 0) {
			printf("Failed to send response to root server\n");
			return 1;
		}
		printf("Response Sent\n\n");
	}

	close(sockfd);
}
