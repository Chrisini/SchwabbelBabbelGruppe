#ifndef IMAGE_WRITER
#define IMAGE_WRITER

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/sem.h>
#include <stdlib.h>
#define MAXMYMEM 128

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
};

#endif
