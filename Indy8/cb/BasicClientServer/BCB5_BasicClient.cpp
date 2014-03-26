//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("BCB5_BasicClient.res");
USEFORM("frmClient.cpp", FormClient);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TFormClient), &FormClient);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
