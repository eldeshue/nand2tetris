// VM to Assembly
// Intermediate Language translator.
// Backe end of the Jack compiler.
// translate IL to Assembly.

// g++ -o VMtoAssembly main.cpp ASM_Writer.cpp VM_Parser.cpp
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <deque>
#include <tuple>
#include <vector>
#include <string>

#include "VM_Parser.h"
#include "ASM_Writer.h"

std::vector<VM_Parser> parsers;
std::vector<std::string> asm_file_name;
std::vector<std::pair<std::string, std::deque<std::tuple<int, std::string, std::string>>>> command_buffer;

void processing_file_name(std::string &str)
{
  std::string::size_type pos;
  while ((pos = str.find('/', 0)) != std::string::npos)
  {
    str.erase(str.begin(), str.begin() + pos + 1);
  }
  // erase dot
  pos = str.find('.', 0);
  str.erase(str.begin() + pos, str.end());
}

int main(int argc, char *argv[])
{
  // set VM parsers, 1 parser each on every vm files.
  // get file names
  // argv[1] is name of the asm files
  if (argv[2] == "-d") // target is directory, get vm file name
  {
    // argv[2] is -d, so directory option
    // argv[3] is name of the directory
  }
  else // target is bunch of .vm files
  {
    for (int i = 2; i < argc; i++)
    {
      std::string temp(argv[i]);
      processing_file_name(temp);
      asm_file_name.push_back(temp);
      parsers.push_back(VM_Parser(std::ifstream(argv[i]))); // assign rvalue
    }
  }
  // parse each .vm files
  for (int i = 0; i < argc - 2; i++)
  {
    std::deque<std::tuple<int, std::string, std::string>> temp;
    parsers[i].parseCommand(temp);
    command_buffer.push_back(std::make_pair(asm_file_name[i], temp));
  }

  // translate each vm files.
  ASM_Writer writer;
  for (const auto &elem : command_buffer)
  {
    writer.translate(elem.first, elem.second);
  }

  // write translated vm at asm files
  // argv[1], the asm file.
  std::ofstream output_file(argv[1]);
  // writer.showAll();
  writer.writeFile(output_file);
}