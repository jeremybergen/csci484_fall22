#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    char buffer[1024] = {0};
    char tmpBuffer[1024] = "Hello";
    // char *tmpBuffer;

    
    strcat(buffer, tmpBuffer);
    strcat(buffer, tmpBuffer);
    printf("%s\n", buffer);
    memset(tmpBuffer, 0, strlen(tmpBuffer));
    printf("%s\n", buffer);
    return 0;
}