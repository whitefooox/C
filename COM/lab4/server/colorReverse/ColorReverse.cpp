#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include "ColorReverseAPI.h"
#include "../../lib/unknown.h"
#include "../color/ColorAPI.h"

using namespace std;

static int g_cComponents = 0;
TCHAR path[MAX_PATH];

void trace(const char* msg)
{
    cout << msg << endl;
};

//_____________________________________________________________________________________

class ColorReverse : public IReverse, IPrint, ISet, IGet
{
    private:
        long countReference = 1;
        IPrint* iPrint;
        ISet* iSet;
        IGet* iGet;

    public:
        H__RESULT QueryInterface(I__ID iid, void** ppv);
        H__RESULT Init();
        U__LONG AddRef();
        U__LONG Release();
        void reverse();
        void print();
        int getR();
        int getG();
        int getB();
        void setR(int r);
        void setG(int g);
        void setB(int b);
        ColorReverse();
        ~ColorReverse();
};

typedef H__RESULT (*GetClass) (CLS__ID clsid, I__ID iid, void** ppv);
HINSTANCE result;

bool getObject(GetClass &GetObjectClass) {
    result = LoadLibrary(TEXT("Manager.dll"));
    if(result == NULL) return false;
    GetObjectClass = (GetClass) GetProcAddress(result, "Get__ClassObject");
    if(!GetObjectClass) return false;
    return true;
}

H__RESULT ColorReverse::Init()
{
    trace("Init");
    GetClass GetObjectClass;
    if(!getObject(GetObjectClass)) return S__FALSE;
    I__ClassFactory* factory;
    GetObjectClass(CLSIDColor, IID__IClassFactory, (void**)&factory);
    factory->CreateInstance(IID__IPrint, (void**)&iPrint);
    factory->Release();
    iPrint->QueryInterface(IID__IGet, (void**)&iGet);
    iPrint->QueryInterface(IID__ISet, (void**)&iSet);
    return S__OK;
}

ColorReverse::ColorReverse()
{
    trace("ColorReverse");
    iPrint = NULL;
    iSet = NULL;
    iGet = NULL;
}

ColorReverse::~ColorReverse() 
{
    trace("~ColorReverse");
    if(iPrint != NULL) 
    {
        iPrint->Release();
    }
    if(iSet != NULL) 
    {
        iSet->Release();
    }
    if(iGet != NULL) 
    {
        iGet->Release();
    }
}

void ColorReverse::reverse()
{
    setR(255 - getR());
    setG(255 - getG());
    setB(255 - getB());
}

void ColorReverse::print() 
{
    iPrint->print();
}

int ColorReverse::getR() 
{
    return iGet->getR();
}

int ColorReverse::getG() 
{
    return iGet->getG();
}

int ColorReverse::getB() 
{
    return iGet->getB();
}

void ColorReverse::setR(int r) 
{
    iSet->setR(r);
}

void ColorReverse::setG(int g) 
{
    iSet->setG(g);
}

void ColorReverse::setB(int b) 
{
    iSet->setB(b);
}

U__LONG ColorReverse::AddRef() 
{
    trace("ColorReverse AddRef");
    countReference++;
    return countReference;
}

U__LONG ColorReverse::Release() 
{
    trace("ColorReverse Release");
    countReference--;
    if(countReference == 0)
    {
        delete this;
    }
    return countReference;
}

H__RESULT ColorReverse::QueryInterface(I__ID iid, void** ppv)
{
    trace("ColorReverse QueryInterface");
    switch (iid)
    {
        case IID__IUnknown:
        {
            *ppv = (I__Unknown*) (IReverse*) this;
            break;
        }
        case IID__IPrint:
        {
            *ppv = (IPrint*) this;
            break;
        }
        case IID__IGet:
        {
            *ppv = (IGet*) this;
            break;
        }
        case IID__ISet:
        {
            *ppv = (ISet*) this;
            break;
        }
        case IID__IReverse:
        {
            *ppv = (IReverse*) this;
            break;
        }
        default:
        {
            *ppv = 0;
            return E__NOINTERFACE;
        }
    }
    AddRef();
    return S__OK;
}

//___________________________________________________________

ColorReverseFactory::ColorReverseFactory() 
{
    trace("ColorReverseFactory");
}

ColorReverseFactory::~ColorReverseFactory() 
{
    trace("~ColorReverseFactory");
}

U__LONG ColorReverseFactory::AddRef() 
{
    trace("ColorReverseFactory AddRef");
    countReference++;
    return countReference;
}

U__LONG ColorReverseFactory::Release() 
{
    trace("ColorReverseFactory Release");
    countReference--;
    if(countReference == 0)
    {
        g_cComponents--;
        delete this;
    }
    return countReference;
}

H__RESULT ColorReverseFactory::CreateInstance(I__ID iid, void** ppv)
{
    trace("ColorReverseFactory CreateInstance");
    ColorReverse* color = new ColorReverse();
    if (color == 0)
    {
        return E__OUTOFMEMORY;
    }
    H__RESULT result = color->Init();
    if (result == S__FALSE) 
    {
        color->Release();
        return result;
    }
    H__RESULT res = color->QueryInterface(iid, ppv);
    g_cComponents++;
    color->Release();
    return res;
}

H__RESULT ColorReverseFactory::QueryInterface(I__ID iid, void** ppv)
{
    trace("ColorReverseFactory QueryInterface");
    if (iid == IID__IUnknown || iid == IID__IClassFactory)
    {
        *ppv = (I__ClassFactory*) this;
    }
    else
    {
        *ppv = 0;
        return E__NOINTERFACE;
    }
    AddRef();
    return S__OK;
}

//_________________________________________________________________

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    GetModuleFileName(hinstDLL, path, MAX_PATH);
    return true;
}

bool deletePath()
{
    ifstream file;
    ofstream file_out;
    file.open("C:\\Users\\dasew\\Desktop\\Homework\\C++\\2.2\\lab4\\manager\\Data.txt");
    if(!file) 
    {
        file.close();
        return false;
    }

    file_out.open("C:\\Users\\dasew\\Desktop\\Homework\\C++\\2.2\\lab4\\manager\\Data_new.txt");
    string str;
    CLS__ID id;
    
    while(getline(file, str))
    {
        istringstream iis(str, istringstream::in);
        iis >> id;
        if(id != CLSIDColorReverse)
        {
            file_out << str;
        }
    }
    file.close();
    file_out.close();
    remove("C:\\Users\\dasew\\Desktop\\Homework\\C++\\2.2\\lab4\\manager\\Data.txt");
    rename("C:\\Users\\dasew\\Desktop\\Homework\\C++\\2.2\\lab4\\manager\\Data_new.txt", 
    "C:\\Users\\dasew\\Desktop\\Homework\\C++\\2.2\\lab4\\manager\\Data.txt");
    return true;
}

bool setPath() 
{
    deletePath();
    ofstream file("C:\\Users\\dasew\\Desktop\\Homework\\C++\\2.2\\lab4\\manager\\Data.txt", std::ios_base::in | std::ios_base::app);
    if(!file) 
    {
        file.close();
        return false;
    }
    
    file << "\n" << CLSIDColorReverse << " " << path;
    file.close();
    return true;
}

STDAPI __declspec(dllexport) DllCanUnloadNow()
{
    if(g_cComponents) {
        return S_FALSE;
    }
    else {
        return S_OK;
    }
}

STDAPI __declspec(dllexport) DllRegisterServer()
{
    if(setPath()) return S_OK;
    else return S_FALSE;
}

STDAPI __declspec(dllexport) DllUnregisterServer()
{
    if(deletePath()) return S_OK;
    else return S_FALSE;
}

extern "C" H__RESULT __declspec(dllexport) Get__ClassObject(CLS__ID clsid, I__ID iid, void** ppv)
{
    if(clsid != CLSIDColorReverse)
    {
        return E__CLASSNOTAVAILABLE;
    }
    ColorReverseFactory* factory = new ColorReverseFactory();
    if(factory == 0) 
    {
        return E_OUTOFMEMORY;
    }
    H__RESULT res = factory->QueryInterface(iid, ppv);
    return res;
}