/* 
 * 
 *      Created on: 2018-10-24
 *      Author: seanwon 
 */  
  
#include <stdio.h>  
#include <stdlib.h>  
#include <errno.h>  
#include <string.h>  
#include <sys/types.h>  
#include <netinet/in.h>  
#include <sys/socket.h>  
#include <sys/wait.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

using namespace std;

  
#define SERVPORT 3333
#define MAXDATASIZE 100
#define SERVER_IP "127.0.0.1"
#define DATA  "this is a client message 客户端的信息"
  
void client(){  
  
  
    int sockfd, recvbytes;  
    char buf[MAXDATASIZE];  
    struct hostent *host;  
    struct sockaddr_in serv_addr;  
  
    cout<<"debug 1"<<endl;
    if (( sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {  
        perror("socket error!");  
        exit(1);  
    }  
    bzero(&serv_addr,sizeof(serv_addr));  
    serv_addr.sin_family    = AF_INET;  
    serv_addr.sin_port      = htons(SERVPORT);  
    serv_addr.sin_addr.s_addr= inet_addr(SERVER_IP);  
  
    if (connect(sockfd, (struct sockaddr *)&serv_addr,sizeof(struct sockaddr)) == -1) {  
        perror("connect error!");  
        exit(1);  
    }  
    
    cout<<"debug 2"<<endl;

    write(sockfd,DATA, sizeof(DATA));  
   if ((recvbytes = recv(sockfd, buf, MAXDATASIZE,0)) == -1) {  
        perror("recv error!");  
        exit(1);  
    }  
  
  
    cout<<"debug 3"<<endl;
    buf[recvbytes] = '\0';  
    printf("Received: %s",buf);  
    close(sockfd);  
}  
  
int main(int argc, char* argv[]) {  
    while(argc){  
        //printf("%s\n", argv[1]);  
        cout<<argv[--argc]<<"   ";
    }  
    cout<<endl;
    client();  
    return 0;  
}  