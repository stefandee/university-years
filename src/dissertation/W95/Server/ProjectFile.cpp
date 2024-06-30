//---------------------------------------------------------------------------
#include <vcl.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <string.h>
#pragma hdrstop

#include "ProjectFile.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall CProject::CProject()
{
  DefaultProject();
}
//---------------------------------------------------------------------------

void       CProject::DefaultProject()
{
  inputsNo         = -1;
  outputsNo        = -1;
  hiddenNo         = -1;
  patternCount     = -1;
  isMomentumTerm   = false;
  learningRate     = 0.01;
  momentumTerm     = 0.3;
  hasBeenTrained   = false;
  functHidden      = act_sigmoid;
  functOutput      = act_sigmoid;
  saveCount        = 100;
  hasBeenTrained   = false;

  fileName         = "";
  projectName      = "New Project";
}
//---------------------------------------------------------------------------

int        CProject::SaveProject()
{
  int handle;
  char name[256];

  AnsiString tempName = projectName;
  tempName.SetLength(256);
  strcpy(name, tempName.c_str());
  strcat(name, "\0");

  if (fileName.IsEmpty()) return -1;

  handle = open(fileName.c_str(), O_CREAT | O_BINARY | O_RDWR, S_IREAD | S_IWRITE);
  if (handle == -1) return -1;

  // scriu headerul
  if (write(handle, name, 256) == -1) return -1;
  if (write(handle, &inputsNo, sizeof(int)) == -1) return -1;
  if (write(handle, &hiddenNo, sizeof(int)) == -1) return -1;
  if (write(handle, &outputsNo, sizeof(int)) == -1) return -1;
  if (write(handle, &hasBeenTrained, sizeof(bool)) == -1) return -1;
  if (write(handle, &isMomentumTerm, sizeof(bool)) == -1) return -1;
  if (write(handle, &momentumTerm, sizeof(float)) == -1) return -1;
  if (write(handle, &learningRate, sizeof(float)) == -1) return -1;
  if (write(handle, &functHidden, sizeof(TActivation)) == -1) return -1;
  if (write(handle, &functOutput, sizeof(TActivation)) == -1) return -1;
  if (write(handle, &saveCount, sizeof(int)) == -1) return -1;

  close(handle);
  return 1;
}
//---------------------------------------------------------------------------

int        CProject::LoadProject()
{
  int handle;
  char name[256];

  if (fileName.IsEmpty()) return -1;

  handle = open(fileName.c_str(), O_BINARY | O_RDWR, S_IREAD | S_IWRITE);
  if (handle == -1) return -1;

  // incarc headerul
  if (read(handle, name, 256) == -1) return -1;
  projectName = AnsiString(name);
  if (read(handle, &inputsNo, sizeof(int)) == -1) return -1;
  if (read(handle, &hiddenNo, sizeof(int)) == -1) return -1;
  if (read(handle, &outputsNo, sizeof(int)) == -1) return -1;
  if (read(handle, &hasBeenTrained, sizeof(bool)) == -1) return -1;
  if (read(handle, &isMomentumTerm, sizeof(bool)) == -1) return -1;
  if (read(handle, &momentumTerm, sizeof(float)) == -1) return -1;
  if (read(handle, &learningRate, sizeof(float)) == -1) return -1;
  if (read(handle, &functHidden, sizeof(TActivation)) == -1) return -1;
  if (read(handle, &functOutput, sizeof(TActivation)) == -1) return -1;
  if (read(handle, &saveCount, sizeof(int)) == -1) return -1;

  close(handle);
  return 1;
}
//---------------------------------------------------------------------------

void       CProject::LoadInputPatternX(int index, float* data)
{
}
//---------------------------------------------------------------------------

void       CProject::LoadTargetPatternX(int index, float* data)
{
}
//---------------------------------------------------------------------------

void       CProject::SaveWeights(float* dataIH, float* dataHO)
{
}
//---------------------------------------------------------------------------

int        CProject::AddPatternSet(float* data)
{
  int handle;

  if ((inputsNo <= 0) ||
     (outputsNo <= 0))
  {
    return -1;
  }

  handle = open(fileName.c_str(), O_RDWR | O_BINARY | O_APPEND);
  if (handle == -1) return -1;

  // scriu datele
  if (write(handle, data, (inputsNo + outputsNo) * sizeof(float)) == -1)
  {
    return -1;
  }

  close(handle);
}
//---------------------------------------------------------------------------

__fastcall CProject::~CProject()
{
}
//---------------------------------------------------------------------------

bool       CProject::DeleteProject()
{
  return DeleteFile(fileName);
}
//---------------------------------------------------------------------------

