//---------------------------------------------------------------------------

#ifndef WSZipCodeServerUnitH
#define WSZipCodeServerUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "IdBaseComponent.hpp"
#include "IdComponent.hpp"
#include "IdTCPServer.hpp"
//---------------------------------------------------------------------------
class TServerMain : public TForm
{
__published:	// IDE-managed Components
        TIdTCPServer *IdTCPServer1;
        TLabel *IndyVersionLabel;
        TLabel *Label2;
        void __fastcall IdTCPServer1Connect(TIdPeerThread *AThread);
        void __fastcall IdTCPServer1Execute(TIdPeerThread *AThread);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations

   TStrings* ZipCodeList;

public:		// User declarations
        __fastcall TServerMain(TComponent* Owner);
        __fastcall ~TServerMain();
};
//---------------------------------------------------------------------------
extern PACKAGE TServerMain *ServerMain;
//---------------------------------------------------------------------------
#endif
