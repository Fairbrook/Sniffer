#ifndef INCLUDE_UDP_H
#define INCLUDE_UDP_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>

#include "protocol.h"
#include "byte.h"
#include "dns.hpp"

class UDP : public Protocol
{
private:
    int originPort;
    int destinyPort;
    unsigned int lenght;
    int checksum;
    Protocol* protocol;

    std::vector<Byte> data;

    static std::string getPortName(const int&);

public:
    UDP(){};
    UDP(const std::vector<Byte> &);
    std::string toString() const;
};

#endif