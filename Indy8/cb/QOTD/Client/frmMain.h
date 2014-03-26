//---------------------------------------------------------------------------

#ifndef frmMainH
#define frmMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "IdBaseComponent.hpp"
#include "IdComponent.hpp"
#include "IdQotd.hpp"
#include "IdTCPClient.hpp"
#include "IdTCPConnection.hpp"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *lblServer;
        TLabel *lblQuote;
        TMemo *mmoQuoteOfTheDay;
        TEdit *edtQuoteDayServer;
        TButton *btnQuote;
        TIdQOTD *IdQtdDemo;
        TLabel *Label1;
        TLabel *IndyVersionLabel;
        void __fastcall btnQuoteClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
