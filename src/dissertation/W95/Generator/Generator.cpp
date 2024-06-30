//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("Generator.res");
USEFORM("MainUnit.cpp", Form1);
USEFORM("Dialog.cpp", formDlg);
USEUNIT("..\COMMON\Defs.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->CreateForm(__classid(TformDlg), &formDlg);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
