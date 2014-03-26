//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmServer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IdBaseComponent"
#pragma link "IdComponent"
#pragma link "IdTCPServer"
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
IndyVersionLabel->Caption=IdTCPServer->Version;
IdTCPServer->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::IdTCPServerExecute(TIdPeerThread *AThread)
{
    AThread->Connection->WriteLn("Hello from Basic Indy Server server.   ");
    AThread->Connection->Disconnect();


}
//---------------------------------------------------------------------------
