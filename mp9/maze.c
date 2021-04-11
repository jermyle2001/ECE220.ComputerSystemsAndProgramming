#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/*
The program accomplishes the MP's goals by utilising File I/O and recursive backtracking.
The function createMaze takes advantage of the file stream and scans the content into the desired structure. 
The structure, containing a double pointer, allocates spaces for each character in the file in order to replicate
the maze as demonstrated. After creating pointers within the double pointer, the contents are stored at the 
designated positions via a for loop based off of the maze's dimensions and a series of if statements, and
the file is closed, returning the struct's pointer.

The function destroyMaze takes each pointer and destroys the associated memory in order to clear it up for 
any future usage. It utilises a for loop which closes each of the pointers' locations, and free the locations
of memory accordingly. 

The function printMaze utilises the pointers created in order to print the desired maze. By using pointer 
arithmetic and the struct provided, the function loops print statements and prints out the maze.

The function solveMazeDFS utilises the algorithm provided in the wiki. It is provided below for reference:
If (col, row) outside bounds of the maze return false
if (col, row) is not an empty cell return false
if (col, row) is the end of the maze return true
set (col, row) as part of the solution path in the maze
if (solveMaze(left of (col, row) ) == true) return true
if (solveMaze(right of (col, row) ) == true) return true
if (solveMaze(up of (col, row) ) == true) return true
if (solveMaze(down of (col, row) ) == true) return true
unmark (col, row) as part of solution and mark as visited
return false
This algorithm essentially tests several base cases first to see if the maze is testing out of bounds, a non-empty cell (already visit, start, or wall), or if
the end has been found. Afterwards, it tests all available directions, and going through the only valid direction. If no directions are valid,
it backtracks.
*/

/* Structure included here for reference
typedef struct {
    int width;
    int height;
    int startColumn;
    int startRow;
    int endColumn;
    int endRow;
    char ** cells;
} maze_t;
    */

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file ----- RETURN A POINTER TO THE STRUCTURE
 * SIDE EFFECTS: None
 */
 
 //Should allocate memory for maze_t structure and memory for cells
 //Parse given file and fill in all parameters of the maze structure, including cells parameter
maze_t * createMaze(char * fileName)
{
    int i, j; //Initializes variables for for loops to allocate memory and store characters for the text file
    char character; //Initializes character to store the char in cells
    FILE* fpointer = fopen(fileName, "r"); //Opens the text file. Reads cause we dont want to change it
    maze_t* maze = (maze_t*)malloc(sizeof(maze_t)); //Allocate memory for maze struct
    fscanf(fpointer, "%d %d", &(maze->width), &(maze->height)); //Scan file for maze dimensions, pop off stream and load into maze.width and maze.height
    maze->cells = (char**)malloc(maze->height * sizeof(char*)); //Allocate memory for cell pointer pointing to strings
    character = fgetc(fpointer); //used to get rid of the next line character
    for(i = 0; i < maze->height; i++){
        *(maze->cells + i) = (char*)malloc((maze->width) * sizeof(char)); //Now the memory for each row has been allocated - pointer towards row pointer is char**, row pointer is char*
    }
     for (i = 0; i < maze->height; i++){ //Stores the text file in a 2D array
         for(j = 0; j < maze->width + 1; j++){
        //i is the row, j is the column (of matrix)
        //first, read the character 
        
        fscanf(fpointer,"%c", &character); //Stores the next character to be checked and stored in cells
        if(character == '\n'){ //If newline found, increment row, reset columns, and continue loop
            continue;
        }
         if(character == 'S'){ //If start found, set startColumn and startRow for start
           maze->startRow = i;
           maze->startColumn = j;
        }
        if(character == 'E'){ //If end found, set startColumn and startRow end
           maze->endRow = i;
           maze->endColumn = j;
        }
        *(*(maze->cells + i) + j) = character; //throw character into designated location
 
        //*(maze->cells + i) for rows
        //*(*(maze->cells + i) + j) for columns
    }}

    fclose(fpointer);
    return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    int i; //Used for iteration
    for(i = 0; i < maze->height; i++){
        free(*(maze->cells + i)); //Frees allocated memory for each string
    }
    free(maze->cells); //Frees the allocated memory for the strings
    free(maze); //Frees the allocated memory for maze
    
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    int i,j; //Used for iteration
    for(i = 0; i < maze->height; i++){
        for(j = 0; j < maze->width + 1; j++){
            printf("%c", *(*(maze->cells + i) + j)); //Iterates through the 2D array
        }
        printf("\n"); //Make sure to print a new line after iterating through a row
    }
    
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    if(col > maze->width || row > maze->height || col < -1 || row < -1) //Base case 1: Out of bounds, and return 0
        return 0;   
    if(*(*(maze->cells + row) + col) == END){
        *(*(maze->cells + maze->startRow) + maze->startColumn) = START; //Base case 2: End is found and return 1
        return 1;
    }
    if(*(*(maze->cells + row) + col) == WALL || *(*(maze->cells + row) + col) == VISITED || *(*(maze->cells + row) + col) == PATH) //Base case 3: Hit a wall, the path or a visited spot and return 0
    return 0;
    *(*(maze->cells + row) + col) = PATH; //Step 4 - set (col, row) as part of the solution to the maze
    //If any of these statements return true, return true.
     if(solveMazeDFS(maze, col, row + 1) == 1) //Test cell above
           return 1;
     if(solveMazeDFS(maze, col, row - 1) == 1) //Test cell below
           return 1;
      if(solveMazeDFS(maze, col + 1, row) == 1) //Test cell to the right
           return 1;
     if(solveMazeDFS(maze, col - 1, row) == 1) //Test cell to the left
           return 1;    
    *(*(maze->cells + row) + col) = VISITED; //Backtrack by setting the current cell to visited in order to avoid future testing
    return 0;
}
