#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

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
    int i, j;
    FILE* fpointer = fopen(fileName, "r"); //Open file, create pointer fpointer
    maze_t* maze = (maze_t*)malloc(sizeof(maze_t)); //Allocate memory for maze struct
    fscanf(fpointer, "%d %d", maze->width, maze->height); //Scan file for maze dimensions, pop off stream and load into maze.width and maze.height

    maze->cells = (char**)malloc(maze->height * sizeof(char)); //Allocates memory for first set of arrays which holds pointers - basically, holds the pointer for each row
    for(i = 0; i < maze->height; i++){
        *(maze->cells + i) = (char*)malloc(maze->width * sizeof(char)); //Now the memory for each row has been allocated - pointer towards row pointer is char**, row pointer is char*
    }
        i = 0;
        j = 0;
    while(!feof(fpointer)){ //Fill board
        //i is the row, j is the column (of matrix)
        //first, read the character
        char character = fgetc(fpointer);
        if(character == '\n'){ //If newline found, increment row, reset columns, and continue loop
            i++;
            j = 0;
            continue;
        }
         if(character == 'S'){ //If start found, set startColumn and startRow
           maze->startRow = i;
           maze->startColumn = j;
        }
        if(character == 'E'){ //If start found, set startColumn and startRow
           maze->endRow = i;
           maze->endColumn = j;
        }
        *(*(maze->cells + i) + j) = character; //throw character into designated location
        j++; //Increment columns, continue until end of file
        //*(maze->cells + i) for rows
        //*(*(maze->cells + i) + j) for columns
    }
    //Now return a pointer

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
    int i;
    for(i = 0; i < maze->height; i++){
        free(*(maze->cells + i));
    }
    free(maze->cells);
    free(maze);
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
    int i,j;
    for(i = 0; i < maze->height; i++){
        for(j = 0; j < maze->width; j++){
            printf("%c", *(*(maze->cells + i) + j));
        }
        printf("\n");
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
    // Your code here. Make sure to replace following line with your own code.
    return 0;
}
