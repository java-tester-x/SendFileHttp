//---------------------------------------------------------------------------

#ifndef MsgEditorFrmH
#define MsgEditorFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "IdBaseComponent.hpp"
#include "IdComponent.hpp"
#include "IdMessage.hpp"
#include "IdMessageClient.hpp"
#include "IdSMTP.hpp"
#include "IdTCPClient.hpp"
#include "IdTCPConnection.hpp"

#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmMsgEditor : public TForm
{
__published:	// IDE-managed Components
        TStatusBar *StatusBar1;
        TPanel *pnlBottom;
        TMemo *Memo1;
        TPanel *pnlButtons;
        TBitBtn *bbtnAdvanced;
        TPanel *pnlSmallButtons;
        TBitBtn *bbtnCancel;
        TBitBtn *bbtnOk;
        TPanel *pnlTop;
        TPanel *pnlTopLeft;
        TLabel *lblCC;
        TLabel *lblBCC;
        TLabel *lblPriority;
        TEdit *edtCC;
        TEdit *edtBCC;
        TComboBox *cboPriority;
        TCheckBox *chkReturnReciept;
        TPanel *pnlMainDetails;
        TLabel *lblTo;
        TLabel *lblSubject;
        TEdit *edtTo;
        TEdit *edtSubject;
        TGroupBox *grpAttachment;
        TListView *lvFiles;
        TBitBtn *btnAttachment;
        TBitBtn *btnText;
        TEdit *Edit1;
        TIdMessage *IdMsgSend;
        TIdSMTP *SMTP;
        TOpenDialog *OpenDialog1;
        void __fastcall bbtnAdvancedClick(TObject *Sender);
        void __fastcall bbtnOkClick(TObject *Sender);
        void __fastcall btnTextClick(TObject *Sender);
        void __fastcall btnAttachmentClick(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmMsgEditor(TComponent* Owner);
        void __fastcall ResetAttachmentListView();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMsgEditor *frmMsgEditor;
//---------------------------------------------------------------------------
#endif
