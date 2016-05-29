#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>

#define KEY 98789



int main()
{
struct msgbuf {
	long mtype;
	char buf[15];
}message;

int qid;
key_t klucz;

if((qid=msgget(KEY,IPC_CREAT))==-1)
{
	printf("Nie utworzono kolejki");
	return 0;
}

message.mtype=1;
printf("Jaki wyraz przekazac do kolejki:\n");
scanf("%s",message.buf);

if((msgsnd(qid,&message,15,0))== -1 )
{
	printf("Blad wysylania wiadomosci");
	return 0;
}

return 0;
}
