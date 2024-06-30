//---------------------------------------------------------------------------
#ifndef MListH
#define MListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TformMList : public TForm
{
__published:	// IDE-managed Components
        TStringGrid *StringGrid;
        TTimer *timerUpdater;
        TPopupMenu *PopupMenu;
        TMenuItem *Ejectmachine1;
        TMenuItem *Banlist1;
        void __fastcall FormResize(TObject *Sender);
        
        void __fastcall timerUpdaterTimer(TObject *Sender);
        
        void __fastcall Ejectmachine1Click(TObject *Sender);
        void __fastcall StringGridDblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TformMList(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TformMList *formMList;
//---------------------------------------------------------------------------
#endif
