#include "JumpIfLessInstruction.h"
#include <sstream>
#include <cstdint>

using Util = AbstractInstructionDecoder::AbstractInstructionDecoderUtils;

std::byte JumpIfLessInstruction::decode(Reader &reader, std::byte opcode, std::stringstream &byteStream,
                                        std::stringstream &asmStream) const {
    std::byte byte;
    std::string addr;
    asmStream << "JL ";
    int addrSize = 1;
    switch (std::to_integer<int>(opcode)) {
        case 0x92:
            byte = reader.nextByte();
            Util::pushByte(byteStream, byte);
            addr = std::to_string(int(std::to_integer<int8_t>(byte)));
            asmStream << addr;
            Util::pushByte(byteStream, byte);
            byte = reader.nextByte();
            return byte;
        case 0x93:
            addr = Util::resolveMultiByteValue(byteStream, reader, byte);
            asmStream << "[" << addr << "]";
            return byte;
    }

    return byte;
}
