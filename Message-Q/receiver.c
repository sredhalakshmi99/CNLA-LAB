#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdlib.h>

struct number{
		long mtype;
		int msg;
	};
int main()
{
	key_t key2;
	int qid;
	key2=ftok("msgQ",45);
	qid=msgget(key2,0666);
	struct number y,u; 
	msgrcv(qid,&y,sizeof(y.msg),0,0);
	msgrcv(qid,&u,sizeof(u.msg),0,0);
	printf("\nmessage is %d ",y.msg);
	printf("\nmessage is %d \n",u.msg);
	msgctl(qid,IPC_RMID,NULL);
	return 0;
	
	
}

