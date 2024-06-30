//---------------------------------------------------------------------------
#ifndef RemoteMachineH
#define RemoteMachineH
//---------------------------------------------------------------------------

#include <winsock2.h>

class CRemoteMachine : public TThread
{
private:
        int sock;
        int iMin, iMax, hMin, hMax, oMin, oMax;
        int inputsNo;
        int hiddenNo;
        int outputsNo;
        float*     ihWeights;
        float*     hoWeights;
        float*     inputs;
        float*     hidden;
        float*     outputs;
        float*     target;
        float*     deltaH;
        float*     deltaO;
        float*     package;
        float*     packageSend;
        float      learningRate;
        bool       isMomentumTerm;
        float      momentumTerm;
        bool       readyMem;
        bool       hasBeenTrained;
        int        saveCount, patternsPresented;

        float      ComputeMachineSpeed();
        void       ConfigureNet();
        void       SendData(float* data, int dataLength);
        int        RecvData(float* data);

        void        SendWeights();
        void        GetWeights();

        void       __fastcall RestoreButtons();
protected:
        void __fastcall Execute();
public:
        __fastcall CRemoteMachine(bool CreateSuspended, AnsiString ipAddr, u_short port);
        __fastcall ~CRemoteMachine();
        bool       MemoryIsReady();
        void       Error(int code);
        void       Pong();
        void       SendMachineInfo();
        void       RecvConfiguration();
        float      theFunction(float x);
};
//---------------------------------------------------------------------------

extern CRemoteMachine* RemoteMachine;

#endif
