#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    int clientSocket;
    struct sockaddr_in servaddr;
    int inetStatus;

    char *hello = "Star Trek RULES!!!";
    char *message = {0};
    size_t msgLen = 0;
    char recvBuffer[1024] = {0};

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(1234);
    inetStatus = inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    printf("inetStatus: %d\n", inetStatus);

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    connect(clientSocket, (struct sockaddr *)&servaddr, sizeof(servaddr));

    while(1) {
        getline(&message, &msgLen, stdin);
        // printf("our message: %s\n", message);
        // printf("msgLen: %lu\n", msgLen);
        // printf("message strlen: %lu\n", strlen(message));
        char *messageLength;
        sprintf(messageLength, "%lu\n", strlen(message));
        printf("messageLength: %li\n", strlen(message));
        send(clientSocket, messageLength, strlen(messageLength), 0);
        recv(clientSocket, recvBuffer, 1024, 0);
        printf("Received from server: %s\n", recvBuffer);
        memset(recvBuffer, 0, sizeof(recvBuffer));

        send(clientSocket, message, strlen(message), 0);
        recv(clientSocket, recvBuffer, 1024, 0);
        printf("Received from server: %s\n", recvBuffer);
        memset(message, 0, sizeof(message));
        memset(recvBuffer, 0, sizeof(recvBuffer));
    }

    return 0;
}