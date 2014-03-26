//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IdAntiFreeze"
#pragma link "IdAntiFreezeBase"
#pragma link "IdBaseComponent"
#pragma link "IdComponent"
#pragma link "IdHTTP"
#pragma link "IdIntercept"
#pragma link "IdSSLIntercept"
#pragma link "IdSSLOpenSSL"
#pragma link "IdTCPClient"
#pragma link "IdTCPConnection"
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::cbURLChange(TObject *Sender)
{
  btnGo->Enabled = (cbURL->Text.Length() > 0);
  cbSSL->Checked = (UpperCase(cbURL->Text).Pos("HTTPS") > 0);
  // btnGo.Enabled := Length(cbURL.Text) > 0;
  // cbSSL.Checked := Pos('HTTPS', UpperCase(cbURL.Text)) > 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormActivate(TObject *Sender)
{
  btnStop->Enabled = false;
  cbMethod->ItemIndex = 1; // Set to GET
  cbProtocol->ItemIndex = 0; // Set to 1.0
  cbProtocol->OnChange(0);
  bPostFile = false;
  // Load history
  if (FileExists(ExtractFilePath(ParamStr(0)) + "history.dat")) {
    cbURL->Items->LoadFromFile(ExtractFilePath(ParamStr(0)) + "history.dat");
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
  btnStop->OnClick(0);
  try {
    cbURL->Items->SaveToFile(ExtractFilePath(ParamStr(0)) + "history.dat");
  }
  catch (...){
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormCreate(TObject *Sender)
{
  // Set the progress bar
  ProgressBar1->Parent = StatusBar1;
  ProgressBar1->Top = 2;
  ProgressBar1->Left = 1;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::cbProtocolChange(TObject *Sender)
{
  switch (cbProtocol->ItemIndex) {
    case 0: HTTP->ProtocolVersion = pv1_0; break;
    case 1: HTTP->ProtocolVersion = pv1_1; break;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::cbSSLClick(TObject *Sender)
{
  // check if the url has proper protocol set
  int p;

  if (cbSSL->Checked) {
    if (UpperCase(cbURL->Text).Pos("HTTPS") <= 0) {
      p = UpperCase(cbURL->Text).Pos("://");
      if (p > 0) {
        cbURL->Text = "https://" + cbURL->Text.SubString(p + 3, cbURL->Text.Length() - (p + 2));
      }
      else {
        cbURL->Text = "https://" + cbURL->Text;
      }
    }
  }
  else {
    if (UpperCase(cbURL->Text).Pos("HTTPS") > 0) {
      p = UpperCase(cbURL->Text).Pos("://");
      cbURL->Text = "http://" + cbURL->Text.SubString(p + 3, cbURL->Text.Length() - (p + 2));
    }
  }

}
//---------------------------------------------------------------------------
void __fastcall TForm2::mePostDataExit(TObject *Sender)
{
  if (mePostData->Lines->Count > 0) {
    edPostFile->Text = "";
    bPostFile = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::edPostFileExit(TObject *Sender)
{
  if (edPostFile->Text.Length() > 0) {
    mePostData->Clear();
    bPostFile = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::SpeedButton1Click(TObject *Sender)
{
  if (OpenDialog1->Execute()) {
    edPostFile->Text = OpenDialog1->FileName;
    edPostFile->OnExit(0);
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::HTTPStatus(TObject *axSender,
      const TIdStatus axStatus, const AnsiString asStatusText)
{
  StatusBar1->Panels->Items[1]->Text = asStatusText;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::HTTPWorkBegin(TObject *Sender, TWorkMode AWorkMode,
      const int AWorkCountMax)
{
  ProgressBar1->Position = 0;
  ProgressBar1->Max = AWorkCountMax;
  if (AWorkCountMax > 0)
    StatusBar1->Panels->Items[1]->Text = "Transfering: " + IntToStr(AWorkCountMax);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::HTTPWorkEnd(TObject *Sender, TWorkMode AWorkMode)
{
  StatusBar1->Panels->Items[1]->Text = "Done";
  ProgressBar1->Position = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::HTTPWork(TObject *Sender, TWorkMode AWorkMode,
      const int AWorkCount)
{
  if (ProgressBar1->Max > 0) {
    StatusBar1->Panels->Items[1]->Text = IntToStr(AWorkCount) +  " bytes of " +
    IntToStr(ProgressBar1->Max) + " bytes.";
    ProgressBar1->Position = AWorkCount;
  }
  else
    StatusBar1->Panels->Items[1]->Text = IntToStr(AWorkCount) + " bytes.";
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnGoClick(TObject *Sender)
{
  TMemoryStream *Source;
  TStringStream *Response;

  // Add the URL to the combo-box.
  if (cbURL->Items->IndexOf(cbURL->Text) == -1)
    cbURL->Items->Add(cbURL->Text);
  Screen->Cursor = crHourGlass;
  btnStop->Enabled = true;
  btnGo->Enabled = false;
  try {
    memoHTML->Clear();
    // Set the properties for HTTP
    HTTP->Request->Username = edUsername->Text;
    HTTP->Request->Password = edPassword->Text;
    HTTP->Request->ProxyServer = edProxyServer->Text;
    HTTP->Request->ProxyPort = StrToIntDef(edProxyPort->Text, 80);
    HTTP->Request->ContentType = edContentType->Text;

    if (cbSSL->Checked)
    HTTP->Intercept = SSL;
    else
    HTTP->Intercept = 0;

    switch ( cbMethod->ItemIndex)
    {
    case 0: // Head
        {
          HTTP->Head(cbURL->Text);
          memoHTML->Lines->Add("This is an example of some of the headers returned: ");
          memoHTML->Lines->Add("---------------------------------------------------");
          memoHTML->Lines->Add("Content-Type: " + HTTP->Response->ContentType);
          memoHTML->Lines->Add("Date: " + DateToStr(HTTP->Response->Date));
          memoHTML->Lines->Add("");
          memoHTML->Lines->Add("You can view all the headers by examining HTTP.Response");
          break;
        }
    case 1: // Get
        {
          memoHTML->Lines->Text = HTTP->Get(cbURL->Text);
          break;
        }
    case 2: // Post
        {
          Response = new TStringStream("");
          try
          {
            if (!bPostFile)
            {
              HTTP->Post(cbURL->Text, mePostData->Lines, Response);
            }
            else
            {
              Source = new TMemoryStream();
              try
              {
                Source->LoadFromFile(edPostFile->Text);
                HTTP->Post(cbURL->Text, Source, Response);
              }
              catch (...)
              {
              }
              Source->Free();
            }
            memoHTML->Lines->Text = Response->DataString;
          }
          catch (...)
          {
          }
          Response->Free();
        }
      }
    }
  catch (...)
  {
  }
  Screen->Cursor = crDefault;
  btnStop->Enabled = False;
  btnGo->Enabled = True;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnStopClick(TObject *Sender)
{
  HTTP->DisconnectSocket();  // Clicking this does not get rid of the hourclass cursor
  btnStop->Enabled = false;
  Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------
