#include "mac.h"

using namespace std;

MAC::MAC(const Byte b[6]){
    for(int i=0;i<6;i++){
        data[i]=b[i];
    }
}

MAC::MAC(const vector<Byte> &v){
    for(int i=0;i<6;i++){
        data[i]=*(v.begin()+i);
    }
}

void MAC::fill(const Byte b[6]){
    for(int i=0;i<6;i++){
        data[i]=b[i];
    }
}

void MAC::fill(const vector<Byte>&v){
    for(int i=0;i<6;i++){
        data[i]=*(v.begin()+i);
    }
}

MAC& MAC::operator=(const MAC &m){
    fill(m.data);
    return *this;
}

ostream& operator <<(ostream &os, const MAC &m){
    for(int i=0;i<6;i++){
        os << m.data[i];
        if(i<5)os<<":";
    }
    return os;
}