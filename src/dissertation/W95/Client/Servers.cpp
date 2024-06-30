//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Servers.h"
#include "basepath.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TformServers *formServers;
//---------------------------------------------------------------------------
__fastcall TformServers::TformServers(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TformServers::cbPortExit(TObject *Sender)
{
   try
   {
      cbPort->Text.ToInt();
   }
   catch(const EConvertError &e)
   {
      cbPort->Text = "0";
   }
}
//---------------------------------------------------------------------------

void __fastcall TformServers::FormShow(TObject *Sender)
{
  try
  {
    cbPort->Items->LoadFromFile(getProgramPath() + PORTS_FILE);
    cbServerList->Items->LoadFromFile(getProgramPath() + SERVERS_FILE);
  }
  catch(...)
  {
  }
}
//---------------------------------------------------------------------------

void __fastcall TformServers::FormHide(TObject *Sender)
{
  // vad daca texttul introdus nu mai exista in lista
  // daca nu, il introduc, astfel incit sa pot salva lista
  if (cbServerList->Items->IndexOf(cbServerList->Text) == -1)
  {
    cbServerList->Items->Add(cbServerList->Text);
  }

  // analog
  if (cbPort->Items->IndexOf(cbPort->Text) == -1)
  {
    cbPort->Items->Add(cbPort->Text);
  }

  try
  {
    cbPort->Items->SaveToFile(getProgramPath() + PORTS_FILE);
    cbServerList->Items->SaveToFile(getProgramPath() + SERVERS_FILE);
  }
  catch(...)
  {
  }
}
//---------------------------------------------------------------------------

