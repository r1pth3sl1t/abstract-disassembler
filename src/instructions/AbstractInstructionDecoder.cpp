#include "AbstractInstructionDecoder.h"
#include <sstream>
#include <iomanip>

using Util = AbstractInstructionDecoder::AbstractInstructionDecoderUtils;

void Util::regToReg(Reader &reader, std::stringstream &byteStream, std::stringstream &asmStream) {
    std::byte byte;
    std::string reg;
    byte = reader.nextByte();
    Util::pushByte(byteStream, byte);
    reg = Util::byteToRegister((byte & std::byte{0xf0}) >> 4);
    asmStream << reg << ", ";
    reg = Util::byteToRegister(byte & std::byte{0xf});
    asmStream << reg;
}

std::string Util::byteToRegister(std::byte byte) {
    return "R" + std::to_string(std::to_integer<int>(byte));
}

std::string Util::resolveMultiByteValue(std::ostream &byteStream, Reader &reader, std::byte &byte, int bytesSize) {
    int addr = 0;
    byte = reader.nextByte();
    for (int i = bytesSize - 1; i >= 0; i--, byte = reader.nextByte()) {
        if (byte == std::byte{0xff})
            if (reader.eof())
                throw std::runtime_error("Unexpected EOF");
        addr = addr | (std::to_integer<int>(byte) << (i * 8));
        pushByte(byteStream, byte);
    }

    std::stringstream ss;
    ss << "0x";
    ss << std::uppercase << std::hex << std::setw(bytesSize << 1) << std::setfill('0') << addr;
    return ss.str();
}

void AbstractInstructionDecoder::AbstractInstructionDecoderUtils::pushByte(std::ostream &byteStream, std::byte byte) {
    byteStream << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << std::to_integer<int>(byte) << " ";
}
