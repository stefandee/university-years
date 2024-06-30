//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Console.h"
#include "Defs.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TformConsole *formConsole;
//---------------------------------------------------------------------------
__fastcall TformConsole::TformConsole(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TformConsole::Edit1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if (Key == VK_RETURN)
  {
    AddMessage(Edit1->Text);
    Edit1->Text = "";
  }
}
//---------------------------------------------------------------------------

void TformConsole::AddMessage(AnsiString message)
{
  if (ListBox1->Items->Count > MAX_MESSAGES) ListBox1->Clear();
  ListBox1->Items->Add(message);
  ListBox1->ItemIndex = ListBox1->Items->Count - 1;
}

