//---------------------------------------------------------------------------

#include <vcl.h>
#include <inifiles.hpp>
#pragma hdrstop

#include "SetupFrm.h"
#include "MainForm.h"
#include "global.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmSetup *frmSetup;
//---------------------------------------------------------------------------
__fastcall TfrmSetup::TfrmSetup(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetup::FormCreate(TObject *Sender)
{
  POPServer->Text = Pop3ServerName;
  POPPort->Text = IntToStr(Pop3ServerPort);
  Account->Text = Pop3ServerUser;
  Password->Text = Pop3ServerPassword;

  SMTPServer->Text = SmtpServerName;
  SMTPPort->Text = IntToStr(SmtpServerPort);
  edtAccount->Text = SmtpServerUser;
  edtPassword->Text = SmtpServerPassword;
  cboAuthType->ItemIndex = SmtpAuthType;

  Email->Text = UserEmail;

  UpdateServerLabel();


}
//---------------------------------------------------------------------------
void __fastcall TfrmSetup::UpdateServerLabel()
{
   MainFrm->pnlServerName->Caption = POPServer->Text;
}

void __fastcall TfrmSetup::BitBtn1Click(TObject *Sender)
{

   TIniFile * MailIni;
   MailIni = new TIniFile(ExtractFilePath(ParamStr(0)) + "Mail.ini");

//  with MailIni do begin
    MailIni->WriteString("Pop3", "ServerName", POPServer->Text);
    Pop3ServerName = POPServer->Text;

    MailIni->WriteString("Pop3", "ServerPort", POPPort->Text);
    Pop3ServerPort = StrToIntDef(POPPort->Text, 110);

    MailIni->WriteString("Pop3", "ServerUser", Account->Text);
    Pop3ServerUser = Account->Text;

    MailIni->WriteString("Pop3", "ServerPassword", Password->Text);
    Pop3ServerPassword = Password->Text;

    MailIni->WriteString("Smtp", "ServerName", SMTPServer->Text);
    SmtpServerName = SMTPServer->Text;

    MailIni->WriteString("Smtp", "ServerPort", SMTPPort->Text);
    SmtpServerPort = StrToIntDef(SMTPPort->Text, 110);

    MailIni->WriteString("Smtp", "ServerUser", edtAccount->Text);
    SmtpServerUser = edtAccount->Text;

    MailIni->WriteString("Smtp", "ServerPassword", edtPassword->Text);
    SmtpServerPassword = edtPassword->Text;

    MailIni->WriteString("Email", "PersonalEmail", Email->Text);
    UserEmail = Email->Text;

    MailIni->WriteInteger("Smtp", "SMTPAuthenticationType", cboAuthType->ItemIndex);
    SmtpAuthType = cboAuthType->ItemIndex;


delete   MailIni;


}
//---------------------------------------------------------------------------

