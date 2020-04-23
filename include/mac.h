#ifndef INCLUDE_MAC_H
#define INCLUDE_MAC_H

#include <vector>

#include "byte.h"

class MAC{
    private:
        Byte data[6];

    public:
        MAC(){};
        MAC(const Byte[6]);
        MAC(const std::vector<Byte>&);
        void fill(const Byte[6]);
        void fill(const std::vector<Byte>&);
        MAC& operator=(const MAC&);
        friend std::ostream& operator << (std::ostream&, const MAC&);
};

#endif