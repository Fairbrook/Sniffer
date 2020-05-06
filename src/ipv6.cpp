#include "ipv6.hpp"

using namespace std;

IPv6::IPv6(const vector<Byte>&data){
    auto begin = data.begin();
    Byte aux = *begin;
    Byte aux2 = *(begin+1);

    counter = 2;
    version=0;
    priority=0;
    type = 0;
    streamTag = 0;

    int helper=0;

    for (int i = 4; i <= 7; i++)
        version += aux[i] * pow(2, (i - 4));
    
    for (int x(0);x<4;x++){
		helper+=aux[x] * pow(2, (x+4));
	}
	for(int x(4);x<8;x++){
		helper+= aux2[x] * pow(2, (x-4));
	}
    
    aux = helper;

	for (int i = 0; i <= 2; i++)
        priority += aux[i] * pow(2, i);

    retard = aux[3];
    performance = aux[4];
    reliable = aux[5];
    
    for(int x(0);x<4;x++){
		streamTag+= aux2[x] * pow (2, x+16);
	}

	streamTag += *(begin+counter)*0x100+*(begin+counter+1);
    counter+=2;

    lenght = *(begin+counter)*0x100+*(begin+counter+1);
    counter+=2;

    type = *(begin+counter);
    counter++;

    jumpLimit = *(begin+counter);
    counter++;

    origin = IPv6Add(vector<Byte>(begin+counter,begin+counter+16));
    counter+=16;

    destiny = IPv6Add(vector<Byte>(begin+counter,begin+counter+16));
    counter+=16;

    switch (type)
    {
    case 1:
        protocol= new ICMPv4(vector<Byte>(begin+counter,data.end()));
        break;
    case 6:
        protocol = new TCP(vector<Byte>(begin+counter,data.end()));
        break;
     case 58:
        protocol= new ICMPv6(vector<Byte>(begin+counter,data.end()));
        break;
    default:
        protocol = new Protocol("");
        break;
    }

    counter+=protocol->getCounter();
    this->data = vector<Byte>(begin+counter,data.end());
}

string IPv6::toString()const{
    ostringstream result;
    result << "\n==Cabecera IPv6==\n";
    result <<"Version: "<<version<<"\n";
    result <<"Prioridad: "<<priority <<getPriorityName()<<"\n";
    result <<"Retardo: "<<((retard)?"Alto":"Normal");
    result <<"\n";
    result <<"Rendimiento: "<<((performance)?"Alto":"Normal")<<"\n";
    result <<"Fiabilidad: "<<((reliable)?"Alto":"Normal")<< "\n";

    result <<"Etiqueta de flujo: "<<dec<<streamTag<<"\n";

    result <<"Longitud de datos: "<< dec << lenght<<"\n";

    result <<"Protocolo: "<<type.toInt()<<getTypeName()<<"\n";

    result << "Limite de saltos: " << dec << jumpLimit.toInt()<< "\n";

    result <<"Direccion IP Origen: "<<origin<<"\n";
    result <<"Direccion IP Destino: "<<destiny<<"\n\n";

    result << *(protocol) << "\n";
    return result.str();
}

string IPv6::getPriorityName()const{
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

string IPv6::getTypeName()const{
    string result=" <";
    switch (type.toInt())
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