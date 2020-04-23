#include "icmpv4.hpp"

using namespace std;

ICMPv4::ICMPv4(const vector<Byte> &data)
{
    auto begin = data.begin();
    counter=0;
    code = 0;
    type = 0;
    checksum = 0;

    type = *(begin+counter);
    counter++;

    code = *(begin+counter);
    counter++;

    checksum = *(begin+counter)*0x100+*(begin+counter+1);
    counter+=2;
}

string ICMPv4::toString() const
{
    ostringstream result;
    result << "\n"<< "=ICMPv4=" << "\n";
    result << "Tipo: " << dec << type << getTypeName()<<"\n";
    result << "Codigo: " << dec << code << getCodeName()<<"\n";
    result << "Checksum: " << hex << checksum << getCodeName()<<"\n";
    return result.str();
}


string ICMPv4::getCodeName() const
{
    string result=" <";
    switch (code)
    {
     case 0:
        result+= "No se puede llegar a la red";
        break;
    case 1:
        result+= "No se puede llegar al Host";
        break;
    case 2:
        result+= "El destino no dispone del protocolo";
        break;
    case 3:
        result+= "No se puede llegar al puerto destino";
        break;
    case 4:
        result+= "Se necesita aplicar fragmentacion";
        break;
    case 5:
        result+= "La ruta de origen no es correcta";
        break;
    case 6:
        result+= "No se conoce la red destino";
        break;
    case 7:
        result+= "No se conoce host destino";
        break;
    case 8:
        result+= "El host origen esta aislado";
        break;
    case 9:
        result+= "La comunicacion con la red esta prohibida";
        break;
    case 10:
        result+= "La comunicacion con el host esta prohibida";
        break;
    case 11:
        result+= "No se puede llegar a la red";
        break;
    case 12:
        result+= "No se puede llegar al host";
        break;

    default:
        result+= "Desconocido";
    }
    result += ">";
    return result;
}

string ICMPv4::getTypeName() const
{
    string result = " <";
    switch (type)
    {
   case 0:
        result+= "Echo Reply";
        break;
    case 3:
        result+= "Destinaton Unreacheable";
        break;
    case 4:
        result+= "Source Quench";
        break;
    case 5:
        result+= "Redirect";
        break;
    case 8:
        result+= "Echo";
        break;
    case 11:
        result+= "Time Exceeded";
        break;
    case 12:
        result+= "Parameter Problem";
        break;
    case 13:
        result+= "Timestamp";
        break;
    case 14:
        result+= "Timestamp Reply";
        break;
    case 15:
        result+= "Information Request";
        break;
    case 16:
        result+= "Information Replay";
        break;
    case 17:
        result+= "Addressmask";
        break;
    case 18:
        result+= "Addressmask Replay";
        break;
    default:
        result+= "Desconocido";
    }
    result += ">";
    return result;
}