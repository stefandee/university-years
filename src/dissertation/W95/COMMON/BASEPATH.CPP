//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "basepath.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

static AnsiString programPath = "";

AnsiString getProgramPath()
{
  return programPath;
}

void initProgramPath()
{
  programPath = GetCurrentDir();
  programPath = programPath + AnsiString("\\");
}

