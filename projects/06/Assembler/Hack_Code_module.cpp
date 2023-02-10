#include <string>
#include "Hack_Code_module.h"

Hack_Code_module::Hack_Code_module() {
  // fill 3 hash map with mnemonic and code. 
  // comp
  comp_code_table.insert(std::pair<std::string, std::string>("0","1110101010"));
  comp_code_table.insert(std::pair<std::string, std::string>("1","1110111111"));
  comp_code_table.insert(std::pair<std::string, std::string>("-1","1110111010"));
  comp_code_table.insert(std::pair<std::string, std::string>("D","1110001100"));
  comp_code_table.insert(std::pair<std::string, std::string>("A","1110110000"));
  comp_code_table.insert(std::pair<std::string, std::string>("!D","1110001101"));
  comp_code_table.insert(std::pair<std::string, std::string>("!A","1110110001"));
  comp_code_table.insert(std::pair<std::string, std::string>("-D","1110001111"));
  comp_code_table.insert(std::pair<std::string, std::string>("-A","1110110011"));
  comp_code_table.insert(std::pair<std::string, std::string>("D+1","1110011111"));
  comp_code_table.insert(std::pair<std::string, std::string>("A+1","1110110111"));
  comp_code_table.insert(std::pair<std::string, std::string>("D-1","1110001110"));
  comp_code_table.insert(std::pair<std::string, std::string>("A-1","1110110010"));
  comp_code_table.insert(std::pair<std::string, std::string>("D+A","1110000010"));
  comp_code_table.insert(std::pair<std::string, std::string>("D-A","1110010011"));
  comp_code_table.insert(std::pair<std::string, std::string>("A-D","1110000111"));
  comp_code_table.insert(std::pair<std::string, std::string>("D&A","1110000000"));
  comp_code_table.insert(std::pair<std::string, std::string>("D|A","1110010101"));

  comp_code_table.insert(std::pair<std::string, std::string>("M","1111110000"));
  comp_code_table.insert(std::pair<std::string, std::string>("!M","1111110001"));
  comp_code_table.insert(std::pair<std::string, std::string>("-M","1111110011"));
  comp_code_table.insert(std::pair<std::string, std::string>("M+1","1111110111"));
  comp_code_table.insert(std::pair<std::string, std::string>("M-1","1111110010"));
  comp_code_table.insert(std::pair<std::string, std::string>("D+M","1111000010"));
  comp_code_table.insert(std::pair<std::string, std::string>("D-M","1111010011"));
  comp_code_table.insert(std::pair<std::string, std::string>("M-D","1111000111"));
  comp_code_table.insert(std::pair<std::string, std::string>("D&M","1111000000"));
  comp_code_table.insert(std::pair<std::string, std::string>("D|M","1111010101"));

  // dest, after comp
  dest_code_table.insert(std::pair<std::string, std::string>("0","000"));
  dest_code_table.insert(std::pair<std::string, std::string>("M","001"));
  dest_code_table.insert(std::pair<std::string, std::string>("D","010"));
  dest_code_table.insert(std::pair<std::string, std::string>("MD","011"));
  dest_code_table.insert(std::pair<std::string, std::string>("A","100"));
  dest_code_table.insert(std::pair<std::string, std::string>("AM","101"));
  dest_code_table.insert(std::pair<std::string, std::string>("AD","110"));
  dest_code_table.insert(std::pair<std::string, std::string>("AMD","111"));

  // jmp, after dest
  jmp_code_table.insert(std::pair<std::string, std::string>(" ","000"));
  jmp_code_table.insert(std::pair<std::string, std::string>("JGT","001"));
  jmp_code_table.insert(std::pair<std::string, std::string>("JEQ","010"));
  jmp_code_table.insert(std::pair<std::string, std::string>("JGE","011"));
  jmp_code_table.insert(std::pair<std::string, std::string>("JLT","100"));
  jmp_code_table.insert(std::pair<std::string, std::string>("JNE","101"));
  jmp_code_table.insert(std::pair<std::string, std::string>("JLE","110"));
  jmp_code_table.insert(std::pair<std::string, std::string>("JMP","111"));

}
Hack_Code_module::~Hack_Code_module() {
  comp_code_table.clear();
  dest_code_table.clear();
  jmp_code_table.clear();
}

std::string Hack_Code_module::dest_to_code(std::string dest_key) {
  return dest_code_table[dest_key];
}
std::string Hack_Code_module::comp_to_code(std::string comp_key) {
  return comp_code_table[comp_key];
}
std::string Hack_Code_module::jmp_to_code(std::string jmp_key) {
  return jmp_code_table[jmp_key];
}

// translate 
// get mnemonic from input buffer
// put bit string in the output buffer
void Hack_Code_module::mnemonic_to_code(
  std::queue<std::string>& input_buffer, 
  std::queue<std::string>& output_buffer 
  ) {
  // use string stream and parse the mnemonic.
  // string stream can treat string as a stream.
  // each line has 3 field, dest -> comp -> jump
  // dest=comp;jump

  // entering critical section

  // escaping critical section



  // entering critical section

  // escaping critical section
}