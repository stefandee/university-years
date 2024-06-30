//---------------------------------------------------------------------------
#include <vcl.h>
#include <winsock2.h>
#pragma hdrstop

#include "Vm.h"
#include "Console.h"
#include "Defs.h"

#pragma package(smart_init)

__fastcall CMachine::CMachine(bool CreateSuspended, int socketNo, struct sockaddr_in info)
        : TThread(CreateSuspended)
{
  FreeOnTerminate = false;
  sock            = socketNo;
  machineIP       = AnsiString(inet_ntoa(info.sin_addr));
  sending         = false;
  receiving       = false;
  data            = NULL;
  SetThreadPriority((void*)Handle, THREAD_PRIORITY_LOWEST);
}
//---------------------------------------------------------------------------

void __fastcall CMachine::Execute()
{
  if (!Terminated) Ping(PACKET_SIZE);
  if (!Terminated) RequestMachineInfo();

  while(!Terminated)
  {
    // terminate if there's no response
    if (receiving)
    {
      RecvData();
      receiving = false;
    }

    if (sending)
    {
      SendData(); 
      sending = false;
    }
  }
}
//---------------------------------------------------------------------------

void CMachine::Error(int code)
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
    case WRONG_REPLY_ID	        :
      formConsole->AddMessage("Reply idd is wrong");
      break;
    case WSAENOTCONN            :
      formConsole->AddMessage("Socket is not connected");
      break;
    case WSAENOTSOCK            :
      formConsole->AddMessage("Not a socket");
      break;
    case WSAEOPNOTSUPP	        :
      formConsole->AddMessage("OOB not supported or receive op only");
      break;
    case WSAESHUTDOWN           :
      formConsole->AddMessage("Socket was shut down");
      break;
    case WSAEWOULDBLOCK         :
      formConsole->AddMessage("Socket is unblocking, op will block");
      break;
    case WSAEMSGSIZE            :
      formConsole->AddMessage("Socket is msg oriented, message is larger than required");
      break;
    case WSAEHOSTUNREACH	:
      formConsole->AddMessage("Host unreachable");
      break;
    case WSAEINVAL              :
      formConsole->AddMessage("Crap error #1");
      break;
    case WSAECONNABORTED        :
      formConsole->AddMessage("The virtual circuit was terminated due to a time-out or other failure. The application should close the socket as it is no longer usable.");
      break;
    case WSAECONNRESET          :
      formConsole->AddMessage("Connection reset");
      break;
    case WSAETIMEDOUT	        :
      formConsole->AddMessage("Connection timed out");
      break;
    case WSAEACCES	        :
      formConsole->AddMessage("The requested address is a broadcast address, but the appropriate flag was not set.");
      break;
    case WSAEINTR	        :
      formConsole->AddMessage("The (blocking) call was canceled through WSACancelBlockingCall.");
      break;
    case WSAEFAULT	        :
      formConsole->AddMessage("The buf argument is not totally contained in a valid part of the user address space.");
      break;
    case WSAENETRESET	        :
      formConsole->AddMessage("The connection has been broken due to the remote host resetting.");
      break;
    case WRONG_ACK              :
      formConsole->AddMessage("Receiving acknowledge failed");
      break;
    case WRONG_DATA_PTR         :
      formConsole->AddMessage("Cannot receive send data...pointer was not set");
      break;
    default                     :
      formConsole->AddMessage("Unknown error code");
      break;
  }
}
//---------------------------------------------------------------------------

__fastcall CMachine::~CMachine()
{
  closesocket(sock);
}
//---------------------------------------------------------------------------

void CMachine::Ping(int packetSize)
{
  int  startTime;
  char pingCmd[5];
  char pingReply[3];

  //if (packetSize > SO_MSG_MAX_SIZE) packetSize = SO_MSG_MAX_SIZE;

  // setez timpul la valoarea neconoscuta
  pingTime = UNK_PINGTIME;

  // trimit comanda
  strcpy(pingCmd, "PING");

  if (send(sock, pingCmd, strlen(pingCmd) + 1, 0) == SOCKET_ERROR)
  {
    Error(WSAGetLastError());
    return;
  }

  // trimit lungimea
  if (send(sock, (char*)(&packetSize), sizeof(packetSize), 0) == SOCKET_ERROR)
  {
    Error(WSAGetLastError());
    return;
  }

  // trimit paketul
  char* packet = new char[packetSize];
  startTime = GetTickCount();
  if (send(sock, packet, packetSize, 0) == SOCKET_ERROR)
  {
    Error(WSAGetLastError());
    delete packet;
    return;
  }

  // astept reply
  if (recv(sock, pingReply, 3, 0) == SOCKET_ERROR)
  {
    Error(WSAGetLastError());
    return;
  }

  pingTime = GetTickCount() - startTime;

  delete packet;

  if (strcmp(pingReply, "OK") != 0)
  {
    Error(WRONG_REPLY_ID);
    return;
  }
}
//---------------------------------------------------------------------------

AnsiString CMachine::GetIP()
{
  return machineIP;
}
//---------------------------------------------------------------------------

AnsiString CMachine::GetPingTime()
{
  if (pingTime != UNK_PINGTIME) return AnsiString(pingTime);
  else return AnsiString("n/a");
}
//---------------------------------------------------------------------------

void CMachine::RequestMachineInfo()
{
  char infoCmd[5];
  TRemoteMachineInfo machineInfo;

  // trimit comanda
  strcpy(infoCmd, "INFO");

  if (send(sock, infoCmd, 5, 0) == SOCKET_ERROR)
  {
    Error(WSAGetLastError());
    return;
  }

  // primesc informatia
  if (recv(sock, (char*)&machineInfo, sizeof(machineInfo), 0) == SOCKET_ERROR)
  {
    Error(WSAGetLastError());
    return;
  }                         

  // completez cimpurile
  machineProc     = AnsiString(machineInfo.processor);
  machineMemTotal = AnsiString(machineInfo.memoryTotal);
  machineMemFree  = AnsiString(machineInfo.memoryFree);
  machineOs       = AnsiString(machineInfo.os);
  machineVersion  = AnsiString(machineInfo.majorVersion) + "." + AnsiString(machineInfo.minorVersion);
  machineSpeed    = AnsiString::FormatFloat("0.00" ,machineInfo.speed);
  machineName     = AnsiString(machineInfo.computerName);
  machineUser     = AnsiString(machineInfo.userName);
}
//---------------------------------------------------------------------------

AnsiString  CMachine::GetMachineSpeed()
{
  return machineSpeed;
}
//---------------------------------------------------------------------------

AnsiString  CMachine::GetMachineOs()
{
  return machineOs;
}
//---------------------------------------------------------------------------

AnsiString  CMachine::GetProcessorName()
{
  return machineProc;
}
//---------------------------------------------------------------------------

AnsiString  CMachine::GetOsVersion()
{
  return machineVersion;
}
//---------------------------------------------------------------------------

AnsiString  CMachine::GetMemoryInfo()
{
  return machineMemFree + "/" + machineMemTotal;
}
//---------------------------------------------------------------------------

AnsiString  CMachine::GetMachineName()
{
  return machineName;
}
//---------------------------------------------------------------------------

AnsiString  CMachine::GetUser()
{
  return machineUser;
}
//---------------------------------------------------------------------------

bool CMachine::hasFinished()
{
  return Terminated;
}
//---------------------------------------------------------------------------

void CMachine::SendConfiguration(int iNoMin, int iNoMax, int hNoMin, int hNoMax, int oNoMin, int oNoMax, int inputsNo, int hiddenNo, int outputsNo, float learningRate, bool isMomentumTerm, float momentumTerm, int saveCount, bool hasBeenTrained)
{
  char cfgCmd[5];
  TPartitionInfo toSend;
  int  values[9];
  char ack[3];

  strcpy(cfgCmd, CMD_NET_CFG);
  // trimit comanda la client
  if (send(sock, cfgCmd, 5, 0) == SOCKET_ERROR)
  {
    Error(WSAGetLastError());
    Terminate();
    return;
  }

  // trimit vectorul de valori
  /*
  values[0] = inputsNo;
  values[1] = hiddenNo;
  values[2] = outputsNo;
  values[3] = iNoMin;
  values[4] = iNoMax;
  values[5] = hNoMin;
  values[6] = hNoMax;
  values[7] = oNoMin;
  values[8] = oNoMax;
  */
  toSend.inputsNo  = inputsNo;
  toSend.hiddenNo  = hiddenNo;
  toSend.outputsNo = outputsNo;
  toSend.iMin      = iNoMin;
  toSend.iMax      = iNoMax;
  toSend.hMin      = hNoMin;
  toSend.hMax      = hNoMax;
  toSend.oMin      = oNoMin;
  toSend.oMax      = oNoMax;
  toSend.learningRate   = learningRate;
  toSend.isMomentumTerm = isMomentumTerm;
  toSend.momentumTerm   = momentumTerm;
  toSend.saveCount      = saveCount;
  toSend.hasBeenTrained = hasBeenTrained;

  if (send(sock, (char*)(&toSend), sizeof(TPartitionInfo), 0) == SOCKET_ERROR)
  {
    Error(WSAGetLastError());
    Terminate();
    return;
  }

  if (recv(sock, ack, 3, 0) == SOCKET_ERROR)
  {
    Error(WSAGetLastError());
    Terminate();
    return;
  }

  if (strcmp(ack, "OK") != 0)
  {
    Error(WRONG_ACK);
    Terminate();
    return;
  }

  formConsole->AddMessage("Configuration sent");
}
//---------------------------------------------------------------------------

bool CMachine::IsConfigured()
{
  return configured;
}
//---------------------------------------------------------------------------

void CMachine::SendCommand(const char* command)
{
  char* cmd = new char[strlen(command) + 1];

  // trimit comanda
  strcpy(cmd, command);

  if (send(sock, cmd, strlen(command) + 1, 0) == SOCKET_ERROR)
  {
    Error(WSAGetLastError());
    Terminate();
  }

  delete cmd;
}
//---------------------------------------------------------------------------

void CMachine::SetData(float* what, int length)
{
  data       = what;
  dataLength = length; 
}
//---------------------------------------------------------------------------

void CMachine::SendData()
{
  if (data != NULL)
  {
    // trimit lungimea, si dup'aia datele
    if (send(sock, (char*)&dataLength, sizeof(int), 0) == SOCKET_ERROR)
    {
      Error(WSAGetLastError());
      Terminate();
      return;
    }

    //formConsole->AddMessage("Sending : " + AnsiString(dataLength));

    // am lungimea, trimit bucati de 64 de floati
    for(int i = 0; i < dataLength / 64; i++)
    {
      //formConsole->AddMessage("Ce naiba caut aici ?");
      if (send(sock, (char*)(data + 64 * i), sizeof(float) * 64, 0) == SOCKET_ERROR)
      {
        Error(WSAGetLastError());
        Terminate();
        return;
      }
    }

    // au mai ramas de trimis "citiva" floati...
    int remains = dataLength % 64;
    if (remains != 0)
    {
      //formConsole->AddMessage("Sending : " + AnsiString(remains));
      if (send(sock, (char*)(data + dataLength - remains), sizeof(float) * remains, 0) == SOCKET_ERROR)
      {
        Error(WSAGetLastError());
        Terminate();
        return;
      }
    }

    /*
    // aici trebuie refacut, dar pentru inceput testez cu pachete mici < 1024b
    if (send(sock, (char*)data, sizeof(float) * dataLength, 0) == SOCKET_ERROR)
    {
      Error(WSAGetLastError());
      Terminate();
      return;
    }
    */
  }
  else
  {
    Error(WRONG_DATA_PTR);
    Terminate();
    return;
  }
}
//---------------------------------------------------------------------------

void CMachine::RecvData()
{
  if (data != NULL)
  {
    // primesc lungimea
    if (recv(sock, (char*)&dataLength, sizeof(int), 0) == SOCKET_ERROR)
    {
      Error(WSAGetLastError());
      Terminate();
      return;
    }

    //formConsole->AddMessage("Receiving : " + AnsiString(dataLength));

    // am lungimea, citesc bucati de 64 de floati
    for(int i = 0; i < dataLength / 64; i++)
    {
      //formConsole->AddMessage("Ce naiba caut aici ?");
      if (recv(sock, (char*)(data + i * 64), sizeof(float) * 64, 0) == SOCKET_ERROR)
      {
        Error(WSAGetLastError());
        Terminate();
        return;
      }
    }

    // au mai ramas de citit "citiva" floati ...
    int remains = dataLength % 64;
    if (remains != 0)
    {
      //formConsole->AddMessage("Receiving : " + AnsiString(remains));
      if (recv(sock, (char*)(data + dataLength - remains), sizeof(float) * remains, 0) == SOCKET_ERROR)
      {
        Error(WSAGetLastError());
        Terminate();
        return;
      }
    }

    /*
    // aici trebuie refacut, dar pentru inceput testez cu pachete mici < 1024b
    if (recv(sock, (char*)data, sizeof(float) * dataLength, 0) == SOCKET_ERROR)
    {
      Error(WSAGetLastError());
      Terminate();
      return;
    }
    */
  }
  else
  {
    Error(WRONG_DATA_PTR);
    Terminate();
    return;
  }
}
//---------------------------------------------------------------------------

void CMachine::GoReceiving()
{
  receiving = true;
}
//---------------------------------------------------------------------------

void CMachine::GoSending()
{
  sending = true;
}
//---------------------------------------------------------------------------

bool CMachine::GetRecvStatus()
{
  return receiving;
}
//---------------------------------------------------------------------------

bool CMachine::GetSendStatus()
{
  return sending;
}
//---------------------------------------------------------------------------


