#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include<errno.h>
int main(int argc, char *argv[])
{
    char buffer[1024] = {0};
    char host_addr[256] = {0};
    char host_file[256] = {0};
    char local_file[256] = {0};
    int sockfd;
    int send, totalsend;
    int nbytes;
    char request[1024] = {0};
    struct sockaddr_in server_addr;
    struct hostent *host;
    if (argc != 2) {
        fprintf(stderr, "Usage:%s web-address!\n", argv[0]);
        exit(1);
    }
    int portnumber = 4040;
    strcpy(host_addr, argv[1]);
    strcpy(host_file, "server.c");
    if ((host = gethostbyname(argv[1])) == NULL) {
        fprintf(stderr,"Gethostname error\n", strerror(errno));
        exit(1);
    }
    char ip_str[32] = {0};
    printf("address: %s\n", inet_ntop(host->h_addrtype, host->h_addr, ip_str, sizeof(ip_str)));
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        fprintf(stderr,"Socket Error:%s!\n",strerror(errno));
        exit(1);
    }
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portnumber);
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);
    if (connect(sockfd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr)) == -1) {
        fprintf(stderr,"Connect Error:%s!\n",strerror(errno));
        exit(1);
    }
    sprintf(request, "GET /%s HTTP/1.1\r\nAccept: */*\r\nAccept-Language: zh-cn\r\n  \
            User-Agent: Mozilla/4.0 (compatible; MSIE 5.01; Windows NT 5.0)\r\n  \
            Host: %s:%d\r\nConnection: Close\r\n\r\n", host_file, host_addr, portnumber);
    strcpy(local_file, "local.txt");
    send = 0;
    totalsend = 0;
    nbytes = strlen(request);
    while (totalsend < nbytes) {
        send = write(sockfd, request + totalsend, nbytes - totalsend);
        if (send == -1) {
            printf("send error:%s!\n", strerror(errno));
            exit(0);
        }
        totalsend += send;
        printf("%d bytes send OK!\n", totalsend);
    }
    FILE * fp = fopen(local_file, "a");
    if(!fp) {
        printf("create file error:%s!\n", strerror(errno));
        return 0;
    }
    //printf("The following is the response header:\n");
    int i = 0;
    /* 连接成功了，接收http响应，response */
    while((nbytes = read(sockfd, buffer, 1)) == 1) {
        if (i < 4) {
            if (buffer[0] == '\r' || buffer[0] == '\n')
                i++;
            else
                i = 0;
            //printf("%c", buffer[0]);
        }
        else {
            fwrite(buffer, 1, 1, fp);/*将http主体信息写入文件*/
            //printf("%c", buffer[0]);
            i++;
            if(i % 1024 == 0)
                fflush(fp);   /**每1K时存盘一次**/
        }
    }
    printf("\n");
    fclose(fp);
    /* 结束通讯 */
    close(sockfd);
    return 0;
}
