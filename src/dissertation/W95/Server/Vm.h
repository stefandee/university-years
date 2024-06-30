//---------------------------------------------------------------------------
#ifndef VmH
#define VmH
//---------------------------------------------------------------------------

#include <winsock2.h>

enum TMachineType {mt_remote, mt_local};

class CMachine : public TThread
{
private:
        int          sock;
        struct sockaddr_in server;
        int          addrlen;
        AnsiString   machineIP;
        AnsiString   machineProc;
        AnsiString   machineSpeed;
        AnsiString   machineMemTotal;
        AnsiString   machineMemFree;
        AnsiString   machineOs;
        AnsiString   machineVersion;
        AnsiString   machineName;
        AnsiString   machineUser;
        TMachineType machineType;
        int          pingTime;
        bool         configured;
        bool         ready;
        float*       data;
        int          dataLength;
        bool         sending;
        bool         receiving;

        void         SendData();
        void         RecvData();
protected:
        void __fastcall Execute();
public:
        __fastcall  CMachine(bool CreateSuspended, int socketNo, struct sockaddr_in info);
        __fastcall  ~CMachine();
        void        Error(int code);
        void        Ping(int packetSize);
        void        RequestMachineInfo();
        void        SendConfiguration(int iNoMin, int iNoMax, int hNoMin, int hNoMax, int oNoMin, int oNoMax, int inputsNo, int hiddenNo, int outputsNo, float learningRate, bool isMomentumTerm, float momentumTerm, int saveCount, bool hasBeenTrained);
        bool        hasFinished();
        AnsiString  GetIP();
        AnsiString  GetPingTime();
        AnsiString  GetMachineSpeed();
        AnsiString  GetMachineOs();
        AnsiString  GetProcessorName();
        AnsiString  GetOsVersion();
        AnsiString  GetMemoryInfo();
        AnsiString  GetMachineName();
        AnsiString  GetUser();
        bool        IsConfigured();
        void        SendCommand(const char* command);
        void        SetData(float* what, int length);
        void        GoReceiving();
        void        GoSending();
        bool        GetRecvStatus();
        bool        GetSendStatus();
};
//---------------------------------------------------------------------------

#endif
