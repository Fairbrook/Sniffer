#ifndef INCLUDE_ICMPV6_H
#define INCLUDE_ICMPV6_H

#include <vector>
#include <math.h>
#include <iostream>
#include <sstream>

#include "byte.h"
#include "protocol.h"

class ICMPv6: public Protocol
{
    private:
        int type;
        int code;
        int checksum;

        std::vector<Byte> data;

        std::string getCodeName()const;
        std::string getTypeName()const;
    public:
        ICMPv6(){};
        ICMPv6(const std::vector<Byte>&);
        std::string toString()const;
};

#endif