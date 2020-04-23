#include "byte.h"

std::ostream &operator<<(std::ostream &os, const Byte &b)
{
    os  << std::setw(2) 
        << std::setfill('0') 
        << std::hex 
        << std::uppercase
        << (int)b.data;
    return os;
}

Byte& Byte::operator=(const Byte &b)
{
    this->data = b.data;
    return *this;
}
bool Byte::operator[](const int &i)const
{
    int help = 1;
    int counter = i;
    while (counter > 0)
    {
        help *= 2;
        counter--;
    }
    return (data & help);
}
bool Byte::operator==(const int &d) const { return data == d; }
bool Byte::operator==(const Byte &d) const { return data == d.data; }
int Byte::operator*(const int &d) const { return data * d; }
Byte Byte::operator*(const Byte &d) const { return data * d.data; }
int Byte::operator+(const int &d) const { return data + d; }
Byte Byte::operator+(const Byte &d) const { return data + d.data; }
Byte::operator int() const { return int(data); }
int Byte::toInt()const{return int(data);}