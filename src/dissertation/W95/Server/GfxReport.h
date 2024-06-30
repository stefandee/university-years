//---------------------------------------------------------------------------
#ifndef GfxReportH
#define GfxReportH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------

#define MAX_TABEL_SIZE 1000
#define BAR_WIDTH        20
#define SUM_ELEMENTS     20

#define X_AXES           30
#define Y_AXES           -30  // de jos
#define AXES_EMBEL       5
#define Y_GRAD           3

#define Y_LABEL          "guess %"
#define X_LABEL          "presentations"

#define BASE_SHOT_NAME   "report"

enum TTabelStyles {ts_bars, ts_circles, ts_earthquake, ts_interpolate};

class TformReport : public TForm
{
__published:	// IDE-managed Components
        TPaintBox *paintBox;
        TPopupMenu *reportMenu;
        TMenuItem *SaveBmp;
        TMenuItem *N1;
        TMenuItem *Drawaslines1;
        TMenuItem *Drawaspints1;
        TMenuItem *Drawashistogram1;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall Drawashistogram1Click(TObject *Sender);
        void __fastcall Drawaspints1Click(TObject *Sender);
        void __fastcall Drawaslines1Click(TObject *Sender);
        
        void __fastcall SaveBmpClick(TObject *Sender);
private:	// User declarations
        float      tabel[MAX_TABEL_SIZE];
        int        last;
        TTabelStyles tabelStyle;
        int        screenShotNo;
public:		// User declarations
        __fastcall TformReport(TComponent* Owner);
        void       AddValue(float value);
        void       SetStyle(TTabelStyles style);
        void       PaintTabel();
};
//---------------------------------------------------------------------------
extern PACKAGE TformReport *formReport;
//---------------------------------------------------------------------------
#endif
