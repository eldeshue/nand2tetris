// get data from assembly file and parse it.
#ifndef _HACK_ASSEMBLY_PARSER_
#define _HACK_ASSEMBLY_PARSER_

#include <fstream>
#include <string>
#include <bitset>
#include <queue>

class Hack_Assembly_Parser {
  private:

  public:
  // method
  Hack_Assembly_Parser() {}
  ~Hack_Assembly_Parser() {}  

  int parse_string_stream(
    std::ifstream& input,
    std::queue<std::string>& buffer 
            ) {
    // read a line and put string in to buffer
    // erase space and comments
    
    // entering critical section

    // escaping critical section
    
  }

};

#endif