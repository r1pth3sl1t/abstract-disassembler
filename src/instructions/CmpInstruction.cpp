#include "CmpInstruction.h"
#include <sstream>

using Util = AbstractInstructionDecoder::AbstractInstructionDecoderUtils;

std::byte CmpInstruction::decode(Reader &reader, std::byte opcode, std::stringstream &byteStream,
                                 std::stringstream &asmStream) const {
    asmStream << "CMP ";
    Util::regToReg(reader, byteStream, asmStream);
    return std::byte{reader.nextByte()};
}
