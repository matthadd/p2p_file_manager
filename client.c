#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(int argc, char **argv)
{
    printf("Hello, client!\n");
    int opt = 1;
    struct sockaddr_in server_address;
    // int addrlen = sizeof(server_address);
    char *message = "Message from client custom!\n";
    char buffer[BUFFER_SIZE] = {0};
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("sockfd : %d\n", sockfd);

    int res_opt = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    printf("res_opt : %d\n", res_opt);

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0)
    {
        printf("\nInvalid server_address/ server_address not supported \n");
        return -1;
    }

    if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)

    {

        printf("\nConnection Failed \n");
        return -1;
    }

    send(sockfd, message, strlen(message), 0);
    printf("Hello message sent\n");

    int valread = read(sockfd, buffer, 1024);
    printf("%s\n", buffer);

    printf("Goodbye, client!\n");

    return 0;
}