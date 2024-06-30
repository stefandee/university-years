//---------------------------------------------------------------------------
#include <vcl.h>
//#include <winsock.h>
#include <winsock2.h>
#pragma hdrstop

#include "Login.h"
#include "Defs.h"
#include "Vm.h"
#include "Console.h"
#include "MManager.h"

CLogin* Login;

#pragma package(smart_init)
//---------------------------------------------------------------------------
//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall CLogin::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
__fastcall CLogin::CLogin(bool CreateSuspended)
        : TThread(CreateSuspended)
{
  FreeOnTerminate = true;
  connectionNo = 0;

  // windoze stupid function
  WSADATA data;
  WORD    versionRequested = MAKEWORD(WINSOCK_MAJOR, WINSOCK_MINOR);

  WSAStartup(versionRequested, &data);
  if ( LOBYTE( data.wVersion ) != WINSOCK_MAJOR ||
       HIBYTE( data.wVersion ) != WINSOCK_MINOR )
  {
      Error(WSA_START_ERR);
      WSACleanup();
      return;
  }

  if((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
  {
    //Application->MessageBox("ERR GETTING SOCKET", "ERR", ID_OK);
    Error(WSAGetLastError());
    return;
  }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(SERVER_PORT);
  addrlen = sizeof(server);

  if (bind(sock, (struct sockaddr*)&server, addrlen) == SOCKET_ERROR)
  {
    //Application->MessageBox("ERR BINDING", "ERR", ID_OK);
    Error(WSAGetLastError());
    return;
  }

  if (listen(sock, MAX_CONNECTIONS_ALLOWED) == -1)
  {
    Error(WSAGetLastError());
    return;
  }

  RejectConnections();
}
//---------------------------------------------------------------------------

void __fastcall CLogin::Execute()
{
  while(1)
  {
    if (acceptConx)
    {
      if (connectionNo < MAX_CONNECTIONS_ALLOWED)
      {
        newsock = accept(sock, (struct sockaddr*) &server, &addrlen);

        if (newsock == INVALID_SOCKET)
        {
          //formConsole->AddMessage("Error accepting socket");
          //Application->MessageBox("ERR ACCEPTING", "ERR", ID_OK);
          //printf("Fatal : accept failed. Closing connection...\n");
          //Terminate();
        }
        else
        {
          // creez o masina virtuala si o initializez cu newsock
          MManager->AddMachine(new CMachine(false, newsock, server));
          connectionNo++;
        }
      }
      else RejectConnections();
    }  
  }
}
//---------------------------------------------------------------------------

void CLogin::Error(int code)
{
  switch(code)
  {
    case WSANOTINITIALISED      :
      formConsole->AddMessage("Not initialized");
      break;
    case WSAENETDOWN            :
      formConsole->AddMessage("Net is down");
      break;
    case WSAEAFNOSUPPORT	:
      formConsole->AddMessage("Specified protocol family is not supported");
      break;
    case WSAEINPROGRESS	        :
      formConsole->AddMessage("Something in progress");
      break;
    case WSAEMFILE		:
      formConsole->AddMessage("No more socket descriptors");
      break;
    case WSAENOBUFS	        :
      formConsole->AddMessage("No buffer space available");
      break;
    case WSAEPROTONOSUPPORT	:
      formConsole->AddMessage("Protocol is not supported");
      break;
    case WSAEPROTOTYPE	        :
      formConsole->AddMessage("Protocol is wrong for this socket type");
      break;
    case WSAESOCKTNOSUPPORT	:
      formConsole->AddMessage("The specified socket type is not supported in this address family");
      break;
    case WSA_START_ERR          :
      formConsole->AddMessage("Cannot start socket DLL");
      break;
    default                     :
      formConsole->AddMessage("Unknown error code");
      break;
  }
}
//---------------------------------------------------------------------------

__fastcall CLogin::~CLogin()
{
  WSACleanup();
}
//---------------------------------------------------------------------------

void CLogin::RejectConnections()
{
  acceptConx = false;
}
//---------------------------------------------------------------------------

void CLogin::AcceptConnections()
{
  acceptConx = true;
}
//---------------------------------------------------------------------------

