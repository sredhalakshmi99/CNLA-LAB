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
	int shmid, limit;
	shmid = shmget(key, 1024, 0666);
	int *ptr = shmat(shmid, NULL, 0);
	limit = ptr[0];
	for (int i = 1; i < limit; i++) {
		if (ptr[i] % 2 != 0)
			printf("%d\t", ptr[i]);
	}
	shmdt(ptr);
	return 0;
}
