// Bornberg

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define fileNameLength 30
#define matriceLength 4

void multiply_matrices(int matriceA[matriceLength][matriceLength],
		       int matriceB[matriceLength][matriceLength]){


}

void read_file(char filename[fileNameLength], int matrice[matriceLength][matriceLength]){
	// one time a, one time b

	srand(time(NULL));
	int i, j;
	for(i = 0; i < matriceLength; i ++){
		for(i = 0; i < matriceLength; i ++){
			matrice[i][j] = rand()%100+20;
		}
	}
}

int main(){

	char filenameA[fileNameLength];
	char fileNameB[fileNameLength];
	int matriceA[matriceLength][matriceLength];
	int matriceB[matriceLength][matriceLength];


	read_file(filenameA, matriceA);
	read_file(fileNameB, matriceB);

	multiply_matrices(matriceA, matriceB);

	write("Good Bye!");
	return 0;
}
