#include "JumpIfLessInstruction.h"
#include <sstream>

using Util = AbstractInstructionDecoder::AbstractInstructionDecoderUtils;

std::byte JumpIfLessInstruction::decode(Reader &reader, std::byte opcode, std::stringstream &byteStream,
                                        std::stringstream &asmStream) const {
    std::byte byte;
    std::string addr;
    asmStream << "JL ";
    int addrSize = 1;
    switch (std::to_integer<int>(opcode)) {
        case 0x92:
            addrSize = 1;
            break;
        case 0x93:
            addrSize = 4;
            break;
    }
    addr = Util::resolveMultiByteValue(byteStream, reader, byte, addrSize);
    asmStream << "[" << addr << "]";
    return byte;
}
