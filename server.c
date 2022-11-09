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

    while(1) {
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, (socklen_t *)&addrsize);
        printf("Accepted new connection from client\n");
        int stillConnected = 1;
        while(stillConnected) {
            int messageLength;
            int offset = 0;
            offset = recv(clientSocket, messageSize, 8, 0);
            printf("Message length is: %s\n", messageSize);
            printf("offset: %i\n", offset);
            messageLength = atoi(messageSize);
            send(clientSocket, messageSize, strlen(messageSize), 0);
            memset(messageSize, 0, strlen(messageSize));
            

            char tmpBuffer[BUFFSIZE];
            int recvBytes = 0;
            while(messageLength > 0) {
            // while(recvBytes = recv(clientSocket, tmpBuffer, BUFFSIZE, 0)) {
                recvBytes = recv(clientSocket, tmpBuffer, BUFFSIZE-1, 0);
                printf("Received Bytes: %i\n", recvBytes);
                printf("tmpBuffer: %s\n", tmpBuffer);
                strcat(buffer, tmpBuffer);
                printf("DEBUG: buffer: %s\n", buffer);
                // printf("DEBUG2: &buffer: %p\n", buffer);
                // printf("DEBUG2: &tmpBuffer: %p\n", tmpBuffer);
                messageLength = messageLength - recvBytes;
                printf("messageLength: %i\n", messageLength);
                memset(tmpBuffer, 0, strlen(tmpBuffer));
            }


            printf("Received: %s\n", buffer);
            if(strcmp(buffer, "quit\n") == 0) {
                char *newBuffer = "Goodbye";
                send(clientSocket, newBuffer, strlen(newBuffer), 0);
                memset(buffer, 0, strlen(buffer));
                stillConnected = 0;

            } else {
                send(clientSocket, buffer, strlen(buffer), 0);
                memset(buffer, 0, strlen(buffer));
            }
        }
        // strcat(sendBuffer, "Received: ");
        // strcat(sendBuffer, buffer);
        // send(clientSocket, sendBuffer, strlen(sendBuffer), 0);
    }
    return 0;
}