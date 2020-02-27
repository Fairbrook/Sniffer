#include <iostream>
#include <iomanip>
#include <math.h>

#include "fcontroller.h"
#include "byte.h"

using namespace std;
void showIPv4(FController &);

int main()
{
    string name;
    int type;

    cout << "Introduzca nombre de archivo: ";
    cin >> name;

    FController file(name);

    cout << "Direccion MAC Destino: ";
    for (int i = 0; i < 6; i++)
        cout << file.getNext() << " ";
    cout << endl;

    cout << "Direccion MAC Origen: ";
    for (int i = 0; i < 6; i++)
        cout << file.getNext() << " ";
    cout << endl;

    cout << "Tipo: ";
    Byte type1 = file.getNext();
    Byte type2 = file.getNext();
    cout << type1 << " ";
    cout << type2;
    cout << " <";

    type = type2 + type1 * 0x100;

    switch (type)
    {
    case 0x0800:
        cout << "IPv4>";
        showIPv4(file);
        break;
    case 0x0806:
        cout << "ARP>";
        break;
    case 0x8035:
        cout << "RARP>";
        break;
    case 0x86DD:
        cout << "IPv6>";
        break;
    }

    cout << endl
         << endl
         << "=Datos=" << endl;
    while (!file.isEOF())
        cout << file.getNext() << " ";
    cout << endl;
}

void showIPv4(FController &file)
{
    int type;
    cout << endl
         << endl
         << "==Cabecera IPv4==" << endl;
    Byte aux = file.getNext();
    type = 0;
    for (int i = 4; i <= 7; i++)
        type += aux[i] * pow(2, (i - 4));
    cout << "Version: " << type << endl;
    type = 0;
    for (int i = 0; i <= 3; i++)
        type += aux[i] * pow(2, i);
    cout << "Cabecera: " << type << " palabras" << endl;
    aux = file.getNext();
    type = 0;
    for (int i = 0; i <= 2; i++)
        type += aux[i] * pow(2, i);
    cout << "Prioridad: ";
    switch (type)
    {
    case 0:
        cout << "De Rutina";
        break;
    case 1:
        cout << "Prioritario";
        break;
    case 2:
        cout << "Inmediato";
        break;
    case 3:
        cout << "Relampago";
        break;
    case 4:
        cout << "Invalidacion relampago";
        break;
    case 5:
        cout << "Procesando llamada critica y de emergencia";
        break;
    case 6:
        cout << "Control de trabajo de internet";
        break;
    case 7:
        cout << "Control de red";
        break;
    }
    cout << endl
         << "Retardo: ";
    if (aux[3])
        cout << "Bajo";
    else
        cout << "Normal";
    cout << endl;
    cout << "Rendimiento: ";
    if (!aux[4])
        cout << "Normal";
    else
        cout << "Alto";
    cout << endl;
    cout << "Fiabilidad: ";
    if (!aux[5])
        cout << "Normal";
    else
        cout << "Alto";
    cout << endl;

    type = 0;
    type = file.getNext() * 0x100;
    type = file.getNext().getData() + type;
    cout << "Longitud Total: " << dec << type << endl;

    type = 0;
    type = file.getNext() * 0x100;
    type = file.getNext().getData() + type;
    cout << "Identificador: " << dec << type << endl;

    aux = file.getNext();
    cout << endl
         << "=Fragmentacion= " << endl;
    cout << "bit1: ";
    if (aux[6])
        cout << "No Divisible";
    else
        cout << "Divisible";
    cout << endl
         << "bit2: ";
    if (aux[5])
        cout << "Fragmento Intermedio";
    else
        cout << "Ultimo fragmento";

    cout << endl
         << "Posicion de Fragmento: ";
    type = 0;
    for (int i = 0; i <= 4; i++)
        type += aux[i] * pow(2, i + 8);
    type += file.getNext().getData();
    cout << dec << type;

    cout << endl
         << endl
         << "Tiempo de vida: " << dec << (int)file.getNext().getData();
    type = file.getNext().getData();
    cout << endl
         << "Protocolo: " << dec << type << " <";
    switch (type)
    {
    case 1:
        cout << "ICMPv4";
        break;
    case 6:
        cout << "TCP";
        break;
    case 17:
        cout << "UDP";
        break;
    case 58:
        cout << "ICMPv6";
        break;
    case 118:
        cout << "STP";
        break;
    case 121:
        cout << "SMP";
        break;
    }
    cout << ">";
    cout << endl
         << "Checksum: " << file.getNext() << " " << file.getNext() << endl;
    cout << "Dirección IP Origen:" << dec << (int)file.getNext().getData() << "."
         << dec << (int)file.getNext().getData() << "."
         << dec << (int)file.getNext().getData() << "."
         << dec << (int)file.getNext().getData() << endl;

    cout << "Dirección IP Destino:" << dec << (int)file.getNext().getData() << "."
         << dec << (int)file.getNext().getData() << "."
         << dec << (int)file.getNext().getData() << "."
         << dec << (int)file.getNext().getData() << endl;
}