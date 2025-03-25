#ifndef LAB3_CMPINSTRUCTION_H
#define LAB3_CMPINSTRUCTION_H


#include "AbstractInstructionDecoder.h"

class CmpInstruction : public AbstractInstructionDecoder {
public:
    ~CmpInstruction() override = default;
    virtual std::byte decode(Reader &reader, std::byte opcode, std::stringstream &byteStream, std::stringstream &asmStream) const override;
};


#endif //LAB3_CMPINSTRUCTION_H
