//---------------------------------------------------------------------------

#include <vcl.h>
#include <FileCtrl.hpp>
#include <shellapi.h>

#pragma hdrstop

#include "frmTFTPServer.h"
#include "Transferfrm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IdBaseComponent"
#pragma link "IdComponent"
#pragma link "IdTrivialFTPServer"
#pragma link "IdUDPBase"
#pragma link "IdUDPServer"
#pragma resource "*.dfm"
TfrmMain *frmMain;




//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormCreate(TObject *Sender)
{

  FTransferList = new TList;
  edtRootDir->Text = GetCurrentDir();
  IdTrivialFTPServer1->Active = True;



}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::IdTrivialFTPServer1ReadFile(TObject *Sender,
      AnsiString &FileName, const TPeerInfo &PeerInfo, bool &GrantAccess,
      TStream *&AStream, bool &FreeStreamOnComplete)
{


 AnsiString  s;
 FreeStreamOnComplete = false;
 s = "denied";
 GrantAccess = CheckAccess(FileName, edtRootDir->Text);
  try
   {
    if (GrantAccess)
    {
      AStream = new TProgressStream(FileName, fmOpenRead);
      TTransferForm *transferform=new TTransferForm((TComponent*)NULL,(TProgressStream*) AStream,AnsiString(PeerInfo.PeerIP),(int)PeerInfo.PeerPort,fmOpenRead,FileName );//create a new instance of the transfer form for this customer
      FTransferList->Add(transferform);
      transferform->Show();
      Application->ProcessMessages();
      s = "granted";
     lblCount->Caption = lblCount->Caption +1 ;
    }
   }

catch(...)
{

}

    AnsiString formatedstring;
formatedstring=formatedstring.sprintf("%s:%d - Read access to %s %s",
      PeerInfo.PeerIP.c_str(), PeerInfo.PeerPort , FileName.c_str(), s.c_str());
    memLog->Lines->Add(formatedstring);









}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::IdTrivialFTPServer1WriteFile(TObject *Sender,
      AnsiString &FileName, const TPeerInfo &PeerInfo, bool &GrantAccess,
      TStream *&AStream, bool &FreeStreamOnComplete)
{
AnsiString  s;

  FreeStreamOnComplete = False;
  GrantAccess = CheckAccess(FileName, edtRootDir->Text);
  s ="denied";
  try
   { if (GrantAccess)
    {
      AStream = new TProgressStream(FileName, fmCreate);
      TTransferForm *transferform=new TTransferForm((TComponent*)NULL,(TProgressStream*) AStream,AnsiString(PeerInfo.PeerIP),(int)PeerInfo.PeerPort, fmOpenWrite,FileName);//create a new instance of the transfer form for this customer
      FTransferList->Add(transferform);
      transferform->Show();
      Application->ProcessMessages();
      s = "granted";
      lblCount->Caption = lblCount->Caption + 1;

     }
   }
  __finally
  { AnsiString formatedstring;
    memLog->Lines->Add(formatedstring.sprintf("%s:%d - Write access to %s %s",
      PeerInfo.PeerIP.c_str(), PeerInfo.PeerPort, FileName.c_str(), s.c_str()));
  }


}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::IdTrivialFTPServer1TransferComplete(
      TObject *Sender, const bool Success, const TPeerInfo &PeerInfo,
      TStream *AStream, const bool WriteOperation)
{

AnsiString  s;
int   i;

  try
   { if (Success)
      s = "completed";
    else
      s = "aborted";
      AnsiString formatedstring;
      memLog->Lines->Add(formatedstring.sprintf("%s:%d - Transfer %s - %d bytes transferred",
      PeerInfo.PeerIP.c_str() , PeerInfo.PeerPort, s.c_str(), AStream->Position));

    }


 catch(...)
  {
  }

    for (i = FTransferList->Count-1;i>=0 ;i--)
    {
      TTransferForm* tempptr=(TTransferForm*)FTransferList->Items[i];
      if (tempptr->AStream ==(TProgressStream*) AStream)
      {tempptr->Close();
       delete tempptr;
       FTransferList->Delete(i);
       break;
      }
     }

    delete AStream;
    lblCount->Caption =lblCount->Caption - 1;



}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnBrowseClick(TObject *Sender)
{
AnsiString   s;
AnsiString Directory;
AnsiString currentdir="C:\\";
s=edtRootDir->Text;





  if (SelectDirectory(s, currentdir,Directory))
    edtRootDir->Text = Directory;

}
//---------------------------------------------------------------------------
bool __fastcall TfrmMain::CheckAccess(AnsiString& FileName,AnsiString RootDir)
{bool Result=true;
AnsiString   s;

  RootDir = ExtractFileDir(ExpandFileName(IncludeTrailingBackslash(RootDir) + "a.b"));
  FileName = ExpandFileName(IncludeTrailingBackslash(RootDir) + FileName);
  s = FileName;
  s.SetLength(RootDir.Length());
  Result = (AnsiCompareText(UpperCase(RootDir),UpperCase( s))==0);

return Result;
}



AnsiString __fastcall TfrmMain::IncludeTrailingBackslash(AnsiString dir )
 {
     if  ( *dir.AnsiLastChar() != '\\' )
         dir += "\\";

     return  dir;
 }



