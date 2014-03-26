//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SyncThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall Unit1::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TSyncThread::TSyncThread(bool CreateSuspended,AnsiString peerip,int peerport,TTransferForm * parent,DWORD StartTime)
        : TThread(CreateSuspended)
{
ParentForm=parent;

starttime=StartTime;


}
//---------------------------------------------------------------------------
void __fastcall TSyncThread::Execute()
{
DWORD bytespersecond=0;

DWORD elaspedmilliseconds=::GetTickCount() - starttime;
DWORD elaspedseconds=(elaspedmilliseconds/1000);
if (elaspedseconds)
bytespersecond=(fileprogress/elaspedseconds);
speed=bytespersecond;
Synchronize(UpdateVCL);
Suspend();




}
//---------------------------------------------------------------------------


void __fastcall TSyncThread::UpdateVCL()
{
ParentForm->prgTransfer->Position =fileprogress;
ParentForm->lblByteRate->Caption=AnsiString(speed);
ParentForm->Update();
}