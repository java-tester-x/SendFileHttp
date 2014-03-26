//---------------------------------------------------------------------------

#ifndef frmFingerClientH
#define frmFingerClientH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "IdBaseComponent.hpp"
#include "IdComponent.hpp"
#include "IdFinger.hpp"
#include "IdTCPClient.hpp"
#include "IdTCPConnection.hpp"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TLabel *lblQuerry;
        TLabel *lblInstructions;
        TEdit *edtQuerry;
        TMemo *mmoQuerryResults;
        TCheckBox *chkVerboseQuerry;
        TBitBtn *bbtnQuerry;
        TIdFinger *IdFngFinger;
        void __fastcall bbtnQuerryClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
