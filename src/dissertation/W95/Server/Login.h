//---------------------------------------------------------------------------
#ifndef LoginH
#define LoginH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <winsock2.h>
//---------------------------------------------------------------------------

class CLogin : public TThread
{
private:
        int          connectionNo;
        int          sock, newsock;
        struct sockaddr_in server;
        int          addrlen;
        bool         acceptConx;
protected:
        void __fastcall Execute();
public:
        __fastcall CLogin(bool CreateSuspended);
        __fastcall ~CLogin();
        void Error(int code);
        void RejectConnections();
        void AcceptConnections();
};
//---------------------------------------------------------------------------

extern CLogin* Login;

#endif
