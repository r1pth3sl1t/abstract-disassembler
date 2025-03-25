#ifndef LAB3_JUMPIFLESSINSTRUCTION_H
#define LAB3_JUMPIFLESSINSTRUCTION_H


#include "AbstractInstructionDecoder.h"

class JumpIfLessInstruction : public AbstractInstructionDecoder {
public:
    ~JumpIfLessInstruction() override = default;
    virtual std::byte decode(Reader &reader, std::byte opcode, std::stringstream &byteStream, std::stringstream &asmStream) const override;
};


#endif //LAB3_JUMPIFLESSINSTRUCTION_H
