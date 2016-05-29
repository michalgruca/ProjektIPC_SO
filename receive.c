#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <fcntl.h>

#define KEY 98789

int main()
{
int pid,pid2;
int fd[2];
int fd2[2];
int czytaj;
pipe(fd);
pid=fork();
if(pid==0)
{
	close(1);
	dup(fd[1]);
	execlp("date","date","+%u",NULL);
}
else
{
	close(0);
	dup(fd[0]);
	int hour;
	char bufor[1];
	char bufor2[2];
	czytaj= fread(bufor,1,1,stdin);
	int date=atoi(bufor);
	if(date >= 5)
	{
		if(date == 5)
		{
		pipe(fd2);
		pid2=fork();
		if(pid2==0)
		{
			close(1);
			dup(fd2[1]);
			execlp("date","date","+%H",NULL);
		}
		}
		else
		{
			close(0);
			dup(fd2[0]);
			scanf("%s",bufor2);
			hour=atoi(bufor2);
			if(hour<17)
			{
			printf("To nie weekend");
			return 0;
			}
		}
}
int receive;
struct msg {
	long mtype;
	char buf[15];
}message;

int qid=msgget(KEY,0);
receive=msgrcv(qid,&message,15,0,0);
int dlg= strlen(message.buf);
int i;
int a;
a=1;
for(i=0;i<dlg;i++)
{
	if(message.buf[i]<32 || message.buf[i]>126)
	{
	a=0;
	}
}

if(!((message.buf[0] >='A' && message.buf[0] <='Z') || (message.buf[0]>='a' && message.buf[0] <='z')))
{
a=0;
}
if(a==1)
{
	int x;
	x=open( "plik" , O_RDWR | O_CREAT , S_IWOTH );
	if(!(x<0))
	{
	write(x,message.buf,dlg);
	}
}
else
{
	printf("To nie slowo, blad");
}
}
return 0;
}
