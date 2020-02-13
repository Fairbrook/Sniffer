#include "byte.h"

std::ostream& operator << (std::ostream& os, const Byte &b){
    os << std::setw(2) << std::setfill('0') << std::hex << (int)b.data;
    return os;
}

bool Byte::operator == (const int&d){return data==d;}
