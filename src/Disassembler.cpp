#include <iostream>
#include <sstream>
#include "Disassembler.h"
#include "instructions/MovInstruction.h"
#include "instructions/SubInstruction.h"
#include "instructions/JumpIfLessInstruction.h"
#include "instructions/CmpInstruction.h"

Disassembler::Disassembler(Reader &_reader, std::ostream &_ostream, bool _format) : reader(_reader), ostream(_ostream),
format(_format) {
    opcodes[std::byte{0x1a}] = std::make_shared<MovInstruction>();
    opcodes[std::byte{0x1b}] = opcodes[std::byte{0x1a}];
    opcodes[std::byte{0x1c}] = opcodes[std::byte{0x1a}];

    opcodes[std::byte{0x0a}] = std::make_shared<SubInstruction>();
    opcodes[std::byte{0x0b}] = opcodes[std::byte{0x0a}];

    opcodes[std::byte{0x92}] = std::make_shared<JumpIfLessInstruction>();
    opcodes[std::byte{0x93}] = opcodes[std::byte{0x92}];

    opcodes[std::byte{0x80}] = std::make_shared<CmpInstruction>();
}

void Disassembler::disassemble() {
    std::byte byte = reader.nextByte();
    while (byte != std::byte{0xff}) {
        std::string reg;
        std::string addr;
        std::stringstream byteStream, asmStream;
        AbstractInstructionDecoder::AbstractInstructionDecoderUtils::pushByte(byteStream, byte);
        if (std::to_integer<int>(byte) == 0xff) return;
        std::shared_ptr<AbstractInstructionDecoder> instruction = opcodes[byte];
        if (!instruction)
            throw std::runtime_error("Unresolved opcode " + std::to_string(std::to_integer<int>(byte)));
        byte = instruction->decode(reader, byte, byteStream, asmStream);
        if (format) {
            ostream << byteStream.str() << ":" << std::endl;
            ostream << asmStream.str() << std::endl << std::endl;
        }
        else ostream << asmStream.str();
    }
}





