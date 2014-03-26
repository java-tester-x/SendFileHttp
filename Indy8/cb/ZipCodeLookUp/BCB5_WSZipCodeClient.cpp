//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("BCB5_WSZipCodeClient.res");
USEFORM("WSZipCodeClientUnit.cpp", ClientMain);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Indy Zip Code Client";
                 Application->CreateForm(__classid(TClientMain), &ClientMain);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
