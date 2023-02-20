#include <fstream>
#include <string>
#include <deque>
#include <tuple>
#include <algorithm>
#include <sstream>
#include "VM_Parser.h"
#include "arg1_Type.h"
#include "arg2_Type.h"

VM_Parser::VM_Parser(std::ifstream& i_stream){

  if(i_stream.is_open()){
    i_stream.seekg(0, std::ios::end);
    int string_size = i_stream.tellg();
    input_string_stream.resize(string_size); 

    i_stream.seekg(0, std::ios::beg);
    i_stream.read(&input_string_stream[0], string_size);
  }
  else{
    fprintf(stderr, "The vm file is not available.");
    exit(-1);
  }

  // initiate hash table
  arg1_table.insert(std::make_pair("add", C_ADD));
  arg1_table.insert(std::make_pair("sub", C_SUB));
  arg1_table.insert(std::make_pair("neg", C_NEG));
  arg1_table.insert(std::make_pair("eq", C_EQ));
  arg1_table.insert(std::make_pair("gt", C_GT));
  arg1_table.insert(std::make_pair("lt", C_LT));
  arg1_table.insert(std::make_pair("and", C_AND));
  arg1_table.insert(std::make_pair("or", C_OR));
  arg1_table.insert(std::make_pair("not", C_NOT));
  arg1_table.insert(std::make_pair("push", C_PUSH));
  arg1_table.insert(std::make_pair("pop", C_POP));
  arg1_table.insert(std::make_pair("label", C_LABEL));
  arg1_table.insert(std::make_pair("goto", C_GOTO));
  arg1_table.insert(std::make_pair("if", C_IF));
  arg1_table.insert(std::make_pair("function", C_FUNCTION));
  arg1_table.insert(std::make_pair("return", C_RETURN));
  arg1_table.insert(std::make_pair("call", C_CALL));
  
  arg2_table.insert(std::make_pair("argument", ARGUMENT));
  arg2_table.insert(std::make_pair("local", LOCAL));
  arg2_table.insert(std::make_pair("static", STATIC));
  arg2_table.insert(std::make_pair("constant", CONST));
  arg2_table.insert(std::make_pair("this", THIS));
  arg2_table.insert(std::make_pair("that", THAT));
  arg2_table.insert(std::make_pair("pointer", POINTER));
  arg2_table.insert(std::make_pair("temp", TEMP));

}
VM_Parser::~VM_Parser(){
  // clear string
  input_string_stream.clear();
  // clear hash table
  arg1_table.clear();
  arg2_table.clear();
}
///////////////////////////////////////////////////
int VM_Parser::arg1Type(std::string& command) {
  // hash table, unordered map
  if(arg1_table.find(command) == arg1_table.end()){
    return 0;
  }
  else{
    return arg1_table[command];
  }
}
int VM_Parser::arg2Type(std::string& command) {
  // hash table, unordered map
  if(arg2_table.find(command) == arg2_table.end()){
    return 0;
  }
  else{
    return arg2_table[command];
  }
}
////////////////////////////////////////////////////
void eraseComment(std::string& command) {
  std::string::size_type cur_pos = 0;
  std::string::size_type end_pos;

  while ((cur_pos = command.find("//", cur_pos)) != std::string::npos)
  {
    end_pos = command.find('\n', cur_pos);
    command.erase(command.begin() + cur_pos, command.begin() + end_pos);
  }
}
void eraseEmptyLine(std::string& command) {
  // erase carriage return
  command.erase( std::remove(command.begin(), command.end(), '\r'), command.end());
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

void VM_Parser::parseCommand(std::deque<std::tuple<int, int, int>> buffer){

  eraseComment(input_string_stream);
  eraseEmptyLine(input_string_stream);

  std::istringstream isstream(input_string_stream);
  std::string current_command;

  while(isstream){
    getline(isstream, current_command);
    std::istringstream cstream(current_command);

    std::string com;
    std::string seg = "";
    int value = 0;
    cstream >> com >> seg >> value;
    buffer.push_back(std::make_tuple(arg1Type(com),
                                     arg2Type(seg),
                                     value)); 
  }
}