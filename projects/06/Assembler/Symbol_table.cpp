#include <fstream>
#include "Symbol_table.h"
  
Symbol_table::Symbol_table() : offset(16), line_counter(0)  {

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

int Symbol_table::scan_assembly(std::ifstream& input) {
  // scan asm file and get symbol

}