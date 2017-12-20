// Bornberg
// An Image Writer program which reads the content of the shared memory segment,
// prepends a PPM header, and writes the image to a file.


// Allgemein

// shared memory accessed by 2 semaphores
// Sa and Sb with same key
// Sa: open
// Sb: closed

// End: The shared memory segment and semaphores must be removed manually using ipcs and ipcrm.
// ???????
// ipcrm -s nummer (shimid)

#include "image_writer.h"
#include "general_header.h"


void image_printer(int* big_mem_p3){
	char openfileName[30];
	char ppm_input[100];
	if (big_mem_p3==NULL){
		printf("Malloc - NULL\n");
	}else{
		printf("Malloc was successful\n");
	}

	FILE * writeFile;
	int file_counter = 1;

	int i;

	sprintf(openfileName,"mandelmap_%d.ppm",file_counter);
	file_counter ++;
	printf("Filename created: %s\n", openfileName);

	// open the file for writing
	writeFile = fopen(openfileName, "w");
	if (writeFile == NULL)
	{
		perror("Error Message");
		exit(EXIT_FAILURE);
	}

	fprintf(writeFile,"P3\n");
	fprintf(writeFile,"%u %u\n", P3WIDTH, P3HEIGHT);
	fprintf(writeFile,"%u\n", P3MAXCOLOUR);

	// P3WIDTH*P3HEIGHT*3
	for (i = 0; i < MAXBIGMEM; i+=3){
		fprintf(writeFile, "%u %u %u\n", (big_mem_p3[i]), (big_mem_p3[i+1]), (big_mem_p3[i+2]));
	}

	fflush(writeFile);
	fclose(writeFile);
}

int main (void)
{

	int count_transmission = 0;

	// shared memory
	int shmid;
	int *buf;
	int intbuffer[MAXMYMEM];
	int i;
	key_t key;
	int ret = 0;

	int* big_mem_p3;
	big_mem_p3 = (int*) malloc(P3WIDTH*P3HEIGHT*3*sizeof(int));

	// semaphores
	int semid;
	struct sembuf sa, sb;
	union semun sema;
	union semun semb;

	int i_color = 0;

	// key
	key = ftok ("/etc/hostname", 'b');
	// check whether semaphore exists - if not create it
	semid = semget (key, 2, IPC_CREAT | IPC_EXCL | 0666);
	if (semid == -1) {
		// if semaphore exists get the semaphore id
		semid = semget (key, 2, 0 | 0666);
		if (semid == -1) {
			perror ("semget");
			exit (EXIT_FAILURE);
		}
	}
		sema.val = 1; // open
		semb.val = 0; // close
		semctl (semid, 0, SETVAL, sema); // sema: number 0
		semctl (semid, 1, SETVAL, semb); // semb: number 1

		puts ("semaphores created");

	// Allocates shared memory segment: key, size, flags
	shmid = shmget (key, MAXMYMEM, 0666);
	if (shmid >= 0) {
		// shared memory attach: id, addr, flags
		buf = shmat (shmid, 0, 0);
		if (buf == NULL) {
			perror ("shmat");
		} else {
			while (1) {
				// pend operation
				sb.sem_num = 1; // nummer von oben
				sb.sem_flg = SEM_UNDO;
				sb.sem_op = -1; // sb wird geschlossen nachdem ausgeführt wurde
				if (semop (semid, &sb, 1) == -1) {
					perror ("semop");
				}

				puts ("critical section");

				for (i = 0; i < MAXMYMEM; i++) {

					if(sizeof(buf[i]) < 1){
						printf("Break");
						break;
					}
					big_mem_p3 [i_color] = buf[i];
					printf (" %d ", big_mem_p3[i_color]);
					i_color ++;
				}

				puts ("\n");

				puts ("Read all the colors");

				// post operation
				sa.sem_num = 0; // nummer von oben
				sa.sem_flg = SEM_UNDO;
				sa.sem_op = 1; // will sa öffnen
				if (semop (semid, &sa, 1) == -1) {
					perror ("semop");
				}

				if(i_color > MAXBIGMEM){
					shmdt (buf);
					break;
				}


				puts ("outside critical section\n");

				printf("wait...\n");


				count_transmission ++;
				printf ("End of get\n");

			}
		}
	}

	image_printer(big_mem_p3);

	// shared memory detach CAREFUL: Core Dumped Errors

	return 0;
}
