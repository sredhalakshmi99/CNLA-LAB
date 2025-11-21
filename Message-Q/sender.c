#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
struct number{
		long mtype;
		int msg;
	};
int main()
{
	key_t key;
	int qid;
	
	key=ftok("msgQ",45);
	printf("\ngenerated key : %d",key);
	qid=msgget(key,0666|IPC_CREAT);
	printf("\nmsg queue id : %d\n",qid);
	
	struct number x;
	struct number z;
	x.mtype=2;
	x.msg=1236;
	z.mtype=4;
	z.msg=2354;
	msgsnd(qid,&x,sizeof(x.msg),0);
	msgsnd(qid,&z,sizeof(z.msg),0);
	return 0;
	
}

