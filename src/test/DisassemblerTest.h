#ifndef LAB3_DISASSEMBLERTEST_H
#define LAB3_DISASSEMBLERTEST_H

#include <vector>
#include <cassert>
#include <functional>
#include "../Disassembler.h"
#include <iostream>
#define TEST_DECLARATION(NAME) void NAME();                                                                                         \
    struct NAME##registerTest {                                                                                                     \
        NAME##registerTest()  { DisassemblerTest::instance().registerFunction(#NAME, [=](){DisassemblerTest::instance().NAME();});} \
    } NAME##RegisterTestInstance;

#define TEST_DEFINITION(NAME) void DisassemblerTest::NAME()

#define ASSERT_EQUALS(actual, expected, input) std::cout << "For input '" << input << "' ";         \
if ((actual) == (expected)) {                                                                       \
    std::cout << "Passed" << std::endl;                                                             \
} else {                                                                                            \
    std::cout << "Failed: expected '" << expected << "' and got '" << actual << '\'' << std::endl;  \
    }

#define ASSERT_THROWS(result, input) {bool caught = false; try {        \
    (result);                                                           \
    } catch(std::runtime_error &e) {                                    \
    caught = true;}                                                     \
    std::cout << "For input '" << input << "' ";                        \
    if (caught) {                                                       \
        std::cout << "Passed" << std::endl;                             \
    } else {                                                            \
    std::cout << "Failed: expected throwing of exception" << std::endl; \
    } }


class DisassemblerTest {
    static DisassemblerTest disassemblerTest;
    struct TestFunction{
        std::string name;
        std::function<void()> function;
    };
    std::vector<TestFunction> testFunctions;
    static std::string test(const std::string &code);

public:
    void registerFunction(std::string name, std::function<void()> function);
    DisassemblerTest() = default;
    void runAll();
    static DisassemblerTest& instance();
    TEST_DECLARATION(mov);
    TEST_DECLARATION(sub);
    TEST_DECLARATION(jl);
    TEST_DECLARATION(cmp);
    TEST_DECLARATION(invalidOpcode);
};

#endif
