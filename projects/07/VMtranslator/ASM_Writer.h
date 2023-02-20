// translate VM command to hack assembly.
#ifndef _ASM_WRITER_
#define _ASM_WRITER_

#include <fstream>
#include <deque>

class ASM_Writer {
  public:
  std::ofstream output_stream;

  private:
  ASM_Writer(std::ofstream& o_stream);
  ~ASM_Writer();

  void setFileName(std::deque<std::pair<int, std::string>> buffer);     // write new VM file  
  void write(std::deque<std::pair<int, std::string>> buffer);
  void Close();

  // 
  // write Arithmetic code
  void writeArithmetic(std::string& command);  
  // write push, pop command
  void writePush(int segment, int index);
  void writePop(int segment, int index);

};

#endif