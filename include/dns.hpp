#ifndef INCLUDE_DNS_H
#define INCLUDE_DNS_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>

#include "protocol.h"
#include "byte.h"

class DNS : public Protocol
{
private:
    unsigned int id;
    int op;
    int rcode;
    bool flags[8];
    unsigned int QDCount;
    unsigned int ANCount;
    unsigned int NSCount;
    unsigned int ARCount;
    int checksum;

    std::vector<Byte> data;

    static std::string getRCode(const int&);
    static std::string getOpCode(const int&);

public:
    DNS(){};
    DNS(const std::vector<Byte> &);
    std::string toString() const;
};

#endif