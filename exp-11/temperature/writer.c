#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
int main()
{
	int fd;
	float temp_c;
	char *fifo = "/tmp/myfifo";
	mkfifo(fifo,0666);
	printf("Enter the temperature in celsius :");
    	scanf("%f",&temp_c);
	fd = open(fifo,O_WRONLY);
	if(fd==-1)
	{
		printf("Error...!");
		exit(-1);		
	}
	write(fd,&temp_c,sizeof(temp_c));
	close(fd);
	return 0;
}
