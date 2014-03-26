//---------------------------------------------------------------------------

#ifndef frmClientH
#define frmClientH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "IdBaseComponent.hpp"
#include "IdComponent.hpp"
#include "IdTCPClient.hpp"
#include "IdTCPConnection.hpp"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormClient : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TLabel *IndyVersionLabel;
        TLabel *Label1;
        TButton *Button1;
        TListBox *ListBox1;
        TIdTCPClient *TCPClient;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormClient(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormClient *FormClient;
//---------------------------------------------------------------------------
#endif
