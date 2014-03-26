//---------------------------------------------------------------------------

#ifndef WSZipCodeClientUnitH
#define WSZipCodeClientUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "IdBaseComponent.hpp"
#include "IdComponent.hpp"
#include "IdTCPClient.hpp"
#include "IdTCPConnection.hpp"
#include "IdAntiFreeze.hpp"
#include "IdAntiFreezeBase.hpp"
//---------------------------------------------------------------------------
class TClientMain : public TForm
{
__published:	// IDE-managed Components
        TMemo *memoInput;
        TPanel *Panel1;
        TButton *btnLookup;
        TButton *btnClear;
        TLabel *Label1;
        TListBox *lboxResults;
        TIdTCPClient *Client;
        TIdAntiFreeze *IdAntiFreeze1;
        TLabel *Label2;
        TLabel *IndyVersionLabel;
        void __fastcall btnClearClick(TObject *Sender);
        void __fastcall btnLookupClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TClientMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TClientMain *ClientMain;
//---------------------------------------------------------------------------
#endif
