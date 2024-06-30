//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdlib.h>
#include <time.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#pragma hdrstop

#include "MainUnit.h"
#include "Defs.h"
#include "Dialog.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  handle   = -1;
  saved    = false;
  fileName = "";
  inputsNo = -1;
  randomize();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Open1Click(TObject *Sender)
{
  char       id[FILE_ID_SIZE];
  AnsiString line;
  float*     inputs;

  if (OpenDialog->Execute())
  {
    if (handle != -1) close(handle);

    fileName = OpenDialog->FileName;
    StatusBar1->SimpleText = "Editing " + ExtractFileName(fileName);
    Memo1->Lines->Clear();

    // citesc fisierul in memo
    handle = open(fileName.c_str(), O_RDWR | O_BINARY);
    if (handle == -1)
    {
      Application->MessageBox("Cannot open file", "Error", MB_OK);
      ResetFile();
      return;
    }

    // citesc identificatorul
    if (read(handle, id, FILE_ID_SIZE) == -1)
    {
      Application->MessageBox("Cannot read file", "Error", MB_OK);
      close(handle);
      handle = -1;
      ResetFile();
      return;
    }

    if (strcmp(id, PTN_FILE_ID) != 0)
    {
      Application->MessageBox("Not a valid .p file", "Error", MB_OK);
      close(handle);
      handle = -1;
      ResetFile();
      return;
    }

    // citesc lungimea
    if (read(handle, &inputsNo, sizeof(int)) == -1)
    {
      Application->MessageBox("Cannot read file", "Error", MB_OK);
      close(handle);
      handle = -1;
      ResetFile();
      return;
    }

    // citesc patternurile
    inputs = new float[inputsNo];

    while(1)
    {
      if (read(handle, inputs, sizeof(float) * inputsNo) <= 0) break;
      line = "Line : ";
      for(int i = 0; i < inputsNo; i++) line = line + " " + AnsiString(inputs[i]);

      if (read(handle, inputs, sizeof(float) * inputsNo) <= 0) break;
      line = line + "  Target : ";
      for(int i = 0; i < inputsNo; i++) line = line + " " + AnsiString(inputs[i]);
      Memo1->Lines->Add(line);
    }

    delete inputs;

    // close(handle);
  }
}
//---------------------------------------------------------------------------

void TForm1::ResetFile()
{
  fileName               = "";
  StatusBar1->SimpleText = "No file";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::New1Click(TObject *Sender)
{
  char       id[FILE_ID_SIZE];

  if (SaveDialog->Execute())
  {
    if (handle != -1) close(handle);
    project.fileName       = SaveDialog->FileName;
    project.projectName    = "New project";
    StatusBar1->SimpleText = fileName;
    Memo1->Lines->Clear();

    // citesc fisierul in memo
    handle = open(fileName.c_str(), O_RDWR | O_BINARY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
    if (handle == -1)
    {
      Application->MessageBox("Cannot open/create file", "Error", MB_OK);
      ResetFile();
      return;
    }

    // scriu identificatorul
    strcpy(id, PTN_FILE_ID);
    if (write(handle, id, FILE_ID_SIZE) == -1)
    {
      Application->MessageBox("Cannot write in file", "Error", MB_OK);
      ResetFile();
      return;
    }

    // citesc numarul de inputs
    formDlg->ShowModal();
    inputsNo = formDlg->CSpinEdit->Value;

    // scriu acest numar
    if (write(handle, &inputsNo, sizeof(int)) == -1)
    {
      Application->MessageBox("Cannot write in file", "Error", MB_OK);
      ResetFile();
      return;
    }

  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
  if (formDlg->ShowModal() == mrOk)
  {
    int dataSize = formDlg->edIn.ToInt() + formDlg->edTarget.ToInt();
    int i;
    float *data = new float[dataSize];

    project.inputsNo  = formDlg->edIn.ToInt();
    project.outputsNo = formDlg->edTarget.ToInt();

    // generez patternul
    for(int i = 0; i < dataSize; i++)
    {
      data[i] = (float)random(1024*1024) / (1024.0*1024.0);
    }


    if (project.AddPatternSet(data) != -1)
    {
      line = "Input : ";
      for(int i = 0; i < project.inputsNo; i++) line = line + " " + AnsiString(data[i]);

      line = line + " Target : ";
      for(int i = project.inputsNo; i < dataSize; i++) line = line + " " + AnsiString(data[i]);
      
      Memo1->Lines->Add(line);
    }
    else
    {
      Application->MessageBox("Cannot add pattern to file", "Error", MB_OK);
    }

    delete data;
  }
}
//---------------------------------------------------------------------------
