#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int fd1, fd2, limit;
	pid_t pid;
	char *fifo1 = "/tmp/fifo1";
	char *fifo2 = "/tmp/fifo2";
	mkfifo(fifo1, 0666);
	mkfifo(fifo2, 0666);

	pid = fork();

	if (pid < 0)
	{
		printf("Fork error");
		return -1;
	}
	else if (pid > 0) 
	{
		printf("Parent process\n");
		int result;
		printf("Enter the limit: ");
		scanf("%d", &limit);
		fd1 = open(fifo1, O_WRONLY);
		fd2 = open(fifo2, O_RDONLY);
		if ((fd1 == -1) || (fd2 == -1))
		exit(-1);
		for (int i = 1; i <= limit; i++)
		write(fd1, &i, sizeof(int));
		int end = -1;
		write(fd1, &end, sizeof(int));

		//reading from child.
			while (read(fd2, &result, sizeof(int)) > 0) 
			{
				if (result == -1) break;
				printf("%d\t", result);
			}
		printf("\n");
		close(fd1);
		close(fd2);
		wait(NULL);
	}
	else
	{
		printf("Child process\n");
		int data;

		fd1 = open(fifo1, O_RDONLY);
		fd2 = open(fifo2, O_WRONLY);

			while (read(fd1, &data, sizeof(int)) > 0)
			{
				if (data == -1) break;
				if (data % 2 == 1)
				write(fd2, &data, sizeof(int));
			}
		int end = -1;
		write(fd2, &end, sizeof(int));
		close(fd1);
		close(fd2);
	}
	unlink(fifo1);
	unlink(fifo2);
	return 0;
}


