/************************************************************************************/
/*                                                                                  */
/* Project : Finger CLient Demo Converted To BCB                                    */
/* Unit Name: frmFingerClient                                                       */
/* Purpose : Simple Finger Client demo                                              */
/* Conversion Author : Ray Toye    raytt@bigfoot.com                                */
/* Date : 12/26/2000 - 19:52:31                                                     */
/* History : This is a Conversion of the Delphi Indy Demo                           */
/*           not an original implementation                                         */
/************************************************************************************/

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmFingerClient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IdBaseComponent"
#pragma link "IdComponent"
#pragma link "IdFinger"
#pragma link "IdTCPClient"
#pragma link "IdTCPConnection"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::bbtnQuerryClick(TObject *Sender)
{
//  {Set the Querry string for the Finger from the text entered}
  IdFngFinger->CompleteQuery = edtQuerry->Text;
//  {Do we want verbose querry - not supported on many systems}
  IdFngFinger->VerboseOutput = chkVerboseQuerry->Checked;
//  {Do our querry with the Finger function}
  mmoQuerryResults->Lines->Text  = IdFngFinger->Finger();

}
//---------------------------------------------------------------------------
 