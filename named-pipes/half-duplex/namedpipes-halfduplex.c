#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

int main() 
{
	int fd, limit;
	pid_t pid;
	char *fifo = "/tmp/myfifo";
	mkfifo(fifo, 0666);
	pid = fork();
	if (pid < 0) 
	{
		printf("fork error");
		exit(-1);
	}
	else if (pid > 0)
	{
		printf("In the parent process\n");
		printf("Enter the limit: \n");
		scanf("%d", &limit);
		fd = open(fifo, O_WRONLY);
		if (fd == -1)
		{
			printf("Open error");
			exit(-1);
		}
		for (int i = 1; i <= limit; i++) 
		{
			write(fd, &i, sizeof(int));
		}
		close(fd);
		wait(NULL);
	}
	else
	{
		printf("In the child process\n");
		int num;
		fd = open(fifo, O_RDONLY);
			if (fd == -1)
			{
				printf("Read error");
				exit(-1);
			}
		while (read(fd, &num, sizeof(num)) > 0)
		{
			if (num % 2 == 1)
			printf("%d\t", num);
		}
		printf("\n");
		close(fd);
	}
	unlink(fifo);
	return 0;
}
