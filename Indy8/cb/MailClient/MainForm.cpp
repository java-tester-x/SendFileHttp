

                   /***************************************************************/
                   /*                                                             */
                   /* Project : Project1                                          */
                   /* Unit Name: MainForm                                         */
                   /* Purpose : Demostate the Use Of the TIDMessage And TIDPOP    */
                   /*           components for EMAIL                              */
                   /* Converted To BCB By: Ray Toye    raytt@bigfoot.com          */
                   /* Date : 12/22/2000 - 23:01                                   */
                   /* History :Changed The Client So That it will Connect and then*/
                   /*        get or send mail then disconnect  to prevent timeouts*/
                   /*                                                             */
                   /***************************************************************/

//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <function.h>
#include <algorith.h>
#include <Sysutils.hpp>
#include <FileCtrl.hpp>
#include <inifiles.hpp>
#include <shellapi.h>
#pragma hdrstop

#include "MainForm.h"
#include "SetupFrm.h"
#include "MsgEditorFrm.h"
#include "global.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IdAntiFreeze"
#pragma link "IdAntiFreezeBase"
#pragma link "IdBaseComponent"
#pragma link "IdComponent"
#pragma link "IdMessage"
#pragma link "IdMessageClient"
#pragma link "IdPOP3"
#pragma link "IdTCPClient"
#pragma link "IdTCPConnection"
#pragma resource "*.dfm"
TMainFrm *MainFrm;




AnsiString  Pop3ServerName ;
int         Pop3ServerPort;
AnsiString  Pop3ServerUser;
AnsiString  Pop3ServerPassword;
AnsiString  SmtpServerName;
int         SmtpServerPort;
AnsiString  SmtpServerUser;
AnsiString  SmtpServerPassword;
int         SmtpAuthType;
AnsiString  UserEmail;




//---------------------------------------------------------------------------
__fastcall TMainFrm::TMainFrm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::ShowBusy( bool blBusy)
{
   if (blBusy)
      Screen->Cursor = crHourGlass;
   else
      Screen->Cursor = crDefault;
}


void __fastcall TMainFrm::ShowStatus(AnsiString stStatus)
{
   StatusBar1->Panels->Items[0]->Text=stStatus;
   StatusBar1->Refresh();
}


void __fastcall TMainFrm::ToggleStatus(const bool Status,const bool PurgeStatus)
{
   CheckMail->Enabled = !Status;
   Disconnect->Enabled = PurgeStatus;
   Retrieve->Enabled = PurgeStatus;
   Delete->Enabled = PurgeStatus;
   Purge->Enabled = PurgeStatus;

   if (Status)
      ShowStatus("Connected");
   else
      ShowStatus("Not connected");
}
void __fastcall TMainFrm::ShowFileStatus()
{AnsiString status;
   StatusBar2->Panels->Items[0]->Text = IntToStr(FMsgCount);
   StatusBar2->Panels->Items[1]->Text = status.sprintf("Mail takes up %dK on the server",FMailBoxSize);
   StatusBar1->Refresh();
}



void __fastcall TMainFrm::RetrievePOPHeaders(int inMsgCount )
{
  AnsiString  stTemp;
  AnsiString stformat;
  int intIndex;
  TListItem *itm;

   stTemp = StatusBar1->Panels->Items[1]->Text;
   lvHeaders->Items->Clear();

   for (intIndex = 1;intIndex<= inMsgCount ;intIndex++)
   {

         // Clear the message properties
         ShowStatus(stformat.sprintf("Messsage %d of %d", intIndex, inMsgCount));
         Application->ProcessMessages();
         Msg->Clear();
         POP->RetrieveHeader(intIndex, Msg);
         // Add info to ListView
         itm = lvHeaders->Items->Add();
         itm->ImageIndex = 5;
         itm->Caption = Msg->Subject;
         itm->SubItems->Add(Msg->From->Text);
         itm->SubItems->Add(DateToStr(Msg->Date));
         itm->SubItems->Add(IntToStr(POP->RetrieveMsgSize(intIndex)));
         itm->SubItems->Add("n/a");
//         itm.SubItems.Add(POP.RetrieveUIDL(intIndex));
   }
   ShowStatus(stTemp);
}

void __fastcall TMainFrm::FormActivate(TObject *Sender)
{
   ResetHeadersGrid();
   ToggleStatus(false,false);
}
//---------------------------------------------------------------------------
void __fastcall TMainFrm::ResetHeadersGrid()
{
   lvHeaders->Items->Clear();
}

void __fastcall TMainFrm::Exit1Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::FormClose(TObject *Sender, TCloseAction &Action)
{
   Disconnect->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::Setup1Click(TObject *Sender)
{
frmSetup->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::Retrievecurrentmessage1Click(TObject *Sender)
{

  AnsiString stTemp;
  int  intIndex;
  TListItem *li;

   stTemp = StatusBar1->Panels->Items[1]->Text;
   if (lvHeaders->Selected ==NULL)
    return;

   //initialise
   ShowBusy(true);
   Msg->Clear();
   Memo1->Clear();
   lvMessageParts->Items->Clear();
   From->Caption = "";
   Cc->Caption = "";
   Subject->Caption = "";
   Date->Caption = "";
   Receipt->Caption = "";
   Organization->Caption = "";
   Priority->Caption = "";
   pnlAttachments->Visible = false;

   //get message and put into MSG
   ShowStatus("Retrieving message " + lvHeaders->Selected->SubItems->Strings[3]  );
   POP->Retrieve(lvHeaders->Selected->Index + 1, Msg);
   StatusBar1->Panels->Items[0]->Text = lvHeaders->Selected->SubItems->Strings[3];

   //Setup fields on screen from MSG
   From->Caption = Msg->From->Text;
   Recipients->Caption = Msg->Recipients->EMailAddresses;
   Cc->Caption = Msg->CCList->EMailAddresses;
   Subject->Caption = Msg->Subject;
   Date->Caption = FormatDateTime("dd mmm yyyy hh:mm:ss", Msg->Date);
   Receipt->Caption = Msg->ReceiptRecipient->Text;
   Organization->Caption = Msg->Organization;

   Priority->Caption = IntToStr((unsigned char)Msg->Priority + 1);
//   Priority->Caption = IntToStr(Ord(Msg.Priority) + 1);

   //Setup attachments list
   ShowStatus("Decoding attachments (" + IntToStr(Msg->MessageParts->Count) + ")");

   //   for (intIndex = 0; intIndex<= pred(Msg->MessageParts->Count) ;intIndex++)
   for (intIndex = 0; intIndex < (Msg->MessageParts->Count) ;intIndex++)
   {

         if (dynamic_cast<TIdAttachment*>(Msg->MessageParts->Items[intIndex]))
           {  //general attachment
               pnlAttachments->Visible = true;
               li = lvMessageParts->Items->Add();
               li->ImageIndex = 8;
               li->Caption = ExtractFilePath(ParamStr(0)) + dynamic_cast<TIdAttachment*>(Msg->MessageParts->Items[intIndex])->FileName;

            }
         else
            {//body text
               if (dynamic_cast<TIdText*>(Msg->MessageParts->Items[intIndex] ))
               {
                     Memo1->Lines->Clear();
                     Memo1->Lines->AddStrings(dynamic_cast<TIdText*>(Msg->MessageParts->Items[intIndex])->Body);
                }
            }

      }
   ShowStatus(stTemp);
   ShowBusy(false);


}
//---------------------------------------------------------------------------






void __fastcall TMainFrm::pnlServerNameClick(TObject *Sender)
{
   SetupExecute(Sender); //show setup screen
}
//---------------------------------------------------------------------------



void __fastcall TMainFrm::FormCreate(TObject *Sender)
{
IndyVersionLabel->Caption=POP->Version;
  ReadConfiguration();
   //setup path to put attachments into
   FAttachPath = IncludeTrailingBackslash(ExtractFileDir(ParamStr(0))); //starting directory
   FAttachPath = FAttachPath + "Attach\\";
   if (!DirectoryExists(FAttachPath))
     ForceDirectories(FAttachPath);

   FMsgCount = 0;
   FMailBoxSize = 0;
   ShowBusy(false);

}
//---------------------------------------------------------------------------


void __fastcall TMainFrm::CheckMailExecute(TObject *Sender)
{
   ShowBusy(true);

   ShowStatus("Connecting....");

   if (POP->Connected())
      {
       POP->Disconnect();
      }

   
   POP->Host = Pop3ServerName;
   POP->Port = Pop3ServerPort;
   POP->UserId = Pop3ServerUser;
   POP->Password = Pop3ServerPassword;
   Application->ProcessMessages();
   Application->ProcessMessages();
   Application->ProcessMessages();
   POP->Connect();
   ToggleStatus(true,true);
   FMsgCount = POP->CheckMessages();
   FMailBoxSize = POP->RetrieveMailBoxSize()/1024;
   ShowFileStatus();
   if (FMsgCount > 0)
        {
         ShowFileStatus();
         RetrievePOPHeaders(FMsgCount);
        }
   else
      {
         ShowStatus("No messages on server");
      }

  if (POP->Connected())
      {
       POP->Disconnect();
      }
   ToggleStatus(false,true);
   ShowBusy(false);

}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::RetrieveExecute(TObject *Sender)
{
   if (!POP->Connected())
      {
       POP->Connect();
      }

  AnsiString LocalAttachmentfilename;
  AnsiString RecievedAttachmentfilename;
  AnsiString stTemp;
  int  intIndex;
  TListItem *li;

   stTemp = StatusBar1->Panels->Items[1]->Text;
   if (lvHeaders->Selected ==NULL)
    return;

   //initialise
   ShowBusy(true);
   Msg->Clear();
   Memo1->Clear();
   lvMessageParts->Items->Clear();
   From->Caption = "";
   Cc->Caption = "";
   Subject->Caption = "";
   Date->Caption = "";
   Receipt->Caption = "";
   Organization->Caption = "";
   Priority->Caption = "";
   pnlAttachments->Visible = false;

   //get message and put into MSG
   ShowStatus("Retrieving message " + lvHeaders->Selected->SubItems->Strings[3]  );
   int msgnum=lvHeaders->Selected->Index + 1;
   POP->Retrieve(msgnum, Msg);
   StatusBar1->Panels->Items[0]->Text = lvHeaders->Selected->SubItems->Strings[3];

   //Setup fields on screen from MSG
   From->Caption = Msg->From->Text;
   Recipients->Caption = Msg->Recipients->EMailAddresses;
   Cc->Caption = Msg->CCList->EMailAddresses;
   Subject->Caption = Msg->Subject;
   Date->Caption = FormatDateTime("dd mmm yyyy hh:mm:ss", Msg->Date);
   Receipt->Caption = Msg->ReceiptRecipient->Text;
   Organization->Caption = Msg->Organization;

   Priority->Caption = IntToStr((unsigned char)Msg->Priority + 1);


   //Setup attachments list
   ShowStatus("Decoding attachments (" + IntToStr(Msg->MessageParts->Count) + ")");
   Memo1->Lines->Clear();
   for (intIndex = 0; intIndex < (Msg->MessageParts->Count) ;intIndex++)
   {
         if (dynamic_cast<TIdAttachment*>(Msg->MessageParts->Items[intIndex]))

           { //general attachment
               pnlAttachments->Visible = true;
               li = lvMessageParts->Items->Add();
               li->ImageIndex = 8;
               RecievedAttachmentfilename= dynamic_cast<TIdAttachment*>(Msg->MessageParts->Items[intIndex])->FileName;

               TIdAttachment*e=dynamic_cast<TIdAttachment*>(Msg->MessageParts->Items[intIndex]);
               LocalAttachmentfilename=ExtractFilePath(ParamStr(0));
               LocalAttachmentfilename=LocalAttachmentfilename + "ATTACH\\";//add attach folder name to store locally in sub folder
               LocalAttachmentfilename=LocalAttachmentfilename + RecievedAttachmentfilename;
               li->Caption=LocalAttachmentfilename;
               if (e!=NULL)
               e->SaveToFile(LocalAttachmentfilename);
            }
         else
            {//body text
              if (dynamic_cast<TIdText*>(Msg->MessageParts->Items[intIndex] ))// then
               {
                Memo1->Lines->AddStrings(dynamic_cast<TIdText*>(Msg->MessageParts->Items[intIndex])->Body);
                }
            }

      }
   ShowStatus(stTemp);

   if (POP->Connected())
      {
       POP->Disconnect();
      }

   ShowBusy(false);

}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::DeleteExecute(TObject *Sender)
{
   if (lvHeaders->Selected !=NULL)
      {
         ShowBusy(true);
         lvHeaders->Selected->ImageIndex = 3;
         ShowBusy(false);
      }

}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::PurgeExecute(TObject *Sender)
{
   TListItem * li;
   int count=lvHeaders->Items->Count;
    while (count)
        {
        li=lvHeaders->Items->Item[count-1];
        if  (li->ImageIndex==3)
        {  if (!POP->Connected())
           POP->Connect();
           POP->Delete(count);
        }
        count--;
        }


   if (POP->Connected())
   POP->Disconnect();
   ToggleStatus(false,false);
   ::Sleep(500);//needed to delay reconnection..... raises an exception otherwise
   CheckMailExecute(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::DisconnectExecute(TObject *Sender)
{


   if (POP->Connected())
      {
         try
           { POP->Reset();
           }

         catch (...)
         {
            ShowStatus("Your POP server doesn''t have Reset feature");
         }
         POP->Disconnect();
      }
    ToggleStatus(false,true);
    TListItem * li;
    int count=lvHeaders->Items->Count;
    while (count)
      {
      li=lvHeaders->Items->Item[count-1];
       if  (li->ImageIndex==3)
       li->ImageIndex=5;
      count--;
      }

}
//---------------------------------------------------------------------------


void __fastcall TMainFrm::SetupExecute(TObject *Sender)
{
frmSetup->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::SendExecute(TObject *Sender)
{
frmMsgEditor->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TMainFrm::ReadConfiguration()
{


    TIniFile * MailIni;
    MailIni = new TIniFile(ExtractFilePath(ParamStr(0)) + "Mail.ini");

    Pop3ServerName = MailIni->ReadString("Pop3", "ServerName", "pop3.server.com");
    Pop3ServerPort = StrToInt(MailIni->ReadString("Pop3", "ServerPort", "110"));
    Pop3ServerUser = MailIni->ReadString("Pop3", "ServerUser", "your_login");
    Pop3ServerPassword = MailIni->ReadString("Pop3", "ServerPassword", "your_password");

    SmtpServerName = MailIni->ReadString("Smtp", "ServerName", "smtp.server.com");
    SmtpServerPort = StrToInt(MailIni->ReadString("Smtp", "ServerPort", "25"));
    SmtpServerUser = MailIni->ReadString("Smtp", "ServerUser", "your_login");
    SmtpServerPassword = MailIni->ReadString("Smtp", "ServerPassword", "your_password");
    SmtpAuthType = MailIni->ReadInteger("Smtp", "SMTPAuthenticationType", 0);
    UserEmail = MailIni->ReadString("Email", "PersonalEmail", "your@email.com");

    delete  MailIni;


}
void __fastcall TMainFrm::lvMessagePartsClick(TObject *Sender)
{
AnsiString LaunchFileName;
  //{display message parts we selected}
   if (lvMessageParts->Selected!=NULL)
      {
              LaunchFileName=lvMessageParts->Selected->Caption;
              LaunchFileName=UpperCase(LaunchFileName);
              if (LaunchFileName.AnsiPos(".EXE")>0)
                {
                WinExec(LaunchFileName.c_str(),SW_NORMAL);
                }
              else
              { char * associatedfilename=new char[MAX_PATH];//buffer for filename of associated executable

                HINSTANCE hinstassociation=FindExecutable(LaunchFileName.c_str(),ExcludeTrailingBackslash(ExtractFilePath(LaunchFileName)).c_str(), associatedfilename);

                if (hinstassociation>(HINSTANCE)32)//successful association found
                 {
                 AnsiString combinedfilenames=associatedfilename;
                 combinedfilenames = combinedfilenames + " \"" + LaunchFileName + "\"";
                 WinExec(combinedfilenames.c_str(),SW_NORMAL);
                 }
                 delete []associatedfilename;//free the memory
               }

      }
}
//---------------------------------------------------------------------------

AnsiString __fastcall TMainFrm::IncludeTrailingBackslash(AnsiString dir )
 {
     if  ( *dir.AnsiLastChar() != '\\' )
         dir += "\\";

     return  dir;
 }


AnsiString __fastcall TMainFrm::ExcludeTrailingBackslash(AnsiString dir)
{
 if  ( *dir.AnsiLastChar() == '\\' )
     dir.Delete(dir.Length(),1);

return dir;
}
