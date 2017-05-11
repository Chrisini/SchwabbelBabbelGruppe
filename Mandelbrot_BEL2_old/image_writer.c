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



void std_printer (int list, int min, int max, int med, int mean)
{
	printf ("%d | Min: %d | Max: %d | Median: %d | Mean: %d\n", list, min, max, med, mean);
}
int calc_min (int smallest)
{
	return smallest;
}
int calc_max (int biggest)
{
	return biggest;
}
int calc_med (int a, int b)
{
	//calculating mean of mem[63] and mem[64] after sorting.
	return (a + b) / 2;
}
int calc_mean (int buf[MAXMYMEM])
{
	int counter = 0, i = 0;
	for (i = 0; i < MAXMYMEM; i++) {
		counter += buf[i];
	}
	return counter / MAXMYMEM;
}
int compare (const void * a, const void * b)
{
	return (* (int*) a - * (int*) b);
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

	// semaphores
	int semid;
	struct sembuf sa, sb;
	union semun sema;
	union semun semb;

	// key
	key = ftok ("/etc/hostname", 'b');
	// check whether semaphore exists - if not create it
	semid = semget (key, 2, IPC_CREAT | IPC_EXCL | 0666); // 2 = anzahl
	if (semid == -1) {
		// if semaphore exists get the semaphore id
		semid = semget (key, 2, 0 | 0666); // 2 = anzahl
		if (semid == -1) {
			perror ("semget");
			exit (EXIT_FAILURE);
		}
	}//else{
		// if sempahore was created new initalize it
		sema.val = 0; // open
		semb.val = 1; // close
		semctl (semid, 0, SETVAL, sema); // nummer
		semctl (semid, 1, SETVAL, semb); // nummer

		puts ("semaphores created");
	//}

	// shared memory create
	shmid = shmget (key, MAXMYMEM, 0666);
	if (shmid >= 0) {
		// shared memory attach
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
					printf (" %d ", buf[i]);
					intbuffer [i] = buf[i];
				}
				puts ("\n");

				puts ("Read all the numbers");

				// post operation
				sa.sem_num = 0; // nummer von oben
				sa.sem_flg = SEM_UNDO;
				sa.sem_op = 1; // will sa öffnen
				if (semop (semid, &sa, 1) == -1) {
					perror ("semop");
				}

				puts ("outside critical section");


				// Sort 128 int values using qsort (done)
				qsort (intbuffer, MAXMYMEM, sizeof (int), compare);
				// Calculate Min, Max, Med, Mean (done)
				std_printer (count_transmission, calc_min (intbuffer[0]), calc_max (intbuffer[MAXMYMEM - 1]),
					     calc_med (intbuffer[63], intbuffer[64]), calc_mean (intbuffer));

				// release access to Sa
				// Programm a initializes new set of
				// 128 int values

				count_transmission ++;
				printf ("End of get");
			}
		/*}else{
			perror("shmget");
		}*/

		}

	}
	shmdt (buf);
	// shared memory detach CAREFUL: Core Dumped Errors

	return 0;
}
