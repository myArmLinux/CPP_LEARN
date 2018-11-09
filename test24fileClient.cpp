#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
 
#define HELLO_WORLD_SERVER_PORT 6666
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512
 
int main(int argc, char *argv[]) 
{
    if (argc != 2) {
        printf("use:[./run][server_ipaddress]\n");
        exit(1);
    }
    struct sockaddr_in client_addr;
    bzero(&client_addr,sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    if (inet_aton(argv[1], &client_addr.sin_addr) == 0) {
        printf("server ip address error!\n");
        exit(1);
    }
    client_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);
    socklen_t client_addr_length = sizeof(client_addr);
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        printf("create socket failed\n");
        exit(1);
    }
    if (connect(client_socket, (struct sockaddr*)&client_addr, client_addr_length) < 0) {
        printf("can not connect to address\n");
        exit(1);
    }
    char file_name[FILE_NAME_MAX_SIZE + 1];
    bzero(file_name, FILE_NAME_MAX_SIZE + 1);
    printf("please input file name:");
    scanf("%s", file_name);
    char buffer[BUFFER_SIZE];
    bzero(buffer, BUFFER_SIZE);
    strncpy(buffer, file_name, strlen(file_name) > BUFFER_SIZE ? BUFFER_SIZE : strlen(file_name));
    send(client_socket, buffer, BUFFER_SIZE, 0);
    FILE *fp = fopen(file_name, "w");
    if (fp == NULL) {
        printf("file can not open\n");
        exit(1);
    }
    bzero(buffer, BUFFER_SIZE);
    int length = 0;
    while (length = recv(client_socket, buffer, BUFFER_SIZE, 0)) {
        if (length < 0) {
            printf("recv failed\n");
            break;
        }
        int write_length = fwrite(buffer, sizeof(char), length, fp);
        if (write_length < length) {
            printf("file write failed\n");
            break;
        }
        bzero(buffer, BUFFER_SIZE);
    }
    printf("recieve file: %s from server %s finished!\n", file_name, argv[1]);
    close(fp);
    close(client_socket);
    return 0;
}
