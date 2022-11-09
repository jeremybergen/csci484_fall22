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

    return 0;
}