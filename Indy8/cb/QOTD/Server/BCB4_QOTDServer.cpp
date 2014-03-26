//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("BCB4_QOTDServer.res");
USEFORM("frmMain.cpp", MainForm);
USERC("quotes.rc");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
