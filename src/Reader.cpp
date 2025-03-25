#include <sstream>
#include <iostream>
#include "Reader.h"

Reader::Reader(std::istream &_file) : file(_file) {

}

std::byte Reader::nextByte() {
    int result;
    std::string str;
    file >> str;

    if (str.empty()) return std::byte{0xff};
    std::stringstream ss;
    ss << std::hex << str;
    ss >> result;

    return std::byte(result);
}

bool Reader::eof() const {
    return file.eof();
}

