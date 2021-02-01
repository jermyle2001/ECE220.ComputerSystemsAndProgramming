;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop

;---INTRO PARAGRAPH---
;Our intial approach composed of three loops, primarily used as counter for exit conditions of the individual loops. 
;The outerloop was used to iterate through the entire alphabet, the middle loop was used to iterate between each set
;Of hex values, and the innerloop was used to iterate through the bit string itself to accomplish bit shifting.
;The program first prints out the character of the histogram, and then extracts the highest four bits of the bit 
;string in order to utilise its hex values in printing. After extraction via BRANCH conditioning and bit shifting, 
;the remaining HEX value is then added to a set ASCII Offset value, and then compared again via BRANCH conditioning to
;another ASCII Hex value to determine whether or not it falls within the first offset's parameters. If it does not fall
;within the original parameters, a second offset is added, and the character is subsequently printed. This is looped 
;until the middleloop counter is fully decreased, when which a newline is added and the outerloop counter is 
;decreased, looped until the outerloop counter is fully decreased, after which the program halts.
;Partners: jeremyl6, tmshu2, bgin2


PRINT_HIST
;Intializing or Clearing Registers
AND R0,R0,#0 ;Clears R0
AND R1,R1,#0 ;Clears R1
AND R2,R2,#0 ;Clears R2
AND R3,R3,#0 ;Clears R3
AND R4,R4,#0 ;Clears R4
AND R5,R5,#0 ;Clears R5
AND R6,R6,#0 ;Clears R6

; -Register Table-
; R0: Used for printing, takes ASCII values and is used in TRAP execution (OUT)
; R1: Used for storing binary string from histogram, shifted left four times per cycle/read/print
; R2: Used for holding the offset values used in calculating the ASCII HEX values for printing
; R3: Used for keeping track of what letter we're currently on - prints first.
; R4: Used for innerloop, starts at 4 for left shifting the binary string
; R5: Used for middleloop, starts at 4 and increments down to zero with each set of HEX values
; R6: Used for outerloop, starts at 27 and increments down to zero

LD R6,NUM_BINS  ;Initializes R6 with the number of bins

PRINT_FIRST
LD R0,STARTCHAR ;Loads R0 with starting character ASCII value
OUT		;Prints first character of line
ADD R0,R0,#1	;Increments value of STARTCHAR
ST R0,STARTCHAR ;Stores new value of STARTCHAR after incrementation
LD R0,SPACE	;Loads R0 with ASCII value for SPACE
OUT		;Prints space

; Next step: extraction 

EXTRACT ;--The next few lines dictate the EXTRACT
AND R0,R0,#0 ;Clears destination register R0, used in printing
AND R1,R1,#0 ;Clears R1 for storing binary string
AND R4,R4,#0 ;Clears R4 for innerloop counter
AND R5,R5,#0 ;Clears R5 for middleloop counter
ADD R5,R5,#4 ;Adds 4 to R5 for middleloop counter
ADD R4,R4,#4 ;Adds 4 to R4 for innerloop counter

LDI R1,HIST_ADDR ;Loads binary string into R1

EXTRACT_LOOP
ADD R0,R0,R0	 ;Shifts R0 to make space for next bit
ADD R1,R1,#0     ;Checks if highest bit of R1 is 0 or 1
BRzp SHIFT	 ;Skips addition if zero
ADD R0,R0,#1     ;Adds 1 to R0 if 1 is present
SHIFT ADD R1,R1,R1 ;Shifts R1 to the left
ADD R4,R4,#-1    ;Subtracts 1 from innerloop
BRp EXTRACT_LOOP ;Loops until R4 hits zero
LD R3,OFFSET1 	 ;Loads the first offset value into R3
ADD R0,R0,R3	 ;Adds the offset value to R0
LD R3,VALCHECK	 ;Loads the value of Valcheck into R3 for subtraction
NOT R3,R3	 ;Inverts R3 for subtraction
ADD R3,R3,#1	 ;Adds 1 to R3 for subtraction
ADD R3,R0,R3	 ;Subtracts R0 and R3 for value check, to see if it exceeds original offset
BRnz  PRINT2	 ;Checks if value is larger than 39. If it's larger, add second offset, if not then skip
LD R3,OFFSET2	 ;Loads second offset value into R3
ADD R0,R0,R3	 ;Adds second offset value into R0
PRINT2 OUT
ADD R4,R4,#4 ;Adds 4 to R4 for innerloop counter\
AND R0,R0,#0 ;Clears R0 for reuse
ADD R5,R5,#-1	 ;Subracts one from R5 to decrease middleloop counter
BRp EXTRACT_LOOP ;Loops back if R5 has not fully decreased
AND R0,R0,#0     ;Clears R0
ADD R0,R0,#10    ;Adds value for newline into R0
OUT              ;Prints newline
ADD R6,R6,#-1	 ;Decreases outerloop counter by 1
BRz DONE	 ;Checks if outerloop is zero
LD R1, HIST_ADDR ;Loads the value of HIST_ADDR
ADD R1,R1,#1	;Adds 1 to HIST_ADDR
ST R1,HIST_ADDR ;Stores new value of incremented HIST_ADDR
BRnzp PRINT_FIRST ;Reiterates back into beginning until R6 = 0. The previous section prevents extra newlines from being added.




DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address
STARTCHAR .FILL x0040
SPACE	  .FILL x0020
VALCHECK  .FILL x0039
OFFSET1   .FILL x0030
OFFSET2   .FILL x0007

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
