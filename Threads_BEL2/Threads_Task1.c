// Bornberg

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define matriceLength 5
#define THREAD_NUMBER 2

struct timeval t1, t2, t3, t4;

void *multiply_by_threads(void *param);

int matriceA[matriceLength][matriceLength];
int matriceB[matriceLength][matriceLength];
int matriceResult[matriceLength][matriceLength];


// CREATE RANDOM NUMBERS
void read_file(){
	// one time a, one time b

	int i, j;
	for(i = 0; i < matriceLength; i ++){
		for(j = 0; j < matriceLength; j ++){
			matriceA[i][j] = rand()%5+1;
		}
	}

	for(i = 0; i < matriceLength; i ++){
		for(j = 0; j < matriceLength; j ++){
			matriceB[i][j] = rand()%5+1;
		}
	}
}

// MULTIPLY NORMAL
void multiply_matrices(void){

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

// MULTIPLY BY THREADS
void *multiply_by_threads(void *param) {

	int s = (int) param;
	int from = (s * matriceLength)/THREAD_NUMBER;
	int to = ((s+1) * matriceLength)/THREAD_NUMBER;
   	int n,m,o;

   //Row multiplied by column
   for(n = from; n < to; n++){
	for(m = 0; m < matriceLength; m++){
		matriceResult[n][m] = 0;
		for(o = 0; o < matriceLength; o++){
			matriceResult[n][m] += matriceA[n][o] * matriceB[o][n];
		}
	}
   }
}

// PRINT MATRICES
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


int main(){

	srand(time(NULL));

	double diff = 0.0;
	int i,j,k = 0;

	printf("begin to create random numbers\n");
	read_file();
	read_file();
	printf("random numbers created\n");

	pthread_t* group_thread;
	group_thread = (pthread_t*) malloc(THREAD_NUMBER*sizeof(pthread_t));


	// BEGIN THREAD
	gettimeofday(&t1, NULL);

	for(i = 0; i < matriceLength; i++){
		if(pthread_create (&group_thread[i], NULL, multiply_by_threads, (void*)i) != 0){
			perror("Can't create thread");
      		free(group_thread);
      		exit(-1);
	   }
	}

	for (i = 1; i < THREAD_NUMBER; i++){
 		pthread_join (group_thread[i], NULL);
	}


	gettimeofday(&t2, NULL);
  	diff = (t2.tv_sec+t2.tv_usec*0.000001)-(t1.tv_sec+t1.tv_usec*0.000001);
  	printf("thread differenz: %f\n", diff);

	// free(group_thread);


	matricePrinter(matriceResult);

	// END THREAD


	// MULTIPLY NORMAL CALL
	gettimeofday(&t3, NULL);
	multiply_matrices();
  	gettimeofday(&t4, NULL);
  	diff = (t4.tv_sec+t4.tv_usec*0.000001)-(t3.tv_sec+t3.tv_usec*0.000001);
	printf("differenz ohne threads: %f\n", diff);

	matricePrinter(matriceResult);

	printf("\n");
	printf("Good Bye!\n");
	return 0;
}
