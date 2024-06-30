//----------------------------------------------------------------------------
#ifndef MainH
#define MainH
//----------------------------------------------------------------------------
#include "ChildWin.h"
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
        TMenuItem *N1;
        TMenuItem *Console1;
        TMenuItem *MachineList1;
        TOpenDialog *OpenDialog;
        TSaveDialog *SaveDialog;
        TSpeedButton *sbStart;
        TSpeedButton *sbStop;
        TMenuItem *N3;
        TMenuItem *Newproject1;
        TMenuItem *Openproject1;
        TMenuItem *Saveproject1;
        TMenuItem *Saveprojectas1;
        TMenuItem *Projectoptions1;
        TMenuItem *Closeproject1;
	void __fastcall FormCreate(TObject *Sender);
	//void __fastcall FileNewItemClick(TObject *Sender);
	void __fastcall WindowCascadeItemClick(TObject *Sender);
	void __fastcall UpdateMenuItems(TObject *Sender);
	void __fastcall WindowTileItemClick(TObject *Sender);
	void __fastcall WindowArrangeItemClick(TObject *Sender);
	//void __fastcall FileCloseItemClick(TObject *Sender);
	void __fastcall FileExitItemClick(TObject *Sender);
	//void __fastcall FileSaveAsItemClick(TObject *Sender);
	void __fastcall WindowMinimizeItemClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);

	void __fastcall HelpAboutItemClick(TObject *Sender);
        void __fastcall Console1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall MachineList1Click(TObject *Sender);
        void __fastcall sbStartClick(TObject *Sender);
        void __fastcall Projectoptions1Click(TObject *Sender);
        void __fastcall Newproject1Click(TObject *Sender);
        void __fastcall Closeproject1Click(TObject *Sender);
        
        void __fastcall sbStopClick(TObject *Sender);
        
        
        void __fastcall Saveproject1Click(TObject *Sender);
        void __fastcall Saveprojectas1Click(TObject *Sender);
        
        
        void __fastcall Openproject1Click(TObject *Sender);
private:
	void __fastcall ShowHint(TObject *Sender);
public:
	virtual __fastcall TMainForm(TComponent *Owner);
};
//----------------------------------------------------------------------------
extern TMainForm *MainForm;
extern TMDIChild *__fastcall MDIChildCreate(void);
//----------------------------------------------------------------------------
#endif
