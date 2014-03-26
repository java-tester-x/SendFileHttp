//---------------------------------------------------------------------------

#ifndef frmTriavialClientH
#define frmTriavialClientH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "IdBaseComponent.hpp"
#include "IdComponent.hpp"
#include "IdTrivialFTP.hpp"
#include "IdUDPBase.hpp"
#include "IdUDPClient.hpp"
#include <Dialogs.hpp>
#include "IdAntiFreeze.hpp"
#include "IdAntiFreezeBase.hpp"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------

class TFormClient;//class declaration
class TProgressStream:  public TFileStream
{
  private:
   DWORD FStartTime;
//   void * FActivity;
//   TEvent* FActivity;

   long FProgress;
   long length;

  public:
   TFormClient * parent;
   TObject * progressbar;
   TProgressStream(const AnsiString FileName,int Mode,TFormClient * Parent);
   virtual int __fastcall Read(void * Buffer, int Count );
   virtual int __fastcall Write(const void* Buffer, int Count);

};










class TFormClient : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *edtRemoteFile;
        TButton *btnUpload;
        TEdit *edtHost;
        TEdit *edtLocalFile;
        TButton *btnDownload;
        TIdTrivialFTP *TrivialFTP;
        TButton *Button1;
        TOpenDialog *OpenDialog1;
        TLabel *VersionLabel;
        TIdAntiFreeze *IdAntiFreeze1;
        TLabel *lblByteRate;
        TLabel *Label5;
        void __fastcall btnUploadClick(TObject *Sender);
        void __fastcall btnDownloadClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormClient(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormClient *FormClient;
//---------------------------------------------------------------------------
#endif
