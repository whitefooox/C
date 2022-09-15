#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include "Manager.h"
#include "../component/Component.h"

using namespace std;

typedef H__RESULT (*GetClass) (CLS__ID clsid, I__ID iid, void** ppv);
GetClass GetObjectClass;
HINSTANCE result;

bool getPath(string &path, CLS__ID clsid) 
{
    ifstream file;
    string str;
    CLS__ID id;
    bool is = false;

    file.open("C:\\Users\\dasew\\Desktop\\Homework\\C++\\2.2\\lab3\\manager\\Data.txt");
    if(!file) 
    {
        file.close();
        return false;
    }
    
    while(getline(file, str) && !is)
    {
        istringstream iis(str, istringstream::in);
        iis >> id;
        if(id == clsid)
        {
            is = true;
            iis >> path;
        }
    }
    file.close();
    return is;
}

extern "C" H__RESULT __declspec(dllexport) Get__ClassObject(CLS__ID clsid, I__ID iid, void** ppv)
{
    string path;
    if(!getPath(path, clsid)) return S__FALSE;

    wstring temp = wstring(path.begin(), path.end());
    LPCWSTR pcstr = temp.c_str();

    result = LoadLibraryW(pcstr);
    if(result == NULL) return S__FALSE;

    GetObjectClass = (GetClass) GetProcAddress(result, "Get__ClassObject");
    if(!GetObjectClass) return S__FALSE;

    GetObjectClass(clsid, iid, ppv);
    return S__OK;
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    return true;
}

STDAPI __declspec(dllexport) DllCanUnloadNow()
{
    return FreeLibrary(result);
}