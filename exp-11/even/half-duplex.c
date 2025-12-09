#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include <math.h>
int main()
{
	pid_t pid;
	int fd[2];
	
	if (pipe(fd) == -1) {
		printf("Error");
		exit(-1);
	}
	
	pid=fork();
	
	if (pid>0)
	{
		close(fd[0]);
		int arr[100], limit, i, j=0;
		printf("Enter the limit : ");
		scanf("%d",&limit);
		for (i=0; i<limit; i++)
		{
			if (i % 2 == 0) {
				arr[j]=i;
				j+=1;
			}
		}
		for(i=0; i<limit/2; i++)
		{
			write(fd[1],&arr[i],sizeof(arr[i]));
		}
		close(fd[1]);
	}
	else if (pid==0)
	{	
		wait(NULL);
		close(fd[1]);
		int fd_2, value, square;

		while(read(fd[0],&value, sizeof(value))>0)
		{
			square=pow(value,2);
			printf("%d\t", square);
		}
		close(fd[0]);

	}
	return 0;	
}
