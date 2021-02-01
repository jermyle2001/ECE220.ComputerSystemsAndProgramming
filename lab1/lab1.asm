.ORIG x3000
EXTRACT
AND R2,R2,#0; clear destination register R2
AND R1,R1,#0; clear bit counter R1
ADD R1,R1,#4; initialize bit counter to 4
EXTRACT_LOOP
ADD R2,R2,R2; shift R2 to make space for next bit
ADD R3,R3,#0; observe the highest bit of R3
BRzp SHIFT; if highest bit is 0, skip adding 1 to R2
ADD R2,R2,#1; Add1 to R2
SHIFT ADD R3,R3,R3; left shift R3
ADD R1,R1,#-1; decrement bit counter
BRp EXTRACT_LOOP; if there’s still more bits go back to EXTRACT_LOOP
