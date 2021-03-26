/* INTRO PARAGRAPH
Within this assignment, we implemented five functions, as directed by the assignment.

The first function, is_val_in_row, checks the entire row to see if the value is present within the row. It compares the value with every item in the present row, and returns true if the val exists in the row.

The second function, is_val_in_col, operates similarly, returning true if the value exists in the column.

The third function, is_val_in_3x3_zone, operates with a similar purpose, albeit with a different implmentation. It uses division and multiplication to determine
what rows/columns to check, returning true if the value exists within the zone.

The fourth function checks to see if any of the above three functions are true, and returns true if none of them are.

The fifth function calculates the sudoku. It uses the algorithm demonstrated on the wiki, first checking for available spaces, finding an available space
if one is available, and inserting/testing values through a recursive formula.

Partners: tmshu2, bgin2, jeremyl6
*/



#include "sudoku.h"

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9); //limits i to >=0 and <9

  // BEG TODO
  int a;                      //initializes the variable to iterate through the row
  for(a = 0; a < 9; a++){    //loops across row, compares "val" to location marked by [i][a]
    if(val == sudoku[i][a])  //compares val and array - if same, return 1
      return 1;              
  }
  return 0;                   //else return zero, showing that the value is not in row
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9); //similar format to is_val_in_row - limits j to values between 0 and 9

  // BEG TODO
  int b;
  for(b = 0; b < 9; b++){ //for loop iterates through column
    if(val == sudoku[b][j]) //checks if val == array value, if so return 1
      return 1;
  }
  return 0;    //if val != array value, then return 0
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
// i = row, j = col
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);

  // BEG TODO
  int start_a = (i / 3) * 3;  //this is to find the starting row and col of the 3 by 3. it limits the value of a to integer divided by 3, then multiplied by 3 again to achieve which box is being evaluated
  int start_b = (j / 3) * 3;  //same as the line above, as these two equations find the starting point of the correspoding 3 by 3 zone to check
  int a, b;    //initializes variables to loop through the 3 by 3
  for(a = 0; a < 3; a++){  //iterates each column
    for(b = 0; b < 3; b++){ //iterates through each row
      if (val == sudoku[start_a + a][start_b + b]) //compares the value and array value, same logic as above
        return 1;             //Return true if value exists within 3x3
    }

  }
  return 0;
  // END TODO 
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);
  
  // BEG TODO
  if((is_val_in_3x3_zone(val, i, j, sudoku)) || (is_val_in_col(val, j, sudoku)) || (is_val_in_row(val, i , sudoku)))
    return 0;
  else
    return 1;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]){
//Step 1: check if all cells are assigned by numbers
int i,j; //i is row #, j is col #
int zeroes = 0;
//Implement rudementary function to find if whole board is full
for(i = 0; i < 9; i++){
    for(j = 0; j < 9; j++){
        if(sudoku[i][j] == 0){ //check if value is zero
            zeroes++;
        }
    }
}
if(zeroes == 0){ //if no zeroes present, whole board is full - return true (1)
    return 1;
}
else{ //else, we find a nonzero cell. Mimic previous function, except save values for i and j.
int k = 0;
int i = 0;
int j = 0;
while(k < 81){ //while loop which iterates throughout entire board. Will be broken upon finding a zero.
    if(sudoku[i][j] == 0){ //upon finding a zero, break loop. Zero found at location [i][j].
        break;
    }
    k++; //increment k, i, and j. Make sure all are within boundaries.
    j++;
    if(j > 8){ //j exceeds boundaries of board - row size exceeded, reset column # and increment row #
        i++;
        j = 0;
    }
    if(i > 8){
	return 1; //i exceeds boundaries of board. Return 1 as all spaces have been filled.
    }
}
//Nonzero cell found. Implement for loop.
for(int num = 1; num <=9; num++){
    if(is_val_valid(num,i,j,sudoku) == 1 ){ //if none of these are true, then set cell to val
        sudoku[i][j] = num;
        if(solve_sudoku(sudoku)){ //if upon recursion, a one is returned at base case, then all values are valid and board has been completed.
        return 1;
    }
    }
    sudoku[i][j] = 0; //Val is not valid, increment
}


}
return 0; //all values invalid, go back to previous call and increment
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





