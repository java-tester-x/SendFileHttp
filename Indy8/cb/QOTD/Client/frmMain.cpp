//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IdBaseComponent"
#pragma link "IdComponent"
#pragma link "IdQotd"
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

void __fastcall TMainForm::btnQuoteClick(TObject *Sender)
{
  IdQtdDemo->Host = edtQuoteDayServer->Text;
  //Get the quote of the day
  mmoQuoteOfTheDay->Lines->Text = IdQtdDemo->Quote;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
IndyVersionLabel->Caption=IdQtdDemo->Version;        
}
//---------------------------------------------------------------------------
