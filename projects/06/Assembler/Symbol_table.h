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

  public: 
  // method
  // constructor
  Symbol_table();

  // destructor
  ~Symbol_table();

  // get
  int get(std::string key) {
    if(table.find(key) == table.end()) {
      return -1;
    }
    else{
      return table[key];
    }
  }

  // scan and set
  int scan_assembly(std::string& input); 
};

#endif