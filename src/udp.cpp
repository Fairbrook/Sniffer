#include "udp.hpp"

using namespace std;

UDP::UDP(const vector<Byte> &data):protocol(new Protocol(""))
{
    auto begin = data.begin();
    Byte aux;

    originPort = *(begin + counter) * 0x100 + *(begin + counter + 1);
    counter += 2;

    destinyPort = *(begin + counter) * 0x100 + *(begin + counter + 1);
    counter += 2;

    lenght = *(begin + counter) * 0x100 + *(begin + counter + 1);
    counter += 2;

    checksum = *(begin + counter) * 0x100 + *(begin + counter + 1);
    counter += 2;

   if(originPort==53 or destinyPort==53){
        protocol = new DNS(vector<Byte>(begin + counter, data.end()));
    }

    counter += protocol->getCounter();
    this->data = vector<Byte>(begin + counter, data.end());
}

string UDP::toString() const
{
    ostringstream result;
    result << "\n==Cabecera UDP==\n";
    result << "Puerto de origen: " << dec << originPort << getPortName(originPort) << "\n";
    result << "Puerto de destino: " << destinyPort << getPortName(destinyPort) << "\n";
    result << "Longitud: " << hex << lenght;
    result << "Suma de Verificacion: " << hex << checksum << "\n";
    return result.str();
}

string UDP::getPortName(const int &port)
{
    string result = " <";
    switch (port)
    {
    case 20:
        result += "FTP";
        break;
    case 21:
        result += "SFTP";
        break;
    case 22:
        result += "SSH";
        break;
    case 23:
        result += "TELNET";
        break;
    case 25:
        result += "SMTP";
        break;
    case 53:
        result += "DNS";
        break;
    case 67:
        result += "DHCP";
        break;
    case 68:
        result += "DHCP";
        break;
    case 69:
        result += "TFTP";
        break;
    case 80:
        result += "HTTP";
        break;
    case 110:
        result += "POP3";
        break;
    case 143:
        result += "IMAP";
        break;
    case 443:
        result += "HTTPS";
        break;
    case 993:
        result += "IMAP SSL";
        break;
    case 995:
        result += "POP SSL";
        break;
    default:
        result += "Desconocido";
        break;
    }
    result += ">";
    return result;
}