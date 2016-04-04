/**************** copy command ******************/
/*
 * cp命令的简单实现
 * 实现思路：文件在磁盘上，源文件在左边，右边的是目标文件，进程在用户空间，缓冲区是进程内存的一部分，
 *          进程有两个文件描述符，一个指向源文件，一个指向目标文件，从源文件中读取数据写入缓冲，再将缓冲中的数据写入目标文件。
 * 测试平台：Ubuntu 12.04
 * create by zhanghuan in 2016-4-4
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFERSIZE 4096
#define COPYMODE 0644

void oops(char *, char *);

int main(int argc, char *argv[])
{
	int inFd, outFd, nChars;
	char buf[BUFFERSIZE];

	if( argc != 3 )
	{
		//参数个数检查
		fprintf(stderr, "usage:%s source destination\n", *argv);  //打印错误信息到标准错误
		exit(1);		//终止程序
	}

	if( (inFd=open(argv[1], O_RDONLY)) == -1 )
	{
		//打开源文件失败
		oops("Cannot open ", argv[1]);
	}

	if( (outFd=creat(argv[2], COPYMODE)) == -1 )
	{
		//创建目标文件失败
		oops("Cannot create ", argv[2]);
	}

	while( (nChars = read(inFd, buf, BUFFERSIZE)) > 0 )
	{
		//从源文件读取的数据长度大于0时，写入目标文件
		if( nChars != write(outFd, buf, nChars) )
		{
			//写文件失败
			oops("Write error to ", argv[2]);
		}
	}

	if( nChars == -1 )
	{
		oops("Read error from ", argv[1]);
	}

	if( close(inFd) == -1 || close(outFd) == -1 )
	{
		oops("Error closing files", "");
	}
}

//出错处理：显示错误信息，并终止程序
void oops(char *s1, char *s2)
{
	fprintf(stderr, "Error: %s ", s1);   //将Error：错误信息格式化输出到标准错误stderr（屏幕）
	perror(s2);		//错误输出函数，输出内容为：（s2:错误内容）
	exit(1);		//终止程序
}