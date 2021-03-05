#include <stdlib.h>
#include <stdio.h>
/*
  INTRO PARAGRAPH
	We essentially fixed this code by fixing a few lines. The first error was a missing 
	semicolon in main.c that caused the line to be incomplete and preventing compilation.
	The second and third errors involved the return values of is_prime. These values were
	switched (in lines 26 and 34 of this document), and needed to be reversed, as their
	values were inconsistent with the intended meanings, causing the program to print
	the same value multiple times. The fourth error involved the calculation of the value
	k, which should have been / instead of %, as we were looking to acquire any 
	semiprimes and not remainders. The fifth error the incorrect ret value at the end
	of the program, causing ret to return the wrong value at the end result. This was
	fixed by adding a line setting ret to the appropriate value. The final error was
	the absence of a "break" line after is_prime(k), as the absence of the break caused
	the program to print the same values multiple times due to common factors - for 
	example, the number 6 would be printed out twice, with common factors 3 and 2
	causing the function to iterate and print multiple times.
	Partners: jeremyl6, tmshu2, bgin2
*/

/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) 
	{
	return 0;
	}
    for (i = 2; i < number; i++) 
	{ //for each number smaller than it
        if (number%i == 0) { //check if the remainder is 0
        return 0; /*
		    changed this from 1 to 0 - if number%i has no remainder, then that means
		    that "number" (either j or i/j) is divisible by "i", meaning "number"
		    is not prime, as it is divisible by another number outside itself or 1,
		    thus returning 0.
		  */
        }
    }
    return 1; //changed this from 0 to 1 - see above.
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <= b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) { //if no remainder
                if (is_prime(j)) { //if j is prime, then...
                    k = i/j; /*
				changed this from % to /. This essentially turns k into
				a semiprime of i. It's run through is_prime to check if
				it's a prime #.
			     */
                    if (is_prime(k)) { //AND i/j is prime, then i is a semiprime. 
                        printf("%d ", i);
			ret = 1; //added a line to change ret to the appropriate value when
				 //there is one confirmed semiprime.
			break; //added break to stop re-iteration of same numbers -
			       //ex. values such as 3,2 and 2,3 for the number 6 would cause
			       //6 to be printed out multiple times.
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}
