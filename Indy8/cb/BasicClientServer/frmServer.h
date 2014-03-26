//---------------------------------------------------------------------------

#ifndef frmServerH
#define frmServerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "IdBaseComponent.hpp"
#include "IdComponent.hpp"
#include "IdTCPServer.hpp"
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *IndyVersionLabel;
        TIdTCPServer *IdTCPServer;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall IdTCPServerExecute(TIdPeerThread *AThread);
private:	// User declarations
public:		// User declarations
        __fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
