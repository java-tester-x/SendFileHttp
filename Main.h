//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TButton *Button2;
        TEdit *Edit1;
        TEdit *Edit2;
        TEdit *Edit3;
        TOpenDialog *OpenDialog1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TMemo *Memo1;
        TLabel *Label4;
        TIdHTTP *IdHttpForm;
        TProgressBar *ProgressBar1;
        TButton *Button3;
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall IdHttpFormWorkBegin(TObject *Sender,
          TWorkMode AWorkMode, const int AWorkCountMax);
        void __fastcall IdHttpFormWork(TObject *Sender,
          TWorkMode AWorkMode, const int AWorkCount);
        void __fastcall IdHttpFormWorkEnd(TObject *Sender,
          TWorkMode AWorkMode);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
