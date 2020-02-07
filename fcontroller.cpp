#include "fcontroller.h"

using namespace std;

FController::FController(const std::string&n)
{
    name = n;
    cursor = 0;
}


unsigned char FController::getNext()
{
    unsigned char aux;
    file.open(name,ios::in|ios::out);
    file.seekg(cursor,file.beg);
    aux = file.get();
    cursor = file.tellg();
    file.clear();
    file.close();
    return aux;
}


bool FController::isEOF()
{
    file.open(name,ios::in|ios::out);
    file.seekg(cursor,file.beg);
    bool value = !file.good();
    file.clear();
    file.close();
    return value;
}
