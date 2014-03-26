//---------------------------------------------------------------------------

#ifndef SyncThreadH
#define SyncThreadH
//---------------------------------------------------------------------------
#include "Transferfrm.h"
#include <Classes.hpp>
//---------------------------------------------------------------------------
class TSyncThread : public TThread
{
private:
TTransferForm* ParentForm;
AnsiString PeerIp;
AnsiString PeerPort;
DWORD speed;
DWORD starttime;
protected:

public:
int fileprogress;
        void __fastcall Execute();
        __fastcall TSyncThread(bool CreateSuspended,AnsiString peername,int peerport,TTransferForm* transferformptr,DWORD starttime);
        void __fastcall UpdateVCL();
};
//---------------------------------------------------------------------------
#endif
