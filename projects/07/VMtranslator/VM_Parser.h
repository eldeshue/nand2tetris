// Parsing module
// delete comments and empty line.
// parse command and classify.

#ifndef _VM_PARSER_
#define _VM_PARSER_

#include <string>
#include <fstream>
#include <deque>
#include <unordered_map>

class VM_Parser
{
private:
  std::string input_string_stream;
  std::unordered_map<std::string, int> arg1_table;
  std::unordered_map<std::string, int> arg2_table;

public:
  VM_Parser(std::ifstream i_stream);
  // VM_Parser(std::ifstream &i_stream);
  ~VM_Parser();

  int arg1Type(std::string &command); // return type of the first arg, operator
  int arg2Type(std::string &command); // return type of the second arg, segment

  void parseCommand(std::deque<std::tuple<int, int, int>> &buffer); // put parsed commands to the buffer
};

void eraseComment(std::string &command);   // erase comments
void eraseEmptyLine(std::string &command); // erase empty line, \n or \r

#endif