// Bornberg

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define fileNameLength 30
#define matriceLength 700
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void *print_message_function( void *ptr );

struct timeval t1, t2, t3, t4;

void multiply_matrices(int matriceA[matriceLength][matriceLength],
		       int matriceB[matriceLength][matriceLength],
		       int matriceResult[matriceLength][matriceLength]){


	int i, j, k;
	for (i = 0; i < matriceLength; i++) {
		for (j = 0; j < matriceLength; j++) {
			matriceResult[i][j] = 0;
			for (k = 0; k < matriceLength; k++) {
			  	matriceResult[i][j] += matriceA[i][k] * matriceB[k][j];
			}
		}
	}
}

void read_file(char filename[fileNameLength], int matrice[matriceLength][matriceLength]){
	// one time a, one time b

	int i, j;
	for(i = 0; i < matriceLength; i ++){
		for(j = 0; j < matriceLength; j ++){
			matrice[i][j] = rand()%5+1;
		}
	}
}

void matricePrinter(int matrice[matriceLength][matriceLength]){
	int i, j;
	for(i = 0; i < matriceLength; i ++){
		for(j = 0; j < matriceLength; j ++){
			if(matrice[i][j] < 10){
				printf("0");
			}
			printf("%d ", matrice[i][j]);
		}
		printf("\n");
	}
}

void thread_multiply_matrices(int matriceA[matriceLength][matriceLength],
		       int matriceB[matriceLength][matriceLength],
		       int matriceResult[matriceLength][matriceLength]){



}

int main(){

	srand(time(NULL));

	char filenameA[fileNameLength];
	char fileNameB[fileNameLength];
	int matriceA[matriceLength][matriceLength];
	int matriceB[matriceLength][matriceLength];
	int matriceResult[matriceLength][matriceLength];

	double diff = 0.0;

	read_file(filenameA, matriceA);
	printf("\n");
	read_file(fileNameB, matriceB);
	printf("\n");

	// BEGIN THREAD
	//
	gettimeofday(&t1, NULL);

	thread_multiply_matrices(matriceA, matriceB, matriceResult);

  	gettimeofday(&t2, NULL);
  	diff = (t2.tv_sec+t2.tv_usec*0.000001)-(t1.tv_sec+t1.tv_usec*0.000001);

	printf("thread differenz: %f\n", diff);


pthread_t thread1, thread2;
  char *message1 = "Thread 1";
  char *message2 = "Thread 2";
  int  iret1, iret2;

  iret1 = pthread_create( &thread1, NULL, print_message_function, (void*) message1);
  iret2 = pthread_create( &thread2, NULL, print_message_function, (void*) message2);

  pthread_join( thread1, NULL);
  pthread_join( thread2, NULL);

  printf("Thread 1 returns: %d\n",iret1);
  printf("Thread 2 returns: %d\n",iret2);



	// END THREAD


	gettimeofday(&t1, NULL);

	multiply_matrices(matriceA, matriceB, matriceResult);

  	gettimeofday(&t2, NULL);
  	diff = (t2.tv_sec+t2.tv_usec*0.000001)-(t1.tv_sec+t1.tv_usec*0.000001);

	printf("differenz ohne threads: %f\n", diff);

	// matricePrinter(matriceResult);
	printf("\n");
	printf("Good Bye!\n");
	return 0;
}

void *print_message_function( void *ptr )
{
  char *message;
  message = (char *) ptr;
  printf("%s \n", message);
}
