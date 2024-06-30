//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CfgNet.h"
#include "MManager.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cspin"
#pragma resource "*.dfm"
TformCfgNet *formCfgNet;
//---------------------------------------------------------------------------
__fastcall TformCfgNet::TformCfgNet(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TformCfgNet::cbMomentumClick(TObject *Sender)
{
  edMT->Enabled = cbMomentum->Checked;
}
//---------------------------------------------------------------------------

void TformCfgNet::ProjectToScreen()
{
  edName->Text   = MManager->project.projectName;
  edIn->Text     = AnsiString(MManager->project.inputsNo);
  edHidden->Text = AnsiString(MManager->project.hiddenNo);
  edOut->Text    = AnsiString(MManager->project.outputsNo);
  edSave->Text   = AnsiString(MManager->project.saveCount);

  cbMomentum->Checked = MManager->project.isMomentumTerm;
  edMT->Enabled       = cbMomentum->Checked;

  edLR->Text = AnsiString(MManager->project.learningRate);
  edMT->Text = AnsiString(MManager->project.momentumTerm);

  // concordanta intre comboboxuri si enumuri
  cbHiddenAct->ItemIndex = (int)MManager->project.functHidden;
  cbOutputAct->ItemIndex = (int)MManager->project.functOutput;
}
//---------------------------------------------------------------------------

void __fastcall TformCfgNet::edInExit(TObject *Sender)
{
   try
   {
      edIn->Text.ToInt();
   }
   catch(const EConvertError &e)
   {
      edIn->Text = "0";
   }
}
//---------------------------------------------------------------------------

void __fastcall TformCfgNet::edHiddenExit(TObject *Sender)
{
   try
   {
      edHidden->Text.ToInt();
   }
   catch(const EConvertError &e)
   {
      edHidden->Text = "0";
   }
}
//---------------------------------------------------------------------------

void __fastcall TformCfgNet::edOutExit(TObject *Sender)
{
   try
   {
      edOut->Text.ToInt();
   }
   catch(const EConvertError &e)
   {
      edOut->Text = "0";
   }
}
//---------------------------------------------------------------------------

void __fastcall TformCfgNet::cbHiddenActExit(TObject *Sender)
{
  if (cbHiddenAct->ItemIndex == -1) cbHiddenAct->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TformCfgNet::cbOutputActExit(TObject *Sender)
{
  if (cbOutputAct->ItemIndex == -1) cbOutputAct->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TformCfgNet::edLRExit(TObject *Sender)
{
   try
   {
      edLR->Text.ToDouble();
   }
   catch(const EConvertError &e)
   {
      edLR->Text = "0";
   }
}
//---------------------------------------------------------------------------

void __fastcall TformCfgNet::edMTExit(TObject *Sender)
{
   try
   {
      edMT->Text.ToDouble();
   }
   catch(const EConvertError &e)
   {
      edMT->Text = "0";
   }
}
//---------------------------------------------------------------------------


void __fastcall TformCfgNet::edSaveExit(TObject *Sender)
{
   try
   {
      edSave->Text.ToInt();
   }
   catch(const EConvertError &e)
   {
      edSave->Text = "0";
   }
}
//---------------------------------------------------------------------------

