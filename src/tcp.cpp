#include "tcp.hpp"

using namespace std;

TCP::TCP(const vector<Byte> &data)
{
    auto begin = data.begin();
    Byte aux;

    originPort = *(begin + counter) * 0x100 + *(begin + counter + 1);
    counter += 2;

    destinyPort = *(begin + counter) * 0x100 + *(begin + counter + 1);
    counter += 2;

    secuence = 0;
    for (int i = 0; i < 4; i++)
    {
        secuence += (*(begin + counter)) * (int)pow(0x100, 3 - i);
        counter++;
    }

    ack = 0;
    for (int i = 0; i < 4; i++)
    {
        ack += (*(begin + counter)) * (int)pow(0x100, 3 - i);
        counter++;
    }

    aux = *(begin + counter);
    counter++;
    header = 0;
    for (int i = 4; i <= 7; i++)
    {
        header += aux[i] * pow(2, i - 4);
    }

    flags[0] = aux[0];

    aux = *(begin + counter);
    counter++;
    for (int i = 0; i < 8; i++)
    {
        flags[i + 1] = aux[7 - i];
    }

    window = *(begin + counter) * 0x100 + *(begin + counter + 1);
    counter += 2;

    checksum = *(begin + counter) * 0x100 + *(begin + counter + 1);
    counter += 2;

    puntero = *(begin + counter) * 0x100 + *(begin + counter + 1);
    counter += 2;

    this->data = vector<Byte>(begin + counter, data.end());
}

string TCP::toString() const
{
    ostringstream result;
    result << "\n==Cabecera TCP==\n";
    result << "Puerto de origen: " << dec << originPort << getPortName(originPort) << "\n";
    result << "Puerto de destino: " << destinyPort << getPortName(destinyPort) << "\n";
    result << "Numero de Secuencia: " << secuence << "\n";
    result << "Numero de acuse de recibo: " << ack << "\n";
    result << "Longitud de la cabecera: " << hex << header << " Palabras \n";
    result << "Banderas: "
           << "\n";
    result << "NS: " << flags[0] << "\n";
    result << "CWR: " << flags[1] << "\n";
    result << "ECE: " << flags[2] << "\n";
    result << "URG: " << flags[3] << "\n";
    result << "ACK: " << flags[4] << "\n";
    result << "PSH: " << flags[5] << "\n";
    result << "RST: " << flags[6] << "\n";
    result << "SYN: " << flags[7] << "\n";
    result << "FIN: " << flags[8] << "\n";
    result << "Tamano de Ventana: " << dec << window << "\n";
    result << "Suma de Verificacion: " << hex << checksum << "\n";
    result << "Puntero urgente: " << dec << puntero << "\n";

    return result.str();
}

string TCP::getPortName(const int &port)
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