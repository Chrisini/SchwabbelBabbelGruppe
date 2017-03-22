// Allgemein

// shared memory accessed by 2 semaphores
// Sa and Sb with same key
// Sa: open
// Sb: closed

// End: The shared memory segment and semaphores must be removed manually using ipcs and ipcrm. 
// ???????

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#define MAXMYMEM 128



void std_printer(int list, int min, int max, int med, int mean){
	
	printf("%d | Min: %d | Max: %d | Median: %d | Mean: %d", list, min, max, med, mean);
	
}

int calc_min(int smallest){
	// kleinste Zahl
	printf("lala: %d", smallest);
	return smallest;
}

int calc_max(int biggest){
	// groesste Zahl
	return biggest;
}

int calc_med(int a, int b){
		//The median value is calculated by calculating the mean of mem[63] and mem[64] after sorting. 
	return (a+b)/2;
}

int calc_mean(int buf[MAXMYMEM]){

	int counter = 0;
	int i = 0;
	for(i = 0; i < MAXMYMEM; i++){
		counter += buf[i];
	}
	
	return counter / MAXMYMEM;
}

int main (void){
	
	int count_transmission = 0;
	
	int shmid;
	int *buf;
	int intbuffer[MAXMYMEM];
	int i;
	key_t key;
	
	// while(1){
		
		// Request access to Sb
		key = ftok("/etc/hostname", 'b');
		// shared memory create
		shmid = shmget(key, MAXMYMEM, 0666);
		if (shmid >= 0){
		// shared memory attach
			buf = shmat(shmid, 0, 0);
			if (buf == NULL){
				perror("shmat");
			}else{
			  for (i=0; i<MAXMYMEM; i++) {
				  printf("buffer: %d", buf[i]);
				  intbuffer [i] = buf[i];
			  }
			  puts("\n");
			  shmdt(buf);
			  // shared memory detach
			}
		}else{
			perror("shmget");
		}
		
		// Sort 128 int values using qsort
	        // qsort(*buf, MAXMYMEM, sizeof(int), int (*compare)(const void *, const void*));
		// Calculate Min, Max, Med, Mean
		
		int tmp;
		
		printf("I am here");
		
		tmp = calc_min(intbuffer[0]);
		printf("a: %d", tmp);
		
		std_printer(count_transmission,calc_min(intbuffer[0]),calc_max(intbuffer[MAXMYMEM-1]),
		            calc_med(intbuffer[63], intbuffer[64]), calc_mean(intbuffer));
		
		// release access to Sa
		// Programm a initializes new set of 
		// 128 int values
		
		count_transmission ++;
	// }
	return 0;
}


