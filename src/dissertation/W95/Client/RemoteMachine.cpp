//---------------------------------------------------------------------------
#include <vcl.h>
#include <winbase.h>
#include <stdlib.h>
#include <math.h>
#pragma hdrstop

#include "RemoteMachine.h"
#include "Console.h"
#include "Defs.h"
#include "Main.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

CRemoteMachine* RemoteMachine;

__fastcall CRemoteMachine::CRemoteMachine(bool CreateSuspended, AnsiString ipAddr, u_short port)
        : TThread(CreateSuspended)
{
  FreeOnTerminate = true;
  SetThreadPriority((void*)Handle, THREAD_PRIORITY_NORMAL);

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

  if((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
  {
    Error(WSAGetLastError());
    Terminate();
  }

  struct sockaddr_in server;
  u_long server_addr     = inet_addr(ipAddr.c_str());
  server.sin_family      = AF_INET;
  server.sin_addr.s_addr = server_addr;
  server.sin_port        = htons(port);
  int addrlen            = sizeof(server);

  if (connect(sock, (struct sockaddr*)&server, addrlen) == SOCKET_ERROR)
  {
    Error(WSAGetLastError());
    Terminate();
  }

  ihWeights = NULL;
  hoWeights = NULL;
  inputs    = NULL;
  hidden    = NULL;
  outputs   = NULL;
  target    = NULL;
  deltaO    = NULL;
  deltaH    = NULL;
  package   = NULL;
  inputsNo  = 0;
  outputsNo = 0;
  hiddenNo  = 0;
  readyMem  = false;
}
//---------------------------------------------------------------------------

void __fastcall CRemoteMachine::RestoreButtons()
{
  MainForm->sbConnect->Enabled    = true;
  MainForm->sbDisConnect->Enabled = false;
}
//---------------------------------------------------------------------------


__fastcall CRemoteMachine::~CRemoteMachine()
{
  delete inputs;
  delete hidden;
  delete outputs;
  delete target;
  delete deltaH;
  delete deltaO;
  delete package;
  delete ihWeights;
  delete hoWeights;
  delete packageSend;

  Synchronize(RestoreButtons);
  // e cam dubios, ar trebui sincronizata
  formConsole->AddMessage("Connection terminated. Please reconnect");
  closesocket(sock);
  WSACleanup();
}
//---------------------------------------------------------------------------

void CRemoteMachine::Error(int code)
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
    case WRONG_PING_ID  	:
      formConsole->AddMessage("Cannot identify the server - server is a fake (PING request)");
      break;
    case WRONG_INFO_ID  	:
      formConsole->AddMessage("Cannot identify the server - server is a fake (INFO request)");
      break;
    default                     :
      formConsole->AddMessage("Unknown error code");
      break;
  }
}
//---------------------------------------------------------------------------

void CRemoteMachine::Pong()
{
  char pingCmd[5];
  char pingReply[3];
  int  packetSize;

  // primesc id'ul
  if (recv(sock, pingCmd, 5, 0) == SOCKET_ERROR)
  {
    Error(WSAGetLastError());
    return;
  }

  // compar cu PING
  if (strcmp(pingCmd, "PING") != 0)
  {
    Error(WRONG_PING_ID);
    return;
  }

  // primesc lungimea
  if (recv(sock, (char*)(&packetSize), sizeof(packetSize), 0) == SOCKET_ERROR)
  {
    Error(WSAGetLastError());
    return;
  }

  // primesc paketul
  char* packet = new char[packetSize];
  if (recv(sock, packet, packetSize, 0) == SOCKET_ERROR)
  {
    Error(WSAGetLastError());
    delete packet;
    return;
  }

  delete packet;

  // trimit reply
  strcpy(pingReply, "OK");
  if (send(sock, pingReply, strlen(pingReply) + 1, 0) == SOCKET_ERROR)
  {
    Error(WSAGetLastError());
    return;
  }
}
//---------------------------------------------------------------------------

void CRemoteMachine::SendMachineInfo()
{
  char infoCmd[5];
  TRemoteMachineInfo machineInfo;

  // primesc id'ul
  if (recv(sock, infoCmd, 5, 0) == SOCKET_ERROR)
  {
    Error(WSAGetLastError());
    return;
  }

  // compar cu INFO
  if (strcmp(infoCmd, "INFO") != 0)
  {
    Error(WRONG_INFO_ID);
    return;
  }

  // completez cimpurile
  // sistemul de operare si versiunea
  OSVERSIONINFO vi;
  vi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
  GetVersionEx(&vi);
  machineInfo.majorVersion = vi.dwMajorVersion;
  machineInfo.minorVersion = vi.dwMinorVersion;
  switch(vi.dwPlatformId)
  {
    case VER_PLATFORM_WIN32_NT       :
      strcpy(machineInfo.os, "Windows NT");
      break;
    case VER_PLATFORM_WIN32_WINDOWS  :
      strcpy(machineInfo.os, "Windows 95");
      break;
    case VER_PLATFORM_WIN32s	  :
      strcpy(machineInfo.os, "Windows 3.1");
      break;
    default :
      strcpy(machineInfo.os, "Unknown platform");
      break;
  }
  strcat(machineInfo.os, vi.szCSDVersion);

  // informatiii despre memorie si procesor
  SYSTEM_INFO si;

  GetSystemInfo(&si);
  switch(si.wProcessorArchitecture)
  {
    case PROCESSOR_ARCHITECTURE_INTEL :
      strcpy(machineInfo.processor, "Intel architecture ");
      break;
    case PROCESSOR_ARCHITECTURE_MIPS  :
      strcpy(machineInfo.processor, "Mips ");
      break;
    case PROCESSOR_ARCHITECTURE_ALPHA :
      strcpy(machineInfo.processor, "Alpha ");
      break;
    case PROCESSOR_ARCHITECTURE_PPC   :
      strcpy(machineInfo.processor, "PPC ");
      break;
    case PROCESSOR_ARCHITECTURE_UNKNOWN :
      strcpy(machineInfo.processor, "Unknown ");
      break;
  }

  switch(si.dwProcessorType)
  {
    case PROCESSOR_INTEL_386 :
      strcat(machineInfo.processor, "386 ");
      break;
    case PROCESSOR_INTEL_486 :
      strcat(machineInfo.processor, "486 ");
      break;
    case PROCESSOR_INTEL_PENTIUM :
      strcat(machineInfo.processor, "Pentium");
      break;
    case PROCESSOR_MIPS_R4000 :
      strcat(machineInfo.processor, "R4000");
      break;
    case PROCESSOR_ALPHA_21064 :
      strcat(machineInfo.processor, "Mips");
      break;
  }
  machineInfo.speed = ComputeMachineSpeed();

  // memoria
  MEMORYSTATUS ms;
  ms.dwLength = sizeof(MEMORYSTATUS);
  GlobalMemoryStatus(&ms);

  machineInfo.memoryTotal = (ms.dwTotalPhys + 1) / (1024 * 1024);
  machineInfo.memoryFree  = ms.dwAvailPhys / (1024 * 1024);

  // alte informatii
  unsigned long size = 64;
  GetComputerName(machineInfo.computerName, &size);
  size = 64;
  GetUserName(machineInfo.userName, &size);

  // trimit informatia
  if (send(sock, (char*)&machineInfo, sizeof(machineInfo), 0) == SOCKET_ERROR)
  {
    Error(WSAGetLastError());
    return;
  }
}
//---------------------------------------------------------------------------

float CRemoteMachine::ComputeMachineSpeed()
{
  float a, b = 178953.0;
  int startTime = GetTickCount(), totalTime;

  for(int i = 0; i < 1000000; i++)
  {
    a = b / 153.0;
  }

  totalTime = GetTickCount() - startTime;
  if (totalTime == 0) return 1000.0;
  else return (1000.0 / totalTime);
}
//---------------------------------------------------------------------------

void CRemoteMachine::RecvConfiguration()
{
  char cmd[5];
  TPartitionInfo toRecv;
  int* values = new int[9];
  enum {cmd_none, cmd_start, cmd_cfg} cmdId;
  struct timeval timeOut = {1, 0};
  //bool  dataReady;
  fd_set socketList;
  //int selResult;

  cmdId = cmd_none;

  FD_ZERO(&socketList);
  FD_SET(sock, &socketList);

  while ((!Terminated) && (cmdId != cmd_start))
  {
    // primesc comanda
    /*
    dataReady = false;
    while(!Terminated)
    {
      if (Terminated) return;

      selResult = select(0, &socketList, NULL, NULL, &timeOut);

      // vad daca nu cumva a fost eroare
      if (selResult == SOCKET_ERROR)
      {
        Error(WSAGetLastError());
        TThread::Terminate();
        return;
      }

      // testez daca am date de citit
      if (selResult == 1)
      {
        dataReady = true;
      }

      if (dataReady) break;

    }
    */

    if (recv(sock, cmd, 5, 0) == SOCKET_ERROR)
    {
      Error(WSAGetLastError());
      TThread::Terminate();
      return;
    }

    if (strcmp(cmd, CMD_NET_CFG) == 0)
    {
      // citesc valorile iMin, iMax , etc
      if (recv(sock, (char*)(&toRecv), sizeof(TPartitionInfo), 0) == SOCKET_ERROR)
      {
        Error(WSAGetLastError());
        TThread::Terminate();
        return;
      }

      formConsole->AddMessage("Incoming transmission...");

      /*
      // completez valorile
      inputsNo  = values[0];
      hiddenNo  = values[1];
      outputsNo = values[2];
      iMin      = values[3];
      iMax      = values[4];
      hMin      = values[5];
      hMax      = values[6];
      oMin      = values[7];
      oMax      = values[8];
      */

      inputsNo  = toRecv.inputsNo;
      hiddenNo  = toRecv.hiddenNo;
      outputsNo = toRecv.outputsNo;
      iMin      = toRecv.iMin;
      iMax      = toRecv.iMax;
      hMin      = toRecv.hMin;
      hMax      = toRecv.hMax;
      oMin      = toRecv.oMin;
      oMax      = toRecv.oMax;
      learningRate   = toRecv.learningRate;
      isMomentumTerm = toRecv.isMomentumTerm;
      momentumTerm   = toRecv.momentumTerm;
      hasBeenTrained = toRecv.hasBeenTrained;
      saveCount      = toRecv.saveCount;

      formConsole->AddMessage("Inputs : " + AnsiString(inputsNo) + ", Hidden : " + AnsiString(hiddenNo) + ", Outputs : " + AnsiString(outputsNo));
      formConsole->AddMessage("Inputs : " + AnsiString(iMin) + " to " + AnsiString(iMax));
      formConsole->AddMessage("Hidden : " + AnsiString(hMin) + " to " + AnsiString(hMax));
      formConsole->AddMessage("Outputs : " + AnsiString(oMin) + " to " + AnsiString(oMax));
      formConsole->AddMessage("Will send weights after " + AnsiString(saveCount) + " patterns");

      ConfigureNet();
      if (!MemoryIsReady())
      {
        formConsole->AddMessage("Memory is not ready");
        TThread::Terminate();
      }

      cmdId = cmd_cfg;
      formConsole->AddMessage("Configuration received succesfully");

      strcpy(cmd, "OK");
      if (send(sock, cmd, 3, 0) == SOCKET_ERROR)
      {
        Error(WSAGetLastError());
        TThread::Terminate();
        return;
      }
    }
    else
    {
      if (strcmp(cmd, CMD_START) == 0)
      {
        formConsole->AddMessage("Server will start in a moment...");
        cmdId = cmd_start;
      }
      else cmdId = cmd_none;
    }

    strcpy(cmd, " ");
  }

  delete values;
}
//---------------------------------------------------------------------------

void CRemoteMachine::ConfigureNet()
{
  //inputsNo  = iNo;
  //hiddenNo  = hNo;
  //outputsNo = oNo;

  if (inputs    != NULL)
  {
    delete inputs;
    inputs = NULL;
  }
  
  if (outputs   != NULL)
  {
   delete outputs;
   outputs = NULL;
  }

  if (target    != NULL)
  {
   delete target;
   target = NULL;
  }

  if (hidden    != NULL) 
  {
   delete hidden;
   hidden = NULL;
  }

  if (deltaH    != NULL)
  {
   delete deltaH;
   deltaH = NULL;
  }

  if (deltaO    != NULL)
  {
   delete deltaO;
   deltaO = NULL;
  }

  if (package != NULL)
  {
   delete package;
   package = NULL;
  }

  if (packageSend != NULL)
  {
   delete packageSend;
   packageSend = NULL;
  }

  if (ihWeights != NULL)
  {
   delete ihWeights;
   ihWeights = NULL;
  }

  if (hoWeights != NULL)
  {
   delete hoWeights;
   hoWeights = NULL;
  }

  try
  {
    inputs    = new float[inputsNo];
    hidden    = new float[hiddenNo];
    outputs   = new float[outputsNo];
    target    = new float[(oMax - oMin)];
    deltaH    = new float[(hMax - hMin)];
    deltaO    = new float[(oMax - oMin)];
    package   = new float[(hMax - hMin) * MAX_CONNECTIONS_ALLOWED];
    ihWeights = new float[inputsNo * (hMax - hMin)];
    hoWeights = new float[hiddenNo * (oMax - oMin)];
    packageSend = new float[hiddenNo];
  }
  catch(...)
  {
    formConsole->AddMessage("Cannot alloc memory");
    inputsNo  = 0;
    hiddenNo  = 0;
    outputsNo = 0;
    return;
  }

  // trebuie acordata foarte mare atentie modului in
  // care se initializeaza ponderile; valori ne-aleatoare
  // pot duce la comportari "anormale" ale retelei neuronale 
  for(int i = 0; i < hMax - hMin; i++)
  {
    for(int j = 0; j < inputsNo; j++)
      ihWeights[j + i * inputsNo] = (-0.5 + (float)random(2000)/2000.0) / 2;
  }

  for(int i = 0; i < hiddenNo; i++)
  {
    for(int j = 0; j < oMax - oMin; j++)
      hoWeights[i + j * hiddenNo] = (-0.5 + (float)random(2000)/2000.0) / 2;
  }
}
//---------------------------------------------------------------------------

bool CRemoteMachine::MemoryIsReady()
{
  if (inputsNo  <= 0) readyMem = false;
  if (outputsNo <= 0) readyMem = false;
  if (hiddenNo  <= 0) readyMem = false;

  if ((inputs    != NULL) &&
      (outputs   != NULL) &&
      (target    != NULL) &&
      (hidden    != NULL) &&
      (deltaH    != NULL) &&
      (deltaO    != NULL) &&
      (package   != NULL) &&
      (packageSend != NULL) &&
      (ihWeights != NULL) &&
      (hoWeights != NULL)
     ) readyMem = true;
  else readyMem = false;

  return readyMem;
}
//---------------------------------------------------------------------------

void CRemoteMachine::SendData(float* data, int dataLength)
{
  // trimit lungimea, si dup'aia datele
  if (send(sock, (char*)&dataLength, sizeof(int), 0) == SOCKET_ERROR)
  {
    Error(WSAGetLastError());
    TThread::Terminate();
    return;
  }

  //formConsole->AddMessage("Sending : " + AnsiString(dataLength));

  // am lungimea, citesc bucati de 64 de floati
  for(int i = 0; i < dataLength / 64; i++)
  {
    if (send(sock, (char*)(data + i * 64), sizeof(float) * 64, 0) == SOCKET_ERROR)
    {
      Error(WSAGetLastError());
      TThread::Terminate();
      return;
    }
  }

  // au mai ramas de citit "citiva" floati ...
  int remains = dataLength % 64;
  if (remains != 0)
  {
    //formConsole->AddMessage("Sending : " + AnsiString(remains));
    if (send(sock, (char*)(data + dataLength - remains), sizeof(float) * remains, 0) == SOCKET_ERROR)
    {
      Error(WSAGetLastError());
      TThread::Terminate();
      return;
    }
  }
  /*
  // aici trebuie refacut, dar pentru inceput testez cu pachete mici < 1024b
  if (send(sock, (char*)data, sizeof(float) * dataLength, 0) == SOCKET_ERROR)
  {
    Error(WSAGetLastError());
    TThread::Terminate();
  }
  */
}
//---------------------------------------------------------------------------

int CRemoteMachine::RecvData(float* data)
{
  int dataLength;

  // primesc lungimea
  if (recv(sock, (char*)&dataLength, sizeof(int), 0) == SOCKET_ERROR)
  {
    Error(WSAGetLastError());
    TThread::Terminate();
    return -1;
  }

  //formConsole->AddMessage("Receiving : " + AnsiString(dataLength));

  // am lungimea, citesc bucati de 64 de floati
  for(int i = 0; i < dataLength / 64; i++)
  {
    if (recv(sock, (char*)(data + i * 64), sizeof(float) * 64, 0) == SOCKET_ERROR)
    {
      Error(WSAGetLastError());
      TThread::Terminate();
      return -1;
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
      TThread::Terminate();
      return -1;
    }
  }

  /*
  // aici trebuie refacut, dar pentru inceput testez cu pachete mici < 1024b
  if (recv(sock, (char*)data, sizeof(float) * dataLength, 0) == SOCKET_ERROR)
  {
    Error(WSAGetLastError());
    TThread::Terminate();
  }
  */

  return dataLength;
}
//---------------------------------------------------------------------------

float CRemoteMachine::theFunction(float x)
{
  float result;

  try
  {
    if (x > 10.0) x = 10.0;
    if (x < -10.0) x = -10.0;
    result = (1.0 / (1.0 + exp(-x)));
  }
  catch(...)
  {
    formConsole->AddMessage("Overload");
    result = 0.02;
  }

  return result;
}
//---------------------------------------------------------------------------

void __fastcall CRemoteMachine::Execute()
{
  float      net, oldValue;
  int        i, j;
  int        packageSize;
  AnsiString line;

  if (!Terminated) Pong();
  if (!Terminated) SendMachineInfo();
  if (!Terminated) RecvConfiguration();

  if (hasBeenTrained)
  {
    formConsole->AddMessage("Getting starting weights...");
    GetWeights();
  }

  patternsPresented = 0;

  while(!Terminated)
  {
    // primesc intrarile
    patternsPresented++;
    formConsole->AddMessage("Processing pattern " + AnsiString(patternsPresented) + " - " + AnsiString(saveCount));
    if (patternsPresented > saveCount)
    {
      // trimit ponderile la server
      formConsole->AddMessage("SENDING WEIGHTS TO SERVER...");
      SendWeights();
      // reiau numaratoarea
      patternsPresented = 0;
    }

    formConsole->AddMessage("Receiving input pattern");
    RecvData(inputs);
    if (Terminated) break;

    formConsole->AddMessage("Receiving target pattern");
    RecvData(target);
    if (Terminated) break;

    line = "Input received : ";
    for(i = 0; i < inputsNo; i++) line = line + " " + AnsiString::FormatFloat("0.00", inputs[i]);
    formConsole->AddMessage(line);

    line = "Target received : ";
    for(i = 0; i < oMax - oMin; i++) line = line + " " + AnsiString::FormatFloat("0.00", target[i]);
    formConsole->AddMessage(line);

    // calculez hidden units activities
    formConsole->AddMessage("Computing hidden unit activities");
    for(j = hMin; j < hMax; j++)
    {
      net = 0.0;
      for(i = 0; i < inputsNo; i++)
      {
        net = net + ihWeights[(j - hMin) * inputsNo + i] * inputs[i];
      }
      hidden[j] = theFunction(net);
    }

    line = "Hidden : ";
    for(i = hMin; i < hMax; i++) line = line + " " + AnsiString::FormatFloat("0.00", hidden[i]);
    formConsole->AddMessage(line);

    // trimit hidden units activities la server
    formConsole->AddMessage("Sending hidden unit activities");
    SendData(hidden + hMin, hMax - hMin);
    if (Terminated) break;

    // primesc toate activitatile hidden 
    formConsole->AddMessage("Receiving all hidden unit activities");
    RecvData(hidden);
    if (Terminated) break;

    // calculez activitatile output
    formConsole->AddMessage("Computing output activities");
    for(j = oMin; j < oMax; j++)
    {
      net = 0.0;
      for(i = 0; i < hiddenNo; i++)
      {
        if (hoWeights[(j - oMin) * hiddenNo + i] == 0.0) net = net + 0.02 * hidden[i];
        else net = net + hoWeights[(j - oMin) * hiddenNo + i] * hidden[i];
      }
      outputs[j] = theFunction(net);
    }

    line = "Output computed : ";
    for(i = 0; i < oMax - oMin; i++) line = line + " " + AnsiString::FormatFloat("0.00", outputs[i + oMin]);
    formConsole->AddMessage(line);

    // trimit output units activities la server
    formConsole->AddMessage("Sending output activities to server");
    SendData(outputs + oMin, oMax - oMin);
    if (Terminated) break;

    // STEP 3
    // calculez delta output
    for(i = 0; i < oMax - oMin; i++)
    {
      if (outputs[i + oMin] == 0.0) deltaO[i] = (target[i + oMin] - outputs[i + oMin]);
      else
        if (outputs[i + oMin] == 1.0) deltaO[i] = (target[i + oMin] - outputs[i + oMin]);
        else deltaO[i] = (target[i + oMin] - outputs[i + oMin]) * outputs[i + oMin] * (1.0 - outputs[i + oMin]);
    }

    line = "DeltaO : ";
    for(i = 0; i < oMax - oMin; i++) line = line + " " + AnsiString::FormatFloat("0.00", deltaO[i]);
    formConsole->AddMessage(line);

    // STEP 4
    for(i = 0; i < hMin; i++)
    {
      packageSend[i] = 0.0;
      for(j = 0; j < oMax - oMin; j++)
      {
        packageSend[i] += hoWeights[hiddenNo*j + i] * deltaO[j];
      }
    }

    // calcule
    for(i = 0; i < hMax - hMin; i++)
    {
      deltaH[i] = 0.0;
      for(j = 0; j < oMax - oMin; j++)
      {
        deltaH[i] += (hoWeights[hiddenNo*j + i] * deltaO[j]);
      }
    }

    //line = "DeltaH(1) : ";
    //for(i = 0; i < hMax - hMin + 1; i++) line = line + " " + AnsiString::FormatFloat("0.0000", deltaH[i]);
    //formConsole->AddMessage(line);

    // mai multe calcule - rezultate partiale pentru celelalte masini
    for(i = 0; i < hiddenNo; i++)
    {
      if ((i <= hMin) && (i > hMax))
      {
        packageSend[i] = 0.0;
        for(j = 0; j < oMax - oMin; j++)
        {
          packageSend[i] += hoWeights[hiddenNo*j + i] * deltaO[j];
        }
      }
    }

    // trimit rezultatele partiale pe care le calculeaza masina locala pentru
    // celelalte masini
    SendData(packageSend, hiddenNo);
    if (Terminated) break;

    // primesc ceea ce merit :-) rezultatele pe care celelalte masini le'au calculat
    packageSize = RecvData(package);
    if (packageSize == -1) break;
    if (Terminated) break;
    formConsole->AddMessage("Received : " + AnsiString(packageSize) + " values");

    // calculez deltaH cu rezultatele pe care le'am primit si ce am calculat mai sus
    for(i = 0; i < hMax - hMin; i++)
    {
      for(j = 0; j < packageSize / (hMax - hMin) - 1; j++)
        deltaH[i] += package[j * (hMax - hMin) + i]; // ?
      oldValue = deltaH[i];
      try
      {
        deltaH[i] = deltaH[i] * hidden[i + hMin] * (1.0 - hidden[i + hMin]);
      }
      catch(...)
      {
        if (oldValue > 1.0) oldValue = 1.0;
        if (oldValue <-1.0) oldValue = -1.0;
        deltaH[i] = oldValue;
        formConsole->AddMessage("Floating point exception");
      }
    }

    line = "DeltaH : ";
    for(i = 0; i < hMax - hMin; i++) line = line + " " + AnsiString::FormatFloat("0.0000", deltaH[i]);
    formConsole->AddMessage(line);

    // STEP 5
    for(i = 0; i < oMax - oMin; i++)
    {
      for(j = 0; j < hiddenNo; j++)
      {
        hoWeights[hiddenNo * i + j] += learningRate * deltaO[i] * hidden[j];
      }
    }

    // STEP 6
    for(i = 0; i < hMax - hMin; i++)
    {
      for(j = 0; j < inputsNo; j++)
      {
        ihWeights[i * inputsNo + j] += learningRate * deltaH[i] * inputs[j];
      }
    }

    // STEP 7
    // nu mai e nevoie, s'a facut la pasii anteriori
  }
}
//---------------------------------------------------------------------------

// Descriere   : trimite ponderile la server
// Param       : n/a
// Rezultat    : n/a
// Comentarii  : n/a
void CRemoteMachine::SendWeights()
{
  // de fapt aici nu e mare brinza de peshte; pe
  // server e mai kakacios :-))))
  SendData(ihWeights, inputsNo * (hMax - hMin));
  SendData(hoWeights, hiddenNo * (oMax - oMin));
}
//---------------------------------------------------------------------------

// Descriere   : receptionez ponderile de la server
// Param       : n/a
// Rezultat    : n/a
// Comentarii  : n/a
void CRemoteMachine::GetWeights()
{
  RecvData(ihWeights);
  RecvData(hoWeights);
}
//---------------------------------------------------------------------------

