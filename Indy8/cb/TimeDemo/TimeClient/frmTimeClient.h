//---------------------------------------------------------------------------

#ifndef frmTimeClientH
#define frmTimeClientH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "IdBaseComponent.hpp"
#include "IdComponent.hpp"
#include "IdTCPClient.hpp"
#include "IdTCPConnection.hpp"
#include "IdTime.hpp"
//---------------------------------------------------------------------------
class TTimeClient : public TForm
{
__published:	// IDE-managed Components
        TLabel *lblTimeServer;
        TLabel *Label1;
        TEdit *edtTimeResult;
        TButton *btnGetTime;
        TComboBox *cmboTimeServer;
        TIdTime *IdDemoTime;
        TLabel *Label2;
        TLabel *IndyVersionLabel;
        void __fastcall btnGetTimeClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TTimeClient(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTimeClient *TimeClient;
//---------------------------------------------------------------------------
#endif
