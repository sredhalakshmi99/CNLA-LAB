#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#define f (9.0/5)
int main()
{
	int fd2;
	float temp_c,temp_f;
	char *fifo2="/tmp/myfifo";
	fd2=open(fifo2,	O_RDONLY);
	if(fd2==-1)
	{
		printf("Error...!");
		exit(-1);	
	}
	read(fd2,&temp_c,sizeof(temp_c));
	temp_f=(temp_c*f+32);
    	printf("Temperature in fahrenheit : %.2f\n",temp_f);
    	close(fd2);
    	unlink(fifo2);
    	return 0;

	
	
	
	
	
}
