/********* who command ************/
/*
 * who命令的简单实现
 * 实现思路：读取utmp文件，将类型为USER_PROCESS的记录一条一条显示出来
 * 测试平台：Ubuntu 12.04
 * modify by zhanghuan 2016/4/3
*/


#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>

#define SHOWHOST	//远程访问输出

void show_info(struct utmp *utbufp);  //显示一条记录的函数

int main()
{
	struct utmp  currentRecord;
	int utmpfd;		//utmp文件描述符
	int recordLen = sizeof(currentRecord);    //一条记录的长度

	if( (utmpfd = open(UTMP_FILE,O_RDONLY)) == -1 )
	{
		//文件打开失败
		perror(UTMP_FILE);
		exit(1);
	}
	while( read(utmpfd,&currentRecord,recordLen) == recordLen )
	{
		//循环读取并显示
		show_info(&currentRecord);
	}

	close(utmpfd);
	return 0;
}

void show_info(struct utmp *utbufp)
{
	if(utbufp->ut_type != USER_PROCESS)
		return;
	printf("%-8.8s", utbufp->ut_user);
	printf(" ");
	printf("%-8.8s",utbufp->ut_line);
	printf(" ");
	printf("%12.12s", ctime(&(utbufp->ut_tv.tv_sec)) + 4);
	printf(" ");
	#ifdef SHOWHOST
	printf("( %s )", utbufp->ut_host);
	#endif
	printf("\n");
}
