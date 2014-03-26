//---------------------------------------------------------------------------

#ifndef ServerFrmH
#define ServerFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CSPIN.h"
#include "IdBaseComponent.hpp"
#include "IdComponent.hpp"
#include "IdTCPServer.hpp"
#include "IdThreadMgr.hpp"
#include "IdThreadMgrDefault.hpp"
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
                 /*
class  TSimpleClient : public (TObject)
{
   AnsiString Name;
   int ListLink;
   Pointer  Thread;
  };
               */
class TSimpleClient : public TObject
{
public:
    AnsiString DNS;
    AnsiString Name;
    int ListLink;
    void *Thread;
};
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
        TStatusBar *StatusBar1;
        TPanel *Panel1;
        TPanel *Panel2;
        TListBox *lbClients;
        TToolBar *ToolBar1;
        TToolButton *btnServerUp;
        TToolButton *ToolButton1;
        TToolButton *btnClients;
        TToolButton *btnKillClient;
        TToolButton *btnPM;
        TPageControl *PageControl1;
        TTabSheet *TabSheet3;
        TLabel *Label3;
        TLabel *lblDNS;
        TLabel *lblSocketVer;
        TLabel *Label5;
        TLabel *Label4;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label12;
        TMemo *memEntry;
        TMemo *memEMotes;
        TEdit *edSyopName;
        TTabSheet *TabSheet2;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *lblClientName;
        TLabel *lblClientDNS;
        TImageList *ImageList1;
        TIdTCPServer *tcpServer;
        TIdThreadMgrDefault *IdThreadMgrDefault1;
        TPopupMenu *puMemoMenu;
        TMenuItem *Savetofile1;
        TMenuItem *Loadfromfile1;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TImage *Image1;
        TLabel *Label1;
        TEdit *seBinding;

        void __fastcall btnServerUpClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Savetofile1Click(TObject *Sender);
        void __fastcall Loadfromfile1Click(TObject *Sender);
        void __fastcall btnClientsClick(TObject *Sender);
        void __fastcall seBinding1Change(TObject *Sender);
        void __fastcall tcpServerConnect(TIdPeerThread *AThread);
        void __fastcall tcpServerDisconnect(TIdPeerThread *AThread);
        void __fastcall tcpServerExecute(TIdPeerThread *AThread);
        void __fastcall btnPMClick(TObject *Sender);
        void __fastcall btnKillClientClick(TObject *Sender);
        void __fastcall lbClientsClick(TObject *Sender);
private:	// User declarations
public:	                TList* Clients;	// User declarations
        __fastcall TfrmMain(TComponent* Owner);
        void __fastcall UpdateBindings();
        void __fastcall UpdateClientList();
        void __fastcall BroadcastMessage(AnsiString WhoFrom, AnsiString TheMessage );
        void __fastcall TfrmMain::KillClient(AnsiString ClientName);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
