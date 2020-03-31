#include <iostream>
#include <iomanip>
#include <math.h>

#include "fcontroller.h"
#include "byte.h"

using namespace std;
void showIPv6(FController &);
void showICMPv6(FController &);
void showIPv4(FController &);
void showICMPv4(FController &);
void showIPAdd(FController &);
void showARP(FController &);
void showProtocol(Byte,Byte);
void wait();

int main()
{
    string name;
    int type;

    cout << "Introduzca nombre de archivo: ";
    getline(cin,name);

    if(!FController::isFile(name)){
        cout << "Archivo no encontrado\n";
        wait();
        return 1;
    }

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
        showARP(file);
        break;
    case 0x8035:
        cout << "RARP>";
        break;
    case 0x86DD:
        cout << "IPv6>";
		showIPv6(file);
        break;
    }

    cout << endl
         << endl
         << "=Datos=" << endl;
    while (!file.isEOF())
        cout << file.getNext() << " ";
    cout << endl;
    wait();
    return 0;
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
        cout << "ICMPv4>";
        showIPAdd(file);
        showICMPv4(file);
        break;
    case 6:
        cout << "TCP>";
        break;
    case 17:
        cout << "UDP>";
        break;
    case 58:
        cout << "ICMPv6>";
		showIPAdd(file);
		showICMPv6(file);
        break;
    case 118:
        cout << "STP>";
        break;
    case 121:
        cout << "SMP>";
        break;
    }
}

void showIPAdd(FController &file)
{
    cout << endl
         << "Checksum: " << file.getNext() << " " << file.getNext() << endl;
    cout << "Direccion IP Origen:" << dec << (int)file.getNext().getData() << "."
         << dec << (int)file.getNext().getData() << "."
         << dec << (int)file.getNext().getData() << "."
         << dec << (int)file.getNext().getData() << endl;

    cout << "Direccion IP Destino:" << dec << (int)file.getNext().getData() << "."
         << dec << (int)file.getNext().getData() << "."
         << dec << (int)file.getNext().getData() << "."
         << dec << (int)file.getNext().getData() << endl;
}

void showICMPv4(FController &file)
{
    cout << endl
         << "=ICMPv4=" << endl;
    int typeNum = file.getNext().getData();
    cout << "Tipo: " << dec << typeNum << " <";
    switch (typeNum)
    {
    case 0:
        cout << "Echo Reply";
        break;
    case 3:
        cout << "Destinaton Unreacheable";
        break;
    case 4:
        cout << "Source Quench";
        break;
    case 5:
        cout << "Redirect";
        break;
    case 8:
        cout << "Echo";
        break;
    case 11:
        cout << "Time Exceeded";
        break;
    case 12:
        cout << "Parameter Problem";
        break;
    case 13:
        cout << "Timestamp";
        break;
    case 14:
        cout << "Timestamp Reply";
        break;
    case 15:
        cout << "Information Request";
        break;
    case 16:
        cout << "Information Replay";
        break;
    case 17:
        cout << "Addressmask";
        break;
    case 18:
        cout << "Addressmask Replay";
        break;
    default:
        cout << "Desconocido";
    }
    cout << ">" << endl;

    typeNum = file.getNext().getData();
    cout << "Codigo: " << dec << typeNum << " <";

    switch (typeNum)
    {
    case 0:
        cout << "No se puede llegar a la red";
        break;
    case 1:
        cout << "No se puede llegar al Host";
        break;
    case 2:
        cout << "El destino no dispone del protocolo";
        break;
    case 3:
        cout << "No se puede llegar al puerto destino";
        break;
    case 4:
        cout << "Se necesita aplicar fragmentacion";
        break;
    case 5:
        cout << "La ruta de origen no es correcta";
        break;
    case 6:
        cout << "No se conoce la red destino";
        break;
    case 7:
        cout << "No se conoce host destino";
        break;
    case 8:
        cout << "El host origen esta aislado";
        break;
    case 9:
        cout << "La comunicacion con la red esta prohibida";
        break;
    case 10:
        cout << "La comunicacion con el host esta prohibida";
        break;
    case 11:
        cout << "No se puede llegar a la red";
        break;
    case 12:
        cout << "No se puede llegar al host";
        break;

    default:
        cout << "Desconocido";
    }
    cout << ">";
    cout << endl
         << "Checksum: " << file.getNext() << " " << file.getNext();
}

void showProtocol(Byte type2, Byte type1){
    int type = type1 + type2 * 0x100;

    cout << "\nProtocolo: " << type2 << " " << type1 << " <";
    switch (type)
    {
    case 0x0800:
        cout << "IPv4>";
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
}

void showARP(FController &file){
    int type = (int)file.getNext().getData();
    type = type*0x100 + file.getNext().getData();
    cout << endl << endl << "=ARP / RARP=" << endl;
    cout << "Tipo de Hardware: "<<  type << " <";
    switch (type)
    {
    case 1: cout << "Ethernet";break;
    case 6: cout << "IEEE 802";break;
    case 7: cout << "ARCNET";break;
    case 15: cout << "Frame Relay";break;
    case 16: cout << "ATM";break;
    case 17: cout << "HDLC";break;
    case 18: cout << "Fibre Channel";break;
    case 19: cout << "ATM";break;
    case 20: cout << "Serial Line";break;
    
    default:
        cout << "Desconocido";
        break;
    }
    cout << ">";

    Byte type2 = file.getNext();
    Byte type1 = file.getNext();
    showProtocol(type2,type1);

    cout << "\nDireccion de Hardware: " << (int)file.getNext().getData();
    cout << "\nDireccion de Protocolo: " << (int)file.getNext().getData();
    type = file.getNext().getData()*0x100 + file.getNext().getData();

    cout << "\nCodigo de operacion: " << type << " <";
    switch (type)
    {
    case 1: cout << "ARP Request";break;
    case 2: cout << "ARP Reply";break;
    case 3: cout << "RARP Request";break;
    case 4: cout << "RARP Reply";break;
    case 5: cout << "DRARP Request";break;
    case 6: cout << "DRARP Reply";break;
    case 7: cout << "DRARP Error";break;
    case 8: cout << "InARP Request";break;
    case 9: cout << "InARP Reply";break;
    default:
        cout << "Desconocido";
        break;
    }
    cout << ">" << endl;

    cout << "Direccion MAC Origen: ";
    for (int i = 0; i < 6; i++)
        cout << file.getNext() << " ";
    cout << endl;

    cout << "Direccion IP Origen:" << dec << (int)file.getNext().getData() << "."
         << dec << (int)file.getNext().getData() << "."
         << dec << (int)file.getNext().getData() << "."
         << dec << (int)file.getNext().getData() << endl;

    cout << "Direccion MAC Destino: ";
    for (int i = 0; i < 6; i++)
        cout << file.getNext() << " ";
    cout << endl;

    cout << "Direccion IP Destino:" << dec << (int)file.getNext().getData() << "."
         << dec << (int)file.getNext().getData() << "."
         << dec << (int)file.getNext().getData() << "."
         << dec << (int)file.getNext().getData() << endl;
}

void showIPv6(FController &file){
	int type;
	cout << endl
		<< endl
		<< "==Cabecera IPv6==" << endl;
	Byte aux = file.getNext();
	type = 0;
	for (int i = 4; i <= 7; i++)
		type += aux[i] * pow(2, (i - 4));
	cout << "Version: " << type << endl;
	type = 0;
	//dudoso
	Byte aux2= file.getNext();
	for (int x(0);x<4;x++){
		type+=aux[x] * pow(2, (x+4));
	}
	for(int x(4);x<8;x++){
		type+= aux2[x] * pow(2, (x-4));
	}
	
	
	aux = type;
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
	type=0;
	for(int x(0);x<4;x++){
		type+= aux2[x] * pow (2, x+16);
	}
	type +=file.getNext()*0x100;
	type +=file.getNext().getData();
	
	cout<<"Etiqueta de flujo: "<<dec<<type;
	
	type = 0;
	type = file.getNext() * 0x100;
	type = file.getNext().getData() + type;
	cout <<endl<< "Longitud de datos: " << dec << type << endl;
	
	
	type = file.getNext().getData();
	cout << endl
		<< "Protocolo: " << dec << type << " <";
	switch (type)
	{
	case 1:
		cout << "ICMPv4>";
		break;
	case 6:
		cout << "TCP>";
		break;
	case 17:
		cout << "UDP>";
		break;
	case 58:
		cout << "ICMPv6>";
		break;
	case 118:
		cout << "STP>";
		break;
	case 121:
		cout << "SMP>";
		break;
	}
	aux=file.getNext();
	cout<<endl<<"Limite de saltos "<<dec<<(int)aux.getData()<<endl;
	
	cout<<endl<<"Direccion de origen: ";
	for(int x(0);x<8;x++){
		cout<<file.getNext()<<file.getNext();
		if(x<7){
			cout<<":";
		}
	}
	cout<<endl<<"Direccion de destino: ";
	for(int x(0);x<8;x++){
		cout<<file.getNext()<<file.getNext();
		if(x<7){
			cout<<":";
		}
	}
	switch (type)
	{
	case 1:
		showICMPv4(file);
		break;
	case 6:
		cout << "TCP>";
		break;
	case 17:
		cout << "UDP>";
		break;
	case 58:
		showICMPv6(file);
		break;
	case 118:
		cout << "STP>";
		break;
	case 121:
		cout << "SMP>";
		break;
	}
}

void showICMPv6(FController &file){
	cout << endl << endl
		<< "=ICMPv6=" << endl;
	int typeNum = file.getNext().getData();
    int code;
	cout << "Tipo: " << dec << typeNum << " <";
	switch (typeNum)
	{
	case 129:
		cout << "Echo Reply";
		break;
	case 1:
		cout << "Destinaton Unreacheable";
		break;
	case 2:
		cout << "Too big packet message";
		break;
	case 128:
		cout << "Echo Request";
		break;
	case 3:
		cout << "Time Exceeded";
		break;
	case 4:
		cout << "Parameter Problem";
		break;
	case 133:
		cout << "Router Solicitation";
		break;
	case 134:
		cout << "Router Advertisement";
		break;
	case 135:
		cout << "Neighbor Solicitation";
		break;
	case 136:
		cout << "Neighbor Advertisement";
		break;
	case 137:
		cout << "Redirect";
		break;
	default:
		cout << "Desconocido";
	}
	cout << ">" << endl;
	code=typeNum;
	typeNum = file.getNext().getData();
	cout << "Codigo: " << dec << typeNum << " <";
	switch (code){
		case 1:
			switch (typeNum){
			case 0:
				cout<<"No existe ruta destino";
				break;
			case 1:
				cout<<"Comunicacion con el destino administrativamente prohibida";
				break;
			case 2:
				cout<<"No asignado";
				break;
			case 3:
				cout<<"Direccion inalcanzable";
				break;
			default:
				cout<<"No se puede, no hay tortillas";
				break;
			}
			break;
		case 3:
			switch(typeNum){
			case 0:
				cout<<"Limite del salto excedido";
				break;
			case 1:
				cout<<"Tiempo de reensamble de fragmento excedido";
				break;
			default:
				cout<<"No se puede, no hay tortillas";
				break;
			}
			break;
		case 4:
			switch(typeNum){
			case 0:
				cout<<"El campo de cabecera encontrado es erroneo";
				break;
			case 1:
				cout<<"No fue reconocido el tipo de la siguiente cabecera encontrada";
				break;
			case 2:
				cout<<"Opcion desconocida del IPv6 encontrada";
				break;
			default:
				cout<<"No se puede, no hay tortillas";
				break;
			}
			break;
        default:
            cout << "No aplica";
	}
	cout << ">";
	cout << endl
		<< "Checksum: " << file.getNext() << " " << file.getNext();
}

void wait() {
    cout << "Presione [Enter] para continuar";
    while(cin.get()!='\n');
}