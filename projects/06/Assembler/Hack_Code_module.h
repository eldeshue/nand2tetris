// class with a mnemonic - bit code table
// translate mnemonic to bit code

#ifndef _HACK_CODE_
#define _HACK_CODE_

#include <unordered_map>
#include <queue>
#include <bitset>
#include "Symbol_table.h"

class Hack_Code_module {
  private:
  // field
  std::unordered_map<std::string, std::string> dest_code_table;
  std::unordered_map<std::string, std::string> comp_code_table;
  std::unordered_map<std::string, std::string> jmp_code_table;

  public:
  // method
  Hack_Code_module();
  ~Hack_Code_module();

  std::string dest_to_code(std::string dest_key); 
  std::string comp_to_code(std::string comp_key);
  std::string jmp_to_code(std::string jmp_key); 

  // translate 
  // get mnemonic from input buffer
  // put bit string in the output buffer
  void mnemonic_to_code( std::queue<std::string>& input_buffer , 
                         std::queue<std::string>& output_buffer ); 

};

#endif