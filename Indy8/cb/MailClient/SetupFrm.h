//---------------------------------------------------------------------------

#ifndef SetupFrmH
#define SetupFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmSetup : public TForm
{
__published:	// IDE-managed Components
        TBitBtn *BitBtn1;
        TPageControl *pcSetup;
        TTabSheet *tsPop3;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TEdit *POPServer;
        TEdit *POPPort;
        TEdit *Email;
        TEdit *Account;
        TEdit *Password;
        TTabSheet *tsSmtp;
        TLabel *lblAuthenticationType;
        TLabel *lbAccount;
        TLabel *lbPassword;
        TLabel *Label11;
        TLabel *Label12;
        TComboBox *cboAuthType;
        TEdit *edtAccount;
        TEdit *edtPassword;
        TEdit *SMTPServer;
        TEdit *SMTPPort;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmSetup(TComponent* Owner);
        void __fastcall UpdateServerLabel();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSetup *frmSetup;
//---------------------------------------------------------------------------
#endif
