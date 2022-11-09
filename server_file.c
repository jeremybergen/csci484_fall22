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
#include <sys/stat.h>
#include <fcntl.h>

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

    struct stat st;
    char *fileName = "server.out";
    char fileSize[8] = {0};

    stat(fileName, &st);
    printf("File size: %ld\n", st.st_size);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(NULL, "1234", &hints, &res);

    serverSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    bind(serverSocket, res->ai_addr, res->ai_addrlen);
    
    listen(serverSocket, 1);

    while (1) {
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, (socklen_t *)&addrsize);
        printf("Accepted new connection from client\n");

        sprintf(fileSize, "%ld", st.st_size);
        send(clientSocket, fileSize, strlen(fileSize), 0);

        recv(clientSocket, buffer, 1024, 0);
        printf("Received reply from client: %s\n", buffer);
        memset(buffer, 0, 1024);

        unsigned long remaining = st.st_size;
        int nread = 0;
        int fileDescriptor = 0;
        fileDescriptor = open(fileName, O_RDONLY);
        while(remaining > 0) {
            printf("DEUBG: remaining: %ld\n", remaining);
            nread = read(fileDescriptor, buffer, 1024);
            send(clientSocket, buffer, nread, 0);
            memset(buffer, 0, 1024);
            remaining -= nread;
        }
        close(fileDescriptor);
        close(clientSocket);
    }
    return 0;
}