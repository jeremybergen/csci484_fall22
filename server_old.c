/*
c socket server
*/
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    int serverSocket;
    int clientSocket;
    int yes = 1;
    struct sockaddr_in address;
    int addrsize = sizeof(struct sockaddr_storage);
    char buffer[10] = {0};

    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_family = AF_INET;
    address.sin_port = htons(1234);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    bind(serverSocket, (struct sockaddr *)&address, sizeof(address));
    listen(serverSocket, 1);
    clientSocket = accept(serverSocket, (struct sockaddr *)&address, (socklen_t *)&addrsize);
    recv(clientSocket, buffer, 10, 0);
    printf("Received: %s\n", buffer);

    return 0;
}