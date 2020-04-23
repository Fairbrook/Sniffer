#include "ethernet.h"

using namespace std;

Ethernet::Ethernet(const vector<Byte> &data){
    auto begin = data.begin();
    counter=0;
    to = MAC(vector<Byte>(begin+counter,begin+counter+6));
    counter+=6;
    from = MAC(vector<Byte>(begin+counter,begin+counter+6));
    counter+=6;
    type = *(begin+counter)*0x100+*(begin+counter+1);
    counter+=2;
    switch (type)
    {
    case 0x0800:
        protocol= new IPv4(vector<Byte>(begin+counter,data.end()));
        break;
    case 0x0806:
        protocol= new ARP(vector<Byte>(begin+counter,data.end()));
        break;
    // case 0x8035:
    //     protocol="RARP";
    //     break;
    case 0x86DD:
        protocol= new IPv6(vector<Byte>(begin+counter,data.end()));
        break;
    default:
        protocol = new Protocol("");
        break;
    }
    counter+=protocol->getCounter();
    this->data = vector<Byte>(begin+counter,data.end());
}

std::ostream& operator<<(std::ostream &os,const Ethernet &e){
    os << "\n==Cabecera Ethernet==\n";
    os << "Direccion Mac Destino: " << e.to << "\n";
    os << "Direccion Mac Origen: " << e.from << "\n";
    os << "Tipo: " << hex << setfill('0')<<setw(4) <<e.type << e.getTypeName()<<"\n\n";
    os << *(e.protocol);
    os<< "\n==Datos==\n";
    for(auto i=e.data.begin();i!=e.data.end();i++){
        os << *i << " ";
    }
    os<<endl;
    return os;
}

string Ethernet::getTypeName()const{
    string result=" <";
    switch (type)
    {
    case 0x0800:
        result+="IPv4";
        break;
    case 0x0806:
        result+="ARP";
        break;
    case 0x8035:
        result+="RARP";
        break;
    case 0x86DD:
        result+="IPv6";
        break;
    }
    result+=">";
    return result;
}