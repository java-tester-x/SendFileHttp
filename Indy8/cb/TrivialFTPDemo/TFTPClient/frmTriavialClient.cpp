//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmTriavialClient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IdBaseComponent"
#pragma link "IdComponent"
#pragma link "IdTrivialFTP"
#pragma link "IdUDPBase"
#pragma link "IdUDPClient"
#pragma link "IdAntiFreeze"
#pragma link "IdAntiFreezeBase"
#pragma resource "*.dfm"
TFormClient *FormClient;
//---------------------------------------------------------------------------
TProgressStream::TProgressStream(const AnsiString FileName,int Mode,TFormClient * Parent)
:TFileStream(FileName,(WORD)Mode)
{
FStartTime=::GetTickCount();
parent=Parent;




}

int __fastcall TProgressStream::Read(void * Buffer, int Count )
{DWORD bytespersecond=0;
int rcount;
rcount= TFileStream::Read(Buffer,Count);
FProgress+=rcount;
DWORD elaspedmilliseconds=::GetTickCount() - FStartTime;
DWORD elaspedseconds=(elaspedmilliseconds/1000);
if (elaspedseconds)
bytespersecond=(FProgress/elaspedseconds);
parent->lblByteRate->Caption=AnsiString(bytespersecond);
parent->Update();
return rcount;
}
int __fastcall TProgressStream::Write(const void* Buffer, int Count)
{DWORD bytespersecond=0;
int wcount;
wcount=TFileStream::Write(Buffer,Count);
FProgress+=wcount;
DWORD elaspedmilliseconds=::GetTickCount() - FStartTime;
DWORD elaspedseconds=(elaspedmilliseconds/1000);
if (elaspedseconds)
bytespersecond=(FProgress/elaspedseconds);
parent->lblByteRate->Caption=AnsiString(bytespersecond);
parent->Update();
return wcount;
}
















//------------------------------------------------------------------
__fastcall TFormClient::TFormClient(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TFormClient::btnUploadClick(TObject *Sender)
{


AnsiString  s;

  s = edtRemoteFile->Text;
  if (s.Length()==0)
    {
    s = ExtractFileName(edtLocalFile->Text);
    }


  {
    TrivialFTP->Host = edtHost->Text;
    TrivialFTP->Put(edtLocalFile->Text, s);
  }


}
//---------------------------------------------------------------------------
void __fastcall TFormClient::btnDownloadClick(TObject *Sender)
{


  TProgressStream *strm;
  AnsiString s;

  s = edtLocalFile->Text;
if (s.Length() !=0)
{
   s = ExtractFileName(edtRemoteFile->Text);
   strm = new TProgressStream(s, fmCreate,this);


  try
   {
    TrivialFTP->Host = edtHost->Text;
    TrivialFTP->Get(edtRemoteFile->Text, strm);
   }
  catch(...)
  {

  }

 delete strm;

}

}
//---------------------------------------------------------------------------
void __fastcall TFormClient::Button1Click(TObject *Sender)
{
if (OpenDialog1->Execute())
{
edtLocalFile->Text=OpenDialog1->FileName;
}
}
//---------------------------------------------------------------------------
void __fastcall TFormClient::FormCreate(TObject *Sender)
{
VersionLabel->Caption="Indy Version "+TrivialFTP->Version;
}
//---------------------------------------------------------------------------
