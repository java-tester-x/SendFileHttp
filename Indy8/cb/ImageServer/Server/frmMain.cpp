//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IdBaseComponent"
#pragma link "IdComponent"
#pragma link "IdTCPServer"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
IdTCPServer->Active = true;
if (IdTCPServer->Active == true )
    lstRequests->Items->Add("Active");


}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IdTCPServerConnect(TIdPeerThread *AThread)
{
lstRequests->Items->Add("Server Connected");
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::IdTCPServerDisconnect(TIdPeerThread *AThread)
{
lstRequests->Items->Add("Dis-Connected");

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::IdTCPServerExecute(TIdPeerThread *AThread)
{

    AnsiString s;
    AnsiString sCommand;
    AnsiString sAction;
    TFileStream* tmpfStream;
    Graphics::TBitmap *tbm;

try
{
s = UpperCase(AThread->Connection->ReadLn("",5000));

sCommand = s.SubString (1,3);
sAction = s.SubString(5,s.Length()-4);

if (sCommand == "LST")
   {
    AThread->Connection->WriteLn(GetList());
    AThread->Connection->Disconnect();
   }
else if (sCommand == "PIC")
    {
    if (FileExists(ExtractFileDir(ParamStr(0)) + "\\images\\" + sAction))
        {
        lstRequests->Items->Add("Serving up: " + sAction);
        // open file stream to image requested
        tmpfStream = new TFileStream(ExtractFileDir(ParamStr(0)) + "\\images\\" + sAction,fmOpenRead |fmShareDenyNone);
        // copy file stream to write stream
        AThread->Connection->OpenWriteBuffer(-1);
        AThread->Connection->WriteStream(tmpfStream,true,false);
        AThread->Connection->CloseWriteBuffer();
        // free the file stream
        delete tmpfStream;
        tmpfStream=NULL;
        lstRequests->Items->Add("File transfer completed");
        AThread->Connection->Disconnect();
        }
        else
          {AThread->Connection->WriteLn("ERR - Requested file does not exist");
           AThread->Connection->Disconnect();
          }
    }
else if (sCommand == "SRN")
   {
    // in production version you would use a unique file name such as one generated
    // from a tickcount plus clint IP / id etc.
    // take snapshot
    lstRequests->Items->Add("Taking screen snap shot");

    tbm = new Graphics::TBitmap();

    ScreenShot(0,0,Screen->Width,Screen->Height,tbm);
    if (FileExists (ExtractFileDir(ParamStr(0)) + "\\images\\ScreenShot.BMP"))
        DeleteFile(ExtractFileDir(ParamStr(0)) + "\\images\\ScreenShot.BMP");
    tbm->SaveToFile(ExtractFileDir(ParamStr(0)) + "\\images\\ScreenShot.BMP");
    tbm->FreeImage();
    delete tbm;
    tbm=NULL;

    lstRequests->Items->Add("Serving up: SCREENSHOT.BMP");
    // open file stream to image requested
    tmpfStream = new TFileStream(ExtractFileDir(ParamStr(0)) + "\\images\\ScreenShot.BMP",fmOpenRead | fmShareDenyNone);
    // copy file stream to write stream
    AThread->Connection->OpenWriteBuffer(-1);
    AThread->Connection->WriteStream(tmpfStream,true,false);
    AThread->Connection->CloseWriteBuffer();
    // free the file stream
    delete tmpfStream;
    tmpfStream=NULL;
    lstRequests->Items->Add("File transfer completed");
    AThread->Connection->Disconnect();
    }
else
if ((sCommand != "LST") && (sCommand != "PIC") && (sCommand != "SRN"))
     {
     AThread->Connection->WriteLn("ERR : Unknown command / action");
     AThread->Connection->Disconnect();
     }

     }


catch (Exception& E)
{
ShowMessage(E.Message);
}


}
//---------------------------------------------------------------------------



AnsiString  __fastcall TMainForm::GetList()
{
   TSearchRec sr;
   AnsiString s;
   AnsiString result;
sFilePattern = ExtractFileDir(ParamStr(0)) + "\\images\\*.bmp";
s = "";
if (FindFirst(sFilePattern,faAnyFile,sr) == 0)
    {
    s = sr.Name;
    while (FindNext(sr) == 0 )
        {s = s + "," + sr.Name;
        }
    }
result = s;
return result;
}




void __fastcall TMainForm::ScreenShot(int x ,int  y ,int  Width ,int Height,Graphics::TBitmap  *bm)
{
 bm->Width=Screen->Width;
 bm->Height=Screen->Height;
 HWND desktop=GetDesktopWindow();
     HDC desktophdc=GetDC(desktop);

 BitBlt(bm->Canvas->Handle,x,y,Screen->Width,Screen->Height,desktophdc,0,0,SRCCOPY);
 ReleaseDC(desktop,desktophdc);
}

