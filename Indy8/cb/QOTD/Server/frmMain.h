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
#include "IdQotdServer.hpp"
#include "IdTCPServer.hpp"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TIdQOTDServer *IdQOTDServer1;
        TLabel *Label1;
        TLabel *IndyVersionLabel;
        void __fastcall IdQOTDServer1CommandQOTD(TIdPeerThread *Thread);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
