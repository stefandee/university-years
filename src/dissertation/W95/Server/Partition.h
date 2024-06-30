//---------------------------------------------------------------------------
#ifndef PartitionH
#define PartitionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TformPartition : public TForm
{
__published:	// IDE-managed Components
        TButton *bOk;
        TButton *bCancel;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *edIn;
        TEdit *edHidden;
        TEdit *edOut;
        void __fastcall edInExit(TObject *Sender);
        void __fastcall edHiddenExit(TObject *Sender);
        void __fastcall edOutExit(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TformPartition(TComponent* Owner);
        void       PartitionToScreen(int iNo, int hNo, int oNo);
};
//---------------------------------------------------------------------------
extern PACKAGE TformPartition *formPartition;
//---------------------------------------------------------------------------
#endif
