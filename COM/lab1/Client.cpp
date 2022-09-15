#include <iostream>
#include "Servers.h"

using namespace std;
int main()
{
    IServer* ppv;
    CLS_ID clsid = 1;
    I_ID iid = 1;
    if(CreateInstance(clsid, iid, (void**)&ppv) != 0)
    {
        cout << "Error";
        return 0;
    }
    ppv->Func();
}