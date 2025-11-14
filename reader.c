#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int fd1, fd2, data;
	char *fifo1 = "/tmp/myfifo1";
	char *fifo2 = "/tmp/myfifo2";
	mkfifo(fifo1, 0666);
	mkfifo(fifo2, 0666);
	fd1 = open(fifo1, O_RDONLY);
	fd2 = open(fifo2, O_WRONLY);
	while (read(fd1, &data, sizeof(data)) > 0) {
		if (data == -1) break;
		else if (data % 2 == 1) write(fd2, &data, sizeof(int));
	}
	int end = -1;
	write(fd2, &end, sizeof(int));
	close(fd2);
	close(fd1);
	unlink(fifo1);
	unlink(fifo2);
	return 0;
}
