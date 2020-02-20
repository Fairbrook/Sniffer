#ifndef Byte_H_INCLUDED
#define Byte_H_INCLUDED

#include <iostream>
#include <iomanip>

class Byte{
protected:
    unsigned char data;

public:
    Byte();
    Byte(const unsigned char &d):data(d){}
    Byte(const Byte&b):data(b.data){}

    unsigned char getData(){return data;}

    Byte& operator=(const Byte&);
    bool operator[](const int&);
    bool operator==(const int&);
    int operator*(const int&);
    int operator+(const int&);
    friend std::ostream& operator << (std::ostream& os, const Byte &b);
};

#endif // Byte_H_INCLUDED
