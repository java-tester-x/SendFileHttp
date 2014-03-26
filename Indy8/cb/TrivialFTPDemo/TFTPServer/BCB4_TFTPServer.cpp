//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("BCB4_TFTPServer.res");
USEFORM("frmTFTPServer.cpp", frmMain);
USEUNIT("SyncThread.cpp");
USEFORM("Transferfrm.cpp", TransferForm);
USELIB("..\..\Program Files\Borland\CBuilder4\Lib\Release\vclx40.lib");
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
