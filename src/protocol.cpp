#include "protocol.h"

using namespace std;

ostream& operator<<(ostream&os,const Protocol&p){
    os << p.toString();
    return os;
}