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
#include "IdMessage.hpp"
#include "IdMessageClient.hpp"
#include "IdPOP3.hpp"
#include "IdTCPClient.hpp"
#include "IdTCPConnection.hpp"
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------
class TMainFrm : public TForm
{
__published:	// IDE-managed Components
        TStatusBar *StatusBar1;
        TToolBar *ToolBar1;
        TToolButton *ToolButton1;
        TToolButton *ToolButton2;
        TToolButton *ToolButton8;
        TToolButton *ToolButton3;
        TToolButton *ToolButton4;
        TToolButton *ToolButton5;
        TToolButton *ToolButton9;
        TToolButton *ToolButton6;
        TToolButton *ToolButton10;
        TToolButton *ToolButton7;
        TToolButton *ToolButton11;
        TToolButton *ToolButton12;
        TPanel *pnlServerName;
        TPanel *pnlMain;
        TSplitter *Splitter1;
        TPanel *pnlBottom;
        TPanel *Panel1;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *From;
        TLabel *Recipients;
        TLabel *Cc;
        TLabel *Subject;
        TLabel *Date;
        TLabel *Priority;
        TLabel *Receipt;
        TLabel *Organization;
        TPanel *pnlBottomBottom;
        TPanel *pnlAttachments;
        TLabel *Label1;
        TListView *lvMessageParts;
        TBitBtn *Button1;
        TMemo *Memo1;
        TPanel *pnlTop;
        TListView *lvHeaders;
        TStatusBar *StatusBar2;
        TMainMenu *MainMenu1;
        TMenuItem *Exit1;
        TMenuItem *Actions1;
        TMenuItem *Checkmail1;
        TMenuItem *Retrievecurrentmessage1;
        TMenuItem *Deletecurrentmessage1;
        TMenuItem *Purgemarkedmessages1;
        TMenuItem *N2;
        TMenuItem *Send1;
        TMenuItem *N3;
        TMenuItem *Disconnect1;
        TMenuItem *Setup1;
        TIdPOP3 *POP;
        TSaveDialog *SaveDialog1;
        TImageList *ImageList1;
        TActionList *ActionList1;
        TAction *CheckMail;
        TAction *Retrieve;
        TAction *Delete;
        TAction *Purge;
        TAction *Disconnect;
        TAction *Setup;
        TAction *Send;
        TIdMessage *Msg;
        TIdAntiFreeze *IdAntiFreeze1;
        TLabel *Label2;
        TLabel *IndyVersionLabel;
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall Exit1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Setup1Click(TObject *Sender);
        void __fastcall Retrievecurrentmessage1Click(TObject *Sender);
//        void __fastcall ToolButton5Click(TObject *Sender);
        void __fastcall pnlServerNameClick(TObject *Sender);
//        void __fastcall ToolButton6Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall CheckMailExecute(TObject *Sender);
        void __fastcall RetrieveExecute(TObject *Sender);
        void __fastcall DeleteExecute(TObject *Sender);
        void __fastcall PurgeExecute(TObject *Sender);
        void __fastcall DisconnectExecute(TObject *Sender);
        void __fastcall SetupExecute(TObject *Sender);
        void __fastcall SendExecute(TObject *Sender);
        void __fastcall lvMessagePartsClick(TObject *Sender);
private:
       void __fastcall RetrievePOPHeaders(int inMsgCount);
       void __fastcall  ResetHeadersGrid();
       void __fastcall ToggleStatus(const bool Status,const bool PurgeStatus);
       void __fastcall  ReadConfiguration();	// User declarations
public:	 AnsiString   FAttachPath;
      int FMsgCount;
      int FMailBoxSize;
	// User declarations
        __fastcall TMainFrm(TComponent* Owner);
        void __fastcall ShowBusy( bool blBusy);
        void __fastcall ShowStatus(AnsiString stStatus);
        void __fastcall ShowFileStatus();
AnsiString __fastcall IncludeTrailingBackslash(AnsiString dir );
AnsiString __fastcall ExcludeTrailingBackslash(AnsiString dir);

};
//---------------------------------------------------------------------------
extern PACKAGE TMainFrm *MainFrm;
//---------------------------------------------------------------------------
#endif
