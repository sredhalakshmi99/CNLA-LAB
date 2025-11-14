#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int fd1, fd2, limit, result;
	char *fifo1 = "/tmp/myfifo1";
	char *fifo2 = "/tmp/myfifo2";
	mkfifo(fifo1, 0666);
	mkfifo(fifo2, 0666);
	printf("enter the limit: ");
	scanf("%d", &limit);
	fd1 = open(fifo1, O_WRONLY);
	fd2 = open(fifo2, O_RDONLY);
	for (int i = 1; i <= limit; i++)
	write(fd1, &i, sizeof(int));
	int end = -1;
	write(fd1, &end, sizeof(int));
	//reading from the reader.c
	while (read(fd2, &result, sizeof(int)) > 0)
	{
		if (result == -1) break;
		printf("%d\t", result);
	}
	printf("\n");
	close(fd1);
	close(fd2);
	unlink(fifo1);
	unlink(fifo2);
	return 0;
}

