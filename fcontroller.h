#ifndef FCONTROLLER_H_INCLUDED
#define FCONTROLLER_H_INCLUDED

#include <fstream>
#include <iostream>
#include <string>

class FController {
private:
    std::fstream file;
    std::string name;
    int cursor;

public:
    FController(const std::string&);
    unsigned char getNext();
    bool isEOF();
};

#endif // FCONTROLLER_H_INCLUDED
