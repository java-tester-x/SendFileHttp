//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("BCB5_MailClient.res");
USEFORM("MainForm.cpp", MainFrm);
USEFORM("SetupFrm.cpp", frmSetup);
USEFORM("MsgEditorFrm.cpp", frmMsgEditor);
USEFORM("MsgEditAdvFrm.cpp", frmMsgEditAdv);
USEFORM("SMTPAuthenticationfrm.cpp", frmSMTPAuthentication);
USELIB("C:\Program Files\Borland\CBuilder5\Lib\Debug\vclx50.lib");
USEUNIT("C:\Indy\source\IdPOP3.pas");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TMainFrm), &MainFrm);
                 Application->CreateForm(__classid(TfrmSetup), &frmSetup);
                 Application->CreateForm(__classid(TfrmMsgEditor), &frmMsgEditor);
                 Application->CreateForm(__classid(TfrmMsgEditAdv), &frmMsgEditAdv);
                 Application->CreateForm(__classid(TfrmSMTPAuthentication), &frmSMTPAuthentication);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
