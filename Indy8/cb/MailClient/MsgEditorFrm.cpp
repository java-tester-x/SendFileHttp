//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MsgEditorFrm.h"
#include "MsgEditAdvFrm.h"
#include "global.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IdBaseComponent"
#pragma link "IdComponent"
#pragma link "IdMessage"
#pragma link "IdMessageClient"
#pragma link "IdSMTP"
#pragma link "IdTCPClient"
#pragma link "IdTCPConnection"
#pragma resource "*.dfm"
TfrmMsgEditor *frmMsgEditor;
//---------------------------------------------------------------------------
__fastcall TfrmMsgEditor::TfrmMsgEditor(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMsgEditor::bbtnAdvancedClick(TObject *Sender)
{

frmMsgEditAdv->edtSender->Text=IdMsgSend->Sender->Text;
frmMsgEditAdv->mmoExtraHeaders->Lines = IdMsgSend->ExtraHeaders;
   int showmodal=frmMsgEditAdv->ShowModal();
//   with TfrmAdvancedOptions.Create(Application) do
  // try
//      edtSender->Text := IdMsgSend.Sender.Text;
//      mmoExtraHeaders.Lines := IdMsgSend.ExtraHeaders;
      if (showmodal== mrOk)// then
         {
          //  {Sender header}
            IdMsgSend->Sender->Text = frmMsgEditAdv->edtSender->Text;
          //  {Extra header}
            IdMsgSend->ExtraHeaders->Assign(frmMsgEditAdv->mmoExtraHeaders->Lines);
         }
//   finally
  //    Free;


}
//---------------------------------------------------------------------------

void __fastcall TfrmMsgEditor::bbtnOkClick(TObject *Sender)
{
int intIndex;

    //IdMsgSend do
      //{begin
         IdMsgSend->Body->Assign(Memo1->Lines);
         IdMsgSend->From->Text = UserEmail;
         IdMsgSend->Recipients->EMailAddresses = edtTo->Text; //{ To: header }
         IdMsgSend->Subject = edtSubject->Text; //{ Subject: header }
         IdMsgSend->Priority = TIdMessagePriority(cboPriority->ItemIndex);// { Message Priority }
         IdMsgSend->CCList->EMailAddresses = edtCC->Text;// {CC}
         IdMsgSend->BccList->EMailAddresses = edtBCC->Text; //{BBC}
         if (chkReturnReciept->Checked)
            {//{We set the recipient to the From E-Mail address }
               IdMsgSend->ReceiptRecipient->Text = IdMsgSend->From->Text;
            }
         else
            {// {indicate that there is no receipt recipiant}
               IdMsgSend->ReceiptRecipient->Text = "";
            }
      //end;}
switch (SmtpAuthType)
{
 // {authentication settings}
   case  0:
       SMTP->AuthenticationType = atNone;
      break;
   case 1:
       SMTP->AuthenticationType = atLogin; //{Simple Login}
       break;
 };
   SMTP->UserID = SmtpServerUser;
   SMTP->Password = SmtpServerPassword;

//   {General setup}
   SMTP->Host = SmtpServerName;
   SMTP->Port = SmtpServerPort;

//   {now we send the message}
   SMTP->Connect();
   try
   {
      SMTP->Send(IdMsgSend);
   }
   catch(...)
   {
   }
  SMTP->Disconnect();


}
//---------------------------------------------------------------------------

void __fastcall TfrmMsgEditor::btnTextClick(TObject *Sender)
{

   if (Edit1->Text.Length() == 0)
      {
         MessageBox(this->Handle,"Indicate ContentType first", "ERROR", MB_OK);//mtError
      }
   else
      {  TIdText* idtext;//=new TIdText;
         //idtext->Create(IdMsgSend->MessageParts, Memo1->Lines);
         //do
            {//begin
               IdMsgSend->ContentType = Edit1->Text;
            }//end;
         Memo1->Clear();
         ResetAttachmentListView();
      }


}
//---------------------------------------------------------------------------
void __fastcall TfrmMsgEditor::ResetAttachmentListView()
{
  TListItem* li;
  int idx;

  lvFiles->Items->Clear();

   for (idx = 0;idx < IdMsgSend->MessageParts->Count;idx++)
        {
        li = lvFiles->Items->Add();
         if (dynamic_cast<TIdAttachment *>(IdMsgSend->MessageParts->Items[idx])  )
            {
               li->ImageIndex = 0;
               li->Caption = dynamic_cast<TIdAttachment *>(IdMsgSend->MessageParts->Items[idx])->FileName;
               li->SubItems->Add(dynamic_cast<TIdAttachment *>(IdMsgSend->MessageParts->Items[idx])->ContentType);
            }
         else
          {
               li->ImageIndex = 1;
               li->Caption = IdMsgSend->MessageParts->Items[idx]->ContentType;

           }
          }
}
void __fastcall TfrmMsgEditor::btnAttachmentClick(TObject *Sender)
{
  if (OpenDialog1->Execute())
      {

      IdMsgSend->MessageParts->Add();
      new TIdAttachment(IdMsgSend->MessageParts, OpenDialog1->FileName);
      ResetAttachmentListView();

      }

}
//---------------------------------------------------------------------------

void __fastcall TfrmMsgEditor::FormActivate(TObject *Sender)
{
   cboPriority->ItemIndex = IdMsgSend->Priority;

}
//---------------------------------------------------------------------------

