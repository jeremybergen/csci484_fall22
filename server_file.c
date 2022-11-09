/*
c socket server
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFSIZE 10

int main(int argc, char **argv) {
    int serverSocket;
    int clientSocket;
    int yes = 1;
    struct addrinfo hints, *res;
    struct sockaddr_storage clientAddr;
    int addrsize = sizeof(struct sockaddr_storage);
    char buffer[1024] = {0};
    char sendBuffer[BUFFSIZE] = {0};
    char messageSize[8] = {0};

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(NULL, "1234", &hints, &res);

    serverSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    bind(serverSocket, res->ai_addr, res->ai_addrlen);
    
    listen(serverSocket, 1);

    
    return 0;
}