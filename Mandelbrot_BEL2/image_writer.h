#ifndef IMAGE_WRITER_H
#define IMAGE_WRITER_H


union semun {
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
};

#endif
