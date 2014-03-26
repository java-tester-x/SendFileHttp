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
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TShape *Shape1;
        TImage *imgMain;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TButton *btnGetImageList;
        TListBox *lstAvailableImages;
        TButton *btnGetSelectedImage;
        TButton *btnExit;
        TEdit *edtServerHost;
        TButton *btnServerScreenShot;
        TEdit *edtServerPort;
        TIdTCPClient *IdTCPClient;
        void __fastcall btnGetImageListClick(TObject *Sender);
        void __fastcall btnGetSelectedImageClick(TObject *Sender);
        void __fastcall btnExitClick(TObject *Sender);
        void __fastcall btnServerScreenShotClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
        void __fastcall LoadItems(AnsiString s);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
