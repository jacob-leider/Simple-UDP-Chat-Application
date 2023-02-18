#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAXLINE 1024


// A linked list of clients
struct node {
	struct sockaddr_in data;
	struct node *next;
};
struct node *head = NULL;


// adds a client to the list of active clients
void add_client(struct sockaddr_in data) {
	struct node *link = (struct node*) malloc(sizeof(struct node));
	link->data = data;
	link->next = head;
	head = link;
}


// returns 0 if this address is an active client, -1 if not
int contains_client(struct sockaddr_in new_client) {
    for (struct node *ptr = head; ptr != NULL; ptr = ptr->next) {
        if (ptr->data.sin_port == new_client.sin_port &&
                ptr->data.sin_addr.s_addr == new_client.sin_addr.s_addr) {
            return 1; // new client found in list
        }
    }
	return 0; // if loop terminates, new client not in list
}


// sends the message stored in "buff" to all active clients
void broadcast(int sockfd, char buff[], int n) {
    for (struct node *ptr = head; ptr != NULL; ptr = ptr->next) {
        sendto(sockfd, (const char*)buff, n, MSG_WAITALL, (const struct sockaddr*)&(ptr->data), sizeof ptr->data);
    }
}



int main(int argc, char *argv[]) {


    // ensure port is specified
    if (argc != 2) {
        perror("Format: <PORT>");
    }


    // get server port from command line args
    const int PORT = atoi(argv[1]);


	// socket file descriptor
	int sockfd;
	struct sockaddr_in server_addr, client_addr;


	// attempt to create a socket
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket creation failed");
		exit(EXIT_FAILURE); 				// exit_failure = 8
	}


	// clear memory for server, client addresses
	memset(&server_addr, 0, sizeof server_addr);
	memset(&client_addr, 0, sizeof client_addr);


    // set info for server address (address family, address, port)
	server_addr.sin_family = 		    AF_INET;
	server_addr.sin_addr.s_addr = 		INADDR_ANY;
	server_addr.sin_port   = 		    htons(PORT); // 8080


	// attempt to bind socket to a local address
	if (bind(sockfd,
             (const struct sockaddr *) &server_addr,
             sizeof server_addr) < 0) {
		perror("port in use");
		exit(EXIT_FAILURE);
	}


    // initializations
	socklen_t sock_addr_length;                 // length of client address
	int n;                                      // length of received data
	char buff[MAXLINE];                         // string for storage
	sock_addr_length = sizeof client_addr;      // define length of socket address structure


    // Enter indefinite loop
	while (1) {


		// wait to receive datagram packet from a client
		n = recvfrom(sockfd, 
					(char *)buff, 
					MAXLINE,
					MSG_WAITALL,
					(struct sockaddr *)&client_addr,
					&sock_addr_length);
        buff[n] = '\0';


        // If this is a NEW client:
        // Add client to active clients list if greeting received
		if (!contains_client(client_addr)) {
            if (!strncasecmp(buff, "GREETING", 7)) {
                add_client(client_addr);
            }
        // If this is an ACTIVE client:
        // broadcast client's message to all active clients
		} else {
            char msg[MAXLINE];
            sprintf(msg, "<From %s:%d>:  %s",
                    inet_ntoa(client_addr.sin_addr),
                    client_addr.sin_port,
                    buff);
            broadcast(sockfd, msg, n);
		}
	}
	return 0;
}
