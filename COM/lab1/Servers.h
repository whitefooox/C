#include "IServers.h"

class Server : public IServer, public IServer2
{
public:
    void Func();
    void Func2();
    H_RESULT QueryInterface(I_ID iid, void** ppv);
};

class Server2 : public IServer, public IServer2
{
public:
    void Func();
    void Func2();
    H_RESULT QueryInterface(I_ID iid, void** ppv);
};

H_RESULT CreateInstance(CLS_ID clsid, I_ID iid, void** ppv);