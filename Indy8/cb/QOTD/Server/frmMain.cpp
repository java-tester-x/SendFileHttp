/***********************************************************/
/**  Quote Of The Day Server demo                         **/
/***********************************************************/
/**  Created by: Ray Toye    raytt@bigfoot.com            **/
/**  Created on: 01/07/2001                               **/
/**  Origional Indy Version: 8.012B                       **/
/***********************************************************/
/**  Updates                                              **/
/***********************************************************/
/**                                                       **/
/***********************************************************/

//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "frmMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IdBaseComponent"
#pragma link "IdComponent"
#pragma link "IdQotdServer"
#pragma link "IdTCPServer"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::IdQOTDServer1CommandQOTD(TIdPeerThread *Thread)
{

TDateTime today=Now();
unsigned short hr,min,sec,msec;
DecodeTime(today.CurrentTime(),hr,min,sec,msec);
srand(msec);
int strnum=random(10)+1;
AnsiString quote=DateTimeToStr(today)+ "\n" + LoadStr(strnum);
AnsiString quoteauthor=LoadStr(strnum+100);
Thread->Connection->WriteLn(quote);
Thread->Connection->WriteLn(quoteauthor);
Thread->Connection->Disconnect();

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
IndyVersionLabel->Caption=IdQOTDServer1->Version;
IdQOTDServer1->Active=true;
}
//---------------------------------------------------------------------------

