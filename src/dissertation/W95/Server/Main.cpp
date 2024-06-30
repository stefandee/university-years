//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "About.h"
#include "Console.h"
#include "MList.h"
#include "Login.h"
#include "MManager.h"
#include "CfgNet.h"

//---------------------------------------------------------------------
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------

__fastcall TMainForm::TMainForm(TComponent *Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
  Application->OnHint = ShowHint;
  Screen->OnActiveFormChange = UpdateMenuItems;
}
//---------------------------------------------------------------------

void __fastcall TMainForm::ShowHint(TObject *Sender)
{
  StatusBar->SimpleText = Application->Hint;
}
//---------------------------------------------------------------------

void __fastcall TMainForm::FileExitItemClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------

void __fastcall TMainForm::WindowCascadeItemClick(TObject *Sender)
{
  Cascade();
}
//---------------------------------------------------------------------

void __fastcall TMainForm::WindowTileItemClick(TObject *Sender)
{
  Tile();
}
//---------------------------------------------------------------------

void __fastcall TMainForm::WindowArrangeItemClick(TObject *Sender)
{
  ArrangeIcons();
}
//--------------------------------------------------------------------- 

void __fastcall TMainForm::WindowMinimizeItemClick(TObject *Sender)
{
  int i;

  //---- Must be done backwards through the MDIChildren array ----
  for (i=MDIChildCount-1; i >= 0; i--)
          MDIChildren[i]->WindowState = wsMinimized;
}
//---------------------------------------------------------------------

void __fastcall TMainForm::UpdateMenuItems(TObject *Sender)
{
  WindowCascadeItem->Enabled = MDIChildCount > 0;
  WindowTileItem->Enabled = MDIChildCount > 0;
  WindowArrangeItem->Enabled = MDIChildCount > 0;
  WindowMinimizeItem->Enabled = MDIChildCount > 0;
}
//---------------------------------------------------------------------

void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
  Screen->OnActiveFormChange = NULL;
  //delete formConsole;
  //delete formMList;
  Login->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::HelpAboutItemClick(TObject *Sender)
{
    AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Console1Click(TObject *Sender)
{
  Console1->Checked = !(formConsole->WindowState == wsNormal);

  if (Console1->Checked)
  {
    formConsole->WindowState = wsNormal;
  }
  else
  {
    formConsole->Close();
  }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormShow(TObject *Sender)
{
  formConsole = new TformConsole(Application);
  formMList   = new TformMList(Application);
  Login       = new CLogin(true);
  //Login->RejectConnections();
  MManager    = new CMachineManager(true);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MachineList1Click(TObject *Sender)
{
  MachineList1->Checked = !(formMList->WindowState == wsNormal);

  if (MachineList1->Checked)
  {
    formMList->WindowState = wsNormal;
  }
  else
  {
    formMList->Close();
  }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::sbStartClick(TObject *Sender)
{
  /*
  OpenDialog->FilterIndex = 2;
  if (OpenDialog->Execute())
  {
    MManager->inputFile = OpenDialog->FileName;
    if (!MManager->Start())
    {
      Application->MessageBox("Something is not prepared...cannot start", "Error", MB_OK);
    }
    else
    {
      MManager->Start();
    }
  }
  */
  // salvez proiectul intii
  if (MManager->project.fileName.IsEmpty())
  {
    // prima salvare - am nevoie de numele fisierului
    if (SaveDialog->Execute())
    {
      MManager->project.fileName = SaveDialog->FileName;
    }
    else
    {
      // daca se da cancel, atunci nu se poate porni
      Application->MessageBox("You must supply a file name.", "Error", MB_OK);
      return;
    }
  }

  if (MManager->project.SaveProject() == -1)
  {
    Application->MessageBox("Cannot save", "Error", MB_OK);
    return;
  }

  Saveproject1->Enabled = false;

  if (!MManager->Start())
  {
    Application->MessageBox("Something is not prepared...cannot start", "Error", MB_OK);
  }
  else
  {
    // si pornesc masinaria infernala
    MManager->Start();
    sbStart->Enabled = false;
    sbStop->Enabled  = true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Projectoptions1Click(TObject *Sender)
{
  formCfgNet->ProjectToScreen();

  if (formCfgNet->ShowModal() == mrOk)
  {
    // anunt userul ca skimbind configuratia, fisierul proiect va fi sters daca
    // reteaua a fost deja antrenata
    if (MManager->project.hasBeenTrained)
    {
      if (Application->MessageBox("The net is already trained. Reconfiguration will erase the weights. Continue ?", "Warning", MB_YESNO) == ID_NO) return;
      // sterg vechiul fisier
      if (!MManager->project.DeleteProject())
      {
        Application->MessageBox("Cannot delete project", "Error", MB_OK);
        return;
      }
      MManager->project.hasBeenTrained = false;
    }

    MManager->project.projectName = formCfgNet->edName->Text;
    Application->Title            = MManager->project.projectName + " - N2Server";
    MainForm->Caption             = MManager->project.projectName + " - N2Server";

    MManager->project.inputsNo  = formCfgNet->edIn->Text.ToInt();
    MManager->project.hiddenNo  = formCfgNet->edHidden->Text.ToInt();
    MManager->project.outputsNo = formCfgNet->edOut->Text.ToInt();

    MManager->project.saveCount = formCfgNet->edSave->Text.ToInt();

    MManager->project.isMomentumTerm = formCfgNet->cbMomentum->Checked;

    MManager->project.learningRate = formCfgNet->edLR->Text.ToDouble();
    MManager->project.momentumTerm = formCfgNet->edMT->Text.ToDouble();

    MManager->project.functHidden = (TActivation)formCfgNet->cbHiddenAct->ItemIndex;
    MManager->project.functOutput = (TActivation)formCfgNet->cbOutputAct->ItemIndex;

    MManager->ConfigureNet();
    if (!MManager->MemoryIsReady()) formConsole->AddMessage("Memory allocation error");
    else formConsole->AddMessage("Neural net configured succesfully");

    Saveproject1->Enabled    = true;
    Saveprojectas1->Enabled  = true;
    Projectoptions1->Enabled = true;
    Closeproject1->Enabled   = true;
    sbStart->Enabled         = true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Newproject1Click(TObject *Sender)
{
  MManager->project.DefaultProject();
  formCfgNet->ProjectToScreen();

  if (formCfgNet->ShowModal() == mrOk)
  {
    MManager->project.projectName = formCfgNet->edName->Text;
    Application->Title            = MManager->project.projectName + " - N2Server";
    MainForm->Caption             = MManager->project.projectName + " - N2Server";

    MManager->project.inputsNo  = formCfgNet->edIn->Text.ToInt();
    MManager->project.hiddenNo  = formCfgNet->edHidden->Text.ToInt();
    MManager->project.outputsNo = formCfgNet->edOut->Text.ToInt();

    MManager->project.saveCount = formCfgNet->edSave->Text.ToInt();

    MManager->project.isMomentumTerm = formCfgNet->cbMomentum->Checked;

    MManager->project.learningRate = formCfgNet->edLR->Text.ToDouble();
    MManager->project.momentumTerm = formCfgNet->edMT->Text.ToDouble();

    MManager->project.functHidden = (TActivation)formCfgNet->cbHiddenAct->ItemIndex;
    MManager->project.functOutput = (TActivation)formCfgNet->cbOutputAct->ItemIndex;

    MManager->ConfigureNet();
    if (!MManager->MemoryIsReady()) formConsole->AddMessage("Memory allocation error");
    else formConsole->AddMessage("Neural net configured succesfully");

    MManager->Resume();
    Login->AcceptConnections();
    Login->Resume();

    Saveproject1->Enabled    = true;
    Saveprojectas1->Enabled  = true;
    Projectoptions1->Enabled = true;
    Closeproject1->Enabled   = true;
    Newproject1->Enabled     = false;
    sbStart->Enabled         = true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Closeproject1Click(TObject *Sender)
{
  Login->RejectConnections();
  Login->Suspend();
  for(int i = 0; i < MManager->GetMachineNo(); i++)
    if (MManager->ValidMachine(i)) MManager->KillMachine(i);
  MManager->Suspend();

  // salvez proiectul
  if (MManager->project.fileName.IsEmpty() || Saveproject1->Enabled)
  {
    if (Application->MessageBox("Project was modified. Do you want to save the project ?", "Decision", MB_YESNO) == ID_YES)
    {
      Saveproject1Click(this);
    }
  }

  Saveproject1->Enabled    = false;
  Saveprojectas1->Enabled  = false;
  Projectoptions1->Enabled = false;
  Closeproject1->Enabled   = false;
  Newproject1->Enabled     = true;
  sbStart->Enabled         = false;
  sbStop->Enabled          = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::sbStopClick(TObject *Sender)
{
  sbStart->Enabled = true;
  sbStop->Enabled  = false;
  MManager->Terminate();
  MManager->WaitFor();
  Login->Resume();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Saveproject1Click(TObject *Sender)
{
  if (MManager->project.fileName.IsEmpty())
  {
    // prima salvare - am nevoie de numele fisierului
    if (SaveDialog->Execute())
    {
      MManager->project.fileName = SaveDialog->FileName;
    }
    else return;
  }

  // salvarea efectiva
  if (MManager->project.SaveProject() == -1)
  {
    Application->MessageBox("Cannot save", "Error", MB_OK);
    return;
  }

  Saveproject1->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Saveprojectas1Click(TObject *Sender)
{
  if (SaveDialog->Execute())
  {
    MManager->project.fileName = SaveDialog->FileName;
  }
  else return;

  // salvarea
  if (MManager->project.SaveProject() == -1)
  {
    Application->MessageBox("Cannot save", "Error", MB_OK);
    return;
  }

  Saveproject1->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Openproject1Click(TObject *Sender)
{
  if (OpenDialog->Execute())
  {
    MManager->project.fileName = OpenDialog->FileName;
    if (MManager->project.LoadProject() == -1)
    {
      Application->MessageBox("Cannot save", "Error", MB_OK);
      return;
    }

    Application->Title            = MManager->project.projectName + " - N2Server";
    MainForm->Caption             = MManager->project.projectName + " - N2Server";

    MManager->ConfigureNet();
    if (!MManager->MemoryIsReady()) formConsole->AddMessage("Memory allocation error");
    else formConsole->AddMessage("Neural net configured succesfully");

    MManager->Resume();
    Login->AcceptConnections();
    Login->Resume();

    Saveproject1->Enabled    = false;
    Saveprojectas1->Enabled  = true;
    Closeproject1->Enabled   = true;
    Newproject1->Enabled     = false;
    Projectoptions1->Enabled = true;
    sbStart->Enabled         = true;
    sbStop->Enabled          = false;
  }
}
//---------------------------------------------------------------------------

