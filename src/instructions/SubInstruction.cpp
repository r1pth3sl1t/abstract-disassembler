#include "SubInstruction.h"
#include <sstream>

using Util = AbstractInstructionDecoder::AbstractInstructionDecoderUtils;

std::byte SubInstruction::decode(Reader &reader, std::byte opcode, std::stringstream &byteStream,
                                 std::stringstream &asmStream) const {
    std::string reg, addr;
    std::byte byte;
    asmStream << "SUB ";
    switch (std::to_integer<int>(opcode)) {
        case 0x0a:
            Util::regToReg(reader, byteStream, asmStream);
            return std::byte{reader.nextByte()};
        case 0x0b:
            byte = reader.nextByte();
            if (static_cast<bool>(byte & std::byte{0xf0})) {
                throw std::runtime_error("Invalid reg code");
            }
            reg = Util::byteToRegister(byte);
            Util::pushByte(byteStream, byte);
            addr = Util::resolveMultiByteValue(byteStream, reader, byte);
            asmStream << reg << ", [" << addr << "]";
            return byte;

    }
    return std::byte{0xff};
}
