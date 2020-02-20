#include "byte.h"

std::ostream& operator << (std::ostream& os, const Byte &b){
    os << std::setw(2) << std::setfill('0') << std::hex << (int)b.data;
    return os;
}

Byte& Byte::operator=(const Byte& b){this->data = b.data; return *this;}
bool Byte::operator[](const int&i){
    int help = 1;
    int counter = i;
    while(counter>0){
        help *= 2;
        counter--;
    }
    return (data & help);
}
bool Byte::operator == (const int&d){return data==d;}
int Byte::operator*(const int&d){return data*d;}
int Byte::operator+(const int&d){return data+d;}