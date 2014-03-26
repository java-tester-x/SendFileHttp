//---------------------------------------------------------------------------

#include <vcl.h>
#include <idstack.hpp>
#include <stdio.h>
#pragma hdrstop

#include "MainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IdAntiFreeze"
#pragma link "IdAntiFreezeBase"
#pragma link "IdBaseComponent"
#pragma link "IdComponent"
#pragma link "IdIcmpClient"
#pragma link "IdRawBase"
#pragma link "IdRawClient"
#pragma link "IdUDPBase"
#pragma link "IdUDPClient"
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::acGoExecute(TObject *Sender)
{
TCursor  saveCursor;

  saveCursor = Screen->Cursor;
  Screen->Cursor = crHourGlass;
  try
    {  Stopped = false;
      acGo->Enabled = false;
      acStop->Enabled = true;
      acResolve->Execute();
      if ((bResolved) &&(!Stopped))
        {
        acPing->Execute();
        if (!Stopped)
           acTrace->Execute();
        }
      acGo->Enabled = true;
      acStop->Enabled = false;
     }
     catch(...)
     {
     }
  Screen->Cursor = saveCursor;



}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::acResolveExecute(TObject *Sender)
{
char *s=new char[256];//for AnsiString.sprintf differences in bcb5 and bcb4
  bResolved = false;
  sprintf(s,"resolving %s",edTarget->Text.c_str());
  lbLog->Items->Append(s);
  try
 {  Application->ProcessMessages();
    ResolvedHost =GStack->WSGetHostByName(edTarget->Text.c_str());
    bResolved = true;
    sprintf(s,"%s resolved to %s",edTarget->Text.c_str(), ResolvedHost.c_str());
    lbLog->Items->Append(s);
  }
  catch(Exception& e)
  {
      lbLog->Items->Text  = lbLog->Items->Text + e.Message;
 }
delete []s;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::acTraceExecute(TObject *Sender)
{
 char *s=new char[256];//used because BCB4 AnsiString Sprintf is different than bcb5 sprintf
  int TTL;
  bool Reached;
 TListItem* aItem;

  TTL = 0;
  Reached = false;
  lvTrace->Items->Clear();
  do
   { TTL++;
    IdIcmpClient->Host = ResolvedHost;
    IdIcmpClient->TTL = TTL;
    IdIcmpClient->ReceiveTimeout = 5000;
    IdIcmpClient->Ping();
    aItem =lvTrace->Items->Add();
    aItem->SubItems->Clear();
    aItem->SubItems->Append(AnsiString(TTL));
    switch (IdIcmpClient->ReplyStatus.ReplyStatusType)
    {
    case  rsEcho:
    {
        aItem->SubItems->Add(IdIcmpClient->ReplyStatus.FromIpAddress);
        sprintf(s,"Reached in : %d ms",IdIcmpClient->ReplyStatus.MsRoundTripTime);
        aItem->SubItems->Add(s);
        Reached = true;
        break;
     }
     case rsError:
        {
        aItem->SubItems->Add(IdIcmpClient->ReplyStatus.FromIpAddress);
        aItem->SubItems->Add("Unknown error.");
        break;
        }
     case rsTimeOut:
     {
        aItem->SubItems->Add("?.?.?.?");
        aItem->SubItems->Add("Timed out.");
        break;
     }
     case rsErrorUnreachable:
     { aItem->SubItems->Add(IdIcmpClient->ReplyStatus.FromIpAddress);
       sprintf(s,"Destination network unreachable %d",IdIcmpClient->ReplyStatus.MsRoundTripTime);
       aItem->SubItems->Add(s);
        break;
     }
      case rsErrorTTLExceeded:
        {
        aItem->SubItems->Add(IdIcmpClient->ReplyStatus.FromIpAddress);
        sprintf(s,"TTL=%d",IdIcmpClient->ReplyStatus.TimeToLive);
        aItem->SubItems->Add(s);
        break;
      }
    }; // case
    Application->ProcessMessages();
   }
  while  ((!Reached)&& (TTL < StrToInt(seMaxHops->Text))&&(!Stopped));
delete []s;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::acPingExecute(TObject *Sender)
{
 PingHost(ResolvedHost, StrToInt(seMaxHops->Text));
 Application->ProcessMessages();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::acStopExecute(TObject *Sender)
{
  Stopped = true;
  acStop->Enabled  = false;

}
//---------------------------------------------------------------------------


bool __fastcall TfrmMain::PingHost(AnsiString Host,int TTL)
{bool result = false;
char * s=new char[256];//used because of differences in AnsiString.sprintf between    bcb4 and bcb5
  IdIcmpClient->Host = Host;
  IdIcmpClient->TTL = TTL;
  IdIcmpClient->ReceiveTimeout = 5000;
  IdIcmpClient->Ping();
  switch (IdIcmpClient->ReplyStatus.ReplyStatusType)
{
  case rsEcho:
    {
      sprintf(s,"response from host %s in %d millisec.",
              IdIcmpClient->ReplyStatus.FromIpAddress.c_str(),
              IdIcmpClient->ReplyStatus.MsRoundTripTime);
      lbLog->Items->Append(s);
      result = true;
      break;
    }
    case rsError:
     {
     lbLog->Items->Append("Unknown error.");
     break;
     }
    case rsTimeOut:
    {
      lbLog->Items->Append("Timed out.");
      break;
     }
    case rsErrorUnreachable:
    {

      sprintf(s,"Host %s reports destination network unreachable.",
            IdIcmpClient->ReplyStatus.FromIpAddress.c_str());
      lbLog->Items->Append(s);

    break;
    }
    case rsErrorTTLExceeded:
    {
       sprintf(s,"Hop %d %s: TTL expired.",
                  IdIcmpClient->TTL,
               IdIcmpClient->ReplyStatus.FromIpAddress.c_str());

      lbLog->Items->Append(s);
      break;
      }
 } // case
delete []s;
return result;
}
void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
IndyVersionLabel->Caption=IdIcmpClient->Version;        
}
//---------------------------------------------------------------------------

