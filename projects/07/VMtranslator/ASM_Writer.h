// translate VM command to hack assembly.
#ifndef _ASM_WRITER_
#define _ASM_WRITER_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <deque>
#include <unordered_map>
#include <tuple>

class ASM_Writer
{
private:
  std::ostringstream output_s;
  std::unordered_map<std::string, int> segment_table;
  int i;

public:
  ASM_Writer();
  ~ASM_Writer();

  // get segment
  int segType(std::string &command);

  //  generate code
  // Stack Pointer control
  void writeIncSP();
  void writeDecSP();

  // Arithmatic operation
  void writeAdd();
  void writeSub();
  void writeGt(int i, std::string &s);
  void writeLt(int i, std::string &s);
  void writeEq(int i, std::string &s);
  void writeNeg();
  void writeAnd();
  void writeOr();
  void writeNot();

  // flow control
  void writeLabel(std::string &label);
  void writeGoto(std::string &label);
  void writeIfGoto(std::string &label);

  // subroutine
  void writeCall(int index, std::string &function_name, std::string &argc);
  void writeFunction(std::string &function_name, std::string &local_varc);
  void writeReturn();

  // memory access
  void writeSegPush(std::string vm_file_name, std::string segment, std::string index);
  void writeSegPop(std::string vm_file_name, std::string segment, std::string index);

  // initial routine
  void writeInitial();

  // translate a vm file
  void translate(std::string vm_file_name, std::deque<std::tuple<int, std::string, std::string>> buffer);
  // write to file
  void writeFile(std::ofstream &output_file);
  //
  void showAll();
};

#endif