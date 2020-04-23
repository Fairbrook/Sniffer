#ifndef INCLUDE_PROTOCOL_H
#define INCLUDE_PROTOCOL_H

#include <vector>
#include <string>

#include "byte.h"

class Protocol{
    protected:
        std::string name;
        int counter;

    public:
        Protocol():counter(0),name("Protocolo Desconocido"){};
        Protocol(const std::string&str):counter(0),name(str){};
        Protocol(const std::vector<Byte>&):counter(0),name("Protocolo Desconocido"){};
        virtual std::string toString()const{return name;};
        friend std::ostream& operator<<(std::ostream&, const Protocol&);
        int getCounter()const{return counter;};
};

#endif