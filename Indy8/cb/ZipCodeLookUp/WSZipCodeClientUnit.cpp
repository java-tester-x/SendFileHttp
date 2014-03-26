//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WSZipCodeClientUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IdBaseComponent"
#pragma link "IdComponent"
#pragma link "IdTCPClient"
#pragma link "IdTCPConnection"
#pragma link "IdAntiFreeze"
#pragma link "IdAntiFreezeBase"
#pragma resource "*.dfm"
TClientMain *ClientMain;
//---------------------------------------------------------------------------
__fastcall TClientMain::TClientMain(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TClientMain::btnClearClick(TObject *Sender)
{
   memoInput->Clear();
   lboxResults->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TClientMain::btnLookupClick(TObject *Sender)
{
   String s;
   lboxResults->Clear();
   try {
      Client->Connect();
      lboxResults->Items->Add( Client->ReadLn("\r\n",5000) );
      for( int i = 0 ; i < memoInput->Lines->Count ; ++i ) {
        Client->WriteLn( String("ZipCode ") + memoInput->Lines->Strings[i] );
        lboxResults->Items->Add( memoInput->Lines->Strings[i] );
        s = Client->ReadLn("\r\n",5000);
        if( s.Length() == 0 )
          s = "-- No entry found for this zip code.";
        lboxResults->Items->Add( s );
        lboxResults->Items->Add("");
      }
      Client->WriteLn( "Quit" );
      Client->Disconnect();
   }
   catch( EIdException& error ) {
     Client->Disconnect();
   }
}
//---------------------------------------------------------------------------
void __fastcall TClientMain::FormCreate(TObject *Sender)
{
IndyVersionLabel->Caption=Client->Version;        
}
//---------------------------------------------------------------------------

