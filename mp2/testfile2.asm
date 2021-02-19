.ORIG x3000
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
	HALT

EQUAL_CHECK				; This subroutine checks if the equal call was valid or not.
	LD R3,STACK_START	; Loads R3 with address of STACK_START
	LD R4,STACK_TOP		; Loads R4 with address of STACK_TOP
	ADD R4,R4,#-1		; Subtracts one from R4 for STACK value checks
	NOT R4,R4			; Inverts R4 for value check
	ADD R4,R4,#1		; Adds 1 to R4 for valid check
	ADD R1,R4,R3		; Add R3 and R4 for valid check. If they are equal, then valid. If not, then invalid.
	BRz	PRINT_HEX
	JSR INVALID_CALL	; Otherwise, equal call was invalid.
	HALT		

INVALID_CALL
	LEA R0,INVALID_EXP	; Loads R0 with string for "Invalid Expression"	
	PUTS				; Prints string for "Invalid Expression"
	HALT

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
	JSR MULT				; Calls MULT function if true
	BRnzp GET_NEXT_CHAR		; Returns to GET_NEXT_CHAR
DIVD_CHECK	
	LD R1,ASCII_DIVD		; Loads R1 with ASCII value for DIVD sign
	NOT R1,R1				; Inverts R1
	ADD R1,R1,#1			; Adds 1 to R1 for inversion
	ADD R1,R1,R0			; Adds R0 and R1 for character check
	BRnp EXP_CHECK			; Skips to next check if not EXP sign
	JSR EXP					; Calls EXP function if true
	BRnzp GET_NEXT_CHAR		; Returns to GET_NEXT_CHAR	
EXP_CHECK	
	LD R1,ASCII_EXPN		; Loads R1 with ASCII value for EXPN sign
	NOT R1,R1				; Inverts R1
	ADD R1,R1,#1			; Adds 1 to R1 for inversion
	ADD R1,R1,R0			; Adds R0 and R1 for character check
	BRnp INVALID_CALL		; If not exponent, then value is invalid. Print invalid call.
	JSR EXP					; Calls EXPn funciton if true
	BRnzp GET_NEXT_CHAR

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
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET

PLUS
	AND R1,R1,#0		; Clears R1
	ADD R1,R0,#0		; Moves R0 to R1 for storage (reference)
	LEA R0,TEST_OPERATION
	ST 	R7,R7_SAVE1	
	PUTS
	LD R7,R7_SAVE1
	RET
MIN
	AND R1,R1,#0		; Clears R1
	ADD R1,R0,#0		; Moves R0 to R1 for storage (reference)
	LEA R0,TEST_OPERATION
	ST 	R7,R7_SAVE1
	PUTS
	LD R7,R7_SAVE1
	RET
EXP
	AND R1,R1,#0		; Clears R1
	ADD R1,R0,#0		; Moves R0 to R1 for storage (reference)
	LEA R0,TEST_OPERATION
	ST 	R7,R7_SAVE1	
	PUTS
	LD R7,R7_SAVE1
	RET
DIV
	AND R1,R1,#0		; Clears R1
	ADD R1,R0,#0		; Moves R0 to R1 for storage (reference)
	LEA R0,TEST_OPERATION	
	ST 	R7,R7_SAVE1	
	PUTS
	LD R7,R7_SAVE1
	RET
MULT
	AND R1,R1,#0		; Clears R1
	ADD R1,R0,#0		; Moves R0 to R1 for storage (reference)
	LEA R0,TEST_OPERATION	
	ST 	R7,R7_SAVE1
	PUTS
	LD R7,R7_SAVE1
	RET
PRINT_HEX
	HALT


R7_SAVE1	.FILL x0000
POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;
ASCII_SPACE	.FILL x0020	;
ASCII_EQUAL .FILL x003D	; ASCII Value for Equal Sign
INVALID_EXP .STRINGZ "Invalid Expression" ;
ASCII_ZERO 	.FILL x0030
ASCII_NINE	.FILL x0039
ASCII_MULT	.FILL x002A
ASCII_PLUS 	.FILL x002B 
ASCII_SUBT	.FILL x002D
ASCII_DIVD	.FILL x002F
ASCII_EXPN	.FILL x005E
TEST_OPERATION .STRINGZ "Operation performed"

.END
