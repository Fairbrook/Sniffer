#ifndef INCLUDE_IPv6Add_H
#define INCLUDE_IPv6Add_H

#include <vector>

#include "byte.h"

class IPv6Add{
    private:
        Byte data[16];
    
    public:
        IPv6Add(){};
        IPv6Add(const Byte[16]);
        IPv6Add(const std::vector<Byte>&);
        void fill(const Byte[16]);
        void fill(const std::vector<Byte>&);
        IPv6Add& operator=(const IPv6Add&);
        friend std::ostream& operator << (std::ostream&, const IPv6Add&);

};

#endif