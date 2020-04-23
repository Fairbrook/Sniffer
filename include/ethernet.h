#ifndef INCLUDE_ETHERNET_H
#define INCLUDE_ETHERNET_H

#include <vector>
#include <string>

#include "byte.h"
#include "mac.h"
#include "protocol.h"
#include "ipv4.h"
#include "arp.hpp"
#include "ipv6.hpp"

class Ethernet{
    private:
        MAC from;
        MAC to;
        int type;
        Protocol *protocol;
        int counter;
        std::string getTypeName()const;
        std::vector<Byte> data;

    public:
        Ethernet(){};
        Ethernet(const std::vector<Byte>&);

        MAC getFrom()const{return from;};
        MAC getTo()const{return to;};
        int getType()const{return type;};

        void setFrom(const MAC &f){from=f;};
        void setTo(const MAC &t){to=t;};
        void setType(const int &t){type=t;};
        friend std::ostream& operator<<(std::ostream&,const Ethernet&);

};

#endif