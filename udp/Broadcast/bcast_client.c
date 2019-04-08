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
	struct sockaddr_in bcast_client_addr;
	
	//连接相应的广播地址：xxx.xxx.xxx.255
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

	memset(&bcast_client_addr,0,sizeof(bcast_client_addr));
	bcast_client_addr.sin_family = AF_INET;
	bcast_client_addr.sin_addr.s_addr = inet_addr(argv[1]);
	bcast_client_addr.sin_port = htons(atoi(argv[2]));	
	addr_len=sizeof(bcast_client_addr);

	//绑定本机ip与端口 注意：本机只能绑定一次，测试时需要在通一个局域网内多台机器运行
	if(bind(socketfd,(struct sockaddr*)&bcast_client_addr,addr_len) < 0)
	{
		perror("bind");
		exit(-1);
	}
	char name[64];
	size_t len = sizeof(name);
	gethostname(name,len);
	while(1)
	{
		if(recvfrom(socketfd,buf,64,0,(struct sockaddr*)&bcast_client_addr,&addr_len) < 0)
		{
			perror("sendrto");
			exit(-1);
		}
		if(strncmp(buf,"quit",4) == 0)
			break;

		printf("host name>%s",name);
		printf("from: %s port:%d >%s",inet_ntoa(bcast_client_addr.sin_addr),ntohs(bcast_client_addr.sin_port),buf);
	}

	close(socketfd);
	return 0;
}