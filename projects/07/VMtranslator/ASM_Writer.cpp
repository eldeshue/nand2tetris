#include <fstream>
#include <sstream>
#include "ASM_Writer.h"
#include "arg2_Type.h"

ASM_Writer::ASM_Writer()
{
  output_s = std::stringstream(ouput_buffer);
}

ASM_Writer::~ASM_Writer()
{
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

void ASM_Writer::writeGt(int i)
{ // implement comparing two value by conditional jump.
  writeDecSP();
  output_s << "@SP\nA=M\nD=M\n"; // D = y
  writeDecSP();
  output_s << "@SP\nA=M\nD=M-D\n@true" << i // M = x
           << "\nD;JGT\n@false" << i        // if D = M - D > 0
           << "\n0;JMP\n(true" << i
           << ")\n@SP\nA=M\nM=-1\n@end" << i
           << "\n0;JMP\n(false" << i
           << ")\n@SP\nA=M\nM=0\n(end" << i
           << ")\n";
  writeIncSP();
}

void ASM_Writer::writeLt(int i)
{
  writeDecSP();
  output_s << "@SP\nA=M\nD=M\n";
  writeDecSP();
  output_s << "@SP\nA=M\nD=M-D\n@true" << i // M = x, D = y
           << "\nD;JLT\n@false" << i        // if D = M - D < o
           << "\n0;JMP\n(true" << i
           << ")\n@SP\nA=M\nM=-1\n@end" << i
           << "\n0;JMP\n(false" << i
           << ")\n@SP\nA=M\nM=0\n(end" << i
           << ")\n";
  writeIncSP();
}

void ASM_Writer::writeEq(int i)
{
  writeDecSP();
  output_s << "@SP\nA=M\nD=M\n";
  writeDecSP();
  output_s << "@SP\nA=M\nD=M-D\n@true" << i // M = x, D = y
           << "\nD;JEQ\n@false" << i        // if D = M - D == 0
           << "\n0;JMP\n(true" << i
           << ")\n@SP\nA=M\nM=-1\n@end" << i
           << "\n0;JMP\n(false" << i
           << ")\n@SP\nA=M\nM=0\n(end" << i
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
  output_s << "@SP\nA=M\nD=M"; // D = y
  writeDecSP();
  output_s << "@SP\nA=M\nD=M&D\n@SP\nA=M\nM=D\n"; // M = x, M & D
  writeIncSP();
}

void ASM_Writer::writeOr()
{
  writeDecSP();
  output_s << "@SP\nA=M\nD=M";
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

void ASM_Writer::writeSegPush(int segment, int index)
{
  switch (segment)
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

void ASM_Writer::writeSegPop(int segment, int index)
{
  switch (segment)
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
  case CONST:
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