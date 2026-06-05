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
    char reply[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t len;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&server_addr,
             sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    printf("UDP Server is running on port %d...\n", PORT);

    while (1) {
        len = sizeof(client_addr);

        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
                         (struct sockaddr *)&client_addr, &len);

        buffer[n] = '\0';

        printf("Client: %s\n", buffer);

        printf("Server: ");
        fgets(reply, BUFFER_SIZE, stdin);

        sendto(sockfd, reply, strlen(reply), 0,
               (struct sockaddr *)&client_addr, len);

        if (strncmp(reply, "exit", 4) == 0)
            break;
    }

    close(sockfd);
    return 0;
}