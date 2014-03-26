//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmTFTPServer.h"
#include "SyncThread.h"
#include "Transferfrm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTransferForm *TransferForm;



TProgressStream::TProgressStream(const AnsiString FileName,int Mode)
:TFileStream(FileName,(WORD)Mode)
{
//FStartTime=::GetTickCount();
}

int __fastcall TProgressStream::Read(void * Buffer, int Count )
{
int rcount;
rcount= TFileStream::Read(Buffer,Count);
FProgress+=rcount;
parent->syncthread->fileprogress=FProgress;
parent->syncthread->Resume();
return rcount;
}
int __fastcall TProgressStream::Write(const void* Buffer, int Count)
{int wcount;
wcount=TFileStream::Write(Buffer,Count);
FProgress+=wcount;
parent->syncthread->fileprogress=FProgress;
parent->syncthread->Execute();
return wcount;
}
















//---------------------------------------------------------------------------
__fastcall TTransferForm::TTransferForm(TComponent* Owner,TProgressStream * NewStream,AnsiString PeerIPAddress,int PeerPort,WORD filemode,AnsiString Filename)
        : TForm(Owner)
{

AStream=NewStream;
AStream->progressbar=this->prgTransfer;
if (AStream->Size>0)
prgTransfer->Position=AStream->Size;
AStream->parent=this;
peerip=PeerIPAddress;
peerport=PeerPort;
IPAddressLabel->Caption=peerip;
PortLabel->Caption=peerport;
AnsiString s;
 if (filemode == fmOpenRead)
    s = "Reading ";
  else
    s = "Writing ";
  Caption = s + ExtractFileName(Filename);

syncthread=new TSyncThread(true,peerip,peerport,this,::GetTickCount());
syncthread->FreeOnTerminate=false;
syncthread->Resume();


 }
//---------------------------------------------------------------------------
void __fastcall TTransferForm::FormDestroy(TObject *Sender)
{
if (syncthread)
{
syncthread->Terminate();
delete syncthread;
}
}
//---------------------------------------------------------------------------

