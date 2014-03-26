/***********************************************************/
/**  Chat room demo                                       **/
/***********************************************************/
/**  Created by: Jeremy Darling    webmaster@eonclash.com **/
/**  Created on: Sept. 21st 2000                          **/
/**  Origional Indy Version: 8.005B                       **/
/**  Converted TO BCB5 BY: Ray Toye raytt@bigfoot.com     **/
/**  Converted on: 12/26/2000                             **/
/**  Converted Indy Version: 8.010B                       **/
/***********************************************************/
/**  Updates                                              **/
/***********************************************************/
/**  Sept. 25th 2000 Jeremy Darling                       **/
/**    Added functionality that is commonly wanted in a   **/
/**    chat program.                                      **/
/**      1)  Added send client list on request            **/
/**      2)  Added ability to add system commands         **/
/**                                                       **/
/***********************************************************/





//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ServerFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma link "IdBaseComponent"
#pragma link "IdComponent"
#pragma link "IdTCPServer"
#pragma link "IdThreadMgr"
#pragma link "IdThreadMgrDefault"
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnServerUpClick(TObject *Sender)
{

  try
   {  // Setup GUI buttons
    btnClients->Enabled= btnServerUp->Down;
    seBinding->Enabled = ! btnServerUp->Down;
    edSyopName->Enabled= ! btnServerUp->Down;
//   Check to see if the server is online or offline
    if (btnServerUp->Down)
      {
      // Server is online
        btnServerUp->ImageIndex = 1;
        btnServerUp->Hint       = "Shut down server";
      // Startup server
        tcpServer->Active       = true;
      }
    else
      {
      // Server is offline
        btnServerUp->ImageIndex = 0;
        btnServerUp->Hint       = "Start up server";
      // Shutdown server
        tcpServer->Active       = false;
      }

  }
  catch(...)
//   If we have a problem then rest things
{   btnServerUp->Down  = false;
    seBinding->Enabled = ! btnServerUp->Down;
    btnClients->Enabled= btnServerUp->Down;
    edSyopName->Enabled= ! btnServerUp->Down;
 }


}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
//Initalize our clients list
  Clients = new TList;
//Call updatebindings so that the servers bindings are correct
  UpdateBindings();
//Get the local DNS entry for this computer
  lblDNS->Caption = tcpServer->LocalName;
//Display the current version of indy running on the system
  lblSocketVer->Caption = tcpServer->Version;
  //set form caption
  this->Caption="Indy Powered Chat Server";

}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::UpdateBindings()
{

   TIdSocketHandle* Binding;

//Set the TIdTCPServer's port to the chosen value
  tcpServer->DefaultPort = StrToInt(seBinding->Text);
//Remove all bindings that currently exist
  tcpServer->Bindings->Clear();
//Create a new binding
  Binding = tcpServer->Bindings->Add();
//Assign that bindings port to our new port
  Binding->Port = StrToInt(seBinding->Text);

}
void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
  if ((Clients->Count > 0) ||(btnServerUp->Down))
    {
      Action = caNone;
      ShowMessage("Cannot close CBServ while server is online.");
      return;
    }
  delete Clients;

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Savetofile1Click(TObject *Sender)
{
  if (!dynamic_cast<TMemo*> (puMemoMenu->PopupComponent))
    return;

  if (SaveDialog1->Execute())
    {
     dynamic_cast<TMemo*>(puMemoMenu->PopupComponent)->Lines->SaveToFile(SaveDialog1->FileName);
    }


}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::Loadfromfile1Click(TObject *Sender)
{
  if (!dynamic_cast<TMemo*>(puMemoMenu->PopupComponent))
    return;

  if (OpenDialog1->Execute())
    {
      dynamic_cast<TMemo*>(puMemoMenu->PopupComponent)->Lines->LoadFromFile(OpenDialog1->FileName);
    }


}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnClientsClick(TObject *Sender)
{
  UpdateClientList();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::UpdateClientList()
{
int  Count;
TSimpleClient* simpclient;

//Loop through all the clients connected to the system and set their names
 for ( Count = 0;  Count < lbClients->Items->Count; Count++)
     {
      if (Count < Clients->Count)
      {simpclient=(TSimpleClient*)Clients->Items[Count];
      lbClients->Items->Strings[Count] = simpclient->Name;
      }


    }
}

void __fastcall TfrmMain::seBinding1Change(TObject *Sender)
{
  UpdateBindings();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tcpServerConnect(TIdPeerThread *AThread)
{


 TSimpleClient * Client;

// Send a welcome message, and prompt for the users name
  AThread->Connection->WriteLn("ISD Connection Established...");
  AThread->Connection->WriteLn("Please send valid login sequence...");
  AThread->Connection->WriteLn("Your Name:");
// Create a client object
  Client = new TSimpleClient;
// Assign its default values
  Client->DNS  = AThread->Connection->LocalName;
  Client->Name = "Logging In";
  Client->ListLink = lbClients->Items->Count;
//Assign the thread to it for ease in finding
  Client->Thread = AThread;
//Add to our clients list box
  lbClients->Items->Add(Client->Name);
//Assign it to the thread so we can identify it later
  AThread->Data = Client;
//Add it to the clinents list
  Clients->Add(Client);


}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tcpServerDisconnect(TIdPeerThread *AThread)
{
 TSimpleClient* Client;

//Retrieve Client Record from Data pointer
  Client = (TSimpleClient*)(AThread->Data);
//Remove Client from the Clients TList
  Clients->Delete(Client->ListLink);
//Remove Client from the Clients List Box
  lbClients->Items->Delete(lbClients->Items->IndexOf(Client->Name));
//Free the Client object
  delete Client;
  AThread->Data = NULL;



}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::BroadcastMessage(AnsiString WhoFrom, AnsiString TheMessage   )
{
 int Count;
 TList* List;
 TIdPeerThread * peerthread;
 AnsiString EMote;
 AnsiString Msg;

 Msg = Trim(TheMessage);

 EMote = Trim(memEMotes->Lines->Values[Msg]);

  if (WhoFrom != "System")
    Msg = WhoFrom + ": " + Msg;

  if (EMote != "")
    Msg = Msg.sprintf(EMote.c_str(),WhoFrom.c_str());

  List = tcpServer->Threads->LockList();

  for (Count = 0;Count < List->Count ;Count++)
     {peerthread=(TIdPeerThread*)List->Items[Count];
      if (dynamic_cast <TIdPeerThread*>(peerthread))
      peerthread->Connection->WriteLn(Msg);
     }
  tcpServer->Threads->UnlockList();
}

void __fastcall TfrmMain::tcpServerExecute(TIdPeerThread *AThread)
{
  TSimpleClient *Client;
  AnsiString Com;     // System command
  AnsiString Msg;

//Get the text sent from the client
try
{
  Msg    = AThread->Connection->ReadLn("",5000);
}
catch (...)
{

}
  // Get the clients package info
if (Msg.Length()==0)return;
  Client = (TSimpleClient *)(AThread->Data);
// Check to see if the clients name has been assigned yet
  if (Client->Name == "Logging In")
   {
   //  if not, assign the name and announce the client
      Client->Name = Msg;
      UpdateClientList();
      BroadcastMessage("System", Msg + " has just logged in.");
      AThread->Connection->WriteLn(memEntry->Lines->Text);
   }
  else
  // If name is set, then send the message
  if (Msg[1] != '@')
    {
    // Not a system command
      BroadcastMessage(Client->Name, Msg);
    }
  else
    {
    // System command
      Com = UpperCase(Trim(Msg.SubString(2, Msg.Pos(":") -2)));
      Msg = UpperCase(Trim(Msg.SubString(Msg.Pos(":") +1, Msg.Length())));
      if (Com == "CLIENTS")
     AThread->Connection->WriteLn( AnsiString("@") + AnsiString("clients:") +
                 lbClients->Items->CommaText);

     if (Com == "KILL")
        KillClient(Msg);
    }


}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnPMClick(TObject *Sender)
{


AnsiString Msg;
TSimpleClient*  Client;
TIdPeerThread * threadptr;
  Msg = InputBox("Private Message", "What is the message", "");
  Msg = Trim(Msg);
  Msg = edSyopName->Text + "> " + Msg;
  if ((Msg != "")&&(lbClients->ItemIndex != -1))
        {
      Client =(TSimpleClient*) Clients->Items[lbClients->ItemIndex];
      if (dynamic_cast<TSimpleClient*>(Client))
      {threadptr=( TIdPeerThread*)Client->Thread;
        if (dynamic_cast<TIdPeerThread*>(threadptr))
        threadptr->Connection->WriteLn(Msg);
      }
        }


}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnKillClientClick(TObject *Sender)
{
  AnsiString Msg;
  TSimpleClient* Client;
  TIdPeerThread* peerthread;
  Msg = InputBox("Disconnect message", "Enter a reason for the disconnect", "");
  Msg = Trim(Msg);
  Msg = edSyopName->Text + "> " + Msg;
  if ((Msg != "")&&(lbClients->ItemIndex != -1))
        {
      Client = (TSimpleClient*)Clients->Items[lbClients->ItemIndex];
      peerthread=(TIdPeerThread*)Client->Thread;
      peerthread->Connection->WriteLn(Msg);
     try
     {
      peerthread->Connection->Disconnect();
     }
     catch (...)
     {
     }
  }


}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::lbClientsClick(TObject *Sender)
{


  TSimpleClient* Client;

  btnPM->Enabled = lbClients->ItemIndex != -1;
  btnKillClient->Enabled = btnPM->Enabled;

  if (lbClients->ItemIndex == -1 )
    return;
  Client =(TSimpleClient*) Clients->Items[lbClients->ItemIndex];
  lblClientName->Caption = Client->Name;
  lblClientDNS->Caption  = Client->DNS;


}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::KillClient(AnsiString ClientName)
{
 TSimpleClient* Client;
 TIdPeerThread* peerthread;
 ClientName=UpperCase(ClientName);
 int Count;
 int matchfound=0;
  for ( Count = 0;  Count < lbClients->Items->Count; Count++)
     {
      if (Count < Clients->Count)
      {Client=(TSimpleClient*)Clients->Items[Count];
       if (UpperCase(Client->Name) ==ClientName)
       {
       matchfound=true;
       break;
       }
      }

     }
      if (matchfound==0)
      {
      ShowMessage("Error Finding Client");
      return;
      }

      peerthread=(TIdPeerThread*)Client->Thread;
      try
        {
        peerthread->Connection->Disconnect();
        }
       catch (...)
        {
        }






}

