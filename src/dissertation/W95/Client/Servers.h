//---------------------------------------------------------------------------
#ifndef ServersH
#define ServersH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#define SERVERS_FILE "servers.ini"
#define PORTS_FILE   "ports.ini"
//---------------------------------------------------------------------------
class TformServers : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TComboBox *cbServerList;
        TLabel *Label2;
        TComboBox *cbPort;
        TButton *bOk;
        TButton *bCancel;
        void __fastcall cbPortExit(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormHide(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TformServers(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TformServers *formServers;
//---------------------------------------------------------------------------
#endif
