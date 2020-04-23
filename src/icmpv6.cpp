#include "icmpv6.hpp"

using namespace std;

ICMPv6::ICMPv6(const vector<Byte> &data)
{
    auto begin = data.begin();
    counter = 0;
    code = 0;
    type = 0;
    checksum = 0;

    type = *(begin + counter);
    counter++;

    code = *(begin + counter);
    counter++;

    checksum = *(begin + counter) * 0x100 + *(begin + counter + 1);
    counter += 2;
}

string ICMPv6::toString() const
{
    ostringstream result;
    result << "\n"
           << "=ICMPv6="
           << "\n";
    result << "Tipo: " << dec << type << getTypeName() << "\n";
    result << "Codigo: " << dec << code << getCodeName() << "\n";
    return result.str();
}

string ICMPv6::getCodeName() const
{
    string result = " <";
    switch (type)
    {
    case 1:
        switch (code)
        {
        case 0:
            result+= "No existe ruta destino";
            break;
        case 1:
            result+= "Comunicacion con el destino administrativamente prohibida";
            break;
        case 2:
            result+= "No asignado";
            break;
        case 3:
            result+= "Direccion inalcanzable";
            break;
        default:
            result+= "Desconocido";
            break;
        }
        break;
    case 3:
        switch (code)
        {
        case 0:
            result+= "Limite del salto excedido";
            break;
        case 1:
            result+= "Tiempo de reensamble de fragmento excedido";
            break;
        default:
            result+= "Desconocido";
            break;
        }
        break;
    case 4:
        switch (code)
        {
        case 0:
            result+= "El campo de cabecera encontrado es erroneo";
            break;
        case 1:
            result+= "No fue reconocido el tipo de la siguiente cabecera encontrada";
            break;
        case 2:
            result+= "Opcion desconocida del IPv6 encontrada";
            break;
        default:
            result+= "Desconocido";
            break;
        }
        break;
    default:
        result+= "Desocnocido";
    }
    result += ">";
    return result;
}

string ICMPv6::getTypeName() const
{
    string result = " <";
    switch (type)
    {
    case 129:
        result += "Echo Reply";
        break;
    case 1:
        result += "Destinaton Unreacheable";
        break;
    case 2:
        result += "Too big packet message";
        break;
    case 128:
        result += "Echo Request";
        break;
    case 3:
        result += "Time Exceeded";
        break;
    case 4:
        result += "Parameter Problem";
        break;
    case 133:
        result += "Router Solicitation";
        break;
    case 134:
        result += "Router Advertisement";
        break;
    case 135:
        result += "Neighbor Solicitation";
        break;
    case 136:
        result += "Neighbor Advertisement";
        break;
    case 137:
        result += "Redirect";
        break;
    default:
        result += "Desconocido";
    }
    result += ">";
    return result;
}