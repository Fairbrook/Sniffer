#include "ipv4.h"

using namespace std;

IPv4::IPv4(const vector<Byte>&data):protocol(){
    auto begin = data.begin();
    Byte aux = *begin;

    counter = 1;
    version=0;
    words=0;
    priority=0;
    pos=0;

    for (int i = 4; i <= 7; i++)
        version += aux[i] * pow(2, (i - 4));
    
    for (int i = 0; i <= 3; i++)
        words += aux[i] * pow(2, i);

    aux = *(begin+counter);
    counter++;

    for (int i = 0; i <= 2; i++)
        priority += aux[i] * pow(2, i);

    retard = aux[3];
    performance = aux[4];
    reliable = aux[5];
    
    lenght = *(begin+counter)*0x100+*(begin+counter+1);
    counter+=2;

    id = *(begin+counter)*0x100+*(begin+counter+1);
    counter+=2;

    aux = *(begin+counter);
    counter++;

    div = aux[6];
    frag = aux[5];

    for (int i = 0; i <= 4; i++)
        pos += aux[i] * pow(2, i + 8);
    pos += *(begin+counter);
    counter++;

    lifetime = *(begin+counter);
    counter++;

    type = *(begin+counter);
    counter++;


    checksum = *(begin+counter)*0x100+*(begin+counter+1);
    counter+=2;

    origin = IpAdd(vector<Byte>(begin+counter,begin+counter+4));
    counter+=4;

    destiny = IpAdd(vector<Byte>(begin+counter,begin+counter+4));
    counter+=4;

    switch (type)
    {
    case 1:
        protocol= new ICMPv4(vector<Byte>(begin+counter,data.end()));
        break;
        
    default:
        protocol = new Protocol("");
        break;
    }

    counter+=protocol->getCounter();
    this->data = vector<Byte>(begin+counter,data.end());
}

string IPv4::toString()const{
    ostringstream result;
    result << "\n==Cabecera IPv4==\n";
    result <<"Version: "<<version<<"\n";
    result <<"Cabecera: "<<words<<" palabras"<<"\n";
    result <<"Prioridad: "<<priority <<getPriorityName()<<"\n";
    result <<"Retardo: "<<((retard)?"Alto":"Normal");
    result <<"\n";
    result <<"Rendimiento: "<<((performance)?"Alto":"Normal")<<"\n";
    result <<"Fiabilidad: "<<((reliable)?"Alto":"Normal")<< "\n";
    result <<"Longitud Total: "<< dec << lenght<<"\n";
    result <<"identificador: "<< dec << id<<"\n";

    result << "\n*Fragmentacion*\n";
    result << "bit1: " << ((div)?"No divisible":"Divisible")<<"\n";
    result << "bit2: " << ((frag)?"Fragmento Intermedio":"Ultimo Fragmento")<<"\n";
    result << "Posicion de Fragmento: "<<pos << "\n\n";
    result <<"Tiempo de Vida: "<<lifetime<<"\n";
    result <<"Protocolo: "<<type<<getTypeName()<<"\n";
    result <<"Checksum: "<<hex<<checksum<<"\n\n";

    result <<"Direccion IP Origen: "<<origin<<"\n";
    result <<"Direccion IP Destino: "<<destiny<<"\n\n";

    result << *(protocol) << "\n";
    return result.str();
}

string IPv4::getPriorityName()const{
    string result=" <";
    switch (priority)
    {
    case 0:
        result+= "De Rutina";
        break;
    case 1:
        result+= "Prioritario";
        break;
    case 2:
        result+= "Inmediato";
        break;
    case 3:
        result+= "Relampago";
        break;
    case 4:
        result+= "Invalidacion relampago";
        break;
    case 5:
        result+= "Procesando llamada critica y de emergencia";
        break;
    case 6:
        result+= "Control de trabajo de internet";
        break;
    case 7:
        result+= "Control de red";
        break;
    }
    result +=">";
    return result;
}

string IPv4::getTypeName()const{
    string result=" <";
    switch (type)
    {
    case 1:
        result+= "ICMPv4";
        break;
    case 6:
        result+= "TCP";
        break;
    case 17:
        result+= "UDP";
        break;
    case 58:
        result+= "ICMPv6";
        break;
    case 118:
        result+= "STP";
        break;
    case 121:
        result+= "SMP";
        break;
    }
    result+=">";
    return result;
}