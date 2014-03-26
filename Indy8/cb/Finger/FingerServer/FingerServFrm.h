//---------------------------------------------------------------------------

#ifndef FingerServFrmH
#define FingerServFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "IdBaseComponent.hpp"
#include "IdComponent.hpp"
#include "IdFingerServer.hpp"
#include "IdTCPServer.hpp"
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
        TIdFingerServer *IdFingerServer1;
        TLabel *Label1;
        void __fastcall IdFingerServer1CommandFinger(
          TIdPeerThread *AThread, const AnsiString AUserName);
        void __fastcall IdFingerServer1CommandVerboseFinger(
          TIdPeerThread *AThread, const AnsiString AUserName);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:	TStringList *listofstrings;	// User declarations
        __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
