// hash table for symbols.
// use symbol as a key and use address as it's value

#ifndef _SYMBOL_TABLE_
#define _SYMBOL_TABLE_

#include <unordered_map>
#include <string>

// wrapper class for symbol table
class Symbol_table {
  private:
  // field
  // hash map
  std::unordered_map<std::string, int> table;

  // start index
  // register symbol will start from 16
  // label symbol will start from line number
  int offset;
  int line_counter;
  
  public: 
  // method
  // constructor
  Symbol_table();

  // destructor
  ~Symbol_table();

  // set
  // set label first and set the variable
  // ignore symbol that already exists in the table
  int set_label(std::string key, int line_number) {
    table.insert(std::pair<std::string, int>(key, line_number));
    return line_number;
  }
  int set_variable(std::string key) {
    table.insert(std::pair<std::string, int>(key, offset));
    return offset++; 
  }

  // get
  int get(std::string key) {
    return table[key];
  }

  // scan and set
  int scan_assembly(std::ifstream& input); 
};

#endif