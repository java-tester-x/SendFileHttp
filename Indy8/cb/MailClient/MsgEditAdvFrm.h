//---------------------------------------------------------------------------

#ifndef MsgEditAdvFrmH
#define MsgEditAdvFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmMsgEditAdv : public TForm
{
__published:	// IDE-managed Components
        TLabel *lblSender;
        TLabel *Label1;
        TEdit *edtSender;
        TMemo *mmoExtraHeaders;
        TBitBtn *bbtnOk;
        TBitBtn *bbtnCancel;
private:	// User declarations
public:		// User declarations
        __fastcall TfrmMsgEditAdv(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMsgEditAdv *frmMsgEditAdv;
//---------------------------------------------------------------------------
#endif
