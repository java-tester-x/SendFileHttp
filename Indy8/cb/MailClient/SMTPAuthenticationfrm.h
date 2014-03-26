//---------------------------------------------------------------------------

#ifndef SMTPAuthenticationfrmH
#define SMTPAuthenticationfrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmSMTPAuthentication : public TForm
{
__published:	// IDE-managed Components
        TBitBtn *BitBtn1;
        TGroupBox *GroupBox1;
        TLabel *lblAuthenticationType;
        TLabel *lbAccount;
        TLabel *lbPassword;
        TComboBox *cboAuthType;
        TEdit *edtAccount;
        TEdit *edtPassword;
private:	// User declarations
public:		// User declarations
        __fastcall TfrmSMTPAuthentication(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSMTPAuthentication *frmSMTPAuthentication;
//---------------------------------------------------------------------------
#endif
