//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("BCB4_MailClient.res");
USEFORM("MainForm.cpp", MainFrm);
USEFORM("MsgEditAdvFrm.cpp", frmMsgEditAdv);
USEFORM("MsgEditorFrm.cpp", frmMsgEditor);
USEFORM("SetupFrm.cpp", frmSetup);
USEFORM("SMTPAuthenticationfrm.cpp", frmSMTPAuthentication);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TMainFrm), &MainFrm);
                 Application->CreateForm(__classid(TfrmMsgEditAdv), &frmMsgEditAdv);
                 Application->CreateForm(__classid(TfrmMsgEditor), &frmMsgEditor);
                 Application->CreateForm(__classid(TfrmSetup), &frmSetup);
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
