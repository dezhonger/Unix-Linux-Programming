#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>

#define SHOWHOST	//远程访问输出

void show_info(struct utmp *utbufp);

int main()
{
	struct utmp  currentRecord;
	int utmpfd;		//utmp文件描述符
	int recordLen = sizeof(currentRecord);

	if( (utmpfd = open(UTMP_FILE,O_RDONLY)) == -1 )
	{
		//文件打开失败
		perror(UTMP_FILE);
		exit(1);
	}
	while( read(utmpfd,&currentRecord,recordLen) == recordLen )
	{
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
	printf("time:%s", ctime(&(utbufp->ut_tv.tv_sec)));
	printf(" ");
	#ifdef SHOWHOST
	printf("( remote host:%s )", utbufp->ut_host);
	#endif
	printf("\n");
}
