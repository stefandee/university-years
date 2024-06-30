//---------------------------------------------------------------------------
#ifndef DialogH
#define DialogH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "cspin.h"
//---------------------------------------------------------------------------
class TformDlg : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TGroupBox *GroupBox1;
        TEdit *edIn;
        TEdit *edTarget;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *edSets;
private:	// User declarations
public:		// User declarations
        __fastcall TformDlg(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TformDlg *formDlg;
//---------------------------------------------------------------------------
#endif
