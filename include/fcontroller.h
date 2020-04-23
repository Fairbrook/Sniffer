#ifndef FCONTROLLER_H_INCLUDED
#define FCONTROLLER_H_INCLUDED

#include <fstream>
#include <iostream>
#include <string>

#include "byte.h"

class FController {
private:
    std::fstream file;
    std::string name;
    int cursor;

public:
    FController(const std::string&);
    Byte getNext();
    bool isEOF();
    int getLenght();
    static bool isFile(const std::string&);
};

#endif // FCONTROLLER_H_INCLUDED
