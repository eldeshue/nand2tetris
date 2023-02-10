// Assembler of hack assembly.
// this program translate assembly(mnemonic) to binary code.
// take "program.asm" file as an input
// and generate "program.hack" file as an output. 
// 
#include <iostream>
#include <fstream>
#include <string>
#include <queue>

#include "Hack_Assembly_Parser.h"
#include "Hack_Code_module.h"
#include "Symbol_table.h"

// shared data structure, queue
std::queue<std::string> input_buffer; 
std::queue<std::string> output_buffer;

int main(int argc, char* argv[]) {

  // check the number of the arguments.
  // argv[1] is a relative location of the .asm file.
  if(argc != 2){
    fprintf(stderr, "Wrong number of argements.");
    return -1;
  }
  // processing the file name
  std::string file_name(argv[1]);
  
  // check the type of the file passed as an argument
  if(file_name.find(".asm") == std::string::npos) {
    // if the file name is not an 
    fprintf(stderr, "Wrong input file. asm file needed.");
    return -1;
  }
  // open the assembly file
  std::ifstream input_file(file_name);
  
  // change the name of the file
  std::string::size_type after_dot = file_name.find('.asm') + 1; // find the locaton
  file_name.erase(after_dot);           // erase .asm extension
  file_name.insert(after_dot, "hack");  // add .hack extension

  // create and open a .hack file
  std::ofstream output_file(file_name);

  // set objects
  Symbol_table symbol_table();
  Hack_Assembly_Parser parser();
  Hack_Code_module();

  // Symbol_table
  // scan all the file and make a table of symbol and it's address


  // thread1: Hack_Assembly_Parser, read a line from file and parse
  // erase all the blank and comments
  

  // thread2: Hack_Code_module, translate a word to binary code
  // + change symbol(string) to address(number)


  // thread3: lambda function, write bit strings in the .hack file


}