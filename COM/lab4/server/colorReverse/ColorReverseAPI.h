#pragma once
#include "../../lib/unknown.h"

const I__ID IID__IReverse = 1021;
const CLS__ID CLSIDColorReverse = 102;

class IReverse : public I__Unknown 
{
    public:
        virtual void reverse() = 0;
};

class ColorReverseFactory : public I__ClassFactory
{
    private:
        int countReference = 0;

    public:
        H__RESULT CreateInstance(I__ID iid, void** ppv);
        H__RESULT QueryInterface(I__ID iid, void** ppv);
        U__LONG AddRef();
        U__LONG Release();
        ColorReverseFactory();
        ~ColorReverseFactory();
};