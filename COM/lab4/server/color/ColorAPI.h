#pragma once
#include "../../lib/unknown.h"

const I__ID IID__IMix = 1;
const I__ID IID__IPrint = 2;
const I__ID IID__IGet = 3;
const I__ID IID__ISet = 4;
const CLS__ID CLSIDColor = 101;

class IMix: public I__Unknown
{
    public:
        virtual void mix(int r, int g, int b) = 0;
};

class IPrint: public I__Unknown
{
    public:
        virtual void print() = 0;
};

class IGet: public I__Unknown
{
    public:
        virtual int getR() = 0;
        virtual int getG() = 0;
        virtual int getB() = 0;
};

class ISet: public I__Unknown
{
    public:
        virtual void setR(int r) = 0;
        virtual void setG(int g) = 0;
        virtual void setB(int b) = 0;
};

class ColorFactory : public I__ClassFactory
{
    private:
        int countReference = 0;

    public:
        H__RESULT CreateInstance(I__ID iid, void** ppv);
        H__RESULT QueryInterface(I__ID iid, void** ppv);
        U__LONG AddRef();
        U__LONG Release();
        ColorFactory();
        ~ColorFactory();
};