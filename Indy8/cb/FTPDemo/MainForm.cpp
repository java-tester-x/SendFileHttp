// This demo demonstrates the use of IdFTP and IdDebugLog components
// There is some problems with ABORT function.
//
// This demo supports both UNIX and DOS directory listings
//
//
//
/***************************************************************
*
* Project : FTP Client Demo  Original In Pascal
* Unit Name: MainForm
* Purpose : Demonstrates the Connecting to An Ftp Server
* Conversion Author : Ray  Toye  raytt@bigfoot.com
* Date : 12/26/2000
* History : this is a conversion of a delphi project to BCB
*
****************************************************************/
//---------------------------------------------------------------------------

#include <vcl.h>
#include <inifiles.hpp>
#pragma hdrstop

#include "MainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IdBaseComponent"
#pragma link "IdComponent"
#pragma link "IdFTP"
#pragma link "IdIntercept"
#pragma link "IdLogBase"
#pragma link "IdLogDebug"
#pragma link "IdTCPClient"
#pragma link "IdTCPConnection"
#pragma link "IdAntiFreeze"
#pragma link "IdAntiFreezeBase"
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ConnectButtonClick(TObject *Sender)
{

  if (IdFTP1->Connected())
  {
  try
   {
    if (TransferrignData)
         IdFTP1->Abort();
    IdFTP1->Quit();
    IdFTP1->Disconnect();
    DirectoryListBox->Items->Clear();
    SetFunctionButtons(false);
    Panel3->Caption = "Current directory is: ";

    }
  catch(...)
  {
   ConnectButton->Caption = "Connect";
   ConnectButton->Enabled = true;
   ConnectButton->Default = true;
   return;
  }
   ConnectButton->Caption = "Connect";
   ConnectButton->Enabled = true;
   ConnectButton->Default = true;

  }
  else
   {  try
      {
      IdFTP1->User = UserIDEdit->Text;
      IdFTP1->Password = PasswordEdit->Text;
      IdFTP1->Host = FtpServerEdit->Text;
      IdFTP1->Connect(true);
      ConnectButton->Caption = "DisConnect";
      ConnectButton->Enabled = true;
      ConnectButton->Default = true;
      ChageDir("/");
      SetFunctionButtons(true);
      SaveHostInfo(FtpServerEdit->Text,"FTPHOST");//saving it here so that it is saved only after successful connect
      }
    catch(...)
      {if (IdFTP1->Connected())
         {
         ConnectButton->Enabled = true;
         ConnectButton->Caption = "Disconnect";
         ConnectButton->Default = false;
         }
         else
         {
          ConnectButton->Enabled = true;
          ConnectButton->Caption = "Connect";
         ConnectButton->Default = true;
         }
      }
    }

}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::SetFunctionButtons(bool Value)
{
  int i;
  for (i = 0;i < CommandPanel->ControlCount; i++)
  {
   if (CommandPanel->Controls[i]->Name != "AbortButton")
      CommandPanel->Controls[i]->Enabled = Value;
  }
}


void __fastcall TfrmMain::ChageDir(AnsiString DirName)
{
  try
  {
    SetFunctionButtons(false);
    IdFTP1->ChangeDir(DirName);
    IdFTP1->TransferType = ftASCII;
    Panel3->Caption = "Current directory is: " + IdFTP1->RetrieveCurrentDir() +
      "              Remote system is " + IdFTP1->SystemDesc;
    DirectoryListBox->Items->Clear();
    IdFTP1->List(DirectoryListBox->Items,"",true);
    }
  __finally
    {
    SetFunctionButtons(true);
    }
}
void __fastcall TfrmMain::DirectoryListBoxDblClick(TObject *Sender)
{
AnsiString  Name;
AnsiString Line;
bool  IsDirectory;
int index;
  if (!IdFTP1->Connected())return;
  index=DirectoryListBox->ItemIndex;
  if (index==-1)return;
  Line = DirectoryListBox->Items->Strings[index];
  Name = GetNameFromDirLine(Line, &IsDirectory);
  if (IsDirectory)
  {
    // Change directory
    SetFunctionButtons(false);
    ChageDir(Name);
    SetFunctionButtons(true);
  }
  else
  {
    try
     { SaveDialog1->FileName = Name;
      if (SaveDialog1->Execute())
      {
        SetFunctionButtons(false);
        IdFTP1->TransferType = ftBinary;
        BytesToTransfer = IdFTP1->Size(Name);
        IdFTP1->Get(Name, SaveDialog1->FileName, true);
      }
     }
    __finally
     { SetFunctionButtons(true);
     }
  }


}
//---------------------------------------------------------------------------

AnsiString __fastcall TfrmMain::GetNameFromDirLine(AnsiString Line, bool *IsDirectory )
{AnsiString result;
int i;
bool DosListing;

  *IsDirectory = (Line[1] == 'd');
  DosListing = false;
  for (i = 0;i <= 7;i++)
  {
    if ((i == 2) && (!*IsDirectory))
    { //IsDirectory =(Line.SubString(1,Line.Pos(' ') - 1) = "<DIR>");
      *IsDirectory = (bool)Line.AnsiPos("<DIR>");

      if (!*IsDirectory)
      DosListing = IsNumeric(Line[1]);
      else
      DosListing = true;
    }
    Line.Delete(1,  Line.Pos(' '));
    while (Line[1] == ' ')
     {
     Line.Delete(1, 1);
     };
    if ((DosListing)&&(i == 2))break;
  }
  result = Line;

return result;
}
void __fastcall TfrmMain::UploadButtonClick(TObject *Sender)
{
  if (IdFTP1->Connected())
  {
    if (UploadOpenDialog1->Execute())
    try
    { SetFunctionButtons(false);
      IdFTP1->TransferType = ftBinary;
      IdFTP1->Put(UploadOpenDialog1->FileName, ExtractFileName(UploadOpenDialog1->FileName),false);
      ChageDir(IdFTP1->RetrieveCurrentDir());
     }
    __finally
     { SetFunctionButtons(true);
     }

 }


}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::DeleteButtonClick(TObject *Sender)
{

  AnsiString Name;
  AnsiString Line;
  bool IsDirectory;
int index;
  if (!IdFTP1->Connected())return;
  index=DirectoryListBox->ItemIndex;
  if (index==-1)return;

  Line = DirectoryListBox->Items->Strings[index];
  Name = GetNameFromDirLine(Line, &IsDirectory);
  if (IsDirectory)
  {try
    {  SetFunctionButtons(false);
       IdFTP1->RemoveDir(Name);
       ChageDir(IdFTP1->RetrieveCurrentDir());
     }
     __finally
     {
     }
  }
  else
  {try
    {SetFunctionButtons(false);
     IdFTP1->Delete(Name);
     ChageDir(IdFTP1->RetrieveCurrentDir());
    }
  __finally
  {
  }
  }

}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::BackButtonClick(TObject *Sender)
{
  if (!IdFTP1->Connected())return;
  try
  {
   ChageDir("..");
  }
  __finally
  {
  }

}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::AbortButtonClick(TObject *Sender)
{
  AbortTransfer = true;        
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::TraceCheckBoxClick(TObject *Sender)
{
  IdLogDebug1->Active = TraceCheckBox->Checked;
  DebugListBox->Visible = TraceCheckBox->Checked;
  if (DebugListBox->Visible) Splitter1->Top = DebugListBox->Top + 5;

}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::SaveHostInfo(AnsiString Datatext,AnsiString header)
{

    TIniFile * ServerIni;
    ServerIni = new TIniFile(ExtractFilePath(ParamStr(0)) + "FtpHost.ini");

    ServerIni->WriteString("Server", header, Datatext);

    delete   ServerIni;

}


AnsiString __fastcall TfrmMain::GetHostInfo(AnsiString header)
{
    AnsiString ServerName;
    TIniFile * ServerIni;
    ServerIni = new TIniFile(ExtractFilePath(ParamStr(0)) + "FtpHost.ini");

    ServerName = ServerIni->ReadString("Server", header, header);

    delete   ServerIni;
return ServerName;
}


void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
  SetFunctionButtons(false);
  IdLogDebug1->Active = true;
  FtpServerEdit->Text=GetHostInfo("FTPHOST");

  ProgressBar1->Parent = StatusBar1;
  ProgressBar1->Top = 2;
  ProgressBar1->Left = 1;


}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::DirectoryListBoxClick(TObject *Sender)
{
  AnsiString Line;
  bool IsDirectory;
  int index;
  if (!IdFTP1->Connected())return;
  index=DirectoryListBox->ItemIndex;
  if (index==-1)return;

  Line = DirectoryListBox->Items->Strings[index];
  GetNameFromDirLine(Line, &IsDirectory);
  if (IsDirectory)
  DownloadButton->Caption = "Change dir";
  else
  DownloadButton->Caption = "Download";

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
if (IdFTP1->Connected())
IdFTP1->Disconnect();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::IdLogDebug1LogItem(TComponent *ASender,
      AnsiString &AText)
{
  DebugListBox->ItemIndex = DebugListBox->Items->Add(AText);
  Application->ProcessMessages();

}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::IdFTP1Disconnected(TObject *Sender)
{
  StatusBar1->Panels->Items[1]->Text = "Disconnected.";        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::IdFTP1Status(TObject *axSender,
      const TIdStatus axStatus, const AnsiString asStatusText)
{
  DebugListBox->ItemIndex = DebugListBox->Items->Add(asStatusText);
  StatusBar1->Panels->Items[1]->Text = asStatusText;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::IdFTP1Work(TObject *Sender, TWorkMode AWorkMode,
      const int AWorkCount)
{
AnsiString  s;
TDateTime  TotalTime;
WORD H, M, Sec, MS;
double DLTime;

  TotalTime =  Now() - STime;
  DecodeTime(TotalTime, H, M, Sec, MS);
  Sec = Sec + M * 60 + H * 3600;
  DLTime = Sec + MS / 1000;
  if (DLTime > 0)
    AverageSpeed = (AverageSpeed + (AWorkCount / 1024) / DLTime) / 2;

  s = FormatFloat("0.00 KB/s", AverageSpeed);

  switch (AWorkMode)
 { case  wmRead:
    { StatusBar1->Panels->Items[1]->Text = "Download speed " + s;
      break;
    }
    case wmWrite:
    {
     StatusBar1->Panels->Items[1]->Text = "Upload speed " + s;
    }
 };

  if (AbortTransfer)
   IdFTP1->Abort();

  ProgressBar1->Position = AWorkCount;
  AbortTransfer = false;

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::IdFTP1WorkBegin(TObject *Sender,
      TWorkMode AWorkMode, const int AWorkCountMax)
{
  TransferrignData = true;
  AbortButton->Visible = true;
  AbortTransfer = false;
  STime = Now();
  if (AWorkCountMax > 0)
  ProgressBar1->Max = AWorkCountMax;
  else
  ProgressBar1->Max = BytesToTransfer;
  AverageSpeed = 0;

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::IdFTP1WorkEnd(TObject *Sender,
      TWorkMode AWorkMode)
{
  AbortButton->Visible = false;
  StatusBar1->Panels->Items[1]->Text = "Transfer complete.";
  BytesToTransfer = 0;
  TransferrignData = false;
  ProgressBar1->Position = 0;
  AverageSpeed = 0;
  

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::UsePassiveClick(TObject *Sender)
{
  IdFTP1->Passive = UsePassive->Checked;

}
//---------------------------------------------------------------------------

