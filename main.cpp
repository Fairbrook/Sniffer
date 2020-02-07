#include <iostream>
#include <iomanip>

#include "fcontroller.h"

using namespace std;

int main()
{
    string name;
    cout << "Introduzca nombre de archivo: ";
    cin >> name;

    FController file(name);

    cout << "Direccion MAC Destino: ";
    for(int i = 0;i<6;i++) cout << setw(2) << setfill('0') << hex << (int)file.getNext() << " ";
    cout << endl;

    cout << "Direccion MAC Origen: ";
    for(int i = 0;i<6;i++) cout << setw(2) << setfill('0') << hex << (int)file.getNext() << " ";
    cout << endl;

    cout << "Tipo: ";
    unsigned char type1 = file.getNext();
    unsigned char type2 = file.getNext();
    cout << setw(2) << setfill('0') << hex << (int)type1 << " ";
    cout << setw(2) << setfill('0') << hex << (int)type2;
    cout << " <";

    if((int)type1 == 8){
        if((int)type2 == 0) cout << "IPv4";
        if((int)type2 == 6) cout << "ARP";
    }else{
        if((int)type1 == 128 && (int)type2 == 53) cout << "RARP";
        if((int)type1 == 134 && (int)type2 == 221) cout << "RARP";
    }
    cout << ">" << endl;
    cout << "Datos: ";
    while(!file.isEOF())cout << setw(2) << setfill('0') << hex << (int)file.getNext() << " ";


}
