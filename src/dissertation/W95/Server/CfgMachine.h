//---------------------------------------------------------------------------
#ifndef CfgMachineH
#define CfgMachineH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CfgNet.h"
#include "cspin.h"
//---------------------------------------------------------------------------
class TformCfgMachine : public TformCfgNet
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
        __fastcall TformCfgMachine(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TformCfgMachine *formCfgMachine;
//---------------------------------------------------------------------------
#endif
