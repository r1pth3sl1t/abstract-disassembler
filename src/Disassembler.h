#ifndef LAB3_DISASSEMBLER_H
#define LAB3_DISASSEMBLER_H
#include <memory>
#include <map>
#include "Reader.h"
#include "instructions/AbstractInstructionDecoder.h"

class Disassembler {
    Reader reader;
    bool format;
    std::ostream &ostream;
    std::map<std::byte, std::shared_ptr<AbstractInstructionDecoder>> opcodes;
public:
    explicit Disassembler(Reader &reader, std::ostream &ostream, bool format = true);

    void disassemble();
};


#endif //LAB3_DISASSEMBLER_H
