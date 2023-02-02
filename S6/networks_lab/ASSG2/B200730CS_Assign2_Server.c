#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<poll.h>

#define PORT "9034"

void *get_in_addr(struct sockaddr *sa) {
	if(sa->sa_family == AF_INET) {
		return &( ((struct sockaddr_in *)sa) -> sin_addr );
	}
	
	return &( ((struct sockaddr_in6 *)sa) -> sin6_addr );
}

int get_listener_socket(void) {
	int listener;
	int yes = 1;
	int rv;
	
	struct addrinfo hints, *ai, *p;
	
	memset(&hints, 0, sizeof hints);
	
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	
	if((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0) {
		fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
		exit(1);
	}
	
	for(p = ai; p != NULL; p = p->ai_next) {
		listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		
		if(listener < 0) {
			continue;
		}
		
		//get rid of the "address already in use" error message
		setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
		
		if(bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
			close(listener);
			continue;
		}
		
		break;
	}
	
	freeaddrinfo(ai);
	
	if(p == NULL)
		return -1;
		
	if(listen(listener, 10) == -1) 
		return -1;
		
	return listener;
}

/*void add_to_pfds(struct pollfd *pfds[], int newfd, int *fd_count, int *fd_size) {
	//double the space if there isn't enough room
	if(*fd_count == *fd_size) {
		*fd_size *= 2;
		*pfds = realloc(*pfds, sizeof(**pfds) * (*fd_size));
	}
	
	(*pfds)[*fd_count].fd = newfd;
	(*pfds)[*fd_count].events = POLLIN;
	
	(*fd_count)++;
}

void del_from_pfds(struct pollfd pfds[], int i, int *fd_count) {
	pfds[i] = pfds[*fd_count - 1];
	(*fd_count)--;
}*/

int main() {
	int listener, newfd;
	struct sockaddr_storage remoteaddr;
	socklen_t addrlen;
	
	char buf[256];
	char remoteIP[INET6_ADDRSTRLEN];
	
	/*int fd_count = 0;
	int fd_size = 5;
	//struct pollfd *pfds = (struct pollfd *) malloc (sizeof(struct pollfd) * fd_size);
	struct pollfd *pfds = malloc(sizeof *pfds * fd_size);*/
	
	fd_set master;
	fd_set read_fds;
	int fdmax;
	
	listener = get_listener_socket();
	
	if(listener == -1) {
		fprintf(stderr, "error creating listening socket");
		exit(1);
	}
	
	/*//add the listener socket to the poll fd set
	pfds[0].fd = listener;
	pfds[0].events = POLLIN;
	
	fd_count = 1; //for the listener*/
	
	FD_ZERO(&master);
	FD_ZERO(&read_fds);
	
	//add listener to master set
	FD_SET(listener, &master);
	
	//keep track of the  biggest file descriptor
	fdmax = listener;
	
	while(1) {
		/*int poll_count = poll(pfds, fd_count, -1);
		
		if(poll_count == -1) {
			perror("poll");
			exit(1);
		}*/
		
		read_fds = master;
		if(select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
			perror("select");
			return 1;
		}
		
		//run through existing connections looking for data to read
		for(int i = 0; i <= fdmax; i++) {
			//check if someone is ready to read
			if(FD_ISSET(i, &read_fds)) {
				if(i == listener) { //if listener is ready to read, handle new connection
					addrlen  = sizeof remoteaddr;
					newfd = accept(listener, (struct sockaddr *)  &remoteaddr, &addrlen);
					
					if(newfd == -1) {
						perror("accept");
					} else {
						//add_to_pfds(&pfds, newfd, &fd_count, &fd_size);
						FD_SET(newfd, &master);
						if(newfd > fdmax)
							fdmax = newfd;
						
						printf("selectserver: new connection from %s on socket %d\n", 
											inet_ntop(remoteaddr.ss_family, get_in_addr((struct sockaddr *) &remoteaddr), remoteIP, INET6_ADDRSTRLEN),
											newfd);

						for(int j = 0; j <= fdmax; j++) {
							if(FD_ISSET(j, &master)) {
								if(j != newfd && j != listener) {
									char sfd = (char) (newfd - listener + 48);
									
									memset(buf, 0, sizeof buf);
									strcpy(buf, "\n	Participant ");
									strcat(buf, &sfd);
									strcat(buf, " joined the chat.\n");
									
									int len = strlen(buf) * sizeof(char);
								
									if(send(j, buf, len, 0) == -1) {
										perror("send");
										return 1;
									}
								}
							}
						}
					}
				} else { //if not listener, then it is a regular client
					memset(buf, 0, sizeof buf);
					int nbytes = recv(i, buf, sizeof buf, 0);
					
					if(nbytes <= 0) {
						if(nbytes == 0) {
							printf("selectserver: socket %d hung up\n", i);

							for(int j = 0; j <= fdmax; j++) {
								if(FD_ISSET(j, &master)) {
									char sfd = (char) (i - listener + 48);

									memset(buf, 0, sizeof buf);
		                            strcpy(buf, "\n	Participant ");
		                            strcat(buf, &sfd);
		                            strcat(buf, " left the chat.\n");

									int len = strlen(buf) * sizeof(char);
							
									if(j != listener && j != i) {
										if(send(j, buf, len, 0) == -1) {
											perror("send");
											return 1;
										}
									}
								}
							}
						} else {
							perror("recv");
						}
						
						//close(pfds[i].fd);
						//del_from_pfds(pfds, i, &fd_count);
						
						close(i);
						FD_CLR(i, &master);
					} else {
						char sfd = (char) (i - listener + 48);
						char data[256];
						memset(data, 0, sizeof data);

						strcat(data, &sfd);
						strcat(data, ": ");
						strcat(data, buf);

						int len = strlen(data) * sizeof(char);

						for(int j = 0; j <= fdmax; j++) {
							if(FD_ISSET(j, &master)) {
								if(j != listener && j != i) {
									if(send(j, data, len, 0) == -1) {
										perror("send");
										return 1;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
