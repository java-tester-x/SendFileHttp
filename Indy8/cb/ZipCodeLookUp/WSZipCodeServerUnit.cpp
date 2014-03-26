//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WSZipCodeServerUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IdBaseComponent"
#pragma link "IdComponent"
#pragma link "IdTCPServer"
#pragma resource "*.dfm"
TServerMain *ServerMain;
//---------------------------------------------------------------------------
__fastcall TServerMain::TServerMain(TComponent* Owner)
        : TForm(Owner)
{
  ZipCodeList = new TStringList;
  ZipCodeList->LoadFromFile(ExtractFilePath(Application->ExeName) + "ZipCodes.dat");
}
//---------------------------------------------------------------------------
__fastcall TServerMain::~TServerMain() {
  delete ZipCodeList;
}
//---------------------------------------------------------------------------
void __fastcall TServerMain::IdTCPServer1Connect(TIdPeerThread *AThread)
{
  AThread->Connection->WriteLn("Indy Zip Code Server Ready.");
}
//---------------------------------------------------------------------------
void __fastcall TServerMain::IdTCPServer1Execute(TIdPeerThread *AThread)
{
  TIdTCPServerConnection& conx( *AThread->Connection );
  String sCommand;
  sCommand = conx.ReadLn("\r\n",5000);
  if( sCommand == "QUIT" )
    conx.Disconnect();
  else if( sCommand.SubString(1,8) == "ZipCode " )
    conx.WriteLn(ZipCodeList->Values[sCommand.SubString(9,MaxInt)]);
}
//---------------------------------------------------------------------------
void __fastcall TServerMain::FormCreate(TObject *Sender)
{
IndyVersionLabel->Caption=IdTCPServer1->Version;         
}
//---------------------------------------------------------------------------

