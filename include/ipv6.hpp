#ifndef INCLUDE_IPV6_H
#define INCLUDE_IPV6_H

#include <vector>
#include <math.h>
#include <iostream>
#include <sstream>

#include "byte.h"
#include "protocol.h"
#include "ipv6add.hpp"
#include "icmpv4.hpp"
#include "icmpv6.hpp"

class IPv6: public Protocol
{
    private:
        int version;
        int priority;
        bool retard;
        bool performance;
        bool reliable;
        int streamTag;
        int lenght;
        Byte type;
        Byte jumpLimit;

        IPv6Add origin;
        IPv6Add destiny;
        Protocol *protocol;

        std::vector<Byte> data;

        std::string getPriorityName()const;
        std::string getTypeName()const;
    public:
        IPv6():protocol(){};
        IPv6(const std::vector<Byte>&);
        std::string toString()const;
};

#endif