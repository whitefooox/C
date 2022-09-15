typedef int H_RESULT;
typedef int I_ID;
typedef int CLS_ID;

class I_Unknown {
    public:
        virtual H_RESULT QueryInterface(I_ID iid, void** ppv) = 0;
};