//---------------------------------------------------------------------------
#ifndef ConsoleH
#define ConsoleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TformConsole : public TForm
{
__published:	// IDE-managed Components
        TEdit *Edit1;
        TListBox *ListBox1;
        void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        __fastcall TformConsole(TComponent* Owner);
        void       AddMessage(AnsiString message);
};
//---------------------------------------------------------------------------
extern PACKAGE TformConsole *formConsole;
//---------------------------------------------------------------------------
#endif
