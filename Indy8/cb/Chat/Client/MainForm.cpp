//---------------------------------------------------------------------------

#include <vcl.h>
#include <inifiles.hpp>
#pragma hdrstop

#include "MainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma link "IdBaseComponent"
#pragma link "IdComponent"
#pragma link "IdTCPClient"
#pragma link "IdTCPConnection"
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
edUserName->Text=GetServerInfo("UserName");
edServer->Text=GetServerInfo("ServerAddress");
}

//---------------------------------------------------------------------------
void __fastcall TfrmMain::IdTCPClient1Connected(TObject *Sender)
{
  IdTCPClient1->WriteLn(edUserName->Text);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::SpeedButton1Click(TObject *Sender)
{

 edUserName->Enabled = ! SpeedButton1->Down;
 sePort->Enabled=! SpeedButton1->Down;
 edServer->Enabled=! SpeedButton1->Down;
 AnsiString KillMessage= AnsiString("@KILL:") + edUserName->Text;
  if ((edUserName->Text != "") &&(edServer->Text != "")&&( SpeedButton1->Down))
    {
      IdTCPClient1->Host = edServer->Text;
      IdTCPClient1->Port = sePort->Value;
      if (SpeedButton1->Down)
        {IdTCPClient1->Connect();
        ConnectionStatusLabel->Caption="Disconnect";
        }
        else
        {
        IdTCPClient1->WriteLn(KillMessage);
        ConnectionStatusLabel->Caption="Connect";
        }

    }
  else
    {
       if (!SpeedButton1->Down)
            {
        IdTCPClient1->WriteLn(KillMessage);
        ConnectionStatusLabel->Caption="Connect";
            }

      if ((edUserName->Text == "")||
         (edServer->Text == ""))
        ShowMessage("You must put in a User Name and server name to connect.");
        SpeedButton1->Down = false;
    }






 SaveServerInfo(edUserName->Text,"UserName");//gets here if successfull connect...so save it for next connect
 SaveServerInfo(edServer->Text,"ServerAddress");
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Timer1Timer(TObject *Sender)
{
static int errorctr=0;
AnsiString   Com;
AnsiString  Msg;


  if (!IdTCPClient1->Connected())
    return;


  try
  {
  Msg = IdTCPClient1->ReadLn("", 5);
  }
    catch (...)
  {
  errorctr++;
  if (errorctr>4)
  {Timer1->Enabled=false;
   ShowMessage("Error Recieving Message");
   return;
  }
  }





  if (Msg != "")
    if(Msg[1] != '@')
      {
      // Not a system command
        memLines->Lines->Add(Msg);
      }
    else
      {
      // System command
        Com = UpperCase(Trim(Msg.SubString(2, Msg.Pos(":") -2)));
        Msg = UpperCase(Trim(Msg.SubString(Msg.Pos(":") +1, Msg.Length())));
        if (Com == "CLIENTS")
          lbClients->Items->CommaText = Msg;
      }



}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::edMessageKeyPress(TObject *Sender, char &Key)
{
  if (Key == 13)
    {
      IdTCPClient1->WriteLn(edMessage->Text);
      edMessage->Text = "";
    }

}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Button1Click(TObject *Sender)
{
if (IdTCPClient1->Connected())
   IdTCPClient1->WriteLn(AnsiString("@") + AnsiString("CLIENTS:REQUEST"));
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::SaveServerInfo(AnsiString Datatext,AnsiString header)
{

    TIniFile * ServerIni;
    ServerIni = new TIniFile(ExtractFilePath(ParamStr(0)) + "Server.ini");

    ServerIni->WriteString("Server", header, Datatext);

    delete   ServerIni;

}


AnsiString __fastcall TfrmMain::GetServerInfo(AnsiString header)
{
    AnsiString ServerName;
    TIniFile * ServerIni;
    ServerIni = new TIniFile(ExtractFilePath(ParamStr(0)) + "Server.ini");

    ServerName = ServerIni->ReadString("Server", header, header);

    delete   ServerIni;
return ServerName;
}


//---------------------------------------------------------------------------

void __fastcall TfrmMain::IdTCPClient1Disconnected(TObject *Sender)
{
ConnectionStatusLabel->Caption="Connect";
SpeedButton1->Down=false;
edUserName->Enabled=true;
edServer->Enabled=true;
sePort->Enabled=true;


}
//---------------------------------------------------------------------------

