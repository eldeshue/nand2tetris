#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <tuple>
#include <algorithm>
#include <sstream>
#include "VM_Parser.h"
#include "arg1_Type.h"
#include "arg2_Type.h"

VM_Parser::VM_Parser(std::ifstream i_stream)
{

  if (i_stream.is_open()) // read a file at a time.
  {
    i_stream.seekg(0, std::ios::end);
    int string_size = i_stream.tellg();
    input_string_stream.resize(string_size);

    i_stream.seekg(0, std::ios::beg);
    i_stream.read(&input_string_stream[0], string_size);
  }
  else // reading error
  {
    fprintf(stderr, "The vm file is not available.");
    exit(-1);
  }

  // initiate hash table
  // type of command
  command_table.insert(std::make_pair("add", C_ADD));
  command_table.insert(std::make_pair("sub", C_SUB));
  command_table.insert(std::make_pair("neg", C_NEG));
  command_table.insert(std::make_pair("eq", C_EQ));
  command_table.insert(std::make_pair("gt", C_GT));
  command_table.insert(std::make_pair("lt", C_LT));
  command_table.insert(std::make_pair("and", C_AND));
  command_table.insert(std::make_pair("or", C_OR));
  command_table.insert(std::make_pair("not", C_NOT));
  command_table.insert(std::make_pair("push", C_PUSH));
  command_table.insert(std::make_pair("pop", C_POP));
  command_table.insert(std::make_pair("label", C_LABEL));
  command_table.insert(std::make_pair("goto", C_GOTO));
  command_table.insert(std::make_pair("if", C_IF));
  command_table.insert(std::make_pair("function", C_FUNCTION));
  command_table.insert(std::make_pair("return", C_RETURN));
  command_table.insert(std::make_pair("call", C_CALL));
}
VM_Parser::~VM_Parser()
{
  // clear string
  input_string_stream.clear();
  // clear hash table
  command_table.clear();
}
///////////////////////////////////////////////////
int VM_Parser::comType(std::string &command)
{
  // hash table, unordered map
  if (command_table.find(command) == command_table.end()) // not included
  {
    return 0;
  }
  else
  {
    return command_table[command];
  }
}

////////////////////////////////////////////////////
void eraseComment(std::string &command)
{
  std::string::size_type cur_pos = 0;
  std::string::size_type end_pos;

  while ((cur_pos = command.find("//", cur_pos)) != std::string::npos)
  {
    end_pos = command.find('\n', cur_pos);
    command.erase(command.begin() + cur_pos, command.begin() + end_pos);
  }
}
void eraseEmptyLine(std::string &command)
{
  // erase carriage return
  command.erase(std::remove(command.begin(), command.end(), '\r'), command.end());
  // erase EOL
  std::string::size_type cur_pos = 0;
  while ((cur_pos = command.find("\n\n", cur_pos)) != std::string::npos)
  {
    while (command.at(cur_pos + 1) == '\n')
    {
      command.erase(command.begin() + cur_pos);
    }
  }
  if (command.front() == '\n')
  {
    command.erase(command.begin());
  }
  command.erase(command.end() - 1);
}

void VM_Parser::parseCommand(std::deque<std::tuple<int, std::string, std::string>> &buffer)
{
  eraseComment(input_string_stream);
  eraseEmptyLine(input_string_stream);

  std::istringstream isstream(input_string_stream);
  std::string current_command;

  while (getline(isstream, current_command)) // unless, repeat last line twice
  {
    std::istringstream cstream(current_command);

    std::string com;
    std::string arg1 = "";
    std::string arg2 = "";
    cstream >> com >> arg1 >> arg2;
    buffer.push_back(std::make_tuple(comType(com),
                                     arg1,
                                     arg2));
  }
}