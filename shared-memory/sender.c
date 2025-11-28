#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	key_t key;
	key = ftok("sm", 65);
	int shmid;
	int limit;
	printf("Enter the limit");
	scanf("%d", &limit);
	shmid = shmget(key, 1024, IPC_CREAT | 0666);
	int *ptr = (int *) shmat(shmid, NULL, 0);
	ptr[0] = limit;
	for (int i = 1; i < limit; i++) {
		ptr[i] = i;
	}
	shmdt(ptr);
	return 0;
}
