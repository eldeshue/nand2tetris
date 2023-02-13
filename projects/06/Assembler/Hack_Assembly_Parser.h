// get data from assembly file and parse it.
#ifndef _HACK_ASSEMBLY_PARSER_
#define _HACK_ASSEMBLY_PARSER_

#include <stdlib.h>
#include <algorithm>
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

  void parse_assembly( std::ifstream& input_stream,
                           std::string& buffer ); 
};

void Hack_Assembly_Parser::parse_assembly(
  std::ifstream& input_stream,
  std::string& buffer 
          ) {
  // read all, put them in the string and use it as a string stream
  if(input_stream.is_open()){
    input_stream.seekg(0, std::ios::end); // move cursor to the end
    int buffer_size = input_stream.tellg(); // get size of the file
    buffer.resize(buffer_size);

    input_stream.seekg(0, std::ios::beg); // move cursor to start
    input_stream.read(&buffer[0], buffer_size); // read all and save
  }
  else {
    fprintf(stderr,"The asm file is not available.");
    exit(-1);
  } 

  // erase all space 
  buffer.erase(
    remove(buffer.begin(), buffer.end(), ' '), 
    buffer.end());

  // erase comment line
  std::string::size_type cur_pos = 0;  
  std::string::size_type end_pos;
  
  while((cur_pos = buffer.find("\\",cur_pos)) != std::string::npos) {
    end_pos = buffer.find('\n', cur_pos);
    buffer.erase(cur_pos, end_pos - cur_pos);
  }

  // erase all empty line
  cur_pos = 0;
  while((cur_pos = buffer.find("\n\n",cur_pos)) != std::string::npos) {
    while(buffer.at(cur_pos + 1) == '\n') {
      buffer.erase(cur_pos, 1);
    }
  }
  if(buffer.front() == '\n') {
    buffer.erase(buffer.begin());
  }
}

#endif