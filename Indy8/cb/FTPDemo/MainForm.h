//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "IdBaseComponent.hpp"
#include "IdComponent.hpp"
#include "IdFTP.hpp"
#include "IdIntercept.hpp"
#include "IdLogBase.hpp"
#include "IdLogDebug.hpp"
#include "IdTCPClient.hpp"
#include "IdTCPConnection.hpp"
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include "IdAntiFreeze.hpp"
#include "IdAntiFreezeBase.hpp"
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
        TSplitter *Splitter1;
        TListBox *DirectoryListBox;
        TListBox *DebugListBox;
        TPanel *Panel1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *FtpServerEdit;
        TButton *ConnectButton;
        TPanel *Panel3;
        TCheckBox *TraceCheckBox;
        TEdit *UserIDEdit;
        TEdit *PasswordEdit;
        TPanel *CommandPanel;
        TButton *UploadButton;
        TButton *AbortButton;
        TButton *BackButton;
        TButton *DeleteButton;
        TButton *DownloadButton;
        TIdFTP *IdFTP1;
        TIdLogDebug *IdLogDebug1;
        TOpenDialog *UploadOpenDialog1;
        TSaveDialog *SaveDialog1;
        TProgressBar *ProgressBar1;
        TIdAntiFreeze *IdAntiFreeze1;
        TStatusBar *StatusBar1;
        TCheckBox *UsePassive;
        void __fastcall ConnectButtonClick(TObject *Sender);
        void __fastcall DirectoryListBoxDblClick(TObject *Sender);
        void __fastcall UploadButtonClick(TObject *Sender);
        void __fastcall DeleteButtonClick(TObject *Sender);
        void __fastcall BackButtonClick(TObject *Sender);
        void __fastcall AbortButtonClick(TObject *Sender);
        void __fastcall TraceCheckBoxClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall DirectoryListBoxClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall IdLogDebug1LogItem(TComponent *ASender,
          AnsiString &AText);
        void __fastcall IdFTP1Disconnected(TObject *Sender);
        void __fastcall IdFTP1Status(TObject *axSender,
          const TIdStatus axStatus, const AnsiString asStatusText);
        void __fastcall IdFTP1Work(TObject *Sender, TWorkMode AWorkMode,
          const int AWorkCount);
        void __fastcall IdFTP1WorkBegin(TObject *Sender,
          TWorkMode AWorkMode, const int AWorkCountMax);
        void __fastcall IdFTP1WorkEnd(TObject *Sender,
          TWorkMode AWorkMode);
        void __fastcall UsePassiveClick(TObject *Sender);
private:  bool AbortTransfer;
          bool TransferrignData;
          long BytesToTransfer ;
          TDateTime STime;
          double AverageSpeed;
	// User declarations
public:		// User declarations
        __fastcall TfrmMain(TComponent* Owner);
        void __fastcall SetFunctionButtons(bool Value);
        void __fastcall ChageDir(AnsiString DirName);
        AnsiString __fastcall GetNameFromDirLine(AnsiString Line, bool *IsDirectory );
        void __fastcall SaveHostInfo(AnsiString Datatext,AnsiString header);
        AnsiString __fastcall GetHostInfo(AnsiString header);

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
