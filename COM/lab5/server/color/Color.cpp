#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include "ColorAPI.h"
#include "windows.h"

const CLSID CLSIDColor = {0x91A42CAA,0x2577,0x4E80,{0x93,0x4E,0x07,0xDE,0x64,0x50,0x2F,0xD6}};

using namespace std;

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
        HRESULT __stdcall QueryInterface(const IID& iid, void** ppv);
        ULONG __stdcall AddRef();
        ULONG __stdcall Release();
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

class ColorFactory : public IClassFactory
{
    private:
        int countReference = 0;

    public:
        HRESULT __stdcall CreateInstance(IUnknown* pUnknownOuter, const IID& iid, void** ppv);
        HRESULT __stdcall QueryInterface(const IID& iid, void** ppv);
        HRESULT __stdcall LockServer(BOOL block);
        ULONG __stdcall AddRef();
        ULONG __stdcall Release();
        ColorFactory();
        ~ColorFactory();
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

ULONG __stdcall Color::AddRef() 
{
    trace("Color AddRef");
    countReference++;
    return countReference;
}

ULONG __stdcall Color::Release() 
{
    trace("Color Release");
    countReference--;
    if(countReference == 0)
    {
        delete this;
    }
    return countReference;
}

HRESULT __stdcall Color::QueryInterface(const IID& iid, void** ppv)
{
    trace("Color QueryInterface");
    if (iid == IID_IUnknown) {
        *ppv = (IUnknown*) (IMix*) this;
    } else if (iid == IID_IMix) {
        *ppv = (IMix*) this;
    } else if (iid == IID_IPrint) {
        *ppv = (IPrint*) this;
    } else if (iid == IID_IGet) {
        *ppv = (IGet*) this;
    } else if (iid == IID_ISet) {
        *ppv = (ISet*) this;
    } else {
        *ppv = 0;
        return E_NOINTERFACE;
    }
    AddRef();
    return S_OK;
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

ULONG __stdcall ColorFactory::AddRef() 
{
    trace("ColorFactory AddRef");
    countReference++;
    return countReference;
}

ULONG __stdcall ColorFactory::Release() 
{
    trace("ColorFactory Release");
    countReference--;
    if(countReference == 0)
    {
        delete this;
    }
    return countReference;
}

HRESULT __stdcall ColorFactory::CreateInstance(IUnknown* pUnknownOuter, const IID& iid, void** ppv)
{
    trace("ColorFactory CreateInstance");
    if (pUnknownOuter!=NULL)
    {
        return E_NOTIMPL;
    }
    Color* color = new Color(0, 0, 0);
    if (color == 0)
    {
        return E_OUTOFMEMORY;
    }
    HRESULT res = color->QueryInterface(iid, ppv);
    color->Release();
    return res;
}

HRESULT __stdcall ColorFactory::QueryInterface(const IID& iid, void** ppv)
{
    trace("ColorFactory QueryInterface");
    if (iid == IID_IUnknown) {
        *ppv = (IUnknown*) this;
    } else if (iid == IID_IClassFactory) {
        *ppv = (IClassFactory*) this;
    } else {
        *ppv = 0;
        return E_NOINTERFACE;
    }
    AddRef();
    return S_OK;
}

HRESULT __stdcall ColorFactory::LockServer(BOOL block) {
    trace("ColorFactory LockServer");
    return S_OK;
}

HRESULT __stdcall GetClassObject(const CLSID& clsid, const IID& iid, void** ppv)
{
    trace("Color getClassObject");
    if(clsid != CLSIDColor)
    {
        ppv = NULL;
        return E_NOTIMPL;
    }
    ColorFactory* factory = new ColorFactory();
    HRESULT res = factory->QueryInterface(iid, ppv);
    return res;
}