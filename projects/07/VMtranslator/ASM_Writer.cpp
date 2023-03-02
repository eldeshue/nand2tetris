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
  i = 0;
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

void ASM_Writer::writeLabel(std::string &label)
{
  output_s << "(" << label << ")\n";
}

void ASM_Writer::writeGoto(std::string &label)
{
  output_s << "@" << label << "\n0;JMP\n";
}

void ASM_Writer::writeIfGoto(std::string &label)
{
  writeDecSP();
  output_s << "@SP\nA=M\nD=M\n@" << label << "\nD;JNE\n"; // not equal zero, true
}

void ASM_Writer::writeCall(int index, std::string &function, std::string &argc)
{
  // save return address
  output_s << "@" << function << index << "ret\nD=A\n@SP\nA=M\nM=D\n";
  writeIncSP();
  // save previous frame data
  // LCL
  output_s << "@LCL\nD=M\n@SP\nA=M\nM=D\n";
  writeIncSP();
  // ARG
  output_s << "@ARG\nD=M\n@SP\nA=M\nM=D\n";
  writeIncSP();
  // THIS
  output_s << "@THIS\nD=M\n@SP\nA=M\nM=D\n";
  writeIncSP();
  // THAT
  output_s << "@THAT\nD=M\n@SP\nA=M\nM=D\n";
  writeIncSP();
  // set new frame data
  // save new ARG
  output_s << "@SP\nD=M\n@5\nD=D-A\n@" << argc << "\nD=D-A\n@ARG\nM=D\n";
  // save new LCL
  output_s << "@SP\nD=M\n@LCL\nM=D\n";

  // jump
  output_s << "@" << function << "\n0;JMP\n";

  // label return address
  output_s << "(" << function << index << "ret)\n";
}

void ASM_Writer::writeFunction(std::string &function, std::string &local_varc)
{
  // label the function to jump
  output_s << "(" << function << ")\n";
  // initialize local segment with 0
  for (int i = 0; i < std::stoi(local_varc); i++)
  {
    // push with 0
    output_s << "@SP\nA=M\nM=0\n";
    writeIncSP();
  }
}

void ASM_Writer::writeReturn()
{
  // R14 is a pointer of the return address
  output_s << "@LCL\nD=M\n@5\nD=D-A\n@R14\nM=D\n"; 
  // save return address at R15
  output_s << "@R14\nA=M\nD=M\n@R15\nM=D\n";

  // set return value at ARG
  writeDecSP();
  output_s << "@SP\nA=M\nD=M\n@ARG\nA=M\nM=D\n";

  // restore the previous frame
  // restore the previous SP from current ARG
  output_s << "@ARG\nD=M\n@SP\nM=D\n";
  writeIncSP();
  // restore LCL
  output_s << "@R14\nA=M\nA=A+1\nD=M\n@LCL\nM=D\n";
  // restore ARG
  output_s << "@R14\nD=M\n@2\nA=A+D\nD=M\n@ARG\nM=D\n";
  // restore THIS
  output_s << "@R14\nD=M\n@3\nA=A+D\nD=M\n@THIS\nM=D\n";
  // restore THAT
  output_s << "@R14\nD=M\n@4\nA=A+D\nD=M\n@THAT\nM=D\n";
  
  // jump back to the return address
  output_s << "@R15\nA=M\n0;JMP\n";
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
    output_s << "@"<< vm_file_name << "." << index
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
void ASM_Writer::writeInitial()
{
  // set initial value of the global stack
  // stack pointer.
  output_s << "@261\nD=A\n@SP\nM=D\n"; // SP = 261
  // output_s << "@261\nD=A\n@LCL\nM=D\n"; // LCL = 261
  // output_s << "@256\nD=A\n@ARG\nM=D\n"; // ARG = 256
  //  THIS
  //  THAT
  //  call function Sys.init
  //  jump
  output_s << "@Sys.init\n0;JMP\n";
}

///////////////////////////////
void ASM_Writer::translate(std::string vm_file_name,
                           std::deque<std::tuple<int, std::string, std::string>> buffer)
{

  writeInitial();

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
    case C_LABEL:
      writeLabel(std::get<1>(buffer.front()));
      break;
    case C_GOTO:
      writeGoto(std::get<1>(buffer.front()));
      break;
    case C_IF:
      writeIfGoto(std::get<1>(buffer.front()));
      break;
    case C_FUNCTION:
      writeFunction(std::get<1>(buffer.front()), std::get<2>(buffer.front()));
      break;
    case C_RETURN:
      writeReturn();
      break;
    case C_CALL:
      writeCall(i, std::get<1>(buffer.front()), std::get<2>(buffer.front()));
      break;
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
