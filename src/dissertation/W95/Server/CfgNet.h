//---------------------------------------------------------------------------
#ifndef CfgNetH
#define CfgNetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "cspin.h"
//---------------------------------------------------------------------------
class TformCfgNet : public TForm
{
__published:	// IDE-managed Components
        TButton *bOk;
        TButton *bCancel;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TEdit *edIn;
        TLabel *Label2;
        TEdit *edHidden;
        TLabel *Label3;
        TEdit *edOut;
        TGroupBox *GroupBox2;
        TLabel *Label4;
        TLabel *Label5;
        TComboBox *cbHiddenAct;
        TComboBox *cbOutputAct;
        TGroupBox *GroupBox3;
        TLabel *Label6;
        TEdit *edLR;
        TLabel *Label7;
        TEdit *edMT;
        TCheckBox *cbMomentum;
        TGroupBox *GroupBox4;
        TEdit *edName;
        TGroupBox *GroupBox5;
        TLabel *Label8;
        TEdit *edSave;
        void __fastcall cbMomentumClick(TObject *Sender);

        void __fastcall edInExit(TObject *Sender);
        void __fastcall edHiddenExit(TObject *Sender);
        void __fastcall edOutExit(TObject *Sender);
        void __fastcall cbHiddenActExit(TObject *Sender);
        void __fastcall cbOutputActExit(TObject *Sender);
        void __fastcall edLRExit(TObject *Sender);
        void __fastcall edMTExit(TObject *Sender);
        
        
        
        
        void __fastcall edSaveExit(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TformCfgNet(TComponent* Owner);
        void       ProjectToScreen();
};
//---------------------------------------------------------------------------
extern PACKAGE TformCfgNet *formCfgNet;
//---------------------------------------------------------------------------
#endif
