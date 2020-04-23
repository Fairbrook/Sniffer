#include "ipadd.h"

using namespace std;

IpAdd::IpAdd(const Byte b[4]){
    for(int i=0;i<4;i++){
        data[i]=b[i];
    }
}

IpAdd::IpAdd(const vector<Byte>&v){
    for(int i=0;i<4;i++){
        data[i]=*(v.begin()+i);
    }
}

void IpAdd::fill(const Byte b[4]){
    for(int i=0;i<4;i++){
        data[i]=b[i];
    }
}

void IpAdd::fill(const vector<Byte>&v){
    for(int i=0;i<4;i++){
        data[i]=*(v.begin()+i);
    }
}

IpAdd& IpAdd::operator=(const IpAdd &m){
    fill(m.data);
    return *this;
}

ostream& operator <<(ostream &os, const IpAdd &m){
    for(int i=0;i<4;i++){
        os << dec << m.data[i].toInt();
        if(i<3)os<<".";
    }
    return os;
}