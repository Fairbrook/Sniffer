#include "dns.hpp"

using namespace std;

DNS::DNS(const vector<Byte> &data)
{
    auto begin = data.begin();
    Byte aux;

    id = *(begin + counter) * 0x100 + *(begin + counter + 1);
    counter += 2;

    aux = *(begin+counter);
    counter++;

    flags[7]=aux[7];

    op=0;
    for(int i=3;i<7;i++){
        op+=aux[i]*pow(2,i-3);
    }

    flags[6]=aux[2];
    flags[5]=aux[1];
    flags[4]=aux[0];

    aux = *(begin+counter);
    counter++;

    flags[3]=aux[7];
    flags[2]=aux[6];
    flags[1]=aux[5];
    flags[0]=aux[4];

    rcode=0;
    for(int i=0;i<4;i++){
        rcode+=aux[i]*pow(2,i);
    }

    QDCount = *(begin + counter) * 0x100 + *(begin + counter + 1);
    counter += 2;

    ANCount = *(begin + counter) * 0x100 + *(begin + counter + 1);
    counter += 2;

    NSCount = *(begin + counter) * 0x100 + *(begin + counter + 1);
    counter += 2;

    ARCount = *(begin + counter) * 0x100 + *(begin + counter + 1);
    counter += 2;


    this->data = vector<Byte>(begin + counter, data.end());
}

string DNS::toString() const
{
    ostringstream result;
    result << "\n==Cabecera DNS==\n";
    result << "Identificador: " << hex << id << "\n";
    result << "QR: " << flags[7] << "\n";
    result << "OP: " << op << "\n";
    result << "AA: " << flags[6] << "\n";
    result << "TC: " << flags[5] << "\n";
    result << "RD: " << flags[4] << "\n";
    result << "RA: " << flags[3] << "\n";
    result << "Z: " << flags[2] << "\n";
    result << "AD: " << flags[1] << "\n";
    result << "CD: " << flags[0] << "\n";
    result << "QDCount: " << QDCount <<"\n";
    result << "ANCount: " << ANCount <<"\n";
    result << "NSCount: " << NSCount <<"\n";
    result << "ARCount: " << ARCount <<"\n";
    return result.str();
}

string DNS::getRCode(const int &port)
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