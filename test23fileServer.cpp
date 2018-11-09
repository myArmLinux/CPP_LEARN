#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
 
#define HELLO_WORLD_SERVER_PORT 6666
#define LENGTH_OF_LISTENQ_QUEUE 20
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512
int main(int argc, char *argv[])
{
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);
 
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        printf("create socket failed!\n");
        exit(1);
    }
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr))) {
        printf("bind socket failed!\n");
        exit(1);
    }
    if (listen(server_socket, LENGTH_OF_LISTENQ_QUEUE)) {
        printf("listen socket failed!\n");
        exit(1);
    }
    while (1) {
        struct sockaddr_in client_addr;
        socklen_t length = sizeof(client_addr);
        int new_server_scoket = accept(server_socket, (struct sockaddr*)&client_addr, &length);
        if (new_server_scoket < 0) {
            printf("accept socket failed!\n");
            break;
        }
        char buffer[BUFFER_SIZE];
        bzero(buffer, BUFFER_SIZE);
        length = recv(new_server_scoket, buffer, BUFFER_SIZE, 0);
        if (length < 0) {
            printf("recv data failed!\n");
            break;
        }
        char file_name[FILE_NAME_MAX_SIZE + 1];
        bzero(file_name, FILE_NAME_MAX_SIZE + 1);
        strncpy(file_name, buffer, strlen(file_name) > FILE_NAME_MAX_SIZE ? FILE_NAME_MAX_SIZE : strlen(buffer));
        FILE *fp = fopen(file_name, "r");
        if (fp == NULL) {
            printf("File: %s not found\n", file_name);
        }
        else {
            bzero(buffer, BUFFER_SIZE);
            int file_length = 0;
            while((file_length = fread(buffer, sizeof(char), BUFFER_SIZE, fp)) > 0) {
                printf("file_length = %d\n", file_length);
                if (send(new_server_scoket, buffer, file_length, 0) < 0) {
                    printf("send file: %s failed\n", file_name);
                    break;
                }
                bzero(buffer, BUFFER_SIZE);
            }
            fclose(fp);
            printf("file: %s trandfer finished\n", file_name);
        }
        close(new_server_scoket);
    }
    close(server_socket);
    return 0;
}
