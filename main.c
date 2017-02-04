#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    int socketfd, port;
    size_t bufflen = strlen(argv[2]);
    char buff[bufflen];

    if (argc < 2) {
        printf("Ошибка, слишком мало параметров");
        exit(EXIT_FAILURE);
    }

    port = atoi(argv[1]);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons((uint16_t) port);
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    if (connect(socketfd, (struct sockaddr *) &address, sizeof address) < 0) {
        perror("Ошибка при подключении к соккету:");
        exit(EXIT_FAILURE);
    } else {
        write(socketfd, argv[2], bufflen);
        if (read(socketfd, buff, bufflen) > 0) {
            printf("%s", buff);
            close(socketfd);
            exit(EXIT_SUCCESS);
        }
        close(socketfd);
    }
}