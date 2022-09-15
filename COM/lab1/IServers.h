#include "I_Unknown.h"

class IServer : public I_Unknown
{
public:
    virtual void Func() = 0;
};

class IServer2 : public I_Unknown
{
public:
    virtual void Func2() = 0;
};