/*-----------------------------------------------------------------*/
/* Author: Christina Bornberg BEL 1                                */
/*                                                                 */
/* Created: 2016-10-31                                             */
/* Finished: 2016-11-22											   */
/*                                                                 */
/* About: A userfriendly calculator should be developed, 		   */
/*	input by commandline basic math-operators					   */
/*	Simple Task								 					   */
/*																   */
/*																   */
/* How to use: (GERMAN)											   */
/* Befehle können über die Kommandozeile eingelesen werden		   */
/* Einerseits über Argumente (optional)							   */
/* Bsp: a.exe 23 ** 2											   */
/* Andererseits nach '>'										   */
/* Bsp: > 232 / 1												   */
/* Mittels 'Q' kann das Programm beendet werden					   */
/*-----------------------------------------------------------------*/

// INCLUDES *****************************
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


// PROTOTYPES *****************************
void init(void);
void initScanner(int argc, char *argv[]);
void goodbyData();
void routineScanner(void);
void checkerOperator();
double checkerNumber(char check[]);
void problemPrinter(int an_error);

// Math Functions
double addition();
double subtraction();
double multiplication();
double division();
double powerOf();
double rootOf();
double percentOf();


// DEFINES *****************************
#define NO_PROBLEM 0 // no problem
#define A_PROBLEM 1 // Problem was detected
#define PROBLEM_DIV 2 // (done) dividing 0 = Check if operands suit operation: 2 / 0 
#define PROBLEM_ROOT 3 // (done) minus number at root of = Check if operands suit operation: 2 _/ -10 
#define PROBLEM_NUM 4 // (done) not a real number or ans = Check if both numbers are actually numbers (with or without comma/exponent) or the string "Ans"
#define PROBLEM_OP 5 // operator not found = Check if the entered operator is supported
#define PROBLEM_NOTFOUND 6 // Missing number or operator = Check if both numbers and the operator are present
#define PROBLEM_MUCH 7 // Too many numbers / to long
#define PROBLEM_RES 8 // Result has a too high number
// #define PROBLEM_UNKNOWN 10 // An unnknown Error appeared

#define ARRAYSIZE 33 // size of array double (15 decimal places) + char[] (3 bit) + double (15 decimal places) = 33 


// GLOBAL VARIABLES *****************************
double one;
char operationType[3];
double two;
double storeAsOld;
int problem;
int percent;
int calc_completed;


// DECLARATIONS *****************************
void init(void){
	one = 0;
	operationType[0] = '+';
	operationType[1] = '\0';
	two = 0;
	storeAsOld = 0;
	problem = NO_PROBLEM;
	percent = 0;
	calc_completed == 0;
}


// CODING *****************************

/* Resets the Data */
void goodbyData(){
	one = 0;
	operationType[0] = '+';
	operationType[1] = '\0';
	two = 0;
	problem = NO_PROBLEM;
	percent = 0;
}

/* first routine of scanner -> commandline: a.exe number operator number*/
/* just to learn how to use arguments, arguments not needed */
/* Maxlenghth of inputted numbers is not given / checked */
void initScanner(int argc, char *argv[]){

	// checks, if one and two are numbers or "ans"
	one = checkerNumber(argv[1]);
	two = checkerNumber(argv[3]);
	
	// Saving operation Type
	operationType[0] = argv[2][0]; // Operation
	operationType[1] = argv[2][1]; // if necessary 2nd Operationsign
}

/* Scanner with getchar */
/* routine, after the init scanner*/
void routineScanner(void){

	char text[ARRAYSIZE];
	char * pText;

	int i = 0, durchlauf = 0;

	printf(">");
	text[i] = getc(stdin); // first letter

	while(1){

		i++;
		// read character until /n
		text[i] = getc(stdin);

		if (text[i] == '\n'){
			break;
		}
		if (i >= ARRAYSIZE){
			// if want to break the whole calculation use:
			problemPrinter(PROBLEM_MUCH);
			// in this case: takes 40 letters and calculates with these
			break;
		}		
	}
	
	// last arrayindex should be '\0'
	text[i] = '\0';
	fflush(stdin);

	// Split at " " and saves numbers and operator seperat
	pText = strtok(text, " ");
	while (pText != NULL){
	    if(durchlauf == 0){
	    	one = checkerNumber(pText);
	    //	if(strlen(pText) > 15){
	    //		printf("NOTE: Value is 	imprecise\n");
	    //	}
			pText = strtok (NULL, " ");
		}else if(durchlauf == 1){
			strncpy(operationType, pText, 3);
			pText = strtok (NULL, " ");
		}else if(durchlauf == 2){
			two = checkerNumber(pText);
		//	if(strlen(pText) > 15){
	    //		printf("NOTE: Value is 	imprecise\n");
	    //	}
			pText = strtok (NULL, " ");
		}else{
			break;
		}
		durchlauf ++;
	  }
}

/* Checks if first Argument is "Ans" or a number */
/* call in scanner functions*/
/* Problem Handling: Number*/
double checkerNumber(char check[]){

	if(isalpha(*check)){
		// if letter

		char *str1;
		char *str2;
		int j;

		str1 = check;
		str2 = "ANS";

		for (j=0; j<= sizeof(check); j++){
    		check[j] = toupper(check[j]);
		}
		if(strcmp(str1, str2) == 0){
			// if ANS
			return storeAsOld;
		}else if(str1[0] == 'Q'){
			// if Quit
			printf("Good Bye\n");
			exit(0);
		}else{
			// if invalid
			problemPrinter(PROBLEM_NUM);
		}
	}else if(isdigit(*check) || check[0] == '-' && isdigit(check[1])){
		// if number
		return strtod(check, NULL);
	}else{
		// if invalid
		problemPrinter(PROBLEM_NUM);
	}
}

/* Operation Type is choosed 
Problem Handling: Operation Type
*/
void checkerOperator(){

		switch (operationType[0]){ 
			case '+': 	if(operationType[1] == '\0'){
							addition();
						}else{
							problemPrinter(PROBLEM_OP);
						}break;
			case '-': 	if(operationType[1] == '\0'){
							subtraction();
						}else{
							problemPrinter(PROBLEM_OP);
						}break;
			case '*': 	if(operationType[1] == '*'){
							powerOf();
						}else if(operationType[1] == '\0'){
							multiplication();
						}else{
							problemPrinter(PROBLEM_OP);
						};break;
			case 'x': 	if(operationType[1] == 'x'){
							powerOf();
						}else if(operationType[1] == '\0'){
							multiplication();
						}else{
							problemPrinter(PROBLEM_OP);
						};break;
			case '/': 	if(operationType[1] == '\0'){
							division();
						}else{
							problemPrinter(PROBLEM_OP);
						}break;
			case '_': 	if(operationType[1] == '/'){
							rootOf();
						}else{
							problemPrinter(PROBLEM_OP);
						};break;
			case '%': 	if(operationType[1] == '\0'){
							percentOf();
						}else{
							problemPrinter(PROBLEM_OP);
						}break;
			default: problemPrinter(PROBLEM_OP);break;
		}
}

/* Problem - Handling */
void problemPrinter(int an_error){
	if(an_error == PROBLEM_DIV){ // 2
		printf("Error: Division by zero (Operand 2 can't be Zero!)\n");
	}else if(an_error == PROBLEM_ROOT){ // 3
		printf("Error: -th Root of: a minus Number in the root is prohibited\n");
	}else if(an_error == PROBLEM_NUM){ // 4
		printf("Error: Something went wrong with the scanned Number(s) or \"Ans\"\n"); 
	}else if(an_error == PROBLEM_OP){ //5
		printf("Error: Something went wrong with the operator\n");
	}else if(an_error == PROBLEM_NOTFOUND){ // 6
		printf("Error: Something is missing! (Numbers or Operator)\n");
	}else if(an_error == PROBLEM_MUCH){ // 7
		printf("Error: There is an invalid size of Numbers!\n");
	}else if(an_error == PROBLEM_RES){
		printf("ERROR: The result is too high, ANS set to 0\n");
		storeAsOld = 0;
	}else{ // any other problems
		printf("Undefined Problem\n");
	}
	problem = A_PROBLEM;
	printf("(in case of an Error) Ans = %lf\n", storeAsOld);
	
}

/* Math begin */
double addition(){
	calc_completed = 1;
	storeAsOld = one+two;
	return storeAsOld;
}

double subtraction(){
	calc_completed = 1;
	storeAsOld = one-two;
	return storeAsOld;
}

double multiplication(){
	calc_completed = 1;
	storeAsOld = one*two;
	return storeAsOld;
}

double division(){
	if(two == 0){
		problemPrinter(PROBLEM_DIV);
	}else{
		calc_completed = 1;
		storeAsOld = one/two;
	}
	return storeAsOld;
}

double powerOf(){
	/*	From Math.h:
		double pow(double x, double y);
   		float powf(float x, float y);
   		long double powl(long double x, long double y);
	*/
   	calc_completed = 1;
	storeAsOld = pow(one,two);
	return storeAsOld;
}

double rootOf(){
	// no function for n-th root of another number -> pow(double, double); example: 4th root of 81 : pow(81.0, 1.0/4.0) 
	if(two <= 0){
		problemPrinter(PROBLEM_ROOT);
	}else{
		calc_completed = 1;
		storeAsOld = pow(two, 1.0/one);
	}
	return storeAsOld;
}

/* The outcome percent is the betray*/
double percentOf(){
	if(one >= 0 && two < 0 || one < 0 && two > 0){    
		one = one*(-1);
	}
	storeAsOld = (one/two)*100;
	// storeAsOld = (one[0]*two[0])/100;
	percent = 1;
	return storeAsOld;
}
/* Math end */

/* Main method with routines	*/
int main(int argc, char *argv[]){
	/* INITALISING */
	init();
	if(argc == 4){ // if there are 4 arguments
		initScanner(argc, argv);	
		checkerOperator();
	}else if(argc == 2 || argc == 3 || argc >= 5){
			problemPrinter(PROBLEM_MUCH);
	}
	/* ROUTINE */
	while(1){
		if(problem == NO_PROBLEM){
			if(calc_completed){
				printf("%lf | %c %c | %lf\n", one, operationType[0], operationType[1], two);
			
				if(storeAsOld > 999999999999999){
					if(storeAsOld > 1.7E+308){
						problemPrinter(PROBLEM_RES);
					}else{
		    			printf("NOTE: Result is imprecise\n");
		    		}
		    	}
		    }

			if(percent){
				printf("Ans = %.3lf%%\n", storeAsOld);
			}else{
				printf("Ans = %.3lf\n", storeAsOld);
			}	
		}

		printf("\n\n"); // For usability reasons
		goodbyData();
		routineScanner();
		checkerOperator();

	}
	return 0;
}