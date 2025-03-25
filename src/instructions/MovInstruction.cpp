#include "MovInstruction.h"
#include <sstream>
#include <iostream>
#include <cstdint>

using Util = AbstractInstructionDecoder::AbstractInstructionDecoderUtils;

std::byte MovInstruction::decode(Reader &reader, std::byte opcode, std::stringstream &byteStream,
                            std::stringstream &asmStream) const {
    std::byte byte;
    std::string reg, addr;
    int imm8;
    bool memToReg;
    asmStream << "MOV ";
    switch (std::to_integer<int>(opcode)) {
        case 0x1a:
            Util::regToReg(reader, byteStream, asmStream);
            return reader.nextByte();
        case 0x1b:
            byte = reader.nextByte();
            Util::pushByte(byteStream, byte);
            reg = Util::byteToRegister(byte & std::byte{0xf});
            memToReg = static_cast<bool>(byte & std::byte{0xf0});
            addr = Util::resolveMultiByteValue(byteStream, reader, byte);
            if (memToReg) {
                asmStream << '[' << addr << ']' << ", ";
                asmStream << reg;
            }
            else {
                asmStream << reg << ", ";
                asmStream << '[' << addr << ']';
            }
            return byte;

        case 0x1c:
            byte = reader.nextByte();
            Util::pushByte(byteStream, byte);
            if (static_cast<bool>(byte & std::byte{0xf0}))
                throw std::runtime_error("Invalid reg code");
            reg = Util::byteToRegister(byte & std::byte{0xf});
            byte = reader.nextByte();
            imm8 = int(std::to_integer<int8_t>(byte));
            Util::pushByte(byteStream, byte);
            byte = reader.nextByte();
            asmStream << reg << ", ";
            asmStream << imm8;
            return byte;
        default:
            return std::byte{0xff};
    }

}
