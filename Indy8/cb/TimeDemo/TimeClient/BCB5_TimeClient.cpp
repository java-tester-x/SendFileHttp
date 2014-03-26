//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("BCB5_TimeClient.res");
USEFORM("frmTimeClient.cpp", TimeClient);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TTimeClient), &TimeClient);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
