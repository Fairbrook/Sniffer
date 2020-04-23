#include "ipv6add.hpp"

using namespace std;

IPv6Add::IPv6Add(const Byte b[16]){
    for(int i=0;i<16;i++){
        data[i]=b[i];
    }
}

IPv6Add::IPv6Add(const vector<Byte>&v){
    for(int i=0;i<16;i++){
        data[i]=*(v.begin()+i);
    }
}

void IPv6Add::fill(const Byte b[16]){
    for(int i=0;i<16;i++){
        data[i]=b[i];
    }
}

void IPv6Add::fill(const vector<Byte>&v){
    for(int i=0;i<16;i++){
        data[i]=*(v.begin()+i);
    }
}

IPv6Add& IPv6Add::operator=(const IPv6Add &m){
    fill(m.data);
    return *this;
}

ostream& operator <<(ostream &os, const IPv6Add &m){
    for(int i=0;i<16;i++){
        os << m.data[i];
        if(i%2!=0 and i<15)os<<":";
    }
    return os;
}