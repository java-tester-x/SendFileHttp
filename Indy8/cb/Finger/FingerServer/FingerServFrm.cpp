/************************************************************************************/
/*                                                                                  */
/* Project : Finger Server Demo Converted To BCB                                    */
/* Unit Name: FingerServer Form                                                     */
/* Purpose : Simple Finger Server demo                                              */
/* Conversion Author : Ray Toye    raytt@bigfoot.com                                */
/* Date : 12/26/2000 - 19:52:31                                                     */
/* History : This is a Conversion of the Delphi Indy Demo                           */
/*           not an original implementation                                         */
/************************************************************************************/




//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FingerServFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//#pragma link "IdBaseComponent"
//#pragma link "IdComponent"
//#pragma link "IdFingerServer"
//#pragma link "IdTCPServer"
#pragma resource "*.dfm"
TfrmMain *frmMain;
const AnsiString SampleUsers  [3]=
  {"TIDFINGER", "TIDQUOTD", "TIDTIME"};


//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
        : TForm(Owner)
{
listofstrings=new TStringList;
listofstrings->Add(SampleUsers[0]);
listofstrings->Add(SampleUsers[1]);
listofstrings->Add(SampleUsers[2]);

AnsiString Version= IdFingerServer1->Version;
Label1->Caption="Indy Version "+Version;


}
//---------------------------------------------------------------------------


















void __fastcall TfrmMain::IdFingerServer1CommandFinger(
      TIdPeerThread *AThread, const AnsiString AUserName)
{

//  {general querry - just list users}
  if (AUserName == "")
  {
    AThread->Connection->WriteLn("TIdFinger");
    AThread->Connection->WriteLn("TIdQuotD");
    AThread->Connection->WriteLn("TIdTime");
  } //if AUserName = '' then
  else
 {// {Just Provide breif information}

    int succ=listofstrings->IndexOf(UpperCase(AUserName));
    switch   (succ)
    { case 0 : //TIdFinger
          {
            AThread->Connection->WriteLn("TIdFinger implements RFC 1288");
            break;
          }
      case 1 : //TIdQuotD
          {
            AThread->Connection->WriteLn("TIdQuotD implements RFC 865");
            break;
          }
     case 2 : //TIdTime
        {
            AThread->Connection->WriteLn("TIdTime implements RFC 868");
            break;
        }
      default:
       { // {This user is not on our system}
        AThread->Connection->WriteLn(AUserName + "?" );
        };
    };
  };






}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::IdFingerServer1CommandVerboseFinger(
      TIdPeerThread *AThread, const AnsiString AUserName)
{

  AThread->Connection->WriteLn("Verbose query");
   //{general querry - just list users}
  if (AUserName == "")
        {
    AThread->Connection->WriteLn("TIdFinger");
    AThread->Connection->WriteLn("TIdQuotD");
    AThread->Connection->WriteLn("TIdTime");
  } //if AUserName = '' then
  else
  {// {Just Provide breif information}
   int succ=listofstrings->IndexOf(UpperCase(AUserName));
    switch   (succ)
    { case 0 : //TIdFinger
         {
            AThread->Connection->WriteLn("TIdFinger implements RFC 1288");
            AThread->Connection->WriteLn("");
            AThread->Connection->WriteLn("Finger is used to provide information");
            AThread->Connection->WriteLn("such as if the user is logged into a");
            AThread->Connection->WriteLn("mainframe, when they last checked their");
            AThread->Connection->WriteLn("E-Mail and received new E-Mail.  It");
            AThread->Connection->WriteLn("can also provide other information such");
            AThread->Connection->WriteLn("what a user puts into a plan file.");
            break;
          }
      case 1 : //TIdQuotD
          {
            AThread->Connection->WriteLn("TIdQuotD implements RFC 865");
            AThread->Connection->WriteLn("");
            AThread->Connection->WriteLn("Quote of the Day is used for testing");
            AThread->Connection->WriteLn("TCP development by providing a quote.");
            AThread->Connection->WriteLn("to the client.  It is sometimes used");
            AThread->Connection->WriteLn("brief information for anybody.");
            break;
          }
      case 2 : //TIdTime
          {
            AThread->Connection->WriteLn("TIdTime implements RFC 868");
            AThread->Connection->WriteLn("");
            AThread->Connection->WriteLn("Time is used for synchronizing clocks");
            AThread->Connection->WriteLn("on a local area network.  For acurate");
            AThread->Connection->WriteLn("synchronization, use SNTP (Simple");
            AThread->Connection->WriteLn("Network Time Protocol).");
            break;
            }
      default:
      {
      //  {This user is not on our system}
       AThread->Connection->WriteLn( AUserName + "?" );
      }
    }
  }
   //if AUserName = ''



}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
IdFingerServer1->Active=true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
IdFingerServer1->Active=false;

delete listofstrings;

}
//---------------------------------------------------------------------------

