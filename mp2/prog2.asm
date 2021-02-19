;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;- REGISTER TABLE -
;R0: Primarily used in printing, stack PUSHing or POPing, values PUSHed or POPed to R0 are generally moved to R3 
;	 or R4.
;R1: Primarily used in holding values in R3 that we don't want to get rid of. Holds ASCII values for comparisons
;	 (often inverted), and is commonly used in subtraction. Also used in PRINT_HEX as current position holder in
;	 printed string.
;R2: Used almost exclusively as a negativity checker. Is incremented or decremented based on such. Otherwise used
;	 in pointing STRING entry.
;R3: Often used in POP, PUSH. Also used in holding arithmetic values transferred from R0. In PRINT_HEX, holds ASCII 
;	 offset values.
;R4: Similar to R3.
;R5: Often used to check for over/underflow in PUSH/POP. Also used to hold/store the final result.
;R6: R6 is used as a temporary register, although is rarely utilised at all in this program.
;R7: Untouched, used by TRAP and JSR, in addition to being stored often.




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;- INTRO -
;The stack calculator was primarily achieved using a series of ASCII value comparisons and various Branches that
;included calls to subroutines. Once the program received a character from the keyboard, the program would compare
;the character's ASCII value to the ASCII value of the Equal sign, spacebar, each of the arithmetic operators, and the
;range of available numbers. Once the corresponding value compared through subtraction is found, the program calls
;the corresponding subroutine, either PUSHing, or an arithmetic operation involving POPing two values. If none of the
;checks are fulfilled, the character inputted is invalid and the program terminates. 
;Partners: jeremyl6, tmshu2, bgin2
.ORIG x3000

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
GET_NEXT_CHAR
	GETC				; Read Input
	OUT					; Echo to screen
						; At this point, input char is in R0
	ADD R3,R0,#0		; Move from R0 to R3

	LD R1,ASCII_EQUAL	; Load R1 with ascii value for equal sign
	NOT R1,R1			; Invert equal sign for subtraction
	ADD R1,R1,#1		; Add 1 to R1 for subtraction
	ADD R1,R1,R3		; ADD Inverted ASCII Equal and Input Char to check for EQUAL
	BRz EQUAL_CHECK		; Checks if equal call is valid

	LD R1,ASCII_SPACE 	; Load Ascii value for space into R1	
	NOT R1,R1			; invert R1 for subtraction	
	ADD R1,R1,#1		; Add 1 to R1 for subtraction
	ADD R5,R1,R3		; Add Inverted ASCII Space and Input Char to check for SPACE
	BRz GET_NEXT_CHAR	; If so, ignore and return to GET_NEXT_CHAR
	BRnzp EVALUATE_CHAR ; If not a space or equal sign, we go to EVALUATE_CHAR

ASCII_SPACE	.FILL x0020	;
ASCII_EQUAL .FILL x003D	; ASCII Value for Equal Sign

;;;;;;;;;;;;;;;;;;;;;;;;;;;
EQUAL_CHECK				; This subroutine checks if the equal call was valid or not.
	LD R3,STACK_START	; Loads R3 with address of STACK_START
	LD R4,STACK_TOP		; Loads R4 with address of STACK_TOP
	ADD R4,R4,#1		; Subtracts one from R4 for STACK value checks
	NOT R4,R4			; Inverts R4 for value check
	ADD R4,R4,#1		; Adds 1 to R4 for valid check
	ADD R1,R4,R3		; Add R3 and R4 for valid check. If they are equal, then valid. If not, then invalid.
	BRz	PRINT_HEX
	JSR INVALID_CALL	; Otherwise, equal call was invalid.
	HALT				
;;;;;;;;;;;;;;;;;;;;;;;;;
INVALID_CALL
	LEA R0,INVALID_EXP	; Loads R0 with string for "Invalid Expression"	
	PUTS				; Prints string for "Invalid Expression
	HALT				; Halts program once INVALID_CALL is invoked, as the program must terminate from an invalid 
						; call.

INVALID_EXP .STRINGZ "Invalid Expression" ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
;Load result into R5 first
PRINT_HEX
	JSR POP				; Pops result into R0
	AND R5,R5,#0		; Clears R5
	ADD R5,R5,R0		; Moves value from R0 into R5
	ST R5,SAVE_R5		; Saves value of R5
EXTRACT ;--The next few lines dictate the EXTRACT
AND R0,R0,#0 ;Clears destination register R0, used in printing
AND R1,R1,#0 ;Clears R1 for storing binary string
ADD R1,R5,#0			; Loads binary string stored in R5 into R1
AND R5,R5,#0 ;Clears R5 for middleloop counter
AND R4,R4,#0 ;Clears R4 for innerloop counter
ADD R5,R5,#4 ;Adds 4 to R5 for middleloop counter
ADD R4,R4,#4 ;Adds 4 to R4 for innerloop counter



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
LD R5,SAVE_R5
HALT
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE_CHAR
	LD R1,ASCII_ZERO		; Loads R1 with ASCII value zero
	NOT R1,R1				; Inverts R1
	ADD R1,R1,#1			; Adds 1 to R1 for inversion
	ADD R1,R1,R0			; Adds R0 and R1 for character check
	BRn PLUS_CHECK			; Jumps to NOT_NUM from check
	LD R1,ASCII_NINE		; Loads R1 with ASCII value nine	
	NOT R1,R1				; Inverts R1
	ADD R1,R1,#1			; Adds 1 to R1 for inversion
	ADD R1,R1,R0			; Adds R0 and R1 for character check
	BRp EXP_CHECK			; Checks if char is a number
	ADD R0,R0,#-16			; Applies ASCII offset before PUSH			
	ADD R0,R0,#-16			;
	ADD R0,R0,#-16			;
	JSR PUSH				; If number, PUSH to stack
	BRnzp GET_NEXT_CHAR		; Jump back to GET_NEXT_CHAR
PLUS_CHECK
	LD R1,ASCII_PLUS		; Loads R1 with ASCII value for PLUS sign
	NOT R1,R1				; Inverts R1
	ADD R1,R1,#1			; Adds 1 to R1 for inversion
	ADD R1,R1,R0			; Adds R0 and R1 for character check
	BRnp SUBT_CHECK			; Skips to next check if not PLUS sign
	JSR PLUS				; Calls PLUS function if true
	BRnzp GET_NEXT_CHAR		; Returns to GET_NEXT_CHAR	
SUBT_CHECK	
	LD R1,ASCII_SUBT		; Loads R1 with ASCII value for MINUS sign
	NOT R1,R1				; Inverts R1
	ADD R1,R1,#1			; Adds 1 to R1 for inversion
	ADD R1,R1,R0			; Adds R0 and R1 for character check
	BRnp MULT_CHECK			; Skips to next check if not MINUS sign
	JSR MIN					; Calls MIN function if true
	BRnzp GET_NEXT_CHAR		; Returns to GET_NEXT_CHAR
MULT_CHECK
	LD R1,ASCII_MULT		; Loads R1 with ASCII value for MULT sign
	NOT R1,R1				; Inverts R1
	ADD R1,R1,#1			; Adds 1 to R1 for inversion
	ADD R1,R1,R0			; Adds R0 and R1 for character check
	BRnp DIVD_CHECK			; Skips to next check if not MULT sign
	JSR MUL				; Calls MULT function if true
	BRnzp GET_NEXT_CHAR		; Returns to GET_NEXT_CHAR
DIVD_CHECK	
	LD R1,ASCII_DIVD		; Loads R1 with ASCII value for DIVD sign
	NOT R1,R1				; Inverts R1
	ADD R1,R1,#1			; Adds 1 to R1 for inversion
	ADD R1,R1,R0			; Adds R0 and R1 for character check
	BRnp EXP_CHECK			; Skips to next check if not EXP sign
	JSR DIV					; Calls EXP function if true
	BRnzp GET_NEXT_CHAR		; Returns to GET_NEXT_CHAR	
EXP_CHECK	
	LD R1,ASCII_EXPN		; Loads R1 with ASCII value for EXPN sign
	NOT R1,R1				; Inverts R1
	ADD R1,R1,#1			; Adds 1 to R1 for inversion
	ADD R1,R1,R0			; Adds R0 and R1 for character check
	BRnp INVALID_CALL		; If not exponent, then value is invalid. Print invalid call.
	JSR EXP					; Calls EXPN funciton if true
	BRnzp GET_NEXT_CHAR
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
	ST R7,SAVE_R7			; Stores R7 for return
	AND R3,R3,#0			; Clears R3 for usage
	AND R4,R4,#0			; Clears R4 for usage
	JSR POP					; Pops first value from stack
	ADD R3,R3,R0			; Moves value from Pop stored in R0 to R3	
	JSR POP					; Pops second value from stack
	ADD R4,R4,R0			; Moves value from Pop stored in R0 to R4
	AND R0,R0,#0			; Clears R0 for usage
	ADD R0,R3,R4			; Adds values in R3 and R4, stores in R0	
	JSR PUSH				; Pushes value back to stack
	LD R7,SAVE_R7		 	; Loads R7 for return
	RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here
	ST R7,SAVE_R7			; Stores R7 for return
	AND R3,R3,#0			; Clears R3 for usage
	AND R4,R4,#0			; Clears R4 for usage
	JSR POP					; Pops first value from stack
	ADD R3,R3,R0			; Moves value from Pop stored in R0 to R3	
	JSR POP					; Pops second value from stack
	ADD R4,R4,R0			; Moves value from Pop stored in R0 to R4
	AND R0,R0,#0			; Clears R0 for usage
	NOT R3,R3				; Inverts R3 for subtraction
	ADD R3,R3,#1			; Adds 1 to R3 for subtraction
	ADD R0,R3,R4			; Subtracts R3 from R4
	JSR PUSH				; Pushes value back to stack
	LD R7,SAVE_R7			; Loads R7 for return
	RET	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
; *********NOTE: WE NEED TO SAVE R7 BECAUSE IT'S NESTED (APPLIES TO ROUTINES BELOW)**************
MUL	
	ST R7,SAVE_R7			; Stores R7 for return
	AND R3,R3,#0			; Clears R3 for usage
	AND R4,R4,#0			; Clears R4 for usage
	AND R2,R2,#0			; Clears R2 for negative check
	JSR POP					; Pops first value from stack
	ADD R3,R3,R0			; Moves value from Pop stored in R0 to R3	
	JSR POP					; Pops second value from stack
	ADD R4,R4,R0			; Moves value from Pop stored in R0 to R4
	AND R0,R0,#0			; Clears R0 for usage
ZERO_CHECK_MUL		
	ADD R3,R3,#0			; Checks if R3 is zero
	BRz SET_ZERO_MULT		; Sets R0 to zero if true
	ADD R4,R4,#0			; Checks if R4 is zero
	BRz SET_ZERO_MULT		; Sets R0 to zero is true
NEG_CHECK_MULT
	ADD R4,R4,#0			; Sets CC to check if R4 is negative
	BRzp NEG_CHECK_MULT2	; If not negative, then skip inversion and check if R3 is negative. Otherwise, invert
	NOT R4,R4				; Inverts R4
	ADD R4,R4,#1			; Adds 1 to R4 for inversion
	ADD R2,R2,#-1			; Subtracts 1 from R2 for negative check
NEG_CHECK_MULT2		
	ADD R3,R3,#0			; Sets CC to check if R3 is negative
	BRzp MUL_LOOP			; Skips inversion if R3 is positive
	NOT R3,R3				; Inverts R3
	ADD R3,R3,#1			; Adds 1 to R3 for inversion
	ADD R2,R2,#1			; Adds 1 to R2 for negative check
MUL_LOOP
	ADD R0,R3,R0			; Adds value in R3 to R0 for multiplication
	ADD R4,R4,#-1			; Decreases counter in R4 for multiplication loop
	BRp	MUL_LOOP			; If R4 != zero (counter) then keep adding
	ADD R2,R2,#0			; Sets CC to check if value should be negative or not
	BRz PUSH_MULT			; If R2 != zero, then value needs to be inverted. Otherwise, push to stack
	NOT R0,R0				; Inverts R0
	ADD R0,R0,#1			; Adds 1 to R0 for inversion
BRnzp PUSH_MULT
SET_ZERO_MULT
	AND R0,R0,#0			; Sets R0 to zero if multiplication contains zero
PUSH_MULT
	JSR PUSH				; Pushes value back to stack if loop finished
	LD R7,SAVE_R7			; Loads value for R7 for return
	RET			
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
; Input value will always be positive integers
DIV	
	ST R7,SAVE_R7			; Stores R7 for return
	AND R3,R3,#0			; Clears R3 for usage
	AND R4,R4,#0			; Clears R4 for usage
	JSR POP					; Pops first value from stack
	ADD R3,R3,R0			; Moves value from Pop stored in R0 to R3	
	JSR POP					; Pops second value from stack
	ADD R4,R4,R0			; Moves value from Pop stored in R0 to R4
	AND R0,R0,#0			; Clears R0 for usage
NEG_CHECK_DIV1				; First negative check for division
	ADD R4,R4,#0			; Sets CC to check if R4 is negative
	BRzp NEG_CHECK_DIV2		; If not negative, then go to multiplication loop. If negative, invert both registers
	NOT R4,R4				; Inverts R4
	ADD R4,R4,#1			; Adds 1 to R4 for inversion
	AND R2,R2,#0			; Clears R2 for negative counter
	ADD R2,R2,#-1			; Subtracts 1 from R2 for negative check
NEG_CHECK_DIV2				; Second negative check for division
	ADD R3,R3,#0			; Sets CC to check if R3 is negative
	BRzp DIV_LOOP_SET			; Jumps to DIV_LOOP if nonnegative
	NOT R3,R3				; Inverts R3
	ADD R3,R3,#1			; Adds 1 to R3 for inversion
	ADD R2,R2,#1			; Adds 1 to R2 if negative for negative check
							; These next lines will set up the division loop
DIV_LOOP_SET
	AND R1,R1,#0			; Clears R1 for usage
	ADD R1,R3,#0			; Moves value stored in R3 to R1	
	NOT R1,R1				; Inverts R1 for division
	ADD R1,R1,#1			; Adds 1 to R1 for division - at this point, R1 = -R3
	AND R0,R0,#0			; Clears R0 for division
DIV_LOOP
	ADD R4,R4,R1			; Subtracts R3 from R4, storing back into R4
	BRn	DIV_FIN				; If negative, skip counter addition
	ADD R0,R0,#1			; Adds 1 to R0 for division counter
	BRnzp DIV_LOOP			; Loops back to DIV_LOOP
DIV_FIN
	ADD R2,R2,#0			; Sets CC to check if value should be negative
	BRz DIV_PUSH			; Inverts R0 if value should be negative, otherwise push to stack
	NOT R0,R0				; Inverts R0
	ADD R0,R0,#1			; Adds 1 to R0 for inversion
DIV_PUSH
	JSR PUSH				; Pushes value in R0 to stack
	LD R7,SAVE_R7			; Loads R7 for return
	RET	
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;
SAVE_R5		.FILL x0000	;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
	ST R7,SAVE_R7			; Stores R7 for return
	AND R3,R3,#0			; Clears R3 for usage
	AND R4,R4,#0			; Clears R4 for usage
	JSR POP					; Pops first value from stack
	ADD R3,R3,R0			; Moves value from Pop stored in R0 to R3	
	JSR POP					; Pops second value from stack
	ADD R4,R4,R0			; Moves value from Pop stored in R0 to R4
	AND R0,R0,#0			; Clears R0 for usage
;; First value popped (R3) is exponent
	AND R1,R1,#0			; Clears R1 for usage
	AND R2,R2,#0			; Clears R2 for usage
	AND R0,R0,#0			; Clears R0 for usage
	AND R5,R5,#0			; Clears R5 for usage
	AND R6,R6,#0			; Clears R6 for usage
	ADD R1,R4,#0			; Moves value in R4 to R1
	ADD R2,R1,#0			; Moves value in R1 to R2
	ADD R3,R3,#0			; Checks R3 for its value
	BRz SET_ONE_EXP			; If exponent is zero, set value to zero
	ADD R3,R3,#-1			; Removes one from R3
	BRp EXP_MUL_LOOP		; Checks if exponent >1 prior to subtraction
	ADD R0,R0,R4			; Adds base to R0 if exponent was one
	BRnzp PUSH_EXP			; Jump to PUSH
EXP_MUL_LOOP
	ADD R0,R4,R0			; Adds value in R4 to R0
	ADD R1,R1,#-1			; Decreases R1 for counter
	BRp EXP_MUL_LOOP		; If R1 is not zero, keep adding
	AND R4,R4,#0			; Clears R4
	ADD R4,R0,#0			; Moves value stored in R0 to R4
	AND R0,R0,#0			; Clears R0 for usage
	ADD R1,R2,#0			; Restore value of R1	
	ADD R3,R3,#-1			; Subtract 1 from power
	BRp EXP_MUL_LOOP		; If power is positive, go back to multiplication loop
	ADD R0,R4,#0			; Moves value stored in R4 into R0
PUSH_EXP	
	JSR PUSH				; Pushes value in R0 to stack
	LD R7,SAVE_R7			; Loads R7 for return
	RET
SET_ONE_EXP
	AND R0,R0,#0			; Clears R0 for setting
	ADD R0,R0,#1			; Adds 1 to R0
	BRnzp PUSH_EXP			; Jumps to PUSH call
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACK_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
	JSR INVALID_CALL	; Terminates program if stack overflow
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
	JSR INVALID_CALL	; Terminates program if stack underflow
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET

VALCHECK  .FILL x0039
OFFSET1   .FILL x0030
OFFSET2   .FILL x0007

SAVE_R7		.FILL x0000	; 
SAVE_R7_2	.FILL x0000 ;
POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;

ASCII_ZERO 	.FILL x0030
ASCII_NINE	.FILL x0039
ASCII_MULT	.FILL x002A
ASCII_PLUS 	.FILL x002B 
ASCII_SUBT	.FILL x002D
ASCII_DIVD	.FILL x002F
ASCII_EXPN	.FILL x005E
.END
