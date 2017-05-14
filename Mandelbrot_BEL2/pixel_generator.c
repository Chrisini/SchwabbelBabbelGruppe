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

void color_chooser(int i, PIXEL **pRGB){

	// printf("i: %d\n", i);

	*pRGB = (PIXEL *)malloc(3*sizeof(PIXEL));

	switch (i){
		case 0: // brown pod - brown
			(*pRGB)->r = 66;
			(*pRGB)->g = 30;
			(*pRGB)->b = 15;
			break;
		case 1: // mardi gras - purple
			(*pRGB)->r = 15;
			(*pRGB)->g = 7;
			(*pRGB)->b = 26;
			break;
		case 2: // green
			(*pRGB)->r = 9;
			(*pRGB)->g = 1;
			(*pRGB)->b = 47;
			break;
		case 3: // blue
			(*pRGB)->r = 4;
			(*pRGB)->g = 4;
			(*pRGB)->b = 73;
			break;
		case 4: // blue - a bit lighter
			(*pRGB)->r = 0;
			(*pRGB)->g = 7;
			(*pRGB)->b = 100;
			break;
		case 5: // blue - a bit lighter
			(*pRGB)->r = 12;
			(*pRGB)->g = 44;
			(*pRGB)->b = 138;
			break;
		case 6: // blue - a bit lighter
			(*pRGB)->r = 24;
			(*pRGB)->g = 82;
			(*pRGB)->b = 177;
			break;
		case 7: // light blue
			(*pRGB)->r = 57;
			(*pRGB)->g = 125;
			(*pRGB)->b = 209;
			break;
		case 8: // light blue - lighter
			(*pRGB)->r = 134;
			(*pRGB)->g = 181;
			(*pRGB)->b = 229;
			break;
		case 9: // light blue - nearly white
			(*pRGB)->r = 211;
			(*pRGB)->g = 236;
			(*pRGB)->b = 248;
			break;
		case 10: // light yellow
			(*pRGB)->r = 241;
			(*pRGB)->g = 233;
			(*pRGB)->b = 191;
			break;
		case 11: // yellow
			(*pRGB)->r = 248;
			(*pRGB)->g = 201;
			(*pRGB)->b = 95;
			break;
		case 12: // yellow -darker
			(*pRGB)->r = 255;
			(*pRGB)->g = 170;
			(*pRGB)->b = 0;
			break;
		case 13: // brown
			(*pRGB)->r = 204;
			(*pRGB)->g = 128;
			(*pRGB)->b = 0;
			break;
		case 14: // dark brown
			(*pRGB)->r = 153;
			(*pRGB)->g = 87;
			(*pRGB)->b = 0;
			break;
		case 15: // darker dark brown
			(*pRGB)->r = 106;
			(*pRGB)->g = 52;
			(*pRGB)->b = 3;
			break;
		default: // schwarz
			(*pRGB)->r = 0;
			(*pRGB)->g = 0;
			(*pRGB)->b = 0;
			break;
	} // case end

} // function end



void create_mandel_map(int *big_mem_pix){
	// http://jonisalonen.com/2013/lets-draw-the-mandelbrot-set/

	double x, xx, y, cx, cy;
	int iteration, hx, hy;
	int itermax = 100;
	double magnify = 1.0;
	int hxres = 500; // horizontal
	int hyres = 500; // vertical
	PIXEL *pRGB;
	int color_i  = 0;
	int col = 0;

	for (hy =1; hy <= hyres; hy++) {
	    for (hx = 1; hx <= hxres; hx++) {
		cx = (((float)hx) / ((float)hxres)-0.5)/magnify*3.0-0.7;
		cy = (((float)hy) / ((float)hyres)-0.5)/magnify*3.0;
		x = 0.0;
		y = 0.0;
		for (iteration = 1; iteration < itermax; iteration++){
			// printf(" %d ", iteration);
			xx = x*x-y*y+cx;
			y = 2.0*x*y+cy;
			x = xx;
			if((x*x+y*y)>100.0){
				// printf(" hello: %d ", iteration);
				iteration = 999999;
			}
		}

		//printf(" i:%d m:%d ", iteration, itermax);
		if (iteration > 999){
			int i = iteration % 16;
			printf("i:%d,%d ", iteration, i);

			//printf("a");
			color_chooser(col, &pRGB);
			if(col >= 15){
				col = 0;
			}else{
				col ++;
			}

			big_mem_pix[color_i] = pRGB->r;
			//printf("%d", big_mem_pix[color_i]);
			color_i++;
			big_mem_pix[color_i] = pRGB->g;
			//printf("%d", big_mem_pix[color_i]);
			color_i++;
			big_mem_pix[color_i] = pRGB->b;
			//printf("%d", big_mem_pix[color_i]);
			color_i++;
			free(pRGB);
		}else{
			//printf("b");
			big_mem_pix[color_i] = 0;
			color_i++;
			big_mem_pix[color_i] = 0;
			color_i++;
			big_mem_pix[color_i] = 0;
			color_i++;
			// printf("b");
		}
	    }
	}
}

void communication(int *big_mem_pix){

	// variables for shared memory
	int shmid; // shmid = shared memory id
	int *buf;
	int i;
	int i_col = 0;
	key_t key;

	// variables for semaphores
	int semid;
	struct sembuf sa, sb;
	union semun sema;
	union semun semb;

	// key
	key = ftok ("/etc/hostname", 'b');

	// create semaphores
	semid = semget (key, 2, IPC_CREAT | IPC_EXCL | 0666);
	if (semid == -1) {
		// if semaphore exists get the semaphore id
		semid = semget (key, 2, 0 | 0666);
		puts ("semaphores existed");
		if (semid == -1) {
			perror ("semget");
			exit (EXIT_FAILURE);
		}
	}

	// Semaphores open/close
	sema.val = 1; // open
	semb.val = 0; // close
	semctl (semid, 0, SETVAL, sema);
	semctl (semid, 1, SETVAL, semb);

	puts ("semaphores created");

	// create shared memory
	shmid = shmget(key, MAXMYMEM, IPC_CREAT | 0666);
	if((shmid == -1)||(errno == ENOENT)){
		printf("segment is not yet created");
	}

	//attach
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
		  buf[i] = big_mem_pix[i_col];
		  i_col++;
		  printf(" %d ",buf[i]);
		}
		if(i_col > MAXBIGMEM){
			break;
		}


		// Request acess to Sb
		sb.sem_num = 1;
		sb.sem_flg = SEM_UNDO;
		sb.sem_op = 1; // Open SB
		if (semop (semid, &sb, 1) == -1) {
			perror ("semop");
		}

		puts ("outside critical section");
		printf("wait");

	}
	shmdt(buf);
    }
  }else{
    perror("shmget");
  }

}

void clean_up(int* big_mem_pix){

	printf("Clean");
	free(big_mem_pix);
	exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{

	int* big_mem_pix;
	big_mem_pix = (int*) malloc(P3WIDTH*P3HEIGHT*3*sizeof(int));

	create_mandel_map(big_mem_pix);
	communication(big_mem_pix);
	//clean_up(big_mem_pix);

  return 0;
}

