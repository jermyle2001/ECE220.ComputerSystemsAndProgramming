.ORIG x3000
; Write code to read in characters and echo them
; till a newline character is entered.
	AND R0,R0,#0		;clear registers
	AND R5,R5,#0
	AND R4,R4,#0		
GET_NEXT_CHAR
	GETC			;read input
	OUT			;echo to screen
	ADD R3,R0,#0		;negate the input char
	NOT R3,R3,		;store in R3
	ADD R3,R3,#1		;
	LD R1,SPACE		;is input space?
	ADD R5,R1,R3		;
	BRz GET_NEXT_CHAR	;if so, ignore and keep going
	LD R1,NEW_LINE		;is input new line?	
	ADD R5,R1,R3		;
	BRz DONE_MAIN		;if so, done and CHECK_STACK
	JSR IS_BALANCED		;valid char, call IS_BALANCED
	ADD R1,R6,#1		;if return value is -1
	BRz SET_R5		;then not balanced
	BRnzp GET_NEXT_CHAR	
DONE_MAIN
	JSR POP			;is stack empty?
	ADD R5,R5,#0		;
	BRp HALT_MAIN		;if so, balanced and done
SET_R5
	AND R5,R5,#0		;otherwise, not balanced
	ADD R5,R5,#-1		;and set R5 to -1

HALT_MAIN
	HALT	

 
SPACE   .FILL x0020
NEW_LINE        .FILL x000A
CHAR_RETURN     .FILL x000D
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;if ( push onto stack if ) pop from stack and check if popped value is (
;input - R0 holds the input
;output - R5 set to -1 if unbalanced. else 1.
IS_BALANCED
	AND R6,R6,#0		;clearing R6
	LD R2, NEG_OPEN		;storing 2's complement of open bracket
	ADD R5,R2,R0		;checkingi f input value is open bracket
	JSR PUSH		;push open bracket onto stack
	BRnzp DONE_IS_BALANCED	;exiting subroutine
IS_CLOSE
	JSR POP			;input is close bracket (pop)
	ADD R5,R5,#0		;check for underflow
	BRz DONE_IS_BALANCED 	;if no underflow, exit subroutine
	AND R6,R6,#0		;otherwise, not balanced
	ADD R6,R6,#-1		;set R6 to -1
DONE_IS_BALANCED		;restore register before exiting 
RET
NEG_OPEN .FILL xFFD8
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH
        ST R3, PUSH_SaveR3      ;save R3
        ST R4, PUSH_SaveR4      ;save R4
        AND R5, R5, #0          ;
        LD R3, STACK_END        ;
        LD R4, STACk_TOP        ;
        ADD R3, R3, #-1         ;
        NOT R3, R3              ;
        ADD R3, R3, #1          ;
        ADD R3, R3, R4          ;
        BRz OVERFLOW            ;stack is full
        STR R0, R4, #0          ;no overflow, store value in the stack
        ADD R4, R4, #-1         ;move top of the stack
        ST R4, STACK_TOP        ;store top of stack pointer
        BRnzp DONE_PUSH         ;
OVERFLOW
        ADD R5, R5, #1          ;
DONE_PUSH
        LD R3, PUSH_SaveR3      ;
        LD R4, PUSH_SaveR4      ;
        RET


PUSH_SaveR3     .BLKW #1        ;
PUSH_SaveR4     .BLKW #1        ;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP
        ST R3, POP_SaveR3       ;save R3
        ST R4, POP_SaveR4       ;save R3
        AND R5, R5, #0          ;clear R5
        LD R3, STACK_START      ;
        LD R4, STACK_TOP        ;
        NOT R3, R3              ;
        ADD R3, R3, #1          ;
        ADD R3, R3, R4          ;
        BRz UNDERFLOW           ;
        ADD R4, R4, #1          ;
        LDR R0, R4, #0          ;
        ST R4, STACK_TOP        ;
        BRnzp DONE_POP          ;
UNDERFLOW
        ADD R5, R5, #1          ;
DONE_POP
        LD R3, POP_SaveR3       ;
        LD R4, POP_SaveR4       ;
        RET


POP_SaveR3      .BLKW #1        ;
POP_SaveR4      .BLKW #1        ;
STACK_END       .FILL x3FF0     ;
STACK_START     .FILL x4000     ;
STACK_TOP       .FILL x4000     ;

.END

