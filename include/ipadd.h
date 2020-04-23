#ifndef INCLUDE_IPADD_H
#define INCLUDE_IPADD_H

#include <vector>

#include "byte.h"

class IpAdd{
    private:
        Byte data[4];
    
    public:
        IpAdd(){};
        IpAdd(const Byte[4]);
        IpAdd(const std::vector<Byte>&);
        void fill(const Byte[4]);
        void fill(const std::vector<Byte>&);
        IpAdd& operator=(const IpAdd&);
        friend std::ostream& operator << (std::ostream&, const IpAdd&);

};

#endif