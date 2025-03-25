#ifndef LAB3_MOVINSTRUCTION_H
#define LAB3_MOVINSTRUCTION_H


#include "AbstractInstructionDecoder.h"

class MovInstruction : public AbstractInstructionDecoder {
public:
    ~MovInstruction() override = default;
    std::byte decode(Reader &reader, std::byte opcode, std::stringstream &byteStream, std::stringstream &asmStream) const override;
};


#endif //LAB3_MOVINSTRUCTION_H
