#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
int main()
{
	int arr[100], limit, i, even=0, fd;
	char fifo[] = "/tmp/myfifo";
	mkfifo(fifo,0666);
	printf("Enter the limit : ");
	scanf("%d",&limit);
	for (i=0; i<limit; i++)
	{
		arr[i]=even;
		even+=2;
	}
	fd=open(fifo, O_WRONLY);
	if (fd==-1)
	{
		printf("ERROR...!");
		exit (-1);
	}
	for(i=0; i<limit; i++)
	{
		write(fd,&arr[i],sizeof(arr[i]));
	}
	close(fd);
	return 0;
}
