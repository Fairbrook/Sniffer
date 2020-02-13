#include <iostream>
#include <iomanip>

#include "fcontroller.h"
#include "byte.h"

using namespace std;

int main()
{
    string name;
    cout << "Introduzca nombre de archivo: ";
    cin >> name;

    FController file(name);

    cout << "Direccion MAC Destino: ";
    for(int i = 0;i<6;i++) cout << file.getNext() << " ";
    cout << endl;

    cout << "Direccion MAC Origen: ";
    for(int i = 0;i<6;i++) cout << file.getNext() << " ";
    cout << endl;

    cout << "Tipo: ";
    Byte type1 = file.getNext();
    Byte type2 = file.getNext();
    cout << type1 << " ";
    cout << type2;
    cout << " <";

    if(type1 == 8){
        if(type2 == 0) cout << "IPv4";
        if(type2 == 6) cout << "ARP";
    }else{
        if(type1 == 128 && type2 == 53) cout << "RARP";
        if(type1 == 134 && type2 == 221) cout << "RARP";
    }
    cout << ">" << endl;
    cout << "Datos: ";
    while(!file.isEOF())cout << file.getNext() << " ";


}
