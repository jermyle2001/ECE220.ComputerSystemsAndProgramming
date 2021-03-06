#include "game.h"
/*
----------------------------------------INTRO PARAGRAPH----------------------------------------

The make_game function creates a game and returns a pointer to that game. We set the score to zero and set the row and col based of the arguements in the
function. Finally, we iterate through a for loop to intialize each cell to -1 or open space.

The remake_game function sets new values to the row and col based on the arguements and also sets the score to zero. We also set each cell to -1 of the new game
with a for loop.

The get_cell function first checks to see through an if statement checking to see whether the row and columns called are within the game's boundaries.
If so, the function returns a pointer using the cells pointer plus the 1D equivalent of the pointer arithmetic (rows * #of columns + column#)

The approach used for the move functions consisted of two passes along the board. The first pass merged any tiles that would be merged upon executing
the move function. It iterates in the opposite direction of the movement (i.e. for move_w, visually it iterates down the board), first finding any 
non-empty tiles, then finding another non-empty tile, checking to see if they're compatible (if they are, the function will delete the value in the second
location and multiply the value in the first location by 2 to get its next number) and breaking regardless of whether or not they are. The second pass
moved any tiles that would be moved upon calling the function, first finding an empty tile to move to, and then looking for a non-empty tile to move, iterating
through the board until one is found. Upon finding a non-empty tile, the value of the locations are swapped and the board moves onto the next available empty space.

The legal_move_check functions creates a copy of the game in a different part of the heap. We do this because we want to execute all the move functions 
and check if its a legal move based on the integer it returns. However, we do not want to change the status of the actual game board, and that is why we create a 
copy of the game instead. Also, in order to avoid overflow on the heap, we free the copy of the game after the move functions return a value.

Partners: tmshu2, jeremyl6, bgin2
*/

game * make_game(int rows, int cols){
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/

    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));
	//Above statement equivalent to (*mygame).cells = pointer which points to memory allocated
	//Thus, mygame.cells now points to first location of board (1D array)
	//"cells" is a pointer, points to beginning of board cell data
	//"mygame" now points to 

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct

    /* Personal notes
	-Game struct already defined in game.h as
		int rows - # of rows
		int cols - # of cols
		cell * cells - pointer to the beginning of board cell data, 1D array organized in row-major layout
		int score - score of current game
	-Pointer "mygame" points to memory allocated
	-To set score: mygame->score = (insert score here)
	-To access cell: mygame->cell[array# or whatever]= (insert desired value)

	TO DO FOR make_game
	-Assign correct initial values to rows, cols, and score
	-Assign -1 to each cell in array
    */
//-----------Set intial values of rows, cols, and score-----------
mygame->rows = rows;//sets initial rows 
mygame->cols = cols;//sets initial cols
mygame->score = 0; //sets initial score to zero

//-----------Assign -1 to all cells-----------
for(int i = 0; i<(rows*cols); i++){ //iterate through
    
    mygame->cells[i] = -1;


}
    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell)); //sets value dereferenced by "_cur_game_ptr" to pointer "cells", which points to 

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
    //-----------Set intial values of rows, cols, and score-----------
    (*_cur_game_ptr)->rows = new_rows;//sets initial rows 
    (*_cur_game_ptr)->cols = new_cols;//sets initial cols
    (*_cur_game_ptr)->score = 0; //sets initial score to zero

    //-----------Assign -1 to all cells-----------
    for(int i = 0; i<(new_rows*new_cols); i++){ //iterate through
    
    (*_cur_game_ptr)->cells[i] = -1;


    }



	return;	
}

//-----------------------DON'T TOUCH THIS NEXT FUNCTION----------------------------------------------------------------------------------

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
    if(row >= 0 && col >= 0 && row < (cur_game->rows) && col < (cur_game->cols)) //Checks if the row and col is in bounds. Row and col are current row and col. 
    return ((cur_game->cells) + row * cur_game->cols + col); //return pointer set at cell coordinates. Row-major format, so it's rows*#of columns (given by row * cur_game->cols) + col
    else //Cell coordinates exceed bounds (row/col # is invalid) - return NULL
    return NULL;
}

//You now possess a pointer that points to a certain cell in the game


//-----------------------DON'T TOUCH THE FUNCTION ABOVE-------------------------------------------------------------------------------


int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
/*  
Approach can be loosely modeled as two parts:
1. Merge available cells
-Merges any cells that can be merged in the direction of movement. Operates starting from opposite end of movement,
moving opposite of movement
2. Slide remaining tiles
-Slides any tiles in the direction of movement

Using get_cell, we get the pointer get_cell which points to the cell's location.
We can set the appropriate return value by using a flag which determine whether or not any actual moves were made.
*/


int flag = 0; //Increment this anytime an action occurs to indicate that the move was valid
int i,j,k;
int tempval1, templocation1; //These vars are used in storing temporary locations/values for merging or moving tiles
//1. Merge available cells
for(k = 0; k < cur_game->cols; k++){ //Iterate across column
 for(i = 0; i < cur_game->rows; i++){//Iterate down rows
  if(cur_game->cells[i * cur_game->cols + k] != -1){ //If current cell value is NOT -1 - MAY NEED DEREFERENCE!!!! (Check later)
   templocation1 = i * cur_game->cols + k;
   tempval1 = cur_game->cells[i * cur_game->cols + k];
   for(j = i + 1; j < cur_game->rows; j++){ //Iterate for rows-i times, looking for compatible tiles 
    if(cur_game->cells[j * cur_game->cols + k] != -1){ //If new location's value is also not -1 - MAY NEED DEREFERENCE
     if(tempval1 == cur_game->cells[j * cur_game->cols + k]){ //If the two values are the same, merge and remove second location
      cur_game->cells[templocation1] = tempval1*2; //Multiply original value by 2, store into original location
      cur_game->score = cur_game->score + tempval1*2;
      cur_game->cells[j * cur_game->cols + k] = -1; //Remove value in second location
      flag++;
      break; //break loop, tiles have been merged
}
     else{
      break;
}
}
}
}
}
}
//At this point, all cells that could have been merged have been merged.

//2. Slide remaining tiles
//Accomplished by finding an empty tile, and then iterating through until non-empty tile found
//Then storing the value within the non-empty tile in the empty tile and erasing the value
//In the non-empty tile

for(k = 0; k < cur_game->cols; k++){ //Iterate across columns
 for(i = 0; i < cur_game->rows; i++){ //Iterate down rows
  if(cur_game->cells[i * cur_game->cols + k] == -1){
   templocation1 = i * cur_game->cols + k;
   for(j = (i + 1); j < (cur_game->rows); j++){ //Iterate starting from row i, rows-i tkimes, looking for non-empty tiles
    if(cur_game->cells[j * cur_game->cols + k] != -1){ //If non-empty tile, then move second value into first location and empty second location
     cur_game->cells[templocation1] = cur_game->cells[j * cur_game->cols + k]; //Moves value from second location to first location
     cur_game->cells[j * cur_game->cols + k] = -1; //Empties value in second location
     flag++;
     break;
}
}
}
}
}
if(flag == 0)
return 0;
else
return 1;

/*
REFERENCE FOR TESTING PURPOSES
Original Board:
[ 2  4  4 ]
[ 8  4  - ]
[ -  4  - ]
[ 2  4  8 ]

*/

};


int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE - SIMILAR APPROACH TO MOVE_W

int i,j,k,tempval1,templocation1;
int flag = 0;
for(k = 0; k < cur_game->cols; k++){ //Iterate through columns backwards, subtract 1 to replicate array boundaries/syntax 
					  //(ex. # of columns is 4, array columns only goes 0 to 3)
 for(i = cur_game->rows - 1; i > -1; i--){//Iterate through rows backwards, subtract 1 to replicate array boundaries/syntax
  if(cur_game->cells[i*cur_game->cols + k] != -1){ //If current cell is NOT -1 - loop will iterate until it finds non-empty cell
   templocation1 = i*cur_game->cols + k; //Set templocation
   tempval1 = cur_game->cells[i*cur_game->cols + k]; //Set tempval
   for(j = i - 1; j > -1; j--){ //Look at row above
    if(cur_game->cells[j*cur_game->cols + k] != -1){ //Upon finding a non-empty tile, evaluate if they are the same
     if(cur_game->cells[j*cur_game->cols + k] == tempval1){
     cur_game->cells[templocation1] = tempval1*2;
     cur_game->score = cur_game->score + tempval1*2;
     cur_game->cells[j*cur_game->cols + k] = -1;
     flag++;
     break;
    }
    else{
     break;
    }
}}}}}

//All tiles merged. Proceed to slide merged tiles.

for(k = cur_game->cols - 1; k > -1; k--){ //Iterate through columns backwards
 for(i = cur_game->rows - 1; i > -1; i--){ //Iterate through rows backwards
  if(cur_game->cells[i*cur_game->cols + k] == -1){ //Loop until empty tile found
   templocation1 = i*cur_game->cols + k;
   for(j = i - 1; j > -1; j--){ //Loop until nonempty tile found
    if(cur_game->cells[j*cur_game->cols + k] != -1){ 
     cur_game->cells[templocation1] = cur_game->cells[j*cur_game->cols + k];
     cur_game->cells[j*cur_game->cols + k] = -1;
     flag++;
     break;
}}}}}

//Finished moving tiles. Check if any actions were performed and return appropriate value

if(flag == 0)
return 0;
else
return 1;
};

int move_a(game * cur_game) //slide left
{

    //YOUR CODE STARTS HERE - SIMILAR APPROACH TO MOVE_W, but iterate from left to right since we're sliding left
int i,j,k,tempval1,templocation1;
int flag = 0;
for(i = 0; i < cur_game->rows; i++){ //Iterate through rows
 for(k = 0; k < cur_game->cols; k++){ //Iterate through columns
  if(cur_game->cells[i*cur_game->cols + k] != -1){ //Iterate through board until non-empty tile found
   templocation1 = i*cur_game->cols + k;
   tempval1 = cur_game->cells[i*cur_game->cols + k];
   for(j = k + 1; j < cur_game->cols; j++){ //Iterate through rest of columns until another non-empty tile found
    if(cur_game->cells[i*cur_game->cols + j] != -1){
     if(tempval1 == cur_game->cells[i*cur_game->cols + j]){
      cur_game->cells[templocation1] = tempval1*2;
      cur_game->score = cur_game->score + tempval1*2;
      cur_game->cells[i*cur_game->cols + j] = -1;
      flag++;
      break;
     }
     else{
      break;}
}}}}}


//Now we slide tiles to desire locations
for(i = 0; i < cur_game->rows; i++){ //Iterate through rows
 for(k = 0; k < cur_game->cols; k++){ //Iterate through columns
  if(cur_game->cells[i*cur_game->cols + k] == -1){ //Iterate until empty tile found
   templocation1 = i * cur_game->cols + k;
   for(j = k + 1; j < cur_game->cols; j++){ //Iterate through columns and find nonempty tile
    if(cur_game->cells[i*cur_game->cols + j] != -1){
     cur_game->cells[templocation1] = cur_game->cells[i*cur_game->cols + j];
     cur_game->cells[i*cur_game->cols + j] = -1;
     flag++;
     break;
}}}}}

//All tiles moved. Check if any actions were performed and return.

if(flag == 0)
return 0;
else
return 1;

};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE - SIMILAR APPROACH TO MOVE_W
int i,j,k,tempval1,templocation1;
int flag = 0;
for(i = 0; i < cur_game->rows; i++){ //Iterate through rows (down)
 for(k = cur_game->cols - 1; k > -1; k--){ //Iterate through columns backwards (left)
  if(cur_game->cells[i*cur_game->cols+k] != -1){ //Iterate left until a nonempty tile found
   templocation1 = i*cur_game->cols+k;
   tempval1 = cur_game->cells[i*cur_game->cols + k];
   for(j = k - 1; j > -1; j--){
    if(cur_game->cells[i*cur_game->cols + j] != -1){
     if(tempval1  == cur_game->cells[i*cur_game->cols + j]){
      cur_game->cells[templocation1] = tempval1*2;
      cur_game->cells[i*cur_game->cols + j] = -1;
      cur_game->score = cur_game->score + tempval1*2;
      flag++;
      break;
     }
     else{
      break;}
}}}}}

//All tiles merged. Move remaining tiles

for(i = 0; i < cur_game->rows; i++){ //Iterate through rows (down)
 for(k = cur_game->cols - 1; k > -1; k--){ //Iterate through columns backwards (left)
  if(cur_game->cells[i*cur_game->cols + k] == -1){ //Iterate left until empty file found
   templocation1 = i*cur_game->cols + k;
   for(j = k - 1; j > -1; j--){ //Iterate through columns backwards (left)
    if(cur_game->cells[i*cur_game->cols + j] != -1){ //Iterate until nonempty tile found
     cur_game->cells[templocation1] = cur_game->cells[i*cur_game->cols + j]; //Move tile to empty spot
     cur_game->cells[i*cur_game->cols + j] = -1; //Erase second tile
     flag++;
     break;
}}}}}

//All tiles moved. Check if any actions were performed.
if(flag == 0)
return 0;
else
return 1;




};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
/*
PERSONAL NOTES:
Approach can be summarized as creating a temp board and checking by running through all four moves
Board may need to be recreated every time a move is performed
*/
int i, j;
game* copy = make_game( cur_game->rows, cur_game->cols); //creates a copy of the game
for(i = 0; i < cur_game->rows; i++){ //Copy board into another array
    for(j = 0; j < cur_game->cols; j++){
        copy->cells[i * cur_game->cols + j] = cur_game->cells[i * cur_game->cols + j];
    }
}
if(move_w(copy) || move_a(copy)|| move_s(copy)||move_d(copy) ){
    free(copy);
    return 1;
}
else{
    free(copy);
    return 0;
}

} //End of function


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
