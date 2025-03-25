#include <iostream>
#include "Reader.h"
#include "Disassembler.h"
#include "test/DisassemblerTest.h"
#define TEST

int main() {
#ifdef TEST
    DisassemblerTest::instance().runAll();
#endif
#ifndef TEST
    std::ifstream file("../bin.txt");
    Reader reader(file);
    Disassembler disassembler(reader, std::cout);
    try {
        disassembler.disassemble();
    }
    catch (std::runtime_error &e) {
        std::cerr << e.what();
    }
#endif
    return 0;
}
