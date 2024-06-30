//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "About.h"
#include "Console.h"
#include "RemoteMachine.h"
#include "Servers.h"

//---------------------------------------------------------------------
#pragma resource "*.dfm"
TMainForm *MainForm;
//--------------------------------------------------------------------- 
__fastcall TMainForm::TMainForm(TComponent *Owner)
	: TForm(Owner)
{
}
//--------------------------------------------------------------------- 
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	Application->OnHint = ShowHint;
	Screen->OnActiveFormChange = UpdateMenuItems;
}
//--------------------------------------------------------------------- 
void __fastcall TMainForm::ShowHint(TObject *Sender)
{
	StatusBar->SimpleText = Application->Hint;
}
//--------------------------------------------------------------------- 

void __fastcall TMainForm::WindowCascadeItemClick(TObject *Sender)
{
	Cascade();
}
//--------------------------------------------------------------------- 
void __fastcall TMainForm::WindowTileItemClick(TObject *Sender)
{
	Tile();
}
//--------------------------------------------------------------------- 
void __fastcall TMainForm::WindowArrangeItemClick(TObject *Sender)
{
	ArrangeIcons();
}
//--------------------------------------------------------------------- 
void __fastcall TMainForm::WindowMinimizeItemClick(TObject *Sender)
{
  int i;

  //---- Must be done backwards through the MDIChildren array ----
  for (i=MDIChildCount-1; i >= 0; i--)
          MDIChildren[i]->WindowState = wsMinimized;
}
//--------------------------------------------------------------------- 
void __fastcall TMainForm::UpdateMenuItems(TObject *Sender)
{
  WindowCascadeItem->Enabled = MDIChildCount > 0;
  WindowTileItem->Enabled = MDIChildCount > 0;
  WindowArrangeItem->Enabled = MDIChildCount > 0;
  WindowMinimizeItem->Enabled = MDIChildCount > 0;
}
//---------------------------------------------------------------------
void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
  Screen->OnActiveFormChange = NULL;
  //if (RemoteMachine != NULL) RemoteMachine->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::HelpAboutItemClick(TObject *Sender)
{
  AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::sbConnectClick(TObject *Sender)
{
  if (formServers->ShowModal() == mrOk)
  {
    sbConnect->Enabled    = false;
    sbDisConnect->Enabled = true;
    RemoteMachine = new CRemoteMachine(false, formServers->cbServerList->Text, (u_short)formServers->cbPort->Text.ToInt());
  }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::sbDisConnectClick(TObject *Sender)
{
  RemoteMachine->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Console1Click(TObject *Sender)
{
  Console1->Checked = !(formConsole->WindowState == wsNormal);

  if (Console1->Checked)
  {
    formConsole->WindowState = wsNormal;
  }
  else
  {
    formConsole->Close();
  }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileExitItemClick(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------

