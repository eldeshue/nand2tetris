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

public:
  ASM_Writer();
  ~ASM_Writer();

  // get segment
  int segType(std::string &command);

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

  void writeSegPush(std::string vm_file_name, std::string segment, std::string index);
  void writeSegPop(std::string vm_file_name, std::string segment, std::string index);

  // translate a vm file
  void translate(std::string vm_file_name, std::deque<std::tuple<int, std::string, std::string>> buffer);
  // write to file
  void writeFile(std::ofstream &output_file);
  //
  void showAll();
};

#endif