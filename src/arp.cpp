#include "arp.hpp"

using namespace std;

ARP::ARP(const vector<Byte>&data){
    auto begin = data.begin();
    counter = 0;
    
    hardwareType = *(begin+counter)*0x100+*(begin+counter+1);
    counter+=2;

    protocol = *(begin+counter)*0x100+*(begin+counter+1);
    counter+=2;

    hardwareDir = *(begin+counter);
    counter++;

    protocolDir = *(begin+counter);
    counter++;

    operationCode = *(begin+counter)*0x100+*(begin+counter+1);
    counter+=2;

    macOrigin = MAC(vector<Byte>(begin+counter,begin+counter+6));
    counter+=6;

    ipOrigin = IpAdd(vector<Byte>(begin+counter,begin+counter+4));
    counter+=4;

    macDestiny = MAC(vector<Byte>(begin+counter,begin+counter+6));
    counter+=6;

    ipDestiny = IpAdd(vector<Byte>(begin+counter,begin+counter+4));
    counter+=4;
}

string ARP::toString()const{
    ostringstream result;
    result << "\n=ARP / RARP=\n";
    result << "Tipo de Hardware: "<<  hardwareType << getHardwareName()<<"\n";
    result << "Protocolo: " << protocol << getProtocolName() << "\n";
    result << "Direccion de Hardware: " << hardwareDir << "\n";
    result << "Direccion de Protocolo: " << protocolDir << "\n";
    result << "Codigo de operacion: " << operationCode << getOperationName() << "\n";
    result << "Direccion MAC Origen: " << macOrigin << "\n";
    result << "Direccion IP Origen: " << ipOrigin << "\n";
    result << "Direccion MAC Destino: " << macDestiny << "\n";
    result << "Direccion IP Destino: " << ipOrigin << "\n";
    return result.str();
}

string ARP::getHardwareName()const{
    string result = " <";
    switch (hardwareType)
    {
    case 1: result+= "Ethernet";break;
    case 6: result+= "IEEE 802";break;
    case 7: result+= "ARCNET";break;
    case 15: result+= "Frame Relay";break;
    case 16: result+= "ATM";break;
    case 17: result+= "HDLC";break;
    case 18: result+= "Fibre Channel";break;
    case 19: result+= "ATM";break;
    case 20: result+= "Serial Line";break;
    
    default:
        result+= "Desconocido";
        break;
    }
    result+=">";
    return result;
}

string ARP::getProtocolName()const{
    string result=" <";
    switch (protocol)
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

string ARP::getOperationName()const{
    string result=" <";
    switch (operationCode)
    {
    case 1: result+= "ARP Request";break;
    case 2: result+= "ARP Reply";break;
    case 3: result+= "RARP Request";break;
    case 4: result+= "RARP Reply";break;
    case 5: result+= "DRARP Request";break;
    case 6: result+= "DRARP Reply";break;
    case 7: result+= "DRARP Error";break;
    case 8: result+= "InARP Request";break;
    case 9: result+= "InARP Reply";break;
    default:
        result+= "Desconocido";
        break;
    }
    result+=">";
    return result;
}