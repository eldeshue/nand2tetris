// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here.
// bit shifting and bit level OR operatrion will be easier to implement
// but we dont have such instructions, so add R0 for R1 times.

  // Load R2 as a destination.
  @R2
  M=0 // initialze R2 0.

  // check R1 is greater than 0 and if not, inverse.
  @R1
  D=M
  @Inverse1
  D;JLT

  // repeat this for R1 times.
(Loop)
  @R1
  D=M
  @Endloop  // if R1 is zero, escape from loop
  D;JEQ

  // Load value of R0 to D.
  @R0
  D=M
  // Load R2 to A as a destination.
  @R2
  // calculate addition.
  M=M+D
  // counter --
  @R1
  MD=M-1

  @Loop
  0;JMP // repeat if R1 >= 0
(Endloop)

  // if the flag is not zero, inverse R2 again. 
  @flag
  D=M
  @Inverse2
  D;JGT

  // terminate process
(End)
  @End
  0;JMP

(Inverse1) // R1 * -1
  // negative R1 number to positive R1 number.
  @R1
  M=!M
  M=M+1
  @flag // indicator for Inverse2
  M=1
  @Loop // return
  0;JMP

(Inverse2) // R2 * -1
  // negative R1 number to positive R1 number.
  @R2
  M=!M
  M=M+1
  @End // return
  0;JMP