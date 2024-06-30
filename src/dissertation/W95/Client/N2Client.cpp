//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------
USEFORM("Main.cpp", MainForm);
USERES("N2Client.res");
USEFORM("about.cpp", AboutBox);
USEUNIT("RemoteMachine.cpp");
USEFORM("Console.cpp", formConsole);
USEFORM("Servers.cpp", formServers);
USEUNIT("..\COMMON\Basepath.cpp");
USEUNIT("..\COMMON\Defs.cpp");
//---------------------------------------------------------------------------
#include "basepath.h"
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        initProgramPath();
	Application->Initialize();
	Application->Title = "N2 Client";
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TAboutBox), &AboutBox);
                 Application->CreateForm(__classid(TformConsole), &formConsole);
                 Application->CreateForm(__classid(TformServers), &formServers);
                 Application->Run();

	return 0;
}
//---------------------------------------------------------------------
