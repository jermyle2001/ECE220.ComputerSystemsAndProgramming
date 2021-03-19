/* INTRO PARAGRAPH
Within this document, three functions were implemented.

countLiveNeighbor counts the number of live neighbors in surrounding squares of the game board. 
It iterates throughout the rows and columns of the gameboard, counting the surrounding live neighbors
utilising a mathematical function. It also treats cells on the edges of the board slightly differently, albeit
still fulfilling the same purpose.

updateBoard updates the board by one step. The first step of this function is to count the amount of neighbors at each cell.
We do this by storing the neighbor at each cell in an array. The function then interates throught the board to check how many alive 
neighbors are at that cell, whether it is alive or dead, and update the status of the cell based off its current status and 
is amount of alive neighbors.

aliveStable checks to see if the current board is "stable", or will not change despite another generation. This is achieved
by updating the game board into another array, which is a copy of the game board, and iterating through each cell, checking to see
if any cell contains a value that is different from the original board. Upon detecting a non-identical cell, the function returns the
appropriate value and exits the loop. If the loop is completed, the board is identical and thust able, causing the function to return
the appropriate value and ending the game

Partners: tmshu2, bgin2, jeremyl6

*/


int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
    int i, j, live_neighbors = 0; //initializes int variables for loop iteration and to increment the number of live neighbors
    int* center = board + (row * boardColSize) + col; //initializes the address of the cell to makes sure the center doesn't get evaluated
    for(i = row - 1; i <= row + 1; i++ ){ //iterates through each row surronding the cell
        if((i < 0) || (i > boardRowSize - 1)) //checks if the row is in bounds
            continue;                           //skips this row if row is out of bounds
        for (j = col -1; j<= col +1; j++){
            if((j < 0) || (j > boardColSize - 1)) //checks if the col is in bounds
                continue;                         //skips this col if col is out of bounds
            if ((*(board + (i * boardColSize)+ j) == 1) && ((board + (i * boardColSize)+ j) != center)) //checks whether the neightbor is alive and is not the cell being evaluated
                live_neighbors++;                   //increments live neighbor count
        }

}
return live_neighbors;                          //returns the value of live neighbors surrounding that cell.
}


void updateBoard(int* board, int boardRowSize, int boardColSize) {
int i, j;               //initializes values used for loops
int neighbors_array[boardRowSize*boardColSize]; //initializes the array to store the live neighbors for each cell
for (i = 0; i < boardRowSize; i++){
    for (j = 0; j < boardColSize; j++){
        neighbors_array[i*boardColSize + j] = countLiveNeighbor(board, boardRowSize, boardColSize, i, j ); //creates an array that holds the # of "live neighbors" around each value
    }
}
for (i = 0; i < boardRowSize; i++){
    for (j = 0; j < boardColSize; j++){
        if(*(board + (i * boardColSize) + j) == 0){ //if cell is dead
            if(neighbors_array[(i * boardColSize) + j] == 3){ //check # of neighbors, if 3, set to alive. If not, remain dead.
                *(board + (i * boardColSize) + j) = 1;
            }
        }
        else{ //if the cell is not dead, it is alive
            if((neighbors_array[(i * boardColSize) + j] != 2 ) && (neighbors_array[(i * boardColSize) + j] != 3)){ //if live cell d haveoes not two or three neighbors, it is then dead
                *(board + (i * boardColSize) + j) = 0;
            }
        }
    }
    }
    return;
}


int aliveStable(int* board, int boardRowSize, int boardColSize){
    int i/*, status*/ = 1; //int status is the return value
    int copy_board[boardColSize * boardRowSize];
    for (i = 0; i < (boardColSize*boardRowSize); i++){ //this for loop will copy the board onto another array
        copy_board[i] = *(board + i);                  //the value stored at location board + i is t
 }
    updateBoard(copy_board, boardRowSize, boardColSize);
    for (i = 0; i < (boardColSize*boardRowSize); i++){ //this for loop will copy the board onto another array
     if(copy_board[i] != *(board + i)){                //checks if any part of the copy board is not identical to original
         return 0;                                     //one value is not the same, alive cells change, return 0
         //status = 0;
         //break;
     }
                                              //
     //return status;
     
                       //the value stored at location board + i is t
 }
 return 1;
}
