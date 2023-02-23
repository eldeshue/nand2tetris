// translate VM command to hack assembly.
#ifndef _ASM_WRITER_
#define _ASM_WRITER_

#include <fstream>
#include <string>
#include <sstream>
#include <deque>

class ASM_Writer
{
private:
  std::string vm_file_name;
  std::string ouput_buffer;
  std::stringstream output_s;

public:
  ASM_Writer();
  ~ASM_Writer();

  //  generate code
  void writeIncSP();
  void writeDecSP();

  void writeAdd();
  void writeSub();
  void writeGt(int i);
  void writeLt(int i);
  void writeEq(int i);
  void writeNeg();
  void writeAnd();
  void writeOr();
  void writeNot();

  void writeSegPush(int segment, int index);
  void writeSegPop(int segment, int index);

  // translate a vm file
  void translate(std::string vm_file_name, std::deque<std::tuple<int, int, int>> buffer);
  // write to file
  void writeFile(std::string asm_file_name);
};

#endif