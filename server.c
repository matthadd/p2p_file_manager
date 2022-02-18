#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080
#define BACKLOG 3
#define BUFFER_SIZE 1024

int main(int argc, char **argv)
{
    printf("Hello, server!\n");
    int opt = 1;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char *message = "Message from server custom !\n";
    char buffer[BUFFER_SIZE] = {0};

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("sockfd : %d\n", sockfd);

    int res_opt = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    printf("res_opt : %d\n", res_opt);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    int res_bind = bind(sockfd, (struct sockaddr *)&address, sizeof(address));
    printf("res_bind : %d\n", res_bind);

    int res_listen = listen(sockfd, BACKLOG);
    printf("res_listen : %d\n", res_listen);

    int sock_accept = accept(sockfd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    printf("sock_accept : %d\n", sock_accept);

    int valread = read(sock_accept, buffer, BUFFER_SIZE);
    printf("valread : %d\n", valread);

    printf("buffer : %s\n", buffer);

    send(sock_accept, message, strlen(message), 0);
    printf("sock_accept : %d", sock_accept);
    printf("\nServer message sent!\n");

    valread = read( sockfd , buffer, BUFFER_SIZE);
    printf("%s\n", buffer );

    printf("Goodbye, server!\n");

    return 0;
}