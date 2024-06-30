//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Partition.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TformPartition *formPartition;
//---------------------------------------------------------------------------
__fastcall TformPartition::TformPartition(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TformPartition::edInExit(TObject *Sender)
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
void __fastcall TformPartition::edHiddenExit(TObject *Sender)
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
void __fastcall TformPartition::edOutExit(TObject *Sender)
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

void TformPartition::PartitionToScreen(int iNo, int hNo, int oNo)
{
  edIn->Text = AnsiString(iNo);
  edHidden->Text = AnsiString(hNo);
  edOut->Text = AnsiString(oNo);
}
