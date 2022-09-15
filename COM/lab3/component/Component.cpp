#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include "Component.h"

using namespace std;

static int g_cComponents = 0;
TCHAR path[MAX_PATH];

class ColorFactory : public IColorFactory
{
    private:
        int countReference = 0;

    public:
        H__RESULT CreateInstance(I__ID iid, void** ppv);
        H__RESULT QueryInterface(I__ID iid, void** ppv);
        U__LONG AddRef();
        U__LONG Release();
        ColorFactory();
};

bool deletePath()
{
    ifstream file;
    ofstream file_out;
    file.open("C:\\Users\\dasew\\Desktop\\Homework\\C++\\2.2\\lab3\\manager\\Data.txt");
    if(!file) 
    {
        file.close();
        return false;
    }

    file_out.open("C:\\Users\\dasew\\Desktop\\Homework\\C++\\2.2\\lab3\\manager\\Data_new.txt");
    string str;
    CLS__ID id;
    
    while(getline(file, str))
    {
        istringstream iis(str, istringstream::in);
        iis >> id;
        if(id != CLSIDColor)
        {
            file_out << str;
        }
    }
    file.close();
    file_out.close();
    remove("C:\\Users\\dasew\\Desktop\\Homework\\C++\\2.2\\lab3\\manager\\Data.txt");
    rename("C:\\Users\\dasew\\Desktop\\Homework\\C++\\2.2\\lab3\\manager\\Data_new.txt", 
    "C:\\Users\\dasew\\Desktop\\Homework\\C++\\2.2\\lab3\\manager\\Data.txt");
    return true;
}

bool setPath() 
{
    deletePath();
    ofstream file("C:\\Users\\dasew\\Desktop\\Homework\\C++\\2.2\\lab3\\manager\\Data.txt", std::ios_base::in | std::ios_base::app);
    if(!file) 
    {
        file.close();
        return false;
    }
    
    file << "\n" << CLSIDColor << " " << path;
    file.close();
    return true;
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    GetModuleFileName(hinstDLL, path, MAX_PATH);
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
    if(clsid != CLSIDColor)
    {
        return E__CLASSNOTAVAILABLE;
    }
    ColorFactory* factory = new ColorFactory();
    if(factory == 0) 
    {
        return E_OUTOFMEMORY;
    }
    H__RESULT res = factory->QueryInterface(iid, ppv);
    return res;
}

class Color : public IMix, IPrint
{
    private:
        int countReference = 0;
        int r, g, b;
        bool check(int r, int g, int b);
    public:
        H__RESULT QueryInterface(I__ID iid, void** ppv);
        U__LONG AddRef();
        U__LONG Release();
        void mix(int r, int g, int b);
        void print();
        Color(int r, int g, int b);
};

bool Color::check(int r, int g, int b) 
{
    if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255) return true;
    else return false;
}

Color::Color(int r, int g, int b)
{
    if (check(r, g, b))
    {
        this->r = r;
        this->g = g;
        this->b = b;
    } else throw 0;
}
void Color::mix(int r, int g, int b) 
{
    if (check(r, g, b))
    {
        this->r = (this->r + r) / 2;
        this->g = (this->g + g) / 2;
        this->b = (this->b + b) / 2;
    } else throw 0;

}

void Color::print() 
{
    std::cout << "Color: " << r << " " << g << " " << b << std::endl;
}

U__LONG Color::AddRef() 
{
    countReference++;
    return countReference;
}

U__LONG Color::Release() 
{
    countReference--;
    if(countReference == 0)
    {
        delete this;
    }
    return countReference;
}

H__RESULT Color::QueryInterface(I__ID iid, void** ppv)
{
    switch (iid)
    {
        case IID__IUnknown:
        {
            *ppv = (I__Unknown*) (IMix*) this;
            break;
        }
        case IID__IMix:
        {
            *ppv = (IMix*) this;
            break;
        }
        case IID__IPrint:
        {
            *ppv = (IPrint*) this;
            break;
        }
        default:
        {
            *ppv = 0;
            return E_NOINTERFACE;
        }
    }
    AddRef();
    return S__OK;
}

ColorFactory::ColorFactory() {}

U__LONG ColorFactory::AddRef() 
{
    countReference++;
    return countReference;
}

U__LONG ColorFactory::Release() 
{
    countReference--;
    if(countReference == 0)
    {
        g_cComponents--;
        delete this;
    }
    return countReference;
}

H__RESULT ColorFactory::CreateInstance(I__ID iid, void** ppv)
{
    Color* color = new Color(0, 0, 0);
    if (color == 0)
    {
        return E__OUTOFMEMORY;
    }
    H__RESULT res = color->QueryInterface(iid, ppv);
    g_cComponents++;
    return res;
}

H__RESULT ColorFactory::QueryInterface(I__ID iid, void** ppv)
{
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

//________________Это не должно тут быть, но пусть пока побудет________________________________

class ColorWrapper
{
    private:
        ColorFactory* factory;
        IMix* iMix;
        IPrint* iPrint;

    public:
        void print();
        void mix(int r, int g, int b);
        ColorWrapper(int r, int g, int b);
        ~ColorWrapper();
};

ColorWrapper::ColorWrapper(int r, int g, int b)
{
    Get__ClassObject(CLSIDColor, IID__IClassFactory, (void**)&factory);
    factory->CreateInstance(IID__IMix, (void**)&iMix);
    factory->Release();
    iMix->QueryInterface(IID__IPrint, (void**)&iPrint);
}

ColorWrapper::~ColorWrapper() 
{
    iMix->Release();
    iPrint->Release();
}

void ColorWrapper::print() 
{
    iPrint->print();
}

void ColorWrapper::mix(int r, int g, int b)
{
    iMix->mix(r, g, b);
}

//_________________________________________________________________________________________