#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define KEY 100

unsigned char test_buf1[] = {0x68,0x18,0x0,0x83,0x0,0x0,0x40,0x0,0x0,0x49,0x3,0x1,0x0,0x54,0x48,0x31,0x30,0x21,0x8,0x19,0x10,0x32,0x91,0x16};
unsigned char test_buf2[] = {0x68, 0x38 , 0x00 , 0xC3 , 0x00 , 0x00 , 0x40 , 0x00 , 0x00 , 0x00 , 0x03 , 0x02 , 0x01 , 0xF2 , 0x37 , 0x01 , 0x01 , 0x00 , 0x00 , 0x5A , 0x0A , 0x00 , 0xE8 , 0x03 , 0xE8 , 0x03 , 0x3C , 0x09 , 0x00 , 0x00 , 0x7E , 0x03 , 0x00 , 0xF7 , 0x03 , 0x00 , 0x00 , 0x30 , 0x12 , 0x13 , 0x30 , 0x12 , 0x13 , 0x54 , 0x48 , 0x31 , 0x30 , 0x21 , 0x08 , 0x19 , 0x10 , 0x32 , 0x00 , 0x00 , 0x59 , 0x16};

unsigned char result = 1;

unsigned char encrypt(unsigned char buff, unsigned char key)
{
    return buff ^ key;
}

unsigned char decypt(unsigned char buff, unsigned char key)
{
    return buff ^ key;
}

void test_case(unsigned char* test_buf, unsigned char buf_len, unsigned char key)
{
    struct timeval start, end;
    unsigned char tmp_buf[256];
    unsigned char change_buf[256];

    printf("========================================================\n");
    printf("KEY:%d\n",key);
    gettimeofday( &start, NULL );
    //printf("start : %d.%d\n", start.tv_sec, start.tv_usec);
    
    //加密操作
    for(int i =0; i<buf_len;i++)
    {
        tmp_buf[i] = encrypt(test_buf[i],key);
    }

    gettimeofday( &end, NULL );
    //printf("end   : %d.%d\n", end.tv_sec, end.tv_usec);
    printf("encode use time:%d um\n",end.tv_usec - start.tv_usec);
    
    
    //解密
    for(int i =0; i<buf_len;i++)
    {
        change_buf[i] = decypt(tmp_buf[i],key);
    }
    
    //==============================================================原始数据
    printf("src    Data:");
    for(int i =0; i<buf_len;i++)
    {
        printf("%5X", test_buf[i]);
    }
    printf("\n");
    
    //==============================================================加密后的数据
    printf("encode Data:");
    for(int i =0; i<buf_len;i++)
    {
        printf("%5X", tmp_buf[i]);
    }
    printf("\n");
    
    //==============================================================解密后的数据
    printf("decode Data:");
    for(int i =0; i<buf_len;i++)
    {
        printf("%5X", change_buf[i]);
    }
    printf("\n");
    
    for(int i =0; i<buf_len;i++)
    {
        if(change_buf[i] == test_buf[i]) 
        {
            continue;
        }
        else
        {
            printf("result: decode err!!!\n");
            result = 0;
        }
    }
    printf("result: decode success!!!\n");
    printf("========================================================\n");
    
}

int main(int arg, char *args[])
{
    int oldfd = open("mytest.log",O_RDWR | O_CREAT,0644);
	
	dup2(oldfd,1);
    close(oldfd);
  
    for(int i=1; i<=100; i++)
    {
        test_case(test_buf1, sizeof(test_buf1),KEY+i);
        test_case(test_buf2, sizeof(test_buf2),KEY+i);
    }
    
    
    
    if(result == 1)
    {
        printf("ALL SUCCESS!!!\n");
    }
    else
    {
        printf("HAVE ERROR!!!\n");
    }
    return 0;
}

