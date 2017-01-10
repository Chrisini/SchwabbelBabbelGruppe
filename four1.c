/*-----------------------------------------------------------------*/
/* Author: Christina Bornberg BEL 1                                */
/*                                                                 */
/* Created: 2017-01-06                                             */
/* Finished: 2017-01-10											   */
/*                                                                 */
/* About: The game '4 in a row' should be developed				   */
/* 																   */
/*																   */
/* How to use: (GERMAN)											   */
/* Command line example: a.exe -m pvc -l loadgame.txt -a -b		   */
/* -m ... mode: pvp, pvc, cvc (p = player, vs, c = computer)	   */
/* -l ... load: any .txt, .c, ... file, which follows the command  */
/* from openGame												   */
/* -a ... algorithm: b (brainfuck), c (computer / chrisy)		   */
/* -h ... usage message + quit									   */
/* quit game with 'Z'											   */
/* save it with 'Y' for yes and type in a filename 				   */
/*-----------------------------------------------------------------*/

// includes ------------------
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

// defines ------------------
#define DEBUG 0
#define MAX_FILENAME_LENGTH 100

// prototypes ------------------
char brainfuck_algorithm(int fieldWidth); // random algorithm
char chrisy_algorithm(int fwidth, int fheight, char fEntrys[fwidth][fheight], int myNumber); // my algorithm, ideas from negamax
char checkCommandParam (int argc, char *argv[], char player[2][100], char fileName[MAX_FILENAME_LENGTH]); // command line parameters
void openGame(char fileName[100], int fieldWidth, int fieldHeight, char fieldEntrys[fieldWidth][fieldHeight]); // open a game (fileinput)
void fieldPrinter(int fieldWidth, int fieldHeight, char fieldEntrys[fieldWidth][fieldHeight]); // prints the faming field to command line
void playerName(int playerindex, char player[100]); // player chooses name
void computerName(int playerindex, char player[100]); // computer name is generated
char playerChooses(char player[100], int fieldWidth, int iWhoTurn); // player chooses field
char computerChooses(char choosen_algorithm, int fieldWidth, int fieldHeight, char fieldEntrys[fieldWidth][fieldHeight], int me); // computer chooses field (algorithms)
void fillingArray(int fieldWidth, int fieldHeight, char fieldEntrys[fieldWidth][fieldHeight], char choice, int iWhoTurn); // filling array with choosen field
int evaluateFour(int fieldWidth, int fieldHeight, char fieldEntrys[fieldWidth][fieldHeight], int iWhoTurn); // evaluates if someone has won
void saveGame(int fieldWidth, int fieldHeight, char fieldEntrys[fieldWidth][fieldHeight]); // save game (fileoutput)

// Algorithm, that chooses randomly any letter, without caring about the game
char brainfuck_algorithm(int fieldWidth){
	return (rand()%fieldWidth) + 65; // 0 - width; A-1
}

// my algorithm
// every entry, where it is able to put a chip in, gets a value,
// the measurement could be improved, but all in all it works like that
// ideas from Minimax / Negamax - algorithm https://gist.github.com/MatthewSteel/3158579
char chrisy_algorithm(int fwidth, int fheight, char fEntrys[fwidth][fheight], int myNumber){

	char me = myNumber+'0'; // usually player 2 (pvc)
	char notMe = '2';
	if(me == '2'){
		notMe = '1'; // usually player 1 (pvc)
	}
	
	int evalArray[fwidth][fheight]; // evaluation points
	int j, i; // counter of columns and rows

	// for finding highest
	char choosenLetter = brainfuck_algorithm(fwidth);
	int highest = 0;

	printf("MY NUMBER: %c\n", me);

	// Initialising 
	for(j = 0; j < fwidth; j++){
		for(i = 0; i < fheight; i++){
				evalArray [j][i] = 0; // set ranking to zero
		}
	}

	// Every field of the array gets a ranking
	for(j = 0; j < fwidth; j++){
			for(i = 0; i < fheight; i++){
				// fields who are possible, are getting a '10'
				if(fEntrys[j][i] == ' '){
					if(fEntrys[j][i+1] == me || fEntrys[j][i+1] == notMe || ((i+1) == fheight)){  
						evalArray[j][i] += 10;
					}
				}

				// VERTICALLY ***************************************

				// my way - vertically
				// there can't be chips above me
				if(evalArray[j][i] != 0){
					if(fEntrys[j][i+1] == me){
						if(i-3 > 0){
							evalArray[j][i] += 100;
						}else{
							evalArray[j][i] -= 5; // not enough space
						}
						if(fEntrys[j][i+2] == me){
							if(i-2 > 0){
								evalArray[j][i] += 100;
							}else{
								evalArray[j][i] -= 5; // not enough space
							}
							if(fEntrys[j][i+3] == me){
								if(i-1 > 0){
									evalArray[j][i] += 1000; // high prio
								}else{
									evalArray[j][i] -= 5; // not enough space
								}
							}
						}
					}
				}

				// destroy rivals way - vertically
				// there can't be chips above me
				if(evalArray[j][i] != 0){
					if(fEntrys[j][i+1] == notMe){
						if(i-1 > 0){
							evalArray[j][i] += 50;
						}else{
								evalArray[j][i] -= 5; // not enough space
						}
						if(fEntrys[j][i+2] == notMe){
							if(i-1 > 0){
								evalArray[j][i] += 50;
							}else{
								evalArray[j][i] -= 5; // not enough space
							}
							if(fEntrys[j][i+3] == notMe){
								if(i-1 > 0){
									evalArray[j][i] += 500; // high prio
								}else{
									evalArray[j][i] -= 5; // not enough space

								}
							}
						}
					}
				}

				// HORIZONTALLY ***************************************

				// my way - horizontally
				if(evalArray[j][i] != 0){
					// entrys to the right
					if(fEntrys[j+1][i] == me){
						evalArray[j][i] += 100;
						if(fEntrys[j+2][i] == me){
							evalArray[j][i] += 100;
							if(fEntrys[j+3][i] == me){
								evalArray[j][i] += 1000; // high prio
							}else if(fEntrys[j+3][i] == ' '){
								evalArray[j][i] += 75;
							}
						}else if(fEntrys[j+2][i] == ' '){
							evalArray[j][i] += 75;
						}
					}else if(fEntrys[j+1][i] == ' '){
						evalArray[j][i] += 75;	
					}
					// entrys to the left
					if(fEntrys[j-1][i] == me){
						evalArray[j][i] += 100;
						if(fEntrys[j-2][i] == me){
							evalArray[j][i] += 100;
							if(fEntrys[j-3][i] == me){
								evalArray[j][i] += 100;
							}else if(fEntrys[j-3][i] == ' '){
								evalArray[j][i] += 75;
							}
						}else if(fEntrys[j-2][i] == ' '){
							evalArray[j][i] += 75;
						}
					}else if(fEntrys[j-2][i] == ' '){
						evalArray[j][i] += 75;
					}
				}

				// destroy rivals way - horizontally
				if(evalArray[j][i] != 0){
					// entrys to the right
					if(fEntrys[j+1][i] == notMe){
						evalArray[j][i] += 100;
						if(fEntrys[j+2][i] == notMe){
							evalArray[j][i] += 100;
							if(fEntrys[j+3][i] == notMe){
								evalArray[j][i] += 5000; // high prio
							}
						}
					}
					// entrys to the left
					if(fEntrys[j-1][i] == notMe){
						evalArray[j][i] += 100;
						if(fEntrys[j-2][i] == notMe){
							evalArray[j][i] += 100;
							if(fEntrys[j-3][i] == notMe){
								evalArray[j][i] += 5000; // high prio
							}
						}
					}
				}

				// DIAGONALLY ***************************************

				// my way - diagonally, could be more precise
				if(evalArray[j][i] != 0){
					// entrys diagonally down (0/0 - w/h)
					//pos
					if(fEntrys[j+1][i+1] == me ){
						evalArray[j][i] += 100;
						if(fEntrys[j+2][i+2] == me){
							evalArray[j][i] += 100;
							if(fEntrys[j+3][i+3] == me){
								evalArray[j][i] += 1000; // high prio
							}else if(fEntrys[j+3][i+3] == ' '){
								evalArray[j][i] += 75;
							}
						}else if(fEntrys[j+2][i+2] == ' '){
							evalArray[j][i] += 75;
						}
					}else if(fEntrys[j+1][i+1] == ' '){
						evalArray[j][i] += 75;	
					}
					// neg
					if(fEntrys[j-1][i-1] == me){
						evalArray[j][i] += 100;
						if(fEntrys[j-2][i-2] == me){
							evalArray[j][i] += 100;
							if(fEntrys[j-3][i-3] == me){
								evalArray[j][i] += 1000; // high prio
							}else if(fEntrys[j-3][i-3] == ' '){
								evalArray[j][i] += 75;
							}
						}else if(fEntrys[j-2][i-2] == ' '){
							evalArray[j][i] += 75;
						}
					}else if(fEntrys[j-1][i-1] == ' '){
						evalArray[j][i] += 75;	
					}
					// entrys diagonally up (0/h - w/0)
					// w pos
					if(fEntrys[j+1][i-1] == me){
						evalArray[j][i] += 100;
						if(fEntrys[j+2][i-2] == me){
							evalArray[j][i] += 100;
							if(fEntrys[j+3][i-3] == me){
								evalArray[j][i] += 100;
							}else if(fEntrys[j+3][i-3] == ' '){
								evalArray[j][i] += 75;
							}
						}else if(fEntrys[j+2][i-2] == ' '){
							evalArray[j][i] += 75;
						}
					}else if(fEntrys[j+1][i-1] == ' '){
						evalArray[j][i] += 75;
					}
					// h pos
					if(fEntrys[j-1][i+1] == me){
						evalArray[j][i] += 100;
						if(fEntrys[j-2][i+2] == me){
							evalArray[j][i] += 100;
							if(fEntrys[j-3][i+3] == me){
								evalArray[j][i] += 100;
							}else if(fEntrys[j-3][i+3] == ' '){
								evalArray[j][i] += 75;
							}
						}else if(fEntrys[j-2][i+2] == ' '){
							evalArray[j][i] += 75;
						}
					}else if(fEntrys[j-1][i+1] == ' '){
						evalArray[j][i] += 75;
					}
				}


				// destroying evals way - diagonally
				if(evalArray[j][i] != 0){
					// entrys diagonally down (0/0 - w/h)
					//pos
					if(fEntrys[j+1][i+1] == notMe ){
						evalArray[j][i] += 75;
						if(fEntrys[j+2][i+2] == notMe){
							evalArray[j][i] += 75;
							if(fEntrys[j+3][i+3] == notMe){
								evalArray[j][i] += 750; // high prio
							}
						}
					}
					// neg
					if(fEntrys[j-1][i-1] == notMe){
						evalArray[j][i] += 75;
						if(fEntrys[j-2][i-2] == notMe){
							evalArray[j][i] += 75;
							if(fEntrys[j-3][i-3] == notMe){
								evalArray[j][i] += 750; // high prio
							}
						}
					}
					// entrys diagonally up (0/h - w/0)
					// w pos
					if(fEntrys[j+1][i-1] == notMe){
						evalArray[j][i] += 75;
						if(fEntrys[j+2][i-2] == notMe){
							evalArray[j][i] += 75;
							if(fEntrys[j+3][i-3] == notMe){
								evalArray[j][i] += 750; // high prio
							}
						}
					}
					// h pos
					if(fEntrys[j-1][i+1] == notMe){
						evalArray[j][i] += 75;
						if(fEntrys[j-2][i+2] == notMe){
							evalArray[j][i] += 75;
							if(fEntrys[j-3][i+3] == notMe){
								evalArray[j][i] += 750; // high prio
							}
						}
					}
				}

			}
		}

	#if DEBUG
		printf("evaluation printer\n");
	#endif

	// find the highest evaluation
	// if there are "two highest", first one is taken
	for(j = 0; j < fwidth; j++){
		#if DEBUG
			printf("absatz\n");
		#endif
		for(i = 0; i < fheight; i++){
			#if DEBUG
				printf("eval array: %d\n", evalArray[j][i]);
			#endif
			if(highest < evalArray[j][i]){
				highest = evalArray[j][i];
				choosenLetter = j + 65;
			}
			
		}

	}

	return choosenLetter;

}

// checks command parameters
// -a(algorithm): b(brainfuck) or c(chrisy)
// -m(mode): pvp or pvc or cvc -> p(player) c(computer) (... or chrisy hihi, cause it's my algorithm)
// -l(cause Lfile starts with an L, joking, load): FILENAME 
char checkCommandParam (int argc, char *argv[], char player[2][100], char fileName[MAX_FILENAME_LENGTH]){

	char choosen_algorithm = 'c';
	int c;

	extern char *optarg;

	while ( (c = getopt (argc, argv, "a:m:l:h")) != -1) {
		switch (c) {
 
			case 'a':
				#if DEBUG
					printf("optarg %s\n", optarg);
				#endif
				if(optarg[0] == 'b'){ // optarg[1] != '\n'
					choosen_algorithm = 'b';
				}else if(optarg[0] != 'c'){
					printf("This algorithm doesn't exist, default: Brainfuck-Algorithm\n");
				}

				break;
			case 'm':
				#if DEBUG
					printf ("Gamemode: %s.\n", optarg);
				#endif
					
					// to lower
					// mehr überprüfung

					if(strncmp("pvp", optarg, 4) == 0){
						printf("selected: Player vs Player\n");
						printf("End game with \'Z\'\n");	
						playerName(0, player[0]);
						playerName(1, player[1]);
					}else if(strncmp("cvc", optarg, 4) == 0){
						printf("selected: Computer vs Computer\n");	
						computerName(0, player[0]);
						computerName(1, player[1]);
					}else if(strncmp("pvc", optarg, 4) == 0){
						printf("selected: Player vs Computer\n");	
						playerName(0, player[0]);
						computerName(1, player[1]);
					}else{
						printf("Unknown gamemode -m, use: pvp, pvc or cvc\n");
						exit(EXIT_FAILURE);
					}
					
					break;
			case 'l':
				if(sizeof(optarg) < MAX_FILENAME_LENGTH){
					int iCharToPointer;
					for(iCharToPointer = 0; iCharToPointer < 100; iCharToPointer ++){
    					fileName[iCharToPointer] = optarg[iCharToPointer];
    				}

				}
				
				break;
			case'h':
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 13);
				printf("Usage Message\n");
				printf("Command line example: a.exe -m pvc -l loadgame.txt -a -b\n-m ... mode: pvp, pvc, cvc (p = player, vs, c = computer)\n");
				printf("-l ... load: FILENAME\n-a ... algorithm: b (brainfuck), c (computer / chrisy)\n");
				printf("quit game with 'Z', save it with 'Y' for yes and type in a filename\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 15);
				exit(EXIT_SUCCESS);
				break;
			case '?' :
					printf ("Unknown option encountered\n");
				break;
		}
	}

	#if DEBUG
		printf("Filename: %s\n", fileName);
	#endif

	return choosen_algorithm;
}

// Opens a game from the file name which the user optionally typed as command line arguments
// File is opened and entrys are saved in the Entry array
// The file has to have as much rows and columns as the fieldWidth and fieldHeight are saying!!
// between the letters, there has to be a 32(space), in the end of a line, there has tu be a \n instead
// the last line has neighter space nor \n after the last letter
void openGame(char fileName[100], int fieldWidth, int fieldHeight, char fieldEntrys[fieldWidth][fieldHeight]){

	FILE * openFile;

	int columnCounter = 0, rowCounter = 0;

	char c;
	int i = 1;

	openFile = fopen(fileName, "r");

	if(openFile == NULL){
		perror("Error Message");
		exit(EXIT_FAILURE);
	}else{
		#if DEBUG
			printf("Able to read\n");
		#endif

		// while(i < ((fieldWidth*2)*(fieldHeight*2))){
		while (!feof(openFile)) {
			c = fgetc (openFile);
			if(c == ' '){
				columnCounter ++;
				// printf("next char\n");
			}
			if(c == '\n'){
				columnCounter = 0;
				rowCounter ++;
				// printf("next line\n");
			}

			if(c == '0'){
				c = 32;
			}
			fieldEntrys[columnCounter][rowCounter] = c;
			
			i++;
		}
	}
	if (ferror(openFile)){
		perror("Error Message");
		exit(EXIT_FAILURE);
	}

	fflush(openFile);
	fclose(openFile); 
}


// prints the field, it's kind of responsive = works with more and less rows and columns
void fieldPrinter(int fieldWidth, int fieldHeight, char fieldEntrys[fieldWidth][fieldHeight]){



	int i;

	// printing letters
	for(i = 0; i < fieldWidth; i++){
		printf("  %c ", 65+i);
	}
	printf("\n");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 13);

	// printing arrows
	for(i = 0; i < fieldWidth; i++){
		printf("  %c ", 118);
	}
	printf("\n");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 15);


	// printing entrance
	printf("%c", 43);
	for(i = 0; i < fieldWidth; i++){
		printf("%c %c%c",45,45,43);
	}
	printf("\n");

	// printing playground
	int iRow;
	for(iRow = 0; iRow < fieldHeight; iRow++){
		printf("%c ", 124);
		for(i = 0; i < fieldWidth; i++){
			if(fieldEntrys[i][iRow] == '1'){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 10*16);
			}else if(fieldEntrys[i][iRow] == '2'){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 14*16);
			}
			printf("%c", fieldEntrys[i][iRow]);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , +15);
			printf(" ");
			printf("%c ", 124);
		}
		printf("\n%c", 43);
		for(i = 0; i < fieldWidth; i++){
			printf("%c%c%c%c", 45,45,45,43);
		}
		printf("\n");
	}

}

// Name of Player
void playerName(int playerindex, char player[100]){
	printf("Name of Player %d: ", playerindex+1);
	fscanf (stdin, "%s", player);
	fflush(stdin);
}

// Name of Computer
void computerName(int playerindex, char player[100]){ 
	char name [6] = "Comi";
	name [4] = (char) playerindex+49;
	name [5] = '\0';
	strncpy(player, name, 6);
}

// player is able to choose the letter, where he wants to put his chip in
char playerChooses(char player[100], int fieldWidth, int iWhoTurn){

	char choosenColumn = '0';
	printf("Your turn, ");

	if(iWhoTurn == 1){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 10);
	}else if(iWhoTurn == 2){	
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 14);
	}

	printf("%s", player);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 15);
	printf("> ");

	choosenColumn = toupper(getc(stdin));
	fflush(stdin);

	// A = 65
	if((choosenColumn >= 65 && choosenColumn < 65+fieldWidth) || choosenColumn == 90){
		return choosenColumn;
	}else{
		printf("Your choice is invalid\n");
		return 32; // space
	}
}


// computer chooses a row by an algorithm
char computerChooses(char choosen_algorithm, int fieldWidth, int fieldHeight, char fieldEntrys[fieldWidth][fieldHeight], int me){

	if(choosen_algorithm == 'b'){
		return brainfuck_algorithm(fieldWidth);
	}else if(choosen_algorithm == 'c'){
		return chrisy_algorithm(fieldWidth, fieldHeight, fieldEntrys, me);
	}else{
		printf("Something crashed, computers aren't perfect\n");
		return 32; // space
	}
}


// Function for filling the array with player 1' or player 2' choice
void fillingArray(int fieldWidth, int fieldHeight, char fieldEntrys[fieldWidth][fieldHeight], char choice, int iWhoTurn){

	int iSearch;

	for(iSearch = 0; iSearch < fieldHeight; iSearch++){
		if(fieldEntrys[choice-65][iSearch] != 32){ // 32 = space
			break;
		}		
	}

	if(fieldEntrys[choice-65][0] != 32 && choice != 32){
		printf("The choosen column \' %c \' is already full, sorry\n", choice);
	}else{
		fieldEntrys[choice-65][iSearch-1] = iWhoTurn;
	}



	int iFull;
	int leftColumns = 0;
	for(iFull = 0; iFull < fieldWidth; iFull++){
		// printf("iFull: %d\n", iFull);
		if(fieldEntrys[iFull][0] == 32){
			leftColumns ++;
			// printf("left columns: %d \n", leftColumns);
			break;
		}
	}
	if(leftColumns == 0){
		fieldPrinter(fieldWidth, fieldHeight, fieldEntrys);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 12);
		printf("You both lost the game!\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 15);
		exit(EXIT_SUCCESS);
	}

}

// this function evaluates, if there are 4 chips in a line: either diagonally, horizontally or vertically
int evaluateFour(int fieldWidth, int fieldHeight, char fieldEntrys[fieldWidth][fieldHeight], int iWhoTurn){

	int i, j, countPoints = 0;

	char me = iWhoTurn+'1';
	char notMe = '2';
	if(me == '2'){
		notMe = '1';
	}

	#if DEBUG
		printf("me: %c you %c\n", me, notMe);
	#endif

	// 4 in a row
	for(i = 0; i < fieldHeight; i++){ // reihe
		countPoints = 0;
		for(j = 0; j < fieldWidth; j++){
			if(fieldEntrys[j][i] == me){
				countPoints ++;
				if(countPoints == 4){
					return 1;
				}
			} else if(fieldEntrys[j][i] == ' ' || fieldEntrys[j][i] == notMe){
				countPoints = 0;
			}
		}
	}

	// 4 in a column
	for(j = 0; j < fieldWidth; j++){
		countPoints = 0;
		for(i = 0; i < fieldHeight; i++){
			if(fieldEntrys[j][i] == me){
				countPoints ++;
				if(countPoints == 4){
					return 1;
				}
			}else if(fieldEntrys[j][i] == ' ' || fieldEntrys[j][i] == notMe){
				countPoints = 0;
			}
		}
	}

	// 4 diagonal
	for(i = 0; i < fieldHeight; i++){
		for(j = 0; j < fieldWidth; j++){

			if((i+3) < fieldHeight && (j+3) < fieldWidth){
				if(fieldEntrys[j][i] == me && fieldEntrys[j+1][i+1] == me){
					if(fieldEntrys[j+2][i+2] == me && fieldEntrys[j+3][i+3] == me){
						return 1;
					}
				}
			}

			if((i-3) > 0 && (j+3) < fieldWidth){
				if(fieldEntrys[j][i] == me && fieldEntrys[j+1][i-1] == me){
					if(fieldEntrys[j+2][i-2] == me && fieldEntrys[j+3][i-3] == me){
						return 1;
					}
				}
			}
		}
	}

	return 0;
}


// if Z and Y are given to the console, the player is able to save the game with a name, he chooses
void saveGame(int fieldWidth, int fieldHeight, char fieldEntrys[fieldWidth][fieldHeight]){

	char savingFileName[MAX_FILENAME_LENGTH];

	printf("filename > ");
		int tmpY = 0;

		// EOF !!!
		// Filename
		while(1){

			// read character until /n
			savingFileName[tmpY] = getc(stdin);

			if (savingFileName[tmpY] == '\n'){
				savingFileName[tmpY] = '\0';
				break;
			}
			if (tmpY > 100){
				savingFileName[tmpY] = '\0';
				break;
			}		
			tmpY++;
		}
		
		fflush(stdin);


		// wirte to file
		FILE *pFile;
		char c;
		int rowCounter = 0;
		int columnCounter = 0;

		pFile = fopen (savingFileName, "w");

		if (pFile!=NULL){
			#if DEBUG
				printf("Able to write\n");
			#endif

			while(rowCounter < fieldHeight){

				while(columnCounter < 6){

					if(fieldEntrys[columnCounter][rowCounter] == 32){
						fieldEntrys[columnCounter][rowCounter] = '0';
					}

					c = fieldEntrys[columnCounter][rowCounter];
					// printf(" %c ", c);
					fputc (c, pFile);
					if(columnCounter < 5){
						fputc (32, pFile);
					}
					columnCounter ++;
				}

				if(rowCounter < fieldHeight-1){
					fputc ('\n', pFile);
				}
				rowCounter ++;
				columnCounter = 0;


				if (ferror(pFile)){
	      			perror ("Error Message");
	      			clearerr (pFile);
	      			break;
				}
			}
			fflush(pFile);
		    fclose (pFile);
		}
}

int main(int argc, char *argv[]){

	srand(time(NULL));

	char player[2][100];
	player[0][0] = '\0';
	player[1][0] = '\0';

	// able to change these values
	int fieldWidth = 6; // Columns
	int fieldHeight = 7; // Rows

	// but width should be between 4 and 19
	if(fieldWidth > 19){ 
		fieldWidth = 19;
	}else if(fieldWidth < 4){
		fieldWidth = 4;
	}
	// and height should be between 4 and 20
	if(fieldHeight > 20){
		fieldHeight = 20;
	}else if(fieldWidth < 4){
		fieldWidth = 4;
	}

	char fileName[MAX_FILENAME_LENGTH];
	char fieldEntrys [fieldWidth][fieldHeight];

	int iColumn, iRow, iWhoTurn = 0;
	char choice, save = 'N';
	char choosen_algorithm = 'c'; // in case of computer is playing, otherwise ignored


	// CODE

	// Filename
	choosen_algorithm = checkCommandParam(argc, argv, player, fileName);
	if(strlen(fileName) > 0){
		// saved game
		printf("Loading saved game ...\n");
		openGame(fileName, fieldWidth, fieldHeight, fieldEntrys);
	}else{
		// new game
		printf("New game is generated\n");
		for(iColumn = 0; iColumn < fieldWidth; iColumn++){
			for(iRow = 0; iRow < fieldHeight; iRow++){
				fieldEntrys [iColumn][iRow] = 32; // 32
			}
		}
	}
	
	// routine player vs player

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 13);
	printf("It's time to play \"4 in a row!\"\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 15);

	if(strlen(player[0]) < 1){
		strncpy(player[0], "Player 1", 9);
	}
	if(strlen(player[1]) < 1){
		strncpy(player[1], "Player 2", 9);
	}

	while(1){

		// prints the field
		fieldPrinter(fieldWidth, fieldHeight, fieldEntrys);

		if((strncmp(player[iWhoTurn], "Comi", 4)) == 0){
			choice = computerChooses(choosen_algorithm, fieldWidth, fieldHeight, fieldEntrys, iWhoTurn + 1);
			printf("%s' turn> %c\n", player[iWhoTurn], choice);
		}else{
			// choosen letter
			choice = playerChooses(player[iWhoTurn], fieldWidth, iWhoTurn+1); // 0 = player 1, 1 = player 2	
			// end the game
			if(choice == 'Z'){
				break;
			}
		}		
	
		// the array gets the entry		
		fillingArray(fieldWidth, fieldHeight, fieldEntrys, choice, iWhoTurn+49);

		// if game is won 
		if(evaluateFour(fieldWidth, fieldHeight, fieldEntrys, iWhoTurn) == 1){
			fieldPrinter(fieldWidth, fieldHeight, fieldEntrys);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 11);
			printf("Player %d: %s has won!\n", iWhoTurn+1, player[iWhoTurn]);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , 15);
			exit(EXIT_SUCCESS);
		}

		// player whose turn is, changes
		if(iWhoTurn == 1){
			iWhoTurn = 0;
		}else{
			iWhoTurn = 1;
		}

	}
	
	// save the game
	printf("do you want to save the game? Y> ");
	save = toupper(getc(stdin));	
	fflush(stdin);

	if(save == 'Y'){
		saveGame(fieldWidth, fieldHeight, fieldEntrys);
	}

	printf("Good bye!\n");
	exit(EXIT_SUCCESS);
	
	return 0;
}
