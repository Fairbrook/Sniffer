#ifndef INCLUDE_ICMPV4_H
#define INCLUDE_ICMPV4_H

#include <vector>
#include <math.h>
#include <iostream>
#include <sstream>

#include "byte.h"
#include "protocol.h"

class ICMPv4: public Protocol
{
    private:
        int type;
        int code;
        int checksum;

        std::vector<Byte> data;

        std::string getCodeName()const;
        std::string getTypeName()const;
    public:
        ICMPv4(){};
        ICMPv4(const std::vector<Byte>&);
        std::string toString()const;
};

#endif