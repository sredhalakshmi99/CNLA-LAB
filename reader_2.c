#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
int main()
{
	int fd_2, i, product=1, result;
	char fifo2[]="/tmp/myfifo";
	fd_2=open(fifo2,O_RDONLY);
	if(fd_2==-1)
	{
		printf("Error...!");
		exit(-1);
	}
	while(read(fd_2,&result,sizeof(result))>0)
	{
		product=product*result;
	}
	printf("product=%d\n",product);
	close(fd_2);
	unlink(fifo2);
	return 0;
}
