// Assembler of hack assembly.
// this program translate assembly(mnemonic) to binary code.
// take "program.asm" file as an input
// and generate "program.hack" file as an output. 
// 

// g++ -o HackAssembler main.cpp Hack_Code_module.cpp Symbol_table.cpp
// 

#include <iostream>
#include <fstream>
#include <string>
#include <deque>

#include "Hack_Assembly_Parser.h"
#include "Hack_Code_module.h"
#include "Symbol_table.h"

// shared data structure, queue
std::string input_buffer; 
std::deque<std::string> output_buffer;

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
  std::string::size_type after_dot = file_name.find(".asm") + 1; // find the locaton
  file_name.erase(after_dot);           // erase .asm extension
  file_name.insert(after_dot, "hack");  // add .hack extension

  // create and open a .hack file
  std::ofstream output_file(file_name, std::ios::trunc);

  // set objects
  Hack_Assembly_Parser parser;
  Symbol_table symbol_table;
  Hack_Code_module encoder;

  // Hack_Assembly_Parser, read a line from file and parse
  // erase all the blank and comments
  parser.parse_assembly(input_file, input_buffer);
  
  // Symbol_table
  // scan all the file and make a table of symbol and it's address
  symbol_table.scan_assembly(input_buffer);

  // thread1: Hack_Code_module, translate a word to binary code
  // + change symbol(string) to address(number)
  encoder.mnemonic_to_code(input_buffer, output_buffer, symbol_table);

  // thread2: lambda function, write bit strings in the .hack file
  if(!output_file.is_open()){
    fprintf(stderr, "output file has a problem");
    exit(-1);
  }

  while(output_buffer.size() != 0) {
    output_file << output_buffer.front() << "\n";
    output_buffer.pop_front(); 
  }

  return 0;
}