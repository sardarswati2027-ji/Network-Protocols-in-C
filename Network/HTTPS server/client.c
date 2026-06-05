#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define PORT 8443

int main() {
    SSL_library_init();

    SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

    SSL *ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);

    if (SSL_connect(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
    } else {
        char request[] =
            "GET / HTTP/1.1\r\n"
            "Host: localhost\r\n\r\n";

        SSL_write(ssl, request, strlen(request));

        char buffer[4096] = {0};
        SSL_read(ssl, buffer, sizeof(buffer));

        printf("%s\n", buffer);
    }

    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(sock);
    SSL_CTX_free(ctx);

    return 0;
}
