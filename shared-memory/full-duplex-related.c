#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
	pid_t pid;
	key_t key = ftok("sm", 18);
	int limit;
        printf("Enter the limit: ");
        scanf("%d", &limit);
	int shmid = shmget(key, limit * sizeof(int), 0666 | IPC_CREAT);
	if (shmid < 0) { 
        	printf("shmget error.");
           	exit(-1);
        }

	pid = fork();

	if (pid < 0) {
		printf("Fork error.");
		exit(-1);
	} else if (pid > 0) {
		int *ptr = (int *) shmat(shmid, NULL, 0);
		for (int i = 0; i < limit; i++)
			ptr[i] = i + 1;
		wait(NULL);
		printf("Odd numbers: ");
		for (int i = 0; i < limit / 2; i++)
			printf("%d\t", ptr[i]);
		shmdt(ptr);
		wait(NULL);
    		shmctl(shmid, IPC_RMID, NULL); 

	} else {
		int *ptr2 = (int *) shmat(shmid, NULL, 0);
		int j = 0;
		for (int i = 0; i < limit; i++) {
			if (ptr2[i] % 2 != 0) {
				ptr2[j] = ptr2[i];
				j++;
			}
		}
		shmdt(ptr2);

	}
	return 0;
}
