#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
	int socketfd;
	socklen_t addr_len;
	char buf[64];
	struct sockaddr_in server_addr;
	
	//广播地址为xxx.xxx.xxx.255
	if(argc < 3)
	{
		printf("uasge: %s ip port\n",argv[0]);
		exit(-1);
	}
	if((socketfd = socket(PF_INET,SOCK_DGRAM,0)) < 0)
	{
		perror("socket");
		exit(-1);
	}
	printf("socketfd = %d\n",socketfd);

	int i=1;
	socklen_t len = sizeof(i);

	//设置socket属性为广播
	setsockopt(socketfd,SOL_SOCKET,SO_BROADCAST,&i,len);

	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	server_addr.sin_port = htons(atoi(argv[2]));  
	addr_len=sizeof(server_addr);

	while(1)
	{
		fgets(buf,64,stdin);
		printf("get msg from stain:%s", buf);
		if(sendto(socketfd,buf,64,0,(struct sockaddr*)&server_addr,addr_len) < 0)
		{
			perror("sendrto");
			exit(-1);
		}
		if(strncmp(buf,"quit",4) == 0)
			break;
	}

	close(socketfd);
	return 0;
}