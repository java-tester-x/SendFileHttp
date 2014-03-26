//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("BCB4_WSZipCodeServer.res");
USEFORM("WSZipCodeServerUnit.cpp", ServerMain);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TServerMain), &ServerMain);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
