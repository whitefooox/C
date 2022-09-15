#include <windows.h>
#include <iostream>
#include "../manager/Manager.h"
#include "../component/Component.h"

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

    IPrint* ip;
    IMix* im;
    IColorFactory* factory;

    GetObjectClass(CLSIDColor, IID__IClassFactory, (void**)&factory);
    factory->CreateInstance(IID__IPrint, (void**)&ip);
    factory->Release();

    ip->print();
    ip->QueryInterface(IID__IMix, (void**)&im);
    im->mix(120, 120, 120);
    ip->print();
    ip->Release();
    im->Release();

    FreeLibrary(result);
}