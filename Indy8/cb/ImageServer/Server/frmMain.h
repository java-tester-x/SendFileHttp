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
#include "IdTCPServer.hpp"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TListBox *lstRequests;
        TIdTCPServer *IdTCPServer;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall IdTCPServerConnect(TIdPeerThread *AThread);
        void __fastcall IdTCPServerDisconnect(TIdPeerThread *AThread);
        void __fastcall IdTCPServerExecute(TIdPeerThread *AThread);
private:	// User declarations
public:	  AnsiString sFilePattern;	// User declarations
        __fastcall TMainForm(TComponent* Owner);
        AnsiString  __fastcall GetList();
        void __fastcall TMainForm::ScreenShot(int x ,int  y ,int  Width ,int Height,Graphics::TBitmap  *bm);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
