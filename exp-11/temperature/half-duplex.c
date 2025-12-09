#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<sys/stat.h>
#include <stdlib.h>
#include <sys/wait.h>
#define f (9.0/5)
 
 int main()
 {
 	pid_t pid;
 	int fd[2];
 	
 	if (pipe(fd) == -1) {
 		printf("pipe error");
 		exit(-1);
 	}
 	pid = fork();
 	
 	if (pid > 0) {
 		close(fd[0]);
		float temp_c;
		printf("Enter the temperature in celsius :");
	    	scanf("%f",&temp_c);	
		write(fd[1],&temp_c,sizeof(temp_c));
		close(fd[1]);

 	} 
 	else if (pid == 0) 
 	{
 		wait(NULL);
 		close(fd[1]);
		float temp_c,temp_f;
		read(fd[0],&temp_c,sizeof(temp_c));
		temp_f=(temp_c*f+32);
	    	printf("Temperature in fahrenheit : %.2f\n",temp_f);
	    	close(fd[0]);

 	}
 	return 0;
 }
