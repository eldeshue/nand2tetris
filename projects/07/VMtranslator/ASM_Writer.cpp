#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <deque>
#include <tuple>
#include "ASM_Writer.h"
#include "arg1_Type.h"
#include "arg2_Type.h"

ASM_Writer::ASM_Writer()
{
  // type of segment
  segment_table.insert(std::make_pair("argument", ARGUMENT));
  segment_table.insert(std::make_pair("local", LOCAL));
  segment_table.insert(std::make_pair("static", STATIC));
  segment_table.insert(std::make_pair("constant", CONST));
  segment_table.insert(std::make_pair("this", THIS));
  segment_table.insert(std::make_pair("that", THAT));
  segment_table.insert(std::make_pair("pointer", POINTER));
  segment_table.insert(std::make_pair("temp", TEMP));
}

ASM_Writer::~ASM_Writer()
{
  segment_table.clear();
}

int ASM_Writer::segType(std::string &command)
{
  // hash table, unordered map
  if (segment_table.find(command) == segment_table.end())
  {
    return 0;
  }
  else
  {
    return segment_table[command];
  }
}

void ASM_Writer::writeIncSP()
{
  output_s << "@SP\nM=M+1\n";
}

void ASM_Writer::writeDecSP()
{
  output_s << "@SP\nM=M-1\n";
}

void ASM_Writer::writeAdd()
{
  writeDecSP();
  output_s << "@SP\nA=M\nD=M\n"; // D = y
  writeDecSP();
  output_s << "@SP\nA=M\nD=M+D\n@SP\nA=M\nM=D\n"; // M = x, M + D
  writeIncSP();
}

void ASM_Writer::writeSub()
{
  writeDecSP();
  output_s << "@SP\nA=M\nD=M\n"; // D = y
  writeDecSP();
  output_s << "@SP\nA=M\nD=M-D\n@SP\nA=M\nM=D\n"; // M = x, M - D
  writeIncSP();
}

void ASM_Writer::writeGt(int i, std::string &s)
{ // implement comparing two value by conditional jump.
  writeDecSP();
  output_s << "@SP\nA=M\nD=M\n"; // D = y
  writeDecSP();
  output_s << "@SP\nA=M\nD=M-D\n@true" << i << s // M = x
           << "\nD;JGT\n@false" << i << s        // if D = M - D > 0
           << "\n0;JMP\n(true" << i << s
           << ")\n@SP\nA=M\nM=-1\n@end" << i << s
           << "\n0;JMP\n(false" << i << s
           << ")\n@SP\nA=M\nM=0\n(end" << i << s
           << ")\n";
  writeIncSP();
}

void ASM_Writer::writeLt(int i, std::string &s)
{
  writeDecSP();
  output_s << "@SP\nA=M\nD=M\n";
  writeDecSP();
  output_s << "@SP\nA=M\nD=M-D\n@true" << i << s // M = x, D = y
           << "\nD;JLT\n@false" << i << s        // if D = M - D < o
           << "\n0;JMP\n(true" << i << s
           << ")\n@SP\nA=M\nM=-1\n@end" << i << s
           << "\n0;JMP\n(false" << i << s
           << ")\n@SP\nA=M\nM=0\n(end" << i << s
           << ")\n";
  writeIncSP();
}

void ASM_Writer::writeEq(int i, std::string &s)
{
  writeDecSP();
  output_s << "@SP\nA=M\nD=M\n";
  writeDecSP();
  output_s << "@SP\nA=M\nD=M-D\n@true" << i << s // M = x, D = y
           << "\nD;JEQ\n@false" << i << s        // if D = M - D == 0
           << "\n0;JMP\n(true" << i << s
           << ")\n@SP\nA=M\nM=-1\n@end" << i << s
           << "\n0;JMP\n(false" << i << s
           << ")\n@SP\nA=M\nM=0\n(end" << i << s
           << ")\n";
  writeIncSP();
}

void ASM_Writer::writeNeg()
{
  writeDecSP();
  output_s << "@SP\nA=M\nM=-M\n"; // M = x, M = -x
  writeIncSP();
}

void ASM_Writer::writeAnd()
{
  writeDecSP();
  output_s << "@SP\nA=M\nD=M\n"; // D = y
  writeDecSP();
  output_s << "@SP\nA=M\nD=M&D\n@SP\nA=M\nM=D\n"; // M = x, M & D
  writeIncSP();
}

void ASM_Writer::writeOr()
{
  writeDecSP();
  output_s << "@SP\nA=M\nD=M\n";
  writeDecSP();
  output_s << "@SP\nA=M\nD=M|D\n@SP\nA=M\nM=D\n";
  writeIncSP();
}

void ASM_Writer::writeNot()
{
  writeDecSP();
  output_s << "@SP\nA=M\nM=!M\n";
  writeIncSP();
}

void ASM_Writer::writeSegPush(std::string vm_file_name, std::string segment, std::string index)
{
  switch (segType(segment))
  {
  case ARGUMENT:
    output_s << "@ARG\nD=M\n";
    output_s << "@" << index
             << "\nA=A+D\nD=M\n@SP\nA=M\nM=D\n";
    break;
  case LOCAL:
    output_s << "@LCL\nD=M\n";
    output_s << "@" << index
             << "\nA=A+D\nD=M\n@SP\nA=M\nM=D\n";
    break;
  case STATIC:
    output_s << "@" << vm_file_name << "." << index
             << "\nD=M\n@SP\nA=M\nM=D\n";
    break;
  case CONST:
    output_s << "@" << index
             << "\nD=A\n@SP\nA=M\nM=D\n";
    break;
  case THIS:
    output_s << "@3\nD=M\n";
    output_s << "@" << index
             << "\nA=A+D\nD=M\n@SP\nA=M\nM=D\n";
    break;
  case THAT:
    output_s << "@4\nD=M\n";
    output_s << "@" << index
             << "\nA=A+D\nD=M\n@SP\nA=M\nM=D\n";
    break;
  case POINTER: // point this and that
    output_s << "@3\nD=A\n";
    output_s << "@" << index
             << "\nA=A+D\nD=M\n@SP\nA=M\nM=D\n";
    break;
  case TEMP:
    output_s << "@5\nD=A\n";
    output_s << "@" << index
             << "\nA=A+D\nD=M\n@SP\nA=M\nM=D\n";
    break;
  }
  writeIncSP();
}

void ASM_Writer::writeSegPop(std::string vm_file_name, std::string segment, std::string index)
{
  switch (segType(segment))
  { // save destination address at R13
  case ARGUMENT:
    output_s << "@ARG\nD=M\n@" << index
             << "\nD=A+D\n@R13\nM=D\n";
    break;
  case LOCAL:
    output_s << "@LCL\nD=M\n@" << index
             << "\nD=A+D\n@R13\nM=D\n";
    break;
  case STATIC:
    output_s << "@" << vm_file_name << "." << index
             << "\nD=A\n@R13\nM=D\n";
    break;
  case CONST: // potential threat?
    output_s << "@" << index
             << "\nD=A\n@R13\nM=D\n";
    break;
  case THIS:
    output_s << "@3\nD=M\n@" << index
             << "\nD=A+D\n@R13\nM=D\n";
    break;
  case THAT:
    output_s << "@4\nD=M\n@" << index
             << "\nD=A+D\n@R13\nM=D\n";
    break;
  case POINTER:
    output_s << "@3\nD=A\n@" << index
             << "\nD=A+D\n@R13\nM=D\n";
    break;
  case TEMP:
    output_s << "@5\nD=A\n@" << index
             << "\nD=A+D\n@R13\nM=D\n";
    break;
  }
  writeDecSP();
  output_s << "@SP\nA=M\nD=M\n@R13\nA=M\nM=D\n"; // pop and put it in the destined address
}
///////////////////////////////

///////////////////////////////
void ASM_Writer::translate(std::string vm_file_name,
                           std::deque<std::tuple<int, std::string, std::string>> buffer)
{
  int i = 0;
  while (!buffer.empty())
  {
    switch (std::get<0>(buffer.front()))
    {
    case C_ADD:
      writeAdd();
      break;
    case C_SUB:
      writeSub();
      break;
    case C_NEG:
      writeNeg();
      break;
    case C_EQ:
      writeEq(i, vm_file_name);
      break;
    case C_GT:
      writeGt(i, vm_file_name);
      break;
    case C_LT:
      writeLt(i, vm_file_name);
      break;
    case C_AND:
      writeAnd();
      break;
    case C_OR:
      writeOr();
      break;
    case C_NOT:
      writeNot();
      break;
    case C_PUSH:
      writeSegPush(vm_file_name, std::get<1>(buffer.front()), std::get<2>(buffer.front()));
      break;
    case C_POP:
      writeSegPop(vm_file_name, std::get<1>(buffer.front()), std::get<2>(buffer.front()));
      break;
      /*
    case C_LABEL:
      break;
    case C_GOTO:
      break;
    case C_IF:
      break;
    case C_FUNCTION:
      break;
    case C_RETURN:
      break;
    case C_CALL:
      break;
      */
    default:
      break;
    }
    i++;
    buffer.pop_front();
  }
}

void ASM_Writer::writeFile(std::ofstream &output_file)
{
  if (output_file.is_open())
  {
    output_file << output_s.str() << std::endl;
  }
  else
  {
    perror("output file has a problem, writing failed.");
    exit(-1);
  }
}

void ASM_Writer::showAll()
{
  std::cout << output_s.str() << std::endl;
}
