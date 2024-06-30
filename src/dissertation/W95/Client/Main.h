//----------------------------------------------------------------------------
#ifndef MainH
#define MainH
//----------------------------------------------------------------------------
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Messages.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <StdCtrls.hpp>
#include <Menus.hpp>
#include <Controls.hpp>
#include <Forms.hpp>
#include <Graphics.hpp>
#include <Classes.hpp>
#include <SysUtils.hpp>
#include <Windows.hpp>
#include <System.hpp>
//----------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *Window1;
	TMenuItem *Help1;
	TMenuItem *FileExitItem;
	TMenuItem *WindowCascadeItem;
	TMenuItem *WindowTileItem;
	TMenuItem *WindowArrangeItem;
	TMenuItem *HelpAboutItem;
	TMenuItem *WindowMinimizeItem;
	TPanel *SpeedPanel;
	TStatusBar *StatusBar;
        TSpeedButton *sbConnect;
        TSpeedButton *sbDisConnect;
        TMenuItem *N2;
        TMenuItem *Console1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall WindowCascadeItemClick(TObject *Sender);
	void __fastcall UpdateMenuItems(TObject *Sender);
	void __fastcall WindowTileItemClick(TObject *Sender);
	void __fastcall WindowArrangeItemClick(TObject *Sender);
	void __fastcall WindowMinimizeItemClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);

	void __fastcall HelpAboutItemClick(TObject *Sender);
        void __fastcall sbConnectClick(TObject *Sender);
        void __fastcall sbDisConnectClick(TObject *Sender);
        void __fastcall Console1Click(TObject *Sender);
        void __fastcall FileExitItemClick(TObject *Sender);
private:
	void __fastcall ShowHint(TObject *Sender);
public:
	virtual __fastcall TMainForm(TComponent *Owner);
};
//----------------------------------------------------------------------------
extern TMainForm *MainForm;
//----------------------------------------------------------------------------
#endif
