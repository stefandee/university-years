//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "MList.h"
#include "Vm.h"
#include "MManager.h"
#include "CfgNet.h"
#include "Console.h"
#include "Partition.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TformMList *formMList;
//---------------------------------------------------------------------------
__fastcall TformMList::TformMList(TComponent* Owner)
        : TForm(Owner)
{
  StringGrid->DefaultColWidth = ClientWidth / 8 - 2;
  StringGrid->Cells[0][0] = "Machine";
  StringGrid->Cells[1][0] = "User";
  StringGrid->Cells[2][0] = "IP";
  StringGrid->Cells[3][0] = "Processor";
  StringGrid->Cells[4][0] = "Speed(MFlops)";
  StringGrid->Cells[5][0] = "Memory(MB)";
  StringGrid->Cells[6][0] = "OS";
  StringGrid->Cells[7][0] = "Ping(ms)";
  StringGrid->Cells[8][0] = "Status";
}

//---------------------------------------------------------------------------
void __fastcall TformMList::FormResize(TObject *Sender)
{
  StringGrid->DefaultColWidth = (StringGrid->Width - StringGrid->GridLineWidth * StringGrid->ColCount - 1) / 8;
}
//---------------------------------------------------------------------------

void __fastcall TformMList::timerUpdaterTimer(TObject *Sender)
{
  int machineNo = MManager->GetMachineNo();

  if (machineNo == 0) StringGrid->RowCount = 2;
  else StringGrid->RowCount =  machineNo + 1;

  for(int i = 0; i < MManager->GetMachineNo(); i++)
  {
    if (MManager->ValidMachine(i))
    {
      StringGrid->Cells[0][i + 1] = MManager->GetMachineName(i);
      StringGrid->Cells[1][i + 1] = MManager->GetMachineUser(i);
      StringGrid->Cells[2][i + 1] = MManager->GetMachineIP(i);
      StringGrid->Cells[3][i + 1] = MManager->GetProcessorName(i);
      StringGrid->Cells[4][i + 1] = MManager->GetMachineSpeed(i);
      StringGrid->Cells[5][i + 1] = MManager->GetMemoryInfo(i);
      StringGrid->Cells[6][i + 1] = MManager->GetMachineOs(i);
      StringGrid->Cells[7][i + 1] = MManager->GetMachinePing(i);
    }
    else
    {
      StringGrid->Cells[0][i + 1] = " ";             
      StringGrid->Cells[1][i + 1] = " ";
      StringGrid->Cells[2][i + 1] = " ";
      StringGrid->Cells[3][i + 1] = " ";
      StringGrid->Cells[4][i + 1] = " ";
      StringGrid->Cells[5][i + 1] = " ";
      StringGrid->Cells[6][i + 1] = " ";
      StringGrid->Cells[7][i + 1] = " ";
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TformMList::Ejectmachine1Click(TObject *Sender)
{
  if (MManager->GetMachineNo() >= StringGrid->Row)
  {
    // kick the mother fucker
    // se face un piiiic altfel
    MManager->KillMachine(StringGrid->Row - 1);
  }
}
//---------------------------------------------------------------------------

void __fastcall TformMList::StringGridDblClick(TObject *Sender)
{
  int iNo, hNo, oNo;

  if (MManager->ValidMachine(StringGrid->Row - 1))
  {
    MManager->GetRemoteMachineCfg(StringGrid->Row - 1, &iNo, &hNo, &oNo);
    formPartition->PartitionToScreen(iNo, hNo, oNo);
    //formCfgMachine->CSpinEdit1->Value = iNo;
    //formCfgMachine->CSpinEdit2->Value = hNo;
    //formCfgMachine->CSpinEdit3->Value = oNo;
    // verificari de dimensiuni, etc minvalue, maxvalue

    if (formPartition->ShowModal() == mrOk)
    {
      MManager->ConfigureRemoteMachine
      (
        StringGrid->Row - 1,
        formPartition->edIn->Text.ToInt(),
        formPartition->edHidden->Text.ToInt(),
        formPartition->edOut->Text.ToInt()
      );
    }
  }
}
//---------------------------------------------------------------------------

