//---------------------------------------------------------------------------
#ifndef MManagerH
#define MManagerH
//---------------------------------------------------------------------------

#include "Vm.h"
#include "Defs.h"
#include "ProjectFile.h"

class CMachineManager : public TThread
{
private:
        CMachine*  machines[100];
        bool       readyToStart;
        bool       readyMem;
        bool       readyPart;
        bool       readyLoad;
        int        index;
        float*     inputs;
        float*     hidden;
        float*     outputs;
        float*     target;
        float*     packages;
        float      partition[MAX_CONNECTIONS_ALLOWED][3];
        int        handle;
        bool       start;
        bool       computationInProgress;
        int        patternsPresented;

        void __fastcall UpdateReport();
        void __fastcall GetWeights();
        void __fastcall SendWeights();
protected:
        void __fastcall Execute();
public:
        // no time left, la dreq cu incapsularea
        CProject   project;

        AnsiString inputFile;
        __fastcall CMachineManager(bool CreateSuspended);
        __fastcall ~CMachineManager();
        int    GetMachineNo();
        void   AddMachine(CMachine* machine);
        bool   ValidMachine(int what);
        void   DeleteMachine(int what);
        void   KillMachine(int what);

        AnsiString GetMachineIP(int what);
        AnsiString GetMachinePing(int what);
        AnsiString GetMachineName(int what);
        AnsiString GetMachineUser(int what);
        AnsiString GetProcessorName(int what);
        AnsiString GetMachineSpeed(int what);
        AnsiString GetMemoryInfo(int what);
        AnsiString GetMachineOs(int what);
        
        void ConfigureNet();
        void ConfigureRemoteMachine(int what, int iNo, int hNo, int oNo);
        void GetRemoteMachineCfg(int what, int *iNo, int *hNo, int *oNo);
        void AutoConfigure();

        bool SaveNet(AnsiString outFile);
        bool LoadNet(AnsiString inFile);

        bool MemoryIsReady();
        bool LoadedIsReady();
        bool PartIsReady();
        bool ReadyToStart();

        bool Start();
        void Stop();
};
//---------------------------------------------------------------------------

extern CMachineManager* MManager;

#endif
