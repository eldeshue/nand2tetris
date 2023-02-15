
// compile option
// g++ -o AssemblerTest test.cpp Hack_Code_module.cpp Symbol_table.cpp
// 
#include <iostream>
#include <fstream>
#include <string>
#include <deque>

#include "Hack_Assembly_Parser.h"
#include "Hack_Code_module.h"
#include "Symbol_table.h"

int main() {
  std::cout<<"This is a test case."<<std::endl;

  std::string test_subject = "// This is a test for parser \n M=A+D \n\n\n high.";

  std::cout<<"===== erase spaces ======="<<std::endl;
  erase_space(test_subject);
  std::cout<<test_subject<<std::endl;
  std::cout<<"===== erase comments ====="<<std::endl;
  erase_comment(test_subject);
  std::cout<<test_subject<<std::endl;
  std::cout<<"===== erase EOL =========="<<std::endl;
  erase_EOL(test_subject);
  std::cout<<test_subject<<std::endl;
  std::cout<<"=========================="<<std::endl;

}