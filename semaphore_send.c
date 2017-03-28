#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <time.h>
#define MAXMYMEM 128

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
};

int main(int argc, char **argv)
{

  // shared memory
  int shmid; // shmid = shared memory id
  int *buf;
  int i;
  key_t key;
  srand(time(NULL));

  int abcd = 0;

  // semaphores
  int semid;
  struct sembuf sa, sb;
  union semun sema;
  union semun semb;
  // key_t key;

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
	}


	// if sempahore was created new initalize it
	sema.val = 1; // open
	semb.val = 0; // close
	semctl (semid, 0, SETVAL, sema); // nummer
	semctl (semid, 1, SETVAL, semb); // nummer

	puts ("semaphores created");
	// getchar();

  // shmget = create
  shmid = shmget(key, MAXMYMEM, IPC_CREAT | 0666);
  if (shmid >= 0) {
    buf = shmat(shmid, 0, 0);
    if (buf == NULL) {
      perror("shmat");
    }   else    {
	while(1){
	    // pend operation
	sa.sem_num = 0; // nummer von oben
	sa.sem_flg = SEM_UNDO;
	sa.sem_op = -1; // sa wird geschlossen nachdem ausgeführt wurde
	if (semop (semid, &sa, 1) == -1) {
		perror ("semop");
	}

	puts ("critical section");
	// getchar();

	for (i=0; i<MAXMYMEM; i++) {
	  // 128 random int values
	  // from -20 to + 40
          buf[i] = rand()%61-20;
          printf(" %d ",buf[i]);
        }
	puts ("Numbers are created and send");
        // getchar();


	// post operation
	sb.sem_num = 1; // nummer von oben
	sb.sem_flg = SEM_UNDO;
	sb.sem_op = 1; // will sb öffnen
	if (semop (semid, &sb, 1) == -1) {
		perror ("semop");
	}

	puts ("outside critical section");
	}

      // shmdt = detach
      shmdt(buf);
    }
  }
  else
  {
    perror("shmget");
  }
puts ("End Send");

  return 0;
}
