#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include "ColorAPI.h"
#include "../../lib/unknown.h"

using namespace std;

static int g_cComponents = 0;
TCHAR path[MAX_PATH];

void trace(const char* msg)
{
    cout << msg << endl;
};

//_____________________________________________________________________________________

class Color : public IMix, IPrint, IGet, ISet
{
    private:
        long countReference = 1;
        int r, g, b;
        bool check(int r, int g, int b);
    public:
        H__RESULT QueryInterface(I__ID iid, void** ppv);
        U__LONG AddRef();
        U__LONG Release();
        void mix(int r, int g, int b);
        void print();
        int getR();
        int getG();
        int getB();
        void setR(int r);
        void setG(int g);
        void setB(int b);
        Color(int r, int g, int b);
        ~Color();
};

bool Color::check(int r, int g, int b) 
{
    if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255) return true;
    else return false;
}

Color::Color(int r, int g, int b)
{
    trace("Color");
    if (check(r, g, b))
    {
        this->r = r;
        this->g = g;
        this->b = b;
    } else throw 0;
}

Color::~Color() 
{
    trace("~Color");
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

int Color::getR() 
{
    return r;
}

int Color::getG() 
{
    return g;
}

int Color::getB() 
{
    return b;
}

void Color::setR(int r) 
{
    if (r >= 0 && r <= 255)
    {
        this->r = r;
    }
}

void Color::setG(int g) 
{
    if (g >= 0 && g <= 255)
    {
        this->g = g;
    }
}

void Color::setB(int b) 
{
    if (b >= 0 && b <= 255)
    {
        this->b = b;
    }
}

U__LONG Color::AddRef() 
{
    trace("Color AddRef");
    countReference++;
    return countReference;
}

U__LONG Color::Release() 
{
    trace("Color Release");
    countReference--;
    if(countReference == 0)
    {
        delete this;
    }
    return countReference;
}

H__RESULT Color::QueryInterface(I__ID iid, void** ppv)
{
    trace("Color QueryInterface");
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

ColorFactory::ColorFactory() 
{
    trace("ColorFactory");
}

ColorFactory::~ColorFactory() 
{
    trace("~ColorFactory");
}

U__LONG ColorFactory::AddRef() 
{
    trace("ColorFactory AddRef");
    countReference++;
    return countReference;
}

U__LONG ColorFactory::Release() 
{
    trace("ColorFactory Release");
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
    trace("ColorFactory CreateInstance");
    Color* color = new Color(0, 0, 0);
    if (color == 0)
    {
        return E__OUTOFMEMORY;
    }
    H__RESULT res = color->QueryInterface(iid, ppv);
    g_cComponents++;
    color->Release();
    return res;
}

H__RESULT ColorFactory::QueryInterface(I__ID iid, void** ppv)
{
    trace("ColorFactory QueryInterface");
    switch (iid)
    {
        case IID__IUnknown:
        {
            *ppv = (I__Unknown*) this;
            break;
        } 
        case IID__IClassFactory:
        {
            *ppv = (I__ClassFactory*) this;
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
        if(id != CLSIDColor)
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
    
    file << "\n" << CLSIDColor << " " << path;
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