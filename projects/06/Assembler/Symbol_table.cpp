#include <sstream>
#include "Symbol_table.h"
  
Symbol_table::Symbol_table() {

  // initialize with preempted symbol(keyword)
  table.insert(std::pair<std::string, int>("SP", 0));
  table.insert(std::pair<std::string, int>("LCL", 1));
  table.insert(std::pair<std::string, int>("ARG", 2));
  table.insert(std::pair<std::string, int>("THIS", 3));
  table.insert(std::pair<std::string, int>("THAT", 4));
  table.insert(std::pair<std::string, int>("SCREEN", 16384));
  table.insert(std::pair<std::string, int>("KBD", 24576));
  

  table.insert(std::pair<std::string, int>("R0",0));
  table.insert(std::pair<std::string, int>("R1",1));
  table.insert(std::pair<std::string, int>("R2",2));
  table.insert(std::pair<std::string, int>("R3",3));
  table.insert(std::pair<std::string, int>("R4",4));
  table.insert(std::pair<std::string, int>("R5",5));
  table.insert(std::pair<std::string, int>("R6",6));
  table.insert(std::pair<std::string, int>("R7",7));
  table.insert(std::pair<std::string, int>("R8",8));
  table.insert(std::pair<std::string, int>("R9",9));
  table.insert(std::pair<std::string, int>("R10",10));
  table.insert(std::pair<std::string, int>("R11",11));
  table.insert(std::pair<std::string, int>("R12",12));
  table.insert(std::pair<std::string, int>("R13",13));
  table.insert(std::pair<std::string, int>("R14",14));
  table.insert(std::pair<std::string, int>("R15",15));

}

Symbol_table::~Symbol_table() {
  table.clear();
}

int Symbol_table::scan_assembly(std::string& input_buffer) {
  // scan asm file and get symbol
  // check @ and () to identify symbol
  // insert the new symbol only.
  std::istringstream input(input_buffer);
  std::string s;

  int line_counter = 0;
  int next_address = 16;

  // use input_buffer string as a string stream
  while(input){
    // get a target string from string stream by a line
    getline(input, s);
    // if the target starts with ( or @, test it.
    if (s.front() == '(') {  
      // label of the ROM memory address
      // erase the ( and )
      s.erase(s.begin());
      s.erase(s.end());

      // existance check
      // doesn's exist, add new content
      auto itr = table.find(s);
      if(itr == table.end()) {  // not an element of the table
        table.insert(std::make_pair(s, line_counter));
      }
      
    }
    else if(s.front() == '@') {
      // A - instructions
      // symbol that indicate a new memory address
      // erase the @
      s.erase(s.begin());

      // existance check
      // doesn's exist, add new content
      auto itr = table.find(s);
      if(itr == table.end()) {  // not an element of the table
        table.insert(std::make_pair(s, next_address));
        ++next_address;
      }

      // increase the line of the number 
      ++line_counter;
    }
    else {
      // C - instructions
      // do nothing, ignore the rest
      ++line_counter;
    }
  }
  return 0;
}