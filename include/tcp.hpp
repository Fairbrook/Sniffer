#ifndef INCLUDE_TCP_H
#define INCLUDE_TCP_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>

#include "protocol.h"
#include "byte.h"

class TCP : public Protocol
{
private:
    int originPort;
    int destinyPort;
    unsigned int secuence;
    unsigned int ack;
    int header;
    bool flags[9];
    int window;
    int checksum;
    int urg;
    int puntero;

    std::vector<Byte> data;

    static std::string getPortName(const int&);

public:
    TCP(){};
    TCP(const std::vector<Byte> &);
    std::string toString() const;
};

#endif