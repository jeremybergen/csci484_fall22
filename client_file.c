#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

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

    recv(clientSocket, recvBuffer, 1024, 0);
    printf("Received size: %s\n", recvBuffer);

    send(clientSocket, "Ready to received file", 22, 0);

    unsigned long fileSize = atoi(recvBuffer);
    // char fileBuffer[fileSize] = {0};
    char *fileName = "client_copy.out";
    int fileDescriptor;
    fileDescriptor = open(fileName, O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
    printf("DEBUG: fileDescriptor: %i\n", fileDescriptor);

    unsigned long remaining = fileSize;

    int nread = 0;
    while(remaining > 0) {
        printf("DEBUG: remaining: %ld\n", remaining);
        nread = recv(clientSocket, recvBuffer, 1000, 0);
        write(fileDescriptor, recvBuffer, nread);
        // strcat(fileBuffer, recvBuffer);
        memset(recvBuffer, 0, 1024);
        remaining -= nread;
    }


    

    close(fileDescriptor);
    close(clientSocket);

    return 0;
}