#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<math.h>
int main()
{
	int fd_2, value, square;
	char fifo2[]="/tmp/myfifo";
	fd_2=open(fifo2,O_RDONLY);
	if(fd_2==-1)
	{
		printf("Error...!");
		exit (-1);
	}
	while(read(fd_2,&value, sizeof(value))>0)
	{
		square=pow(value,2);
		printf("%d\t", square);
	}
	close(fd_2);
	unlink(fifo2);
	return 0;	
}
