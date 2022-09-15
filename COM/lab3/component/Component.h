#pragma once
#include "../lib/unknown.h"

const I__ID IID__IUnknown = 0;
const I__ID IID__IClassFactory = 10;
const I__ID IID__IMix = 1;
const I__ID IID__IPrint = 2;
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

class IColorFactory : public I__Unknown
{
    public:
        virtual H__RESULT CreateInstance(I__ID iid, void** ppv) = 0;
};