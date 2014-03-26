//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmClient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IdBaseComponent"
#pragma link "IdComponent"
#pragma link "IdTCPClient"
#pragma link "IdTCPConnection"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btnGetImageListClick(TObject *Sender)
{
try
{
    if (IdTCPClient->Connected())
          IdTCPClient->Disconnect();
    IdTCPClient->Host = edtServerHost->Text;
    IdTCPClient->Port = StrToInt(edtServerPort->Text);
    IdTCPClient->Connect();
    IdTCPClient->WriteLn("LST:");
    lstAvailableImages->Clear();
    LoadItems(IdTCPClient->ReadLn("",5000));
    IdTCPClient->Disconnect();

}
catch (Exception &e)
    {
    ShowMessage(e.Message);
    }






}
//---------------------------------------------------------------------------


void __fastcall TMainForm::LoadItems(AnsiString s)
{
int    iPosComma;
AnsiString  sTmp;

try
{
lstAvailableImages->Clear();
s = Trim(s);
while (s.Pos(",")>0)
{
    iPosComma = s.Pos(","); // locate commas
    sTmp = s.SubString(1,iPosComma - 1); // copy item to tmp string
    lstAvailableImages->Items->Add(sTmp); // add to list
    s = s.SubString(iPosComma + 1,s.Length()); // delete item from string
}
// trap for trailing filename
if (s.Length()!=0)
 lstAvailableImages->Items->Add(s);
}
 catch (Exception& E)
{
    ShowMessage(E.Message);
}



}
void __fastcall TMainForm::btnGetSelectedImageClick(TObject *Sender)
{

TFileStream*    ftmpStream;

try
{
if (lstAvailableImages->ItemIndex  == -1)
  {
   MessageDlg("Cannot proceed until you select an image from the list !",mtInformation  , TMsgDlgButtons()<<mbOK, 0);
  }
else
  {

    if (IdTCPClient->Connected())
          IdTCPClient->Disconnect();
    IdTCPClient->Host = edtServerHost->Text;
    IdTCPClient->Port = StrToInt(edtServerPort->Text);
    IdTCPClient->Connect();
    IdTCPClient->WriteLn("PIC:" + lstAvailableImages->Items->Strings[lstAvailableImages->ItemIndex]);
    // delete if exists
    // in production situation you might store binary downloads like this in a cache folder
    if (FileExists(ExtractFileDir(ParamStr(0)) + "\\" + lstAvailableImages->Items->Strings[lstAvailableImages->ItemIndex]) )
         DeleteFile(ExtractFileDir(ParamStr(0)) + "\\" + lstAvailableImages->Items->Strings[lstAvailableImages->ItemIndex]);
    ftmpStream  = new TFileStream(ExtractFileDir(ParamStr(0)) + "\\" + lstAvailableImages->Items->Strings[lstAvailableImages->ItemIndex],fmCreate);
    while (IdTCPClient->Connected())
            {
            IdTCPClient->ReadStream(ftmpStream,-1,true);
            }
    delete ftmpStream;
    ftmpStream=NULL;
    IdTCPClient->Disconnect();
    imgMain->Picture->LoadFromFile(ExtractFileDir(ParamStr(0)) + "\\" + lstAvailableImages->Items->Strings[lstAvailableImages->ItemIndex]);
  }
}
catch (Exception& E)
{
    ShowMessage(E.Message);
}


}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnExitClick(TObject *Sender)
{
if (MessageDlg("Are you sure you wish to exit?", mtInformation,TMsgDlgButtons()<<mbYes<< mbNo, 0)
== mrYes) PostMessage(this->Handle,WM_CLOSE,0,0l);

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnServerScreenShotClick(TObject *Sender)
{

TFileStream*    ftmpStream;

try
{


    if (IdTCPClient->Connected())
              IdTCPClient->Disconnect();
    IdTCPClient->Host = edtServerHost->Text;
    IdTCPClient->Port = StrToInt(edtServerPort->Text);
    IdTCPClient->Connect();
    IdTCPClient->WriteLn("SRN");
    // delete if exists
    // in production situation you might store binary downloads like this in a cache folder
    if (FileExists(ExtractFileDir(ParamStr(0)) + "\\ServerScreen.bmp"))
        DeleteFile(ExtractFileDir(ParamStr(0)) + "\\ServerScreen.bmp");
    ftmpStream = new TFileStream(ExtractFileDir(ParamStr(0)) + "\\ServerScreen.bmp",fmCreate);
    while (IdTCPClient->Connected())
    {
        IdTCPClient->ReadStream(ftmpStream,-1,true);
    }
    delete ftmpStream;
    ftmpStream=NULL;
    IdTCPClient->Disconnect();
    imgMain->Picture->LoadFromFile(ExtractFileDir(ParamStr(0)) + "\\ServerScreen.bmp");
}
catch (Exception& E)
{
    ShowMessage(E.Message);
}


}
//---------------------------------------------------------------------------

