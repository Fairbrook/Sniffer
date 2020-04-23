#ifndef INCLUDE_IPV4_H
#define INCLUDE_IPV4_H

#include <vector>
#include <math.h>
#include <iostream>
#include <sstream>

#include "byte.h"
#include "protocol.h"
#include "ipadd.h"
#include "icmpv4.hpp"

class IPv4: public Protocol
{
    private:
        int version;
        int words;
        int priority;
        bool retard;
        bool performance;
        bool reliable;
        int lenght;
        int id;
        bool div;
        bool frag;
        int pos;
        int lifetime;
        int type;
        int checksum;
        IpAdd origin;
        IpAdd destiny;
        Protocol *protocol;

        std::vector<Byte> data;

        std::string getPriorityName()const;
        std::string getTypeName()const;
    public:
        IPv4():protocol(){};
        IPv4(const std::vector<Byte>&);
        std::string toString()const;
};

#endif