#include <sstream>
#include <utility>
#include <iostream>
#include "DisassemblerTest.h"

DisassemblerTest DisassemblerTest::disassemblerTest;

std::string DisassemblerTest::test(const std::string &code){
    std::stringstream source(code), dest;
    Reader reader(source);
    Disassembler disassembler(reader, dest, false);
    disassembler.disassemble();
    return dest.str();
}

DisassemblerTest& DisassemblerTest::instance() {
    return DisassemblerTest::disassemblerTest;
}

void DisassemblerTest::registerFunction(std::string name, std::function<void()> function) {
    testFunctions.push_back({std::move(name), std::move(function)});
}

TEST_DEFINITION(mov) {
    //true tests
    ASSERT_EQUALS(test("1A 84"), "MOV R8, R4", "1A 84");
    ASSERT_EQUALS(test("1B 01 00 00 2F 01"), "MOV R1, [0x00002F01]", "1B 01 00 00 2F 01");
    ASSERT_EQUALS(test("1B 11 00 00 2F 01"), "MOV [0x00002F01], R1", "1B 11 00 00 2F 01");
    ASSERT_EQUALS(test("1C 04 C1"), "MOV R4, -63", "1C 04 C1");
    //false tests
    ASSERT_THROWS(test("1B 01 00 2F 01"), "1B 01 00 2F 01"); // 3 byte address instead of 4
    ASSERT_THROWS(test("1C 14 C1"), "1C 14 C1"); // invalid reg code
    ASSERT_THROWS(test("1C 14"), "1C 14"); // not enough bytes to decode
}

TEST_DEFINITION(sub) {
    //true tests
    ASSERT_EQUALS(test("0A 04"), "SUB R0, R4", "0A 04");
    ASSERT_EQUALS(test("0A 34"), "SUB R3, R4", "0A 34");
    ASSERT_EQUALS(test("0B 01 00 00 00 42"), "SUB R1, [0x00000042]", "0B 01 00 00 00 42");
    //false tests
    ASSERT_THROWS(test("0B 51 00 00 00 42"), "0B 51 00 00 00 42"); // invalid reg code
    ASSERT_THROWS(test("0B 01 00 00 42"), "0B 01 00 00 42"); // 3 byte address instead of 4
}

TEST_DEFINITION(jl) {
    //true tests
    ASSERT_EQUALS(test("92 F1"), "JL [0xF1]", "92 F1");
    ASSERT_EQUALS(test("93 00 00 C1 F1"), "JL [0x0000C1F1]", "93 00 00 C1 F1");
    //false tests
    ASSERT_THROWS(test("93 00 00 C1"), "93 00 00 C1"); // 3 byte relative address instead of 4
    ASSERT_THROWS(test("92 F1 C2"), "92 F1 C2"); // too many bytes while C2 is not an opcode of next instruction
}

TEST_DEFINITION(cmp) {
    //true tests
    ASSERT_EQUALS(test("80 C1"), "CMP R12, R1", "80 C1");
    ASSERT_EQUALS(test("80 A3"), "CMP R10, R3", "80 A3");
    ASSERT_EQUALS(test("80 00"), "CMP R0, R0", "80 00");
}

TEST_DEFINITION(invalidOpcode) {
    ASSERT_THROWS(test("AF 01"), "AF 01");
}

void DisassemblerTest::runAll() {
    for(auto &test : testFunctions) {
        std::cout << test.name << ": " << std::endl;
        test.function();
    }
}
