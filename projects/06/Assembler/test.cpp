
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

int main()
{
    std::cout << "This is a test case." << std::endl;

    std::cout << "===== file reading =======" << std::endl;
    std::string test_subject;
    std::ifstream test_file("../add/Add.asm");
    if (test_file.is_open())
    {
        test_file.seekg(0, std::ios::end);   // move cursor to the end
        int buffer_size = test_file.tellg(); // get size of the file
        test_subject.resize(buffer_size);

        test_file.seekg(0, std::ios::beg);             // move cursor to start
        test_file.read(&test_subject[0], buffer_size); // read all and save
    }
    std::cout << test_subject << std::endl;
    /*
    std::string test_subject =
        "// This file is part of www.nand2tetris.org\n // and the book The Elements of Computing Systems\n // by Nisan and Schocken, MIT Press.\n // File name: projects/06/add/Add.asm\n \n // Computes R0 = 2 + 3  (R0 refers to RAM[0])\n \n @2\n D = A\n @3\n D = D + A\n @0\n M = D";
    */
    std::cout << "===== erase spaces =======" << std::endl;
    erase_space(test_subject);
    std::cout << test_subject << std::endl;
    std::cout << "=== erase back spaces ====" << std::endl;
    erase_back_space(test_subject);
    std::cout << test_subject << std::endl;
    std::cout << "===== erase tab ==========" << std::endl;
    erase_tab(test_subject);
    std::cout << test_subject << std::endl;
    std::cout << "===== erase tab2 =========" << std::endl;
    erase_tab2(test_subject);
    std::cout << test_subject << std::endl;
    std::cout << "===== erase FF ===========" << std::endl;
    erase_Form_Feed(test_subject);
    std::cout << test_subject << std::endl;
    std::cout << "===== erase comments =====" << std::endl;
    erase_comment(test_subject);
    std::cout << test_subject << std::endl;
    std::cout << "==== erase carriage ======" << std::endl;
    erase_carriage(test_subject);
    std::cout << test_subject << std::endl;
    std::cout << "===== erase EOL ==========" << std::endl;
    erase_EOL(test_subject);
    std::cout << test_subject << std::endl;
    std::cout << "===== Translate ==========" << std::endl;
    Symbol_table symtable;
    Hack_Code_module test_obj;
    std::deque<std::string> test_buffer;
    test_obj.mnemonic_to_code(test_subject, test_buffer, symtable);
    for (const auto &elem : test_buffer)
    {
        std::cout << elem << std::endl;
    }

    std::cout << "==========================" << std::endl;
    char c;
    for (int i = 1; i < 5; i++)
    {
        if ((c = *(test_subject.end() - i)) == '\n')
        {
            std::cout << "true, " << i << std::endl;
        }
        else
        {
            std::cout << "false, " << c << std::endl;
        }
    }
}
