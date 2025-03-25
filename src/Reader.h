#ifndef LAB3_READER_H
#define LAB3_READER_H


#include <fstream>

class Reader {
    std::istream &file;
public:
    explicit Reader(std::istream &file);
    bool eof() const;
    std::byte nextByte();
};


#endif //LAB3_READER_H
