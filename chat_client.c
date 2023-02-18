#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define TRUE            1
#define FALSE           -1
#define MAXLINE         1024


int main(int argc, char *argv[]) {


    // ensure IP and port are both specified in the command line
    if (argc != 3) {
        perror("Format: <ADDRESS> <PORT>\n");
    }


    // convert command line args to server port and IP
    const int PORT = atoi(argv[2]);
    in_addr_t ADDRESS;
    if ((ADDRESS = inet_addr(argv[1])) == 0) {
        perror("Invalid Address\n");
        exit(EXIT_FAILURE);
    }


	int sockfd;
	struct sockaddr_in	server_addr;


    // attempt to create a socket
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket creation failed\n");
		exit(EXIT_FAILURE); 				// exit_failure = 8
	}


	// set info for server address (address family, address, port)
    memset(&server_addr, 0, sizeof server_addr);
	server_addr.sin_family              = 			AF_INET;
	server_addr.sin_addr.s_addr         =           ADDRESS;
	server_addr.sin_port                = 			htons(PORT);


    // send initial greeting to server
    const char* greeting = "GREETING";
    sendto(sockfd,
           greeting,
           sizeof greeting,
           0,
           (const struct sockaddr*)&server_addr,
           sizeof server_addr);


    // initialization
    struct fd_set readfds;
    struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 500000;
    char buff[1024];
    int n;
    socklen_t length;


    // Enter indefinite loop
	while (TRUE) {


        // add stdin and socket to the fd set
        FD_SET(0, &readfds);
        FD_SET(sockfd, &readfds);
        select(sockfd + 1, &readfds, NULL, NULL, &tv);


        // if stdin is active (user has hit return):
        // send contents of stdin to the server
        if (FD_ISSET(0, &readfds)) {
            fgets(buff, MAXLINE, stdin);
            sendto(sockfd,
                   (const char*)buff,
                   sizeof buff,
                   0,
                   (const struct sockaddr*)&server_addr,
                   sizeof server_addr);
        }


        // if the socket fd is active:
        // receive and display the incoming message
        if (FD_ISSET(sockfd, &readfds)) {
            n = recvfrom(sockfd,
                         (char*)buff,
                         MAXLINE,
                         MSG_WAITALL,
                         (struct sockaddr*)&server_addr,
                         &length);
            buff[n] = '\0';
            printf("%s", buff);
        }
	}
	return 0;
}