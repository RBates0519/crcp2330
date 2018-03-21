// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
//pg 65
//read ch 4
@sum
M=0

@R1		//parameter 1
D=M

@counter
M=D

(LOOP)
@counter
D=M
@End
D;JEQ  	//go to END label if counter is 0

@R0		//param 2, sum R0 with itself R1 times
D=M
@sum
M=M+D

@counter
M=M-1
@LOOP
0;JMP	//continue looping until we have added (counter) # of times

(END)
@sum
D=M
@R2
M=D   	//store sum result in R2