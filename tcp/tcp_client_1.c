#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<errno.h>
#include<sys/un.h>
#include<arpa/inet.h>


#define PORT 5000
#define IP "192.168.1.108"

int main(int argc, char *argv[])
{
    int client_fd;
    char buf[1024] = {0};//读写缓冲区
    struct sockaddr_in client_addr;
    ssize_t size;

    //创建socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return 1;
    }

    //填充ip端口信息
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(PORT);
    client_addr.sin_addr.s_addr = inet_addr(IP);

    //向服务端发起连接
    if (connect(client_fd, (struct sockaddr*)&client_addr, sizeof(client_addr)) < 0) {
        perror("connect");
        return 2;
    }

    while(1) {
        memset(buf, 0, sizeof(buf));
        //从标准输入获取字符串
        if (!gets(buf)) {
            perror("gets");
            return 3;
        }
        if (strcmp(buf, "quit") == 0)
            break;
        if (write(client_fd, buf, strlen(buf)) != strlen(buf)) {
            perror("write");
            return 4;
        }
    }

    close(client_fd);
    return 0;
}

