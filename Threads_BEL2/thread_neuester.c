// Bornberg

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define fileNameLength 30
#define matriceLength 50
#define THREAD_NUMBER 5

struct col_row{
	int i_row;
	int i_col;
};


struct timeval t1, t2, t3, t4;

void *multiply_by_threads(void *param);

int matriceA[matriceLength][matriceLength];
int matriceB[matriceLength][matriceLength];
int matriceResult[matriceLength][matriceLength];


// CREATE RANDOM NUMBERS
void read_file(int matrice[matriceLength][matriceLength]){
	// one time a, one time b

	int i, j;
	for(i = 0; i < matriceLength; i ++){
		for(j = 0; j < matriceLength; j ++){
			matrice[i][j] = rand()%5+1;
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
   struct col_row *data = param; // the structure that holds our data
   int n, sum = 0; //the counter and sum

   //Row multiplied by column
   for(n = 0; n< matriceLength; n++){
      sum += matriceA[data->i_row][n] * matriceB[n][data->i_col];
   }
   //assign the sum to its coordinate
   matriceResult[data->i_row][data->i_col] = sum;

   //Exit the thread
   pthread_exit(0);
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

	read_file(matriceA);
	printf("\n");
	read_file(matriceB);
	printf("\n");

	// BEGIN THREAD

	gettimeofday(&t1, NULL);

	printf("heree");

   for(i = 0; i < matriceLength; i++) {
      for(j = 0; j < matriceLength; j++) {
         //Assign a row and column for each thread
         struct col_row *data = (struct col_row *) malloc(sizeof(struct col_row));
         data->i_col = i;
         data->i_row = j;
         /* Now create the thread passing it data as a parameter */
         pthread_t tid;       //Thread ID
         pthread_attr_t attr; //Set of thread attributes
         //Get the default attributes
         pthread_attr_init(&attr);
         //Create the thread
         pthread_create(&tid,&attr,multiply_by_threads,data);
         //Make sure the parent waits for all thread to complete
         pthread_join(tid, NULL);
         k++;
      }
   }



	gettimeofday(&t2, NULL);
  	diff = (t2.tv_sec+t2.tv_usec*0.000001)-(t1.tv_sec+t1.tv_usec*0.000001);

	printf("thread differenz: %f\n", diff);


	// END THREAD

	// MULTIPLY NORMAL CALL

	gettimeofday(&t3, NULL);
	multiply_matrices();
  	gettimeofday(&t4, NULL);
  	diff = (t4.tv_sec+t4.tv_usec*0.000001)-(t3.tv_sec+t3.tv_usec*0.000001);
	printf("differenz ohne threads: %f\n", diff);

	// matricePrinter(matriceResult);

	printf("\n");
	printf("Good Bye!\n");
	return 0;
}

