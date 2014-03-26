//---------------------------------------------------------------------------

#ifndef frmTFTPServerH
#define frmTFTPServerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "IdBaseComponent.hpp"
#include "IdComponent.hpp"
#include "IdTrivialFTPServer.hpp"
#include "IdUDPBase.hpp"
#include "IdUDPServer.hpp"
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>








class TTransferForm;

class TProgressStream:  public TFileStream
{
  private:
   //DWORD FStartTime;
   void * FActivity;
   long FProgress;
   long length;

  public:
   TTransferForm * parent;
   TObject * progressbar;
    TProgressStream(const AnsiString FileName,int Mode);
    virtual int __fastcall Read(void * Buffer, int Count );
    virtual int __fastcall Write(const void* Buffer, int Count);
    Stream();
};

//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
        TMemo *memLog;
        TPanel *Panel1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *lblCount;
        TEdit *edtRootDir;
        TButton *btnBrowse;



        TIdTrivialFTPServer *IdTrivialFTPServer1;
        TOpenDialog *OpenDialog1;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall IdTrivialFTPServer1ReadFile(TObject *Sender,
          AnsiString &FileName, const TPeerInfo &PeerInfo,
          bool &GrantAccess, TStream *&AStream,
          bool &FreeStreamOnComplete);
        void __fastcall IdTrivialFTPServer1WriteFile(TObject *Sender,
          AnsiString &FileName, const TPeerInfo &PeerInfo,
          bool &GrantAccess, TStream *&AStream,
          bool &FreeStreamOnComplete);
        void __fastcall IdTrivialFTPServer1TransferComplete(
          TObject *Sender, const bool Success, const TPeerInfo &PeerInfo,
          TStream *AStream, const bool WriteOperation);
        void __fastcall btnBrowseClick(TObject *Sender);

private:	// User declarations
public:	  TList* FTransferList;   // User declarations
        __fastcall TfrmMain(TComponent* Owner);
        bool __fastcall CheckAccess(AnsiString & FileName,AnsiString RootDir);
        TProgressStream __fastcall GetStream();
        void __fastcall AddTransfer(const AnsiString FileName,
         const int FileMode,  void * AStream);
         AnsiString __fastcall IncludeTrailingBackslash(AnsiString dir );
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
