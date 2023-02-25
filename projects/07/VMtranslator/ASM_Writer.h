// translate VM command to hack assembly.
#ifndef _ASM_WRITER_
#define _ASM_WRITER_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <deque>
#include <tuple>

class ASM_Writer
{
private:
  std::ostringstream output_s;

public:
  ASM_Writer();
  ~ASM_Writer();

  //  generate code
  void writeIncSP();
  void writeDecSP();

  void writeAdd();
  void writeSub();
  void writeGt(int i, std::string &s);
  void writeLt(int i, std::string &s);
  void writeEq(int i, std::string &s);
  void writeNeg();
  void writeAnd();
  void writeOr();
  void writeNot();

  void writeSegPush(std::string vm_file_name, int segment, int index);
  void writeSegPop(std::string vm_file_name, int segment, int index);

  // translate a vm file
  void translate(std::string vm_file_name, std::deque<std::tuple<int, int, int>> buffer);
  // write to file
  void writeFile(std::ofstream &output_file);
  //
  void showAll();
};

#endif