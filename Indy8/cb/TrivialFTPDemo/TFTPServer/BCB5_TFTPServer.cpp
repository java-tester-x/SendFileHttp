//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("BCB5_TFTPServer.res");
USEFORM("frmTFTPServer.cpp", frmMain);
USEFORM("Transferfrm.cpp", TransferForm);
USELIB("..\Lib\Release\vclx50.lib");
USEUNIT("SyncThread.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TfrmMain), &frmMain);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
