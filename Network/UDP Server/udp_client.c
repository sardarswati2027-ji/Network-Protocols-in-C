#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    char message[BUFFER_SIZE];
    struct sockaddr_in server_addr;
    socklen_t len;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    printf("Connected to UDP Server\n");

    while (1) {
        printf("Client: ");
        fgets(message, BUFFER_SIZE, stdin);

        sendto(sockfd, message, strlen(message), 0,
               (struct sockaddr *)&server_addr,
               sizeof(server_addr));

        if (strncmp(message, "exit", 4) == 0)
            break;

        len = sizeof(server_addr);

        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
                         (struct sockaddr *)&server_addr, &len);

        buffer[n] = '\0';

        printf("Server: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}

