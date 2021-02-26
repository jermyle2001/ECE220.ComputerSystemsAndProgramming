#include <stdio.h>
#include <stdlib.h>
/*This program takes a integer and prints that row's coefficients of the pascal's triangle.
*We used a for loop and the uppercase pi equation to print out each equation. Since the 
*coefficients are a mulitplication summation, we would oprint the coefficient after each
*time we use the equation (n+1-i)/i.
*Partners:tmshu2 jeremyl6 bgin2
*/
int main()
{
  int row, i; 	// Initializes the integers that will contain the user inputted row and the integer for the iteration
  printf("Enter a row index: "); 	//Prints the message that will prompt the user to enter a row index
  scanf("%d",&row); 	//Asks the user to enter the row index. Will be used for for loop and to calculate the coefficient.

  
  // Write your code here
	unsigned int long binom = 1;	//Initializes unsigned int long binom since we want to have as many bits available for big coefficients
    	for(i = 0; i <= row; i++) //Iterates row + 1 times in order to print each coefficient for that row
    	{
     	 if (i == 0)    
          printf("%lu ", binom); 	//For the uppercase pi summation equation the first coefficient should be 1 regardless
     	 else{
          binom = ((binom * (row + 1 - i) )/ i); //For all other cases, calculate the coefficient for the next term
          printf("%lu ", binom); //Prints the term
      }
    }
  return 0;
}
