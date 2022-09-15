#include <windows.h>
#include <iostream>
#include "../lib/unknown.h"
#include "../server/colorReverse/ColorReverseAPI.h"
#include "../server/color/ColorAPI.h"

using namespace std;
typedef H__RESULT (*GetClass) (CLS__ID clsid, I__ID iid, void** ppv);
HINSTANCE result;

bool getObject(GetClass &GetObjectClass) {
    result = LoadLibrary(TEXT("Manager.dll"));
    if(result == NULL) return false;
    GetObjectClass = (GetClass) GetProcAddress(result, "Get__ClassObject");
    if(!GetObjectClass) return false;
    return true;
}

int main() 
{
    GetClass GetObjectClass;
    if(!getObject(GetObjectClass)) return 0;

    IPrint* iPrint;
    IReverse* iReverse;
    ColorReverseFactory* factory;

    GetObjectClass(CLSIDColorReverse, IID__IClassFactory, (void**)&factory);
    factory->CreateInstance(IID__IPrint, (void**)&iPrint);
    factory->Release();

    iPrint->print();
    iPrint->QueryInterface(IID__IReverse, (void**)&iReverse);
    iReverse->reverse();
    iPrint->print();
    iPrint->Release();
    iReverse->Release();

    FreeLibrary(result);
}