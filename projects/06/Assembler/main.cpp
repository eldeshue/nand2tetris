// Assembler of hack assembly.
// this program translate assembly(mnemonic) to binary code.
// take "program.asm" file as an input
// and generate "program.hack" file as an output. 
// 
#include <iostream>
#include <fstream>
#include <string>

// shared data structure, queue


int main(int argc, char* argv[]) {

  // check the number of the arguments.
  // argv[1] is a relative location of the .asm file.
  if(argc != 2){

  }

  // open the assembly file

  // create and open a .hack file

  // scan the file and make a table of symbol and it's address

  // thread1: Parser, read a line from .asm file and parse it.
  // erase all the blank and comments

  // thread2: change symbol(string) to address(number)
  
  // thread3: code, translate a word to binary code

  // thread4: assemble 3 word and make a line of the string

  // thread5: write those strings in the .hack file

}