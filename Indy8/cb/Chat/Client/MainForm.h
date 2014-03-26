//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CSPIN.h"
#include "IdBaseComponent.hpp"
#include "IdComponent.hpp"
#include "IdTCPClient.hpp"
#include "IdTCPConnection.hpp"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TSpeedButton *SpeedButton1;
        TLabel *Label6;
        TEdit *edUserName;
        TEdit *edServer;
        TListBox *lbClients;
        TMemo *memLines;
        TEdit *edMessage;
        TButton *Button1;
        TIdTCPClient *IdTCPClient1;
        TTimer *Timer1;
        TCSpinEdit *sePort;
        TLabel *ConnectionStatusLabel;
        void __fastcall IdTCPClient1Connected(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall edMessageKeyPress(TObject *Sender, char &Key);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall IdTCPClient1Disconnected(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmMain(TComponent* Owner);
        void __fastcall SaveServerInfo(AnsiString ServerName,AnsiString header);
        AnsiString __fastcall GetServerInfo(AnsiString header);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
