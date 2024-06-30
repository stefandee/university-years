//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CfgMachine.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CfgNet"
#pragma link "cspin"
#pragma resource "*.dfm"
TformCfgMachine *formCfgMachine;
//---------------------------------------------------------------------------

__fastcall TformCfgMachine::TformCfgMachine(TComponent* Owner)
        : TformCfgNet(Owner)
{
}
//---------------------------------------------------------------------------
