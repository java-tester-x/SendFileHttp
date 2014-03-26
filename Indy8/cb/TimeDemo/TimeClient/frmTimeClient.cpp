//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmTimeClient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IdBaseComponent"
#pragma link "IdComponent"
#pragma link "IdTCPClient"
#pragma link "IdTCPConnection"
#pragma link "IdTime"
#pragma resource "*.dfm"
TTimeClient *TimeClient;
//---------------------------------------------------------------------------
__fastcall TTimeClient::TTimeClient(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TTimeClient::btnGetTimeClick(TObject *Sender)
{
  IdDemoTime->Host = cmboTimeServer->Text;
// After setting Host, this is all you have to get the time from a time
//  server.  We do the rest. }
//  IdDemoTime->Connect();
//AnsiString f=  IdDemoTime->ConnectAndGetAll();
  edtTimeResult->Text = DateTimeToStr ( IdDemoTime->DateTime );

}
//---------------------------------------------------------------------------
void __fastcall TTimeClient::FormCreate(TObject *Sender)
{
IndyVersionLabel->Caption=IdDemoTime->Version;        
}
//---------------------------------------------------------------------------
