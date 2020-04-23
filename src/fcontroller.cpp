#include "fcontroller.h"

using namespace std;

FController::FController(const std::string&n)
{
    name = n;
    cursor = 0;
    file.open(name,std::ios::in | std::ios::binary);
    if(!file.good())throw "Not a File";
    file.close();
}


Byte FController::getNext()
{
    char aux;
    if(isEOF())throw "EOF";
    file.open(name,std::ios::in | std::ios::binary);    
    file.setf(std::ios_base::hex);
    file.seekg(cursor,file.beg);
    file.get(aux);
    cursor = file.tellg();
    file.close();
    return Byte(aux);
}


bool FController::isEOF()
{
    file.open(name,std::ios::in | std::ios::binary);
    file.seekg(cursor,file.beg);
    bool value = !file.good();
    file.clear();
    file.close();
    return value;
}

int FController::getLenght(){
    file.open(name,std::ios::in | std::ios::binary);
    file.seekg(0,file.end);
    int lenght = file.tellg();
    file.clear();
    file.close();
    return lenght;
}

bool FController::isFile(const string &s){
    ifstream aux(s);
    bool state = aux.good();
    aux.clear();
    aux.close();
    return state;
}