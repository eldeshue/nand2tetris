// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

// mov KBD's value to SCREEN

(Loop)
  // check the KBD
  @KBD
  D=M
  @Fill
  D;JGT
(Return)
  @Erase
  D;JEQ

(Fill)
  @csr
  M=0
  (Loop1)
    @csr
    D=M
    @SCREEN
    A=D+A
    M=-1 // fill the pixel
    @csr
    M=M+1 // cursor moves forward

    @KBD
    D=M
    @Return
    D;JEQ

    @Loop1
    0;JMP


(Erase)
  @csr
  M=0
  (Loop2)
    @csr
    D=M
    @SCREEN
    A=D+A
    M=0 // erase the pixel
    @csr
    M=M+1 // cursor moves forward

    @KBD
    D=M
    @Loop
    D;JGT
    
    @Loop2
    0;JMP
    