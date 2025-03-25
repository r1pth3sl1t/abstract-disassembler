#ifndef LAB3_SUBINSTRUCTION_H
#define LAB3_SUBINSTRUCTION_H


#include "AbstractInstructionDecoder.h"

class SubInstruction : public AbstractInstructionDecoder {
public:
    ~SubInstruction() override = default;
    virtual std::byte decode(Reader &reader, std::byte opcode, std::stringstream &byteStream, std::stringstream &asmStream) const override;
};


#endif //LAB3_SUBINSTRUCTION_H
