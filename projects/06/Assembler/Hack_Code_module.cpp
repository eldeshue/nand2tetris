#include <string>
#include <sstream>
#include <bitset>
#include "Hack_Code_module.h"
#include "Symbol_table.h"

Hack_Code_module::Hack_Code_module()
{
  // fill 3 hash map with mnemonic and code.
  // comp
  comp_code_table.insert(std::pair<std::string, std::string>("0", "1110101010"));
  comp_code_table.insert(std::pair<std::string, std::string>("1", "1110111111"));
  comp_code_table.insert(std::pair<std::string, std::string>("-1", "1110111010"));
  comp_code_table.insert(std::pair<std::string, std::string>("D", "1110001100"));
  comp_code_table.insert(std::pair<std::string, std::string>("A", "1110110000"));
  comp_code_table.insert(std::pair<std::string, std::string>("!D", "1110001101"));
  comp_code_table.insert(std::pair<std::string, std::string>("!A", "1110110001"));
  comp_code_table.insert(std::pair<std::string, std::string>("-D", "1110001111"));
  comp_code_table.insert(std::pair<std::string, std::string>("-A", "1110110011"));
  comp_code_table.insert(std::pair<std::string, std::string>("D+1", "1110011111"));
  comp_code_table.insert(std::pair<std::string, std::string>("1+D", "1110011111"));
  comp_code_table.insert(std::pair<std::string, std::string>("A+1", "1110110111"));
  comp_code_table.insert(std::pair<std::string, std::string>("1+A", "1110110111"));
  comp_code_table.insert(std::pair<std::string, std::string>("D-1", "1110001110"));
  comp_code_table.insert(std::pair<std::string, std::string>("A-1", "1110110010"));
  comp_code_table.insert(std::pair<std::string, std::string>("D+A", "1110000010"));
  comp_code_table.insert(std::pair<std::string, std::string>("A+D", "1110000010"));
  comp_code_table.insert(std::pair<std::string, std::string>("D-A", "1110010011"));
  comp_code_table.insert(std::pair<std::string, std::string>("A-D", "1110000111"));
  comp_code_table.insert(std::pair<std::string, std::string>("D&A", "1110000000"));
  comp_code_table.insert(std::pair<std::string, std::string>("A&D", "1110000000"));
  comp_code_table.insert(std::pair<std::string, std::string>("D|A", "1110010101"));
  comp_code_table.insert(std::pair<std::string, std::string>("A|D", "1110010101"));

  comp_code_table.insert(std::pair<std::string, std::string>("M", "1111110000"));
  comp_code_table.insert(std::pair<std::string, std::string>("!M", "1111110001"));
  comp_code_table.insert(std::pair<std::string, std::string>("-M", "1111110011"));
  comp_code_table.insert(std::pair<std::string, std::string>("M+1", "1111110111"));
  comp_code_table.insert(std::pair<std::string, std::string>("1+M", "1111110111"));
  comp_code_table.insert(std::pair<std::string, std::string>("M-1", "1111110010"));
  comp_code_table.insert(std::pair<std::string, std::string>("D+M", "1111000010"));
  comp_code_table.insert(std::pair<std::string, std::string>("M+D", "1111000010"));
  comp_code_table.insert(std::pair<std::string, std::string>("D-M", "1111010011"));
  comp_code_table.insert(std::pair<std::string, std::string>("M-D", "1111000111"));
  comp_code_table.insert(std::pair<std::string, std::string>("D&M", "1111000000"));
  comp_code_table.insert(std::pair<std::string, std::string>("M&D", "1111000000"));
  comp_code_table.insert(std::pair<std::string, std::string>("D|M", "1111010101"));
  comp_code_table.insert(std::pair<std::string, std::string>("M|D", "1111010101"));

  // dest, after comp
  dest_code_table.insert(std::pair<std::string, std::string>("null", "000"));
  dest_code_table.insert(std::pair<std::string, std::string>("M", "001"));
  dest_code_table.insert(std::pair<std::string, std::string>("D", "010"));
  dest_code_table.insert(std::pair<std::string, std::string>("MD", "011"));
  dest_code_table.insert(std::pair<std::string, std::string>("DM", "011"));
  dest_code_table.insert(std::pair<std::string, std::string>("A", "100"));
  dest_code_table.insert(std::pair<std::string, std::string>("AM", "101"));
  dest_code_table.insert(std::pair<std::string, std::string>("MA", "101"));
  dest_code_table.insert(std::pair<std::string, std::string>("AD", "110"));
  dest_code_table.insert(std::pair<std::string, std::string>("DA", "110"));
  dest_code_table.insert(std::pair<std::string, std::string>("AMD", "111"));
  dest_code_table.insert(std::pair<std::string, std::string>("ADM", "111"));
  dest_code_table.insert(std::pair<std::string, std::string>("MAD", "111"));
  dest_code_table.insert(std::pair<std::string, std::string>("MDA", "111"));
  dest_code_table.insert(std::pair<std::string, std::string>("DAM", "111"));
  dest_code_table.insert(std::pair<std::string, std::string>("DMA", "111"));

  // jmp, after dest
  jmp_code_table.insert(std::pair<std::string, std::string>("null", "000"));
  jmp_code_table.insert(std::pair<std::string, std::string>("JGT", "001"));
  jmp_code_table.insert(std::pair<std::string, std::string>("JEQ", "010"));
  jmp_code_table.insert(std::pair<std::string, std::string>("JGE", "011"));
  jmp_code_table.insert(std::pair<std::string, std::string>("JLT", "100"));
  jmp_code_table.insert(std::pair<std::string, std::string>("JNE", "101"));
  jmp_code_table.insert(std::pair<std::string, std::string>("JLE", "110"));
  jmp_code_table.insert(std::pair<std::string, std::string>("JMP", "111"));
}
Hack_Code_module::~Hack_Code_module()
{
  comp_code_table.clear();
  dest_code_table.clear();
  jmp_code_table.clear();
}

// get mnemonic from input buffer
// put bit string in the output buffer
void Hack_Code_module::mnemonic_to_code(
    std::string &input_buffer,
    std::deque<std::string> &output_buffer,
    Symbol_table &sym_table)
{
  // use string stream and parse the mnemonic.
  // string stream can treat string as a stream.
  std::string inst;
  std::istringstream input_stream(input_buffer);

  while (input_stream)
  {
    getline(input_stream, inst);
    input_stream.sync(); // solve error.

    char first_char = inst.front();

    if (first_char == '@')
    {
      // a - instructions.
      inst.erase(inst.begin());

      // transform symbol to address value(decimal)
      int mem_address = sym_table.get(inst);
      if (mem_address == -1)
      { // not symbol, just number
        std::bitset<16> code(stoi(inst));
        output_buffer.push_back(code.to_string());
      }
      else
      { // symbol
        // transform int to bit string
        std::bitset<16> code(mem_address);
        output_buffer.push_back(code.to_string());
      }
    }
    else if (first_char == '(')
    {
      // label
      // ignore, do not translate
      continue;
    }
    else
    {
      // c - instructions.
      // each line has 3 field, dest -> comp -> jump
      // dest=comp;jmp
      // 1. dest
      std::string::size_type d;
      std::string dest_key;
      if ((d = inst.find('=')) == std::string::npos)
      {
        dest_key = "null";
      }
      else
      {
        dest_key = inst.substr(0, d);
      }
      // 2. jmp, append
      std::string::size_type j;
      std::string jmp_key;
      if ((j = inst.find(';')) == std::string::npos)
      {
        jmp_key = "null";
      }
      else
      {
        jmp_key = inst.substr(j + 1, std::string::npos);
        j = j - d - 1;
      }
      // 3. comp, insert
      std::string comp_key = inst.substr(d + 1, j);
      // assemble the string and put
      std::string code = comp_code_table[comp_key];
      code.append(dest_code_table[dest_key]);
      code.append(jmp_code_table[jmp_key]);

      output_buffer.push_back(code);
    }
  }
}