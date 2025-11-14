#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
int main()
{
	int arr[100], limit, i, fd;
	char fifo[] = "/tmp/myfifo";
	mkfifo(fifo,0666);
	printf("Enter the limit : ");
	scanf("%d",&limit);
	for(i=0;i<limit;i++)
	{
		printf("Enter the value for the position %d : ",i);
		scanf("%d",&arr[i]);
	}
	fd=open(fifo,O_WRONLY);
	if (fd==-1 )
	{
		printf("Error...!");
		exit(-1);
	}
	for(i=0;i<limit;i++)
	{
		if(arr[i]%2==0)
		{
			continue;
		}
		else
		{
			write(fd,&arr[i],sizeof(arr[i]));	
		}
	}
	close(fd);
	return 0;
}
