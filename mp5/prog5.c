/*      
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */

/*
There were three functions completed within this program. 
The first one, set_seed, calls srand and sets the seed for the game.
The second one, start_game, stores the randomized solutions from the pool into an array, setting up the solutions to the game. This was accomplished using the algorithm provided, 
which consisted of 1. Calling rand and using the modulus operator to reduce it to acceptable
ranges, and 2. using the random value to index and copy the string from "pool" to "solutions". After the solutions were copied, the variables were set as specified.
The third function performs the operations needed to evaluate the player's guesses. This was
done by using a series of if statmeents between the solution strings, checking for perfect
or misplaced matches, first checking for perfect matches and secondly checking for misplaced
matches. Upon finding a match, the appropriate counter is incremented and the solution and
guess are marked via a matchchecking array, whose values are set and changed with every call
to the function. 

Partners: tmshu2, jeremyl6, bgin2

 */
#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"

int guess_number;
int *guess_ptr = &guess_number;
int max_score;
int *max_ptr = &max_score;
char w[10];
char x[10];
char y[10];
char z[10];
char solutions[4][10];
char* pool[] = {"Vader", "Padme", "R2-D2", "C-3PO", "Jabba", "Dooku", "Lando", "Snoke",};

void print_pool() {
    printf("Valid term to guess:\n\t");
    for(int i = 0; i < 8 ; ++i) {
        printf("%s ", pool[i]);
    }
    printf("\n");
}

int is_valid(char* str) {
    int i = 0;
    if (str == NULL) {
        return 0;
    }
    for (i = 0; i < 8; i++) {
        if (strcmp(str, pool[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int set_seed (const char seed_str[]) {
    int seed;
    char post[2]; 
    if (sscanf (seed_str, "%d%1s", &seed, post) != 1) {
      // anything other than single integer entered, so return 0
	printf("set_seed:invalid seed\n");	
	return 0;
    }

    else
    {
      // single integer entered, call srand and return 1
	srand(seed);
	return 1;
}
}

void start_game () { //this function throws the randomized index from the pool into the solutions array as strings, accomplished through re-identifiying the solutions array as a pointer array to match the pool array's format.
int k = 0;
int temp;
temp = (int)rand()%8; //random number call, divide by 8 to keep within range (0 to 7)
strcpy(w,pool[temp]);
temp = (int)rand()%8; //random number call, divide by 8 to keep within range (0 to 7)
strcpy(x,pool[temp]);
temp = (int)rand()%8; //random number call, divide by 8 to keep within range (0 to 7)
strcpy(y,pool[temp]);
temp = (int)rand()%8; //random number call, divide by 8 to keep within range (0 to 7)
strcpy(z,pool[temp]);
for(k=0;k<10;k++){ //throws characters in w,x,y,z into solutions array
    solutions[0][k] = w[k];
    solutions[1][k] = x[k];
    solutions[2][k] = y[k];
    solutions[3][k] = z[k];
}
*max_ptr = -1;
*guess_ptr = 1;
}

int make_guess (const char guess_str[]) {
char b[20], c[20], d[20], a[20], e[20];
int i,k,j;
sscanf(guess_str,"%s %s %s %s ", a, b, c, d);
if(sscanf(guess_str,"%s %s %s %s %s", a, b, c, d, e) !=4){
	printf("make_guess: invalid guess\n");        
	return 0;
}

char *ptr[4] = {a,b,c,d}; //we create another array to reference each individual string
for(i=0;i<4;i++){ //check for validity, iterate through all four strings
    if(is_valid(ptr[i])==0){
	printf("make_guess: invalid guess\n");        
	return 0;
    }
}


for(k=0;k<10;k++){ //copy the individual strings in w,x,y,z into the appropriate place in the solutions array.
w[k] = solutions[0][k];
x[k] = solutions[1][k];
y[k] = solutions[2][k];
z[k] = solutions[3][k];
}

int matchchecker[4] = {1,1,1,1}; //this array is used to keep track of what strings have already been marked as "matched".

   //first step, check for perfect matches
   int perfect = 0, misplaced = 0;
   for(k=0;k<4;k++){
       if(strcmp(solutions[k], ptr[k]) == 0){
if (matchchecker[k] == 1){
           perfect++;
         matchchecker[k] = 0;
		}
       }
    //next, check for misplaced matches. 
   }
   for(k=0;k<4;k++){ //this loop iterates through "ptr"
        for(j=0;j<4;j++){ //this loop compares "ptr" and iterates through "solutions"
            if(strcmp(solutions[j], ptr[k]) == 0){
		if(matchchecker[j] == 1){
                misplaced++;
                matchchecker[j] = 0;}
		continue; //upon finding a misplace, move on to the next word via break
            }
        }
    }
    int currentscore = 1000*perfect + 100*misplaced;
    if(currentscore > *max_ptr){
        *max_ptr = currentscore;
    }
    printf("With guess %d, you got %d perfect matches and %d misplaced matches.\nYour score is %d and current max score is %d.\n", guess_number, perfect, misplaced, currentscore, max_score);
    guess_number++;
    if(*max_ptr == 4000){
	guess_number--;
	printf("You guessed correctly in %d guesses.", guess_number);       
	return 2;
    }
    else
    {
        return 1;
    }
}


