#ifndef INCLUDE_ARP_H
#define INCLUDE_ARP_H

#include <vector>
#include <math.h>
#include <iostream>
#include <sstream>

#include "byte.h"
#include "protocol.h"
#include "mac.h"
#include "ipadd.h"

class ARP: public Protocol
{
    private:
        int hardwareType;
        int protocol;
        Byte hardwareDir;
        Byte protocolDir;
        int operationCode;

        MAC macOrigin;
        MAC macDestiny;

        IpAdd ipOrigin;
        IpAdd ipDestiny;

        std::vector<Byte> data;

        std::string getHardwareName()const;
        std::string getProtocolName()const;
        std::string getOperationName()const;
    public:
        ARP(){};
        ARP(const std::vector<Byte>&);
        std::string toString()const;
};

#endif