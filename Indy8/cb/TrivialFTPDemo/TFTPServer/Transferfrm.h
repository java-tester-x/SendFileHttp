//---------------------------------------------------------------------------
#include "SyncThread.h"
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#ifndef TransferfrmH
#define TransferfrmH
//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TSyncThread;
class TProgressStream;
class TTransferForm : public TForm
{        private:
         AnsiString peerip;
         int peerport;
__published:	// IDE-managed Components
        TProgressBar *prgTransfer;
        TLabel *Label1;
        TLabel *lblByteRate;
        TLabel *Label2;
        TLabel *IPAddressLabel;
        TLabel *Port;
        TLabel *PortLabel;
        void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
public:	TProgressStream * AStream;
        TSyncThread *  syncthread;	// User declarations
//     __fastcall TTransferForm(TComponent* Owner,TProgressStream * AStream);
     __fastcall TTransferForm(TComponent* Owner,TProgressStream * AStream,      AnsiString  peerip,int peer_port,WORD filemode,AnsiString Filename );

};
//---------------------------------------------------------------------------
extern PACKAGE TTransferForm *TransferForm;
//---------------------------------------------------------------------------
#endif
