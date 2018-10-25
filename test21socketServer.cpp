// Client/Server模型的服务器端
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define	BUFSIZE	1024
 
#define	SERV_PORT		4507	// 服务器端的端口
#define	LISTENQ			12	// 连接请求队列的最大长度
 
#define	INVALID_USERINFO	'n'	// 用户信息无效
#define	VALID_USERINFO		'y'	// 用户信息有效
 
#define	USERNAME		0	// 接收到的是用户名
#define	PASSWORD		1	// 接收到的是密码
 
struct userinfo {  	// 保存用户名和密码的结构体
    char username[32];
    char password[32];
};
struct userinfo users[ ] = {
{"linux", "unix"},
{"4507", "4508"},
{"clh", "clh"},
{"xl", "xl"},
{" "," "}	   	// 以只含一个空格的字符串作为数组的结束标志
};
/*自定义的错误处理函数*/
void my_err(const char * err_string, int line)
{
    fprintf(stderr, "line:%d  ", line);
    perror(err_string);
    exit(1);
}
 
/*
* 函数名: my_recv
* 描 述 : 从套接字上读取一次数据(以'\n'为结束标志)
* 参 数 : conn_fd 	-- 从该连接套接字上接收数据
*	  data_buf 	-- 读取到的数据保存在此缓冲中
*	  len 		-- data_buf所指向的空间长度
* 返回值: 出错返回-1， 服务器端已关闭连接则返回0， 成功返回读取的字节数
*/
int my_recv(int conn_fd, char *data_buf, int len)
{
    static  char	recv_buf[BUFSIZE]; 	// 自定义缓冲区，BUFSIZE定义在my_recv.h中
    static  char	*pread;			// 指向下一次读取数据的位置
    static  int	len_remain = 0;	 	// 自定义缓冲区中剩余字节数
    int			i;
 
    // 如果自定义缓冲区中没有数据，则从套接字读取数据
    if (len_remain <= 0) {
        if ((len_remain =recv(conn_fd, recv_buf, sizeof (recv_buf), 0)) < 0) {
            my_err("recv", __LINE__);
        } else if (len_remain == 0) {	// 目的计算机端的socket连接关闭
            return 0;
        }
        pread = recv_buf;	// 重新初始化pread指针
    }
    // 从自定义缓冲区中读取一次数据
    for (i=0; *pread != '\n'; i++) {
        if (i > len) {	// 防止指针越界
            return -1;
        }
        data_buf[i] = *pread++;
        len_remain--;
    }
 
    // 去除结束标志
    len_remain--;
    pread++;
 
    return i;	// 读取成功
}
// 查找用户名是否存在，存在返回该用户名的下标,不存在则返回-1，出错返回-2
int find_name(const char *name)
{
    int i;
 
    if (name == NULL) {
        printf("in find_name, NULL pointer");
        return -2;
    }
    for (i=0; users[i].username[0] != ' ';i++) {
        if (strncmp(users[i].username, name, strlen(users[i].username)) == 0) {
            return i;
        }
    }
 
    return -1;
}
 
// 发送数据
void send_data(int conn_fd, const char *string)
{
    if (send(conn_fd, string, strlen(string), 0) < 0) {
        my_err("send", __LINE__);  // my_err函数在my_recv.h中声明
    }
}
int main()
{
    int			sock_fd, conn_fd;
    int			optval;
    int			flag_recv = USERNAME; // 标识接收到的是用户还是密码
    int			ret;
    int			name_num;
    pid_t			pid;
    socklen_t		cli_len;
    struct sockaddr_in	cli_addr, serv_addr;
    char			recv_buf[128];
    // 创建一个TCP套接字
    sock_fd = socket(AF_INET, SOCK_STREAM,0);
    if (sock_fd < 0) {
        my_err("socket", __LINE__);
    }
    cout<< "create socket success !"<<endl;
    // 设置该套接字使之可以重新绑定端口
    optval = 1;
    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR,
                   (void *)&optval, sizeof(int)) < 0) {
        my_err("setsockopt", __LINE__);
    }
    cout<< "setsockopt reused ok !"<< endl;
    // 初始化服务器端地址结构
    memset(&serv_addr, 0, sizeof (struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // 将套接字绑定到本地端口
    if (bind(sock_fd, (struct sockaddr *)&serv_addr,
             sizeof (struct sockaddr_in)) < 0) {
        my_err("bind", __LINE__);
    }
    cout<< "bind socket ok !" <<endl;
    // 将套接字转化为监听套接字
    if (listen(sock_fd, LISTENQ) < 0) {
        my_err("listen", __LINE__);
    }
    cout<< "listen client ......"<<endl;
    cli_len = sizeof (struct sockaddr_in);
    while (1) {
        cout<< "ready to accept client connect ......"<<endl;
        // 通过accept接受客户端的连接请求，并返回连接套接字用于收发数据
        conn_fd = accept(sock_fd, (struct sockaddr *)&cli_addr, &cli_len);
        if (conn_fd < 0) {
            my_err("accept", __LINE__);
        }
        printf("accept a new client, ip:%s\n", inet_ntoa(cli_addr.sin_addr));
        // 创建一个子进程处理刚刚接受的连接请求
        if ( (pid = fork()) == 0 ) {	// 子进程
            while(1) {
                memset(recv_buf, 0, sizeof(recv_buf));
                if ((ret = recv(conn_fd, recv_buf, sizeof (recv_buf), 0)) < 0) {
                    perror("recv");
                    exit(1);
                }
                recv_buf[ret-1] = '\0'; // 将数据结束标志'\n'替换成字符串结束标志
                if (flag_recv == USERNAME) {	// 接收到的是用户名
                    name_num = find_name(recv_buf);
                    switch (name_num) {
                    case -1:
                        send_data(conn_fd, "n\n");
                        break;
                    case -2:
                        exit(1);
                        break;
                    default:
                        send_data(conn_fd, "y\n");
                        flag_recv = PASSWORD;
                        break;
                    }
                } else if (flag_recv == PASSWORD) {	 // 接收到的是密码
                    if (strncmp(users[name_num].password, recv_buf, strlen(users[name_num].password)) == 0) {
                        send_data(conn_fd, "y\n");
                        send_data(conn_fd, "Welcome login my tcp server\n");
                        printf("%s login\n", users[name_num].username);
                        break; // 跳出while循环
                    } else
                        send_data(conn_fd, "n\n");
                }
            }
            close(sock_fd);
            close(conn_fd);
            exit(0);  // 结束子进程
        } else {   // 父进程关闭刚刚接受的连接请求，执行accept等待其他连接请求
            close(conn_fd);
        }
    }
    return 0;
}
