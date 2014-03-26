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
TFormClient *FormClient;
//---------------------------------------------------------------------------
__fastcall TFormClient::TFormClient(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormClient::FormCreate(TObject *Sender)
{
IndyVersionLabel->Caption=TCPClient->Version;


}
//---------------------------------------------------------------------------

void __fastcall TFormClient::Button1Click(TObject *Sender)
{
try
{
TCPClient->Connect();

ListBox1->Items->Add(TCPClient->ReadLn("",5000));
}
catch(...)
{

}
TCPClient->Disconnect();
}
//---------------------------------------------------------------------------
