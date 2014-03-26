//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "IdAntiFreeze.hpp"
#include "IdAntiFreezeBase.hpp"
#include "IdBaseComponent.hpp"
#include "IdComponent.hpp"
#include "IdIcmpClient.hpp"
#include "IdRawBase.hpp"
#include "IdRawClient.hpp"
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "IdUDPBase.hpp"
#include "IdUDPClient.hpp"
//---------------------------------------------------------------------------


class TfrmMain : public TForm
{
__published:	// IDE-managed Components
        TSplitter *Splitter1;
        TPanel *Panel1;
        TListView *lvTrace;
        TPanel *Panel2;
        TPanel *Panel3;
        TListBox *lbLog;
        TPanel *Panel4;
        TLabel *Label1;
        TLabel *Label2;
        TEdit *edTarget;
        TButton *Button1;
        TButton *Button2;
        TEdit *seMaxHops;
        TActionList *ActionList1;
        TAction *acGo;
        TAction *acResolve;
        TAction *acPing;
        TAction *acTrace;
        TAction *acStop;
        TIdIcmpClient *IdIcmpClient;
        TIdAntiFreeze *IdAntiFreeze1;
        TLabel *Label3;
        TLabel *IndyVersionLabel;
        void __fastcall acGoExecute(TObject *Sender);
        void __fastcall acResolveExecute(TObject *Sender);
        void __fastcall acTraceExecute(TObject *Sender);
        void __fastcall acPingExecute(TObject *Sender);
        void __fastcall acStopExecute(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private: bool Stopped;
 bool   bResolved;
AnsiString     ResolvedHost;



// User declarations
public:		// User declarations
        __fastcall TfrmMain(TComponent* Owner);
AnsiString __fastcall TfrmMain::MyGetHostByName(AnsiString text);
bool __fastcall TfrmMain::PingHost(AnsiString Host,int TTL);        
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
