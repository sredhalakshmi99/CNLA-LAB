#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/wait.h>

int main()
{
	pid_t pid;
	int fd[2];
	if (pipe(fd) == -1) {
		printf("Error");
		exit(-1);
	}
	pid = fork();
	
	if (pid > 0) 
	{	
		close(fd[0]);
		int arr[100], limit, i;
		printf("Enter the limit : ");
		scanf("%d",&limit);
		for(i=0;i<limit;i++)
		{
			printf("Enter the value for the position %d : ",i);
			scanf("%d",&arr[i]);
		}
		for(i=0;i<limit;i++)
		{
			if(arr[i]%2==0)
			{
				continue;
			}
			else
			{
				write(fd[1],&arr[i],sizeof(arr[i]));	
			}
		}
		close(fd[1]);

	

	} 
	else if (pid == 0) 
	{
		wait(NULL);
		close(fd[1]);
		int i, product=1, result;
		
		while(read(fd[0],&result,sizeof(result))>0)
		{
			product=product*result;
		}
		printf("product=%d\n",product);
		close(fd[0]);

	}
	return 0;
}
