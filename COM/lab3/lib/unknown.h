#pragma once
typedef int H__RESULT;
typedef int I__ID;
typedef int CLS__ID;
typedef int U__LONG;

const H__RESULT S__OK = 1111;
const H__RESULT S__FALSE = -1111;
const H__RESULT E__NOINTERFACE = -1;
const H__RESULT E__OUTOFMEMORY = -2;
const H__RESULT E__CLASSNOTAVAILABLE = -3;

class I__Unknown {
    public:
        virtual H__RESULT QueryInterface(I__ID iid, void** ppv) = 0;
        virtual U__LONG AddRef() = 0;
        virtual U__LONG Release() = 0;
};

class I__ClassFactory : public I__Unknown
{
    private:
        int countReference = 0;
    public:
        virtual H__RESULT CreateInstance(I__ID iid, void** ppv) = 0;
        U__LONG AddRef()
        {
            countReference++;
            return countReference;
        }
        U__LONG Release() 
        {
            countReference--;
            if(countReference == 0)
            {
                delete this;
            }
            return countReference;
        }
};