// Bornberg
// A Pixel Generator program which repeatedly generates
// pixels of an image, and writes them to a shared memory segment



/*
The Pixel Generator and the Image Writer shall communicate via shared memory. The size of this shared memory shall correspond with the number of R/G/B pixels in the image to be created. This value shall be contained in a common header file included by both programs.

The Pixel Generator program shall create the shared memory when it is launched. When the Image Writer program is started, it shall first check if the shared memory segment exists and exit with an error message if it is not yet created.
*/
#include "pixel_generator.h"
#include "general_header.h"

struct rgb_pix{
	int r;
	int g;
	int b;
};

typedef struct rgb_pix PIXEL;

void color_chooser(int col, int row,int i, PIXEL *pRGB){


	(*pRGB+i)->r = 5;
	(*pRGB+i)->g = 10;
	(*pRGB+i)->b) = 255;




	if (n < MAX_ITERATIONS && n > 0) {
    int i = n % 16;
    QColor mapping[16];
    mapping[0].setRgb(66, 30, 15);
    mapping[1].setRgb(25, 7, 26);
    mapping[2].setRgb(9, 1, 47);
    mapping[3].setRgb(4, 4, 73);
    mapping[4].setRgb(0, 7, 100);
    mapping[5].setRgb(12, 44, 138);
    mapping[6].setRgb(24, 82, 177);
    mapping[7].setRgb(57, 125, 209);
    mapping[8].setRgb(134, 181, 229);
    mapping[9].setRgb(211, 236, 248);
    mapping[10].setRgb(241, 233, 191);
    mapping[11].setRgb(248, 201, 95);
    mapping[12].setRgb(255, 170, 0);
    mapping[13].setRgb(204, 128, 0);
    mapping[14].setRgb(153, 87, 0);
    mapping[15].setRgb(106, 52, 3);
    return mapping[i];
}
else return Qt::black;

}

void create_mandel_map(int *big_mem_pix){
	// http://jonisalonen.com/2013/lets-draw-the-mandelbrot-set/

	PIXEL *pRGB = (PIXEL *)malloc(3*sizeof(PIXEL));
	int row, col, iteration = 0;
	double x = 0, y = 0;
	int color_i  = 0;

	for (row = 0; row < P3HEIGHT; row++) {
	    for (col = 0; col < P3WIDTH; col++) {
		double c_re = (col - P3WIDTH/2.0)*4.0/P3WIDTH;
		double c_im = (row - P3HEIGHT/2.0)*2.0/P3HEIGHT; // iwas mit /2??

		while ((x*x+y*y <= 4) && (iteration < MANDELMAXITERATION)){

		    double x_new = x*x - y*y + c_re;
		    y = 2*x*y + c_im;
		    x = x_new;
		    iteration++;
		}
		if (iteration < MANDELMAXITERATION){
			big_mem_pix[color_i] = color_chooser(col, row, iteration, pRGB);
			color_i++;
			big_mem_pix[color_i] = color_chooser(col, row, iteration, pRGB);
			color_i++;
			big_mem_pix[color_i] = color_chooser(col, row, iteration, pRGB);
			color_i++;

		}else{
			big_mem_pix[i]
		}
	    }
	}

}

void communication(int *big_mem_pix){

	// variables for shared memory
	int shmid; // shmid = shared memory id
	int *buf;
	int i;
	key_t key;
	srand(time(NULL));

	// variables for semaphores
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
		puts ("semaphores existed");
		if (semid == -1) {
			perror ("semget");
			exit (EXIT_FAILURE);
		}
	}
		sema.val = 1; // open
		semb.val = 0; // close
		semctl (semid, 0, SETVAL, sema); // nummer 0
		semctl (semid, 1, SETVAL, semb); // nummer 1
		puts ("semaphores created");


  // shmget = create
  shmid = shmget(key, MAXMYMEM, IPC_CREAT | 0666);
	if((shmid == -1)||(errno == ENOENT)){
		printf("segment is not yet created");
	}
	if (shmid >= 0) {
    buf = shmat(shmid, 0, 0);
    if (buf == NULL) {
      perror("shmat");
    }else{
	while(1){
		// Access to Sa
		sa.sem_num = 0; // nummer 0 von oben
		sa.sem_flg = SEM_UNDO;
		sa.sem_op = -1; // sa wird geschlossen nachdem ausgeführt wurde
		if (semop (semid, &sa, 1) == -1) {
			perror ("semop");
		}

		puts ("critical section: sending");

		// 128 random int values
		// from -20 to + 40
		for (i=0; i<MAXMYMEM; i++) {
		  // 128 random int values
		  // from -20 to + 40
		  buf[i] = rand()%61-20;
		  printf(" %d ",buf[i]);
		}

		puts ("it is send");

		// Request acess to Sb
		// B starts to calculate ... in other file
		sb.sem_num = 1; // nummer von oben
		sb.sem_flg = SEM_UNDO;
		sb.sem_op = 1; // will sb öffnen
		if (semop (semid, &sb, 1) == -1) {
			perror ("semop");
		}

		puts ("outside critical section");
	}

      // shmdt = detach !!! oft FEHLER: Core dumped
      shmdt(buf);
	puts ("Here the buffer would be detached");
    }
  }else{
    perror("shmget");
  }

}

int main(int argc, char **argv)
{

	int* big_mem_pix;
	big_mem_pix = (int*) malloc(P3WIDTH*P3HEIGHT*3*sizeof(int));

	create_mandel_map(big_mem_pix);
	communication(big_mem_pix);




  return 0;
}

