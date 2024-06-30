//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------
USEFORM("Main.cpp", MainForm);
USERES("N2Server.res");
USEFORM("about.cpp", AboutBox);
USEFORM("Console.cpp", formConsole);
USEFORM("MList.cpp", formMList);
USEUNIT("Login.cpp");
USEUNIT("Vm.cpp");
USEUNIT("MManager.cpp");
USEFORM("CfgNet.cpp", formCfgNet);
USEFORM("GfxReport.cpp", formReport);
USEUNIT("..\COMMON\Basepath.cpp");
USEUNIT("ProjectFile.cpp");
USEUNIT("..\COMMON\Defs.cpp");
USEFORM("Partition.cpp", formPartition);
//---------------------------------------------------------------------------
#include "basepath.h"
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        initProgramPath();
	Application->Initialize();
	Application->Title = "N2Server";
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TAboutBox), &AboutBox);
                 Application->CreateForm(__classid(TformCfgNet), &formCfgNet);
                 Application->CreateForm(__classid(TformReport), &formReport);
                 Application->CreateForm(__classid(TformPartition), &formPartition);
                 Application->Run();

	return 0;
}
//---------------------------------------------------------------------
