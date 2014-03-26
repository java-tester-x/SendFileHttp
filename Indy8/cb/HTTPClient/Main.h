//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "IdAntiFreeze.hpp"
#include "IdAntiFreezeBase.hpp"
#include "IdBaseComponent.hpp"
#include "IdComponent.hpp"
#include "IdHTTP.hpp"
#include "IdIntercept.hpp"
#include "IdSSLIntercept.hpp"
#include "IdSSLOpenSSL.hpp"
#include "IdTCPClient.hpp"
#include "IdTCPConnection.hpp"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TBitBtn *btnGo;
        TBitBtn *btnStop;
        TComboBox *cbURL;
        TComboBox *cbProtocol;
        TCheckBox *cbSSL;
        TComboBox *cbMethod;
        TGroupBox *GroupBox1;
        TLabel *Label4;
        TLabel *Label5;
        TEdit *edUsername;
        TEdit *edPassword;
        TGroupBox *GroupBox2;
        TLabel *Label6;
        TLabel *Label7;
        TEdit *edProxyServer;
        TEdit *edProxyPort;
        TGroupBox *GroupBox3;
        TMemo *mePostData;
        TGroupBox *GroupBox4;
        TLabel *Label8;
        TSpeedButton *SpeedButton1;
        TLabel *Label9;
        TEdit *edPostFile;
        TEdit *edContentType;
        TMemo *memoHTML;
        TStatusBar *StatusBar1;
        TProgressBar *ProgressBar1;
        TIdAntiFreeze *IdAntiFreeze1;
        TIdHTTP *HTTP;
        TOpenDialog *OpenDialog1;
        TIdConnectionInterceptOpenSSL *SSL;
        void __fastcall cbURLChange(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall cbProtocolChange(TObject *Sender);
        void __fastcall cbSSLClick(TObject *Sender);
        void __fastcall mePostDataExit(TObject *Sender);
        void __fastcall edPostFileExit(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall HTTPStatus(TObject *axSender,
          const TIdStatus axStatus, const AnsiString asStatusText);
        void __fastcall HTTPWorkBegin(TObject *Sender, TWorkMode AWorkMode,
          const int AWorkCountMax);
        void __fastcall HTTPWorkEnd(TObject *Sender, TWorkMode AWorkMode);
        void __fastcall HTTPWork(TObject *Sender, TWorkMode AWorkMode,
          const int AWorkCount);
        void __fastcall btnGoClick(TObject *Sender);
        void __fastcall btnStopClick(TObject *Sender);
private:	// User declarations
        bool bPostFile;
public:		// User declarations
        __fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
