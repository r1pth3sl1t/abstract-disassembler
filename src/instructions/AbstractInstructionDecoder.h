#ifndef LAB3_ABSTRACTINSTRUCTIONDECODER_H
#define LAB3_ABSTRACTINSTRUCTIONDECODER_H


#include "../Reader.h"


class AbstractInstructionDecoder {
public:
    class AbstractInstructionDecoderUtils {
    public:
        static void regToReg(Reader &reader, std::stringstream &byteStream, std::stringstream &asmStream);
        static std::string byteToRegister(std::byte byte);
        static std::string resolveMultiByteValue(std::ostream &byteStream, Reader &reader, std::byte &byte, int bytesSize = 4);
        static void pushByte(std::ostream &byteStream, std::byte byte);
    };
    virtual ~AbstractInstructionDecoder() = default;
    virtual std::byte decode(Reader &reader, std::byte opcode, std::stringstream &byteStream, std::stringstream &asmStream) const = 0;
};



#endif //LAB3_ABSTRACTINSTRUCTIONDECODER_H
