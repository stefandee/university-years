//---------------------------------------------------------------------------
#include <vcl.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <stdlib.h>
#pragma hdrstop

#include "MManager.h"
#include "Console.h"
#include "Login.h"
#include "GfxReport.h"
#include "MList.h"
#include "Main.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

CMachineManager* MManager;

void CMachineManager::AddMachine(CMachine* machine)
{
  machines[index++] = machine;
}
//---------------------------------------------------------------------------

int CMachineManager::GetMachineNo()
{
  return index;
}
//---------------------------------------------------------------------------

__fastcall CMachineManager::CMachineManager(bool CreateSuspended)
        : TThread(CreateSuspended)
{
  FreeOnTerminate = true;
  SetThreadPriority((void*)Handle, THREAD_PRIORITY_BELOW_NORMAL);
  index = 0;
  
  //ihWeights = NULL;
  //hoWeights = NULL;
  inputs    = NULL;
  hidden    = NULL;
  outputs   = NULL;
  target    = NULL;

  readyToStart = false;
  readyMem     = false;
  readyLoad    = false;
  computationInProgress = false;

  for(int i = 0; i < MAX_CONNECTIONS_ALLOWED; i++)
  {
    partition[i][0] = -1;
    partition[i][1] = -1;
    partition[i][2] = -1;
  }

  randomize();
}
//---------------------------------------------------------------------------

__fastcall CMachineManager::~CMachineManager()
{
}
//---------------------------------------------------------------------------

AnsiString CMachineManager::GetMachineIP(int what)
{
  if (what < index) return machines[what]->GetIP();
  else return AnsiString(" ");
}
//---------------------------------------------------------------------------

void CMachineManager::KillMachine(int what)
{
  if (what < index) machines[what]->Terminate();
}
//---------------------------------------------------------------------------

AnsiString CMachineManager::GetMachinePing(int what)
{
  if (what < index) return machines[what]->GetPingTime();
  else return AnsiString("n/a");
}
//---------------------------------------------------------------------------

AnsiString CMachineManager::GetMachineName(int what)
{
  if (what < index) return machines[what]->GetMachineName();
  else return AnsiString("n/a");
}
//---------------------------------------------------------------------------

AnsiString CMachineManager::GetProcessorName(int what)
{
  if (what < index) return machines[what]->GetProcessorName();
  else return AnsiString("n/a");
}
//---------------------------------------------------------------------------

AnsiString CMachineManager::GetMachineSpeed(int what)
{
  if (what < index) return machines[what]->GetMachineSpeed();
  else return AnsiString("n/a");
}
//---------------------------------------------------------------------------

AnsiString CMachineManager::GetMemoryInfo(int what)
{
  if (what < index) return machines[what]->GetMemoryInfo();
  else return AnsiString("n/a");
}
//---------------------------------------------------------------------------

AnsiString CMachineManager::GetMachineOs(int what)
{
  if (what < index) return machines[what]->GetMachineOs() + machines[what]->GetOsVersion();
  else return AnsiString("n/a");
}
//---------------------------------------------------------------------------

AnsiString CMachineManager::GetMachineUser(int what)
{
  if (what < index) return machines[what]->GetUser();
  else return AnsiString("n/a");
}
//---------------------------------------------------------------------------

void CMachineManager::DeleteMachine(int what)
{
  if (what < index)
  {
    delete machines[what];
    machines[what] = machines[index - 1];
    if (index > 0) index--;
  }
}
//---------------------------------------------------------------------------

bool CMachineManager::ValidMachine(int what)
{
  if (what < index)
    if (machines[what]->hasFinished())
  {
    DeleteMachine(what);
    return false;
  }

  return true;
}
//---------------------------------------------------------------------------

void CMachineManager::ConfigureNet()
{
  //project.inputsNo  = iNo;
  //project.hiddenNo  = hNo;
  //project.outputsNo = oNo;

  if (inputs    != NULL) delete inputs;
  if (outputs   != NULL) delete outputs;
  if (target    != NULL) delete target;
  if (hidden    != NULL) delete hidden;
  if (packages  != NULL) delete packages;
  /*
  if (ihWeights != NULL) delete ihWeights;
  if (hoWeights != NULL) delete hoWeights;
  */

  if ((project.inputsNo  <= 0) ||
     (project.hiddenNo  <= 0) ||
     (project.outputsNo <= 0))
  {
    formConsole->AddMessage("Invalid values for units numbers (<=0)");
    return;
  }

  try
  {
    inputs    = new float[project.inputsNo];
    hidden    = new float[project.hiddenNo];
    outputs   = new float[project.outputsNo];
    target    = new float[project.outputsNo];
    packages  = new float[project.hiddenNo * MAX_CONNECTIONS_ALLOWED];
    /*
    ihWeights = new float[project.inputsNo * project.hiddenNo];
    hoWeights = new float[project.hiddenNo * project.outputsNo];
    */
  }
  catch(...)
  {
    formConsole->AddMessage("Cannot alloc memory");
    project.inputsNo  = 0;
    project.hiddenNo  = 0;
    project.outputsNo = 0;
    return;
  }


  // for(int i = 0; i < project.inputsNo; i++)  inputs [i] = 0.5;
  // for(int i = 0; i < project.hiddenNo; i++)  hidden [i] = 0.5;
  // for(int i = 0; i < project.outputsNo; i++) outputs[i] = 0.5;

  // initializez weighturile cu 0.5
  /*
  for(int i = 0; i < project.hiddenNo; i++)
  {
    for(int j = 0; j < project.inputsNo; j++)
      ihWeights[i + j*project.hiddenNo] = 0.5;
    for(int j = 0; j < project.outputsNo; j++)
      hoWeights[i + j*project.hiddenNo] = 0.5;
  }
  */
}
//---------------------------------------------------------------------------

bool CMachineManager::MemoryIsReady()
{
  if (project.inputsNo  <= 0) readyMem = false;
  if (project.outputsNo <= 0) readyMem = false;
  if (project.hiddenNo  <= 0) readyMem = false;

  if ((inputs    != NULL) &&
      (outputs   != NULL) &&
      (target    != NULL) &&
      (hidden    != NULL) &&
      (packages  != NULL) /*&&
      (ihWeights != NULL) &&
      (hoWeights != NULL) */
     ) readyMem = true;
  else readyMem = false;

  return readyMem;
}
//---------------------------------------------------------------------------

bool CMachineManager::LoadNet(AnsiString inFile)
{
  /*
  int   handle;
  float tempI, tempH, tempO;
  char  id[32];

  readyLoad = false;
  handle = open(inFile.c_str(), O_CREAT | O_TRUNC | O_BINARY | O_RDWR, S_IREAD | S_IWRITE);
  if (handle == -1) return false;

  // incarc identificatorul
  if (read(handle, id, 32) == -1) return false;
  if (strcmp(id, NET_FILE_ID) != 0) return false;

  if (read(handle, &tempI, sizeof(float)) == -1) return false;
  if (read(handle, &tempH, sizeof(float)) == -1) return false;
  if (read(handle, &tempO, sizeof(float)) == -1) return false;

  ConfigureNet(tempI, tempH, tempO);
  if (!MemoryIsReady()) return false;

  // memoria e alocata, incarc in memorie
  if (read(handle, hidden, sizeof(float) * project.inputsNo) == -1) return false;
  if (read(handle, outputs, sizeof(float) * project.outputsNo) == -1) return false;
  if (read(handle, ihWeights, sizeof(float) * project.hiddenNo * project.inputsNo) == -1) return false;
  if (read(handle, hoWeights, sizeof(float) * project.hiddenNo * project.outputsNo) == -1) return false;

  close(handle);

  readyLoad = true;
  return true;
  */
  return false;
}
//---------------------------------------------------------------------------

bool CMachineManager::SaveNet(AnsiString outFile)
{
  return false;
}
//---------------------------------------------------------------------------

void CMachineManager::AutoConfigure()
{
}
//---------------------------------------------------------------------------

bool CMachineManager::LoadedIsReady()
{
  return readyLoad;
}
//---------------------------------------------------------------------------

bool CMachineManager::PartIsReady()
{
  readyPart = false;

  if (index <=0)
  {
    readyPart = false;
    return false;
  }

  for(int i = 0; i < index; i++)
  {
    if (partition[i][0] <= 0) return false;
    if (partition[i][1] <= 0) return false;
    if (partition[i][2] <= 0) return false;
  }

  readyPart = true;
  return true;
}
//---------------------------------------------------------------------------

bool CMachineManager::ReadyToStart()
{
  readyToStart = (MemoryIsReady() && PartIsReady() && !computationInProgress);
  if (readyPart) formConsole->AddMessage("Partition is ready");
  if (readyMem) formConsole->AddMessage("Memory is ready");
  if (!computationInProgress) formConsole->AddMessage("No computation task running");

  return readyToStart;
}
//---------------------------------------------------------------------------

void CMachineManager::ConfigureRemoteMachine(int what, int iNo, int hNo, int oNo)
{
  int iMin, iMax, oMin, oMax, hMin, hMax;

  if ((what >= 0) && (what < index))
  {
    partition[what][0] = iNo;
    partition[what][1] = hNo;
    partition[what][2] = oNo;
    // apel la vm - calculez mai intii min, max pentru i, h, o - parcurg inputP, hiddenP, outputP
    iMin = 0;
    for(int i = 0; i < what; i++)
    {
      iMin += partition[i][0];
    }
    iMax = iMin + iNo;

    hMin = 0;
    for(int i = 0; i < what; i++)
    {
      hMin += partition[i][1];
    }
    hMax = hMin + hNo;

    oMin = 0;
    for(int i = 0; i < what; i++)
    {
      oMin += partition[i][2];
    }
    oMax = oMin + oNo;

    if (ValidMachine(what)) machines[what]->SendConfiguration(iMin, iMax, hMin, hMax, oMin, oMax, project.inputsNo, project.hiddenNo, project.outputsNo, project.learningRate, project.isMomentumTerm, project.momentumTerm, project.saveCount, project.hasBeenTrained);
  }
}
//---------------------------------------------------------------------------

/*
int  CMachineManager::GetInputsNo()
{
  return project.inputsNo;
}
//---------------------------------------------------------------------------

int  CMachineManager::GetHiddenNo()
{
  return project.hiddenNo;
}
//---------------------------------------------------------------------------

int  CMachineManager::GetOutputsNo()
{
  return project.outputsNo;
}
//---------------------------------------------------------------------------

*/

void CMachineManager::GetRemoteMachineCfg(int what, int *iNo, int *hNo, int *oNo)
{
  *iNo = partition[what][0];
  *hNo = partition[what][1];
  *oNo = partition[what][2];
}
//---------------------------------------------------------------------------

bool CMachineManager::Start()
{
  if (ReadyToStart())
  {
    start = true;
  }
  else start = false;

  return start;
}
//---------------------------------------------------------------------------

void CMachineManager::Stop()
{
  start = false;
}
//---------------------------------------------------------------------------

void __fastcall CMachineManager::Execute()
{
  int        startHidden, startOutput, startTarget, i, j, place, startPartition;
  bool       stop;
  AnsiString line;
  float*     packagesSend[MAX_CONNECTIONS_ALLOWED];
  float      error;

  while(!Terminated)
  {
    // terminate if there's no response
    if (start)
    {
      // no more machines will connect
      Login->Suspend();
      formMList->StringGrid->PopupMenu = NULL;
      // nu se mai poate face dbl-click pe grid
      formMList->StringGrid->OnDblClick = NULL;
      start                 = false;
      computationInProgress = true;
      for(i = 0; i < index; i++) machines[i]->SendCommand(CMD_START);
      stop                  = false;
      patternsPresented     = 0;
      formReport->SetStyle(ts_interpolate);
      randomize();

      // trimit ponderile initiale, daca exista...
      if (project.hasBeenTrained)
      {
        formConsole->AddMessage("Sending weights to clients...");
        SendWeights();
      }

      while(!Terminated)
      {
        patternsPresented++;
        formConsole->AddMessage("Processing pattern " + AnsiString(patternsPresented) + " - " + AnsiString(project.saveCount));
        if (patternsPresented > project.saveCount)
        {
          // primesc ponderile de la clienti...
          formConsole->AddMessage("Getting weights from clients...");
          GetWeights();

          if (!project.hasBeenTrained)
          {
            project.hasBeenTrained = true;
            project.SaveProject();
          }

          // ... si reiau numaratoarea
          patternsPresented = 0;
        }
        
        // generez aleator patternul - aici ar trebui sa fie citirea din fisier
        formConsole->AddMessage("Generating input & target pattern");
        for(i = 0; i < project.inputsNo; i++) inputs[i] = (float)random(1000000) / 1000000.0;
        for(i = 0; i < project.outputsNo; i++) target[i] = inputs[i] * inputs[i];

        line = "Input : ";
        for(i = 0; i < project.inputsNo; i++) line = line + " " + AnsiString::FormatFloat("0.00", inputs[i]);
        formConsole->AddMessage(line);

        formConsole->AddMessage("Sending input pattern to all");
        stop = false;
        for(i = 0; i < index; i++)
        {
          if (ValidMachine(i))
          {
            machines[i]->SetData(inputs, project.inputsNo);
            machines[i]->GoSending();
          }
          else
          {
            stop = true;
            break;
          }
        }
        if (stop) break;

        // astept ca masinile sa primeasca inputurile
        for(i = 0; i < index; i++)
        {
          while(machines[i]->GetSendStatus())
          {
          }
        }

        // trimit target pattern la all
        formConsole->AddMessage("Sending target pattern");
        stop = false;
        startTarget = 0;
        for(i = 0; i < index; i++)
        {
          if (ValidMachine(i))
          {
            machines[i]->SetData(target + startTarget, partition[i][2]);
            machines[i]->GoSending();
          }
          else
          {
            stop = true;
            break;
          }
          startTarget += partition[i][2];
        }
        if (stop) break;

        // astept ca masinile sa primeasca targeturile
        for(i = 0; i < index; i++)
        {
          while(machines[i]->GetSendStatus())
          {
          }
        }

        // astept sa primesc activitatile hidden
        // astept masinile sa calculeze activitatile hidden si astept terminarea
        // lor
        startHidden = 0;
        stop = false;
        formConsole->AddMessage("Waiting hidden activities");
        for(i = 0; i < index; i++)
        {
          if (ValidMachine(i))
          {
            machines[i]->SetData(hidden + startHidden, partition[i][1]);
            machines[i]->GoReceiving();
          }
          else
          {
            stop = true;
            break;
          }
          startHidden += partition[i][1];
        }
        if (stop) break;

        // astept sa primesc activitatile hidden
        for(i = 0; i < index; i++)
        {
          while(machines[i]->GetRecvStatus())
          {
          }
        }

        // afisez hidden units activities
        line = "Hidden : ";
        for(i = 0; i < project.hiddenNo; i++) line = line + " " + AnsiString::FormatFloat("0.00", hidden[i]);
        formConsole->AddMessage(line);

        // broadcast de hidden unit la toate masinile
        stop = false;
        formConsole->AddMessage("Sending hidden to all");
        for(i = 0; i < index; i++)
        {
          if (ValidMachine(i))
          {
            machines[i]->SetData(hidden, project.hiddenNo);
            machines[i]->GoSending();
          }
          else
          {
            stop = true;
            break;
          }
        }
        if (stop) break;

        // astept ca masinile sa primeasca hiddenurile
        for(i = 0; i < index; i++)
        {
          while(machines[i]->GetSendStatus())
          {
          }
        }

        // astept masinile sa calculeze activitatile output si astept terminarea
        // lor
        formConsole->AddMessage("Waiting output activities");
        stop = false;
        startOutput = 0;
        for(i = 0; i < index; i++)
        {
          if (ValidMachine(i))
          {
            machines[i]->SetData(outputs + startOutput, partition[i][2]);
            machines[i]->GoReceiving();
          }
          else
          {
            stop = true;
            break;
          }
          startOutput += partition[i][2];
        }
        if (stop) break;

        // astept sa primesc activitatile output
        for(i = 0; i < index; i++)
        {
          while(machines[i]->GetRecvStatus())
          {
          }
        }

        // vad ce s'a calculat
        line = "Output received : ";
        for(i = 0; i < project.outputsNo; i++) line = line + " " + AnsiString::FormatFloat("0.00", outputs[i]);
        formConsole->AddMessage(line);

        // package comm
        stop = false;
        startPartition = 0;
        startHidden = 0;
        formConsole->AddMessage("Receiving packages");
        for(i = 0; i < index; i++)
        {
          if (ValidMachine(i))
          {
            machines[i]->SetData(packages + project.hiddenNo * i, project.hiddenNo);
            machines[i]->GoReceiving();
          }
          else
          {
            stop = true;
            break;
          }
        }
        if (stop) break;

        // astept sa primesc packageurile
        for(i = 0; i < index; i++)
        {
          while(machines[i]->GetRecvStatus())
          {
          }
        }

        // partea nashpa a problemei - trimit packageurile cui trebuie

        // aranjez memoria intii
        stop = false;
        startHidden = 0;
        formConsole->AddMessage("Sending packages");
        for(i = 0; i < index; i++)
        {
          try
          {
            packagesSend[i] = new float[partition[i][1] * (index - 1)];
          }
          catch(...)
          {
            formConsole->AddMessage("Cannot alloc dynamic memory for packagesSend");
            stop = true;
            break;
          }

          place = 0;
          for(j = 0; j < index; j++)
          {
            if (j != i)
            {
              // warning
              memcpy(packagesSend[i] + place, packages + j * project.hiddenNo + startHidden, partition[i][1] * sizeof(float));
              place += partition[i][1];
            }
          }

          if (ValidMachine(i))
          {
            machines[i]->SetData(packagesSend[i], partition[i][1] * (index - 1));
            machines[i]->GoSending();
          }
          else
          {
            stop = true;
            break;
          }

          startHidden += partition[i][1];
          startPartition += partition[i][1] * (index - 1);
        }
        if (stop) break;

        // astept ca masinile sa primeasca package'urile
        for(i = 0; i < index; i++)
        {
          while(machines[i]->GetSendStatus())
          {
          }
        }

        // de'alloc memoria
        for(i = 0; i < index; i++)
        {
          delete packagesSend[i];
        }

        // compar rezultatele, afisez in grafic - pina cind masinile termina de
        // calculat si update'uit delta si weights
        error = 0.0;
        for(i = 0; i < project.outputsNo; i++)
        {
          error += (target[i] - outputs[i]) * (target[i] - outputs[i]);
        }
        //error = error / 2.0;

        if (error > 1.0) error = 1.0;
        
        formReport->AddValue(100.0 * (1.0 - error));
        Synchronize(UpdateReport);


        formConsole->AddMessage("Waiting...");
        Sleep(3000);
      }

      // resume connecting
      if (stop) formConsole->AddMessage("Some trancemission error occured");
      else formConsole->AddMessage("Okie dokie");

      Login->Resume();
      formMList->StringGrid->OnDblClick = formMList->StringGridDblClick;
      formMList->StringGrid->PopupMenu  = formMList->PopupMenu;
      MainForm->sbStart->Enabled = true;
      MainForm->sbStop->Enabled  = false;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall CMachineManager::UpdateReport()
{
  formReport->PaintTabel();
}
//---------------------------------------------------------------------------

// Descriere   : asteapta ponderile de la clienti
// Param       : n/a
// Rezultat    :
// Comentarii  : foloseste file mapping pentru a nu mai aloca memorie
//               suplimentara - memoria necesara ponderilor e foarte
//               mare; in plus, primirea ponderilor se face in paralel,
//               dupa cum se va vedea
void __fastcall CMachineManager::GetWeights()
{
  HANDLE handle;

  handle = CreateFile( project.fileName.c_str(),
             GENERIC_READ | GENERIC_WRITE,          // tipul de acces
             0,                                     // sharing mode
             NULL,                                  // security attrib
             OPEN_EXISTING,
             FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS,
             NULL                                   // template file; n/a pt. W95
             );

  if (handle == NULL)
  {
    formConsole->AddMessage("Could not open project file");
    return;
  }

  // vad ce dimeniune are si lungesc fisierul daca trebuie; ar trebuie verificate si erorile (v. helpul)
  if (GetFileSize(handle, NULL) <= 284)
  {
    // expandez fisierul
    SetFilePointer(handle, (project.inputsNo + project.outputsNo) * project.hiddenNo * sizeof(float), NULL, FILE_END);
    SetEndOfFile(handle);
    FlushFileBuffers(handle);
  }

  // ce urmeaza e copy&paste din help
  HANDLE hMapFile;

  hMapFile = CreateFileMapping(handle,    // Current file handle.
      NULL,                               // Default security.
      PAGE_READWRITE,                     // Read/write permission.
      0,                                  // Max. object size.
      0,                                  // Size of hFile.
      "Receiver");                   // Name of mapping object.

  if (hMapFile == NULL)
  {
    int error = GetLastError();
    formConsole->AddMessage("Could not create file-mapping object." + AnsiString(error));
    return;
  }

  LPVOID lpMapAddress, ptrWork;
  lpMapAddress = MapViewOfFile(hMapFile, // Handle to mapping object.
      FILE_MAP_ALL_ACCESS,               // Read/write permission
      0,                                 // Max. object size.
      0,                                 // Size of hFile.
      0);                                // Map entire file.

  if (lpMapAddress == NULL)
  {
    formConsole->AddMessage("Could not create view of file.");
    return;
  }

  formConsole->AddMessage("Receiving ihWeights...");

  // am pointerul de acces la fisier, pot sa primesc ponderile
  int startPtr = 0;
  ptrWork = (char*)lpMapAddress + 284;

  // primesc intii ponderile IH
  for(int i = 0; i < index; i++)
  {
    if (ValidMachine(i))
    {
      machines[i]->SetData((float*)ptrWork + startPtr, project.inputsNo * partition[i][1]); // lungimea e in floati
      machines[i]->GoReceiving();
    }
    else
    {
      // nu pot primi ponderile; si ce daca...ghinion :-)
      formConsole->AddMessage("Machine " + AnsiString(i) + " cannot transmit ihWeights.");
    }

    startPtr += partition[i][1];
  }

  // sincronizare
  for(int i = 0; i < index; i++)
  {
    while(machines[i]->GetRecvStatus())
    {
    }
  }

  formConsole->AddMessage("Receiving hoWeights...");

  // apoi ponderile HO
  startPtr = 0;
  ptrWork = (char*)lpMapAddress + 284 + project.inputsNo * project.hiddenNo * sizeof(float);
  for(int i = 0; i < index; i++)
  {
    if (ValidMachine(i))
    {
      machines[i]->SetData((float*)ptrWork + startPtr, project.hiddenNo * partition[i][2]); // lungimea e in floati
      machines[i]->GoReceiving();
    }
    else
    {
      // nu pot primi ponderile; si ce daca...ghinion :-)
      formConsole->AddMessage("Machine " + AnsiString(i) + " cannot transmit hoWeights.");
    }

    startPtr += partition[i][2];
  }

  // sincronizare
  for(int i = 0; i < index; i++)
  {
    while(machines[i]->GetRecvStatus())
    {
    }
  }

  // se inchide maghernitza
  if (!UnmapViewOfFile(lpMapAddress))
  {
    formConsole->AddMessage("Cannot unmap view of file.");
  }

  CloseHandle(hMapFile);
  CloseHandle(handle);
}
//---------------------------------------------------------------------------

// Descriere   : trimit ponderile la clienti
// Param       : n/a
// Rezultat    : n/a
// Comentarii  : tot cu file mapping
void __fastcall CMachineManager::SendWeights()
{
  HANDLE handle;

  handle = CreateFile( project.fileName.c_str(),
             GENERIC_READ | GENERIC_WRITE,          // tipul de acces
             0,                                     // sharing mode
             NULL,                                  // security attrib
             OPEN_EXISTING,
             FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS,
             NULL                                   // template file; n/a pt. W95
             );

  if (handle == NULL)
  {
    formConsole->AddMessage("Could not open project file");
    return;
  }

  HANDLE hMapFile;

  hMapFile = CreateFileMapping(handle,   // Current file handle.
      NULL,                              // Default security.
      PAGE_READWRITE,                    // Read/write permission.
      0,                                 // Max. object size.
      0,                                 // Size of hFile.
      "Sender");                       // Name of mapping object.

  if (hMapFile == NULL)
  {
    int error = GetLastError();
    formConsole->AddMessage("Could not create file-mapping object." + AnsiString(error));
    return;
  }

  LPVOID lpMapAddress, ptrWork;
  lpMapAddress = MapViewOfFile(hMapFile, // Handle to mapping object.
      FILE_MAP_ALL_ACCESS,               // Read/write permission
      0,                                 // Max. object size.
      0,                                 // Size of hFile.
      0);                                // Map entire file.

  if (lpMapAddress == NULL)
  {
    formConsole->AddMessage("Could not create view of file.");
    return;
  }

  // am pointerul de acces la fisier, pot sa trimit ponderile
  int startPtr = 0;
  ptrWork = (char*)lpMapAddress + 284;

  // trimit intii ponderile IH
  for(int i = 0; i < index; i++)
  {
    if (ValidMachine(i))
    {
      machines[i]->SetData((float*)ptrWork + startPtr, project.inputsNo * partition[i][1]); // lungimea e in floati
      machines[i]->GoSending();
    }
    else
    {
      // nu pot trimite ponderile
      formConsole->AddMessage("Cannot send ihWeights to machine " + AnsiString(i));
    }

    startPtr += partition[i][1];
  }

  // sincronizare
  for(int i = 0; i < index; i++)
  {
    while(machines[i]->GetSendStatus())
    {
    }
  }

  // apoi ponderile HO
  startPtr = 0;
  ptrWork = (char*)lpMapAddress + 284 + project.inputsNo * project.hiddenNo;
  for(int i = 0; i < index; i++)
  {
    if (ValidMachine(i))
    {
      machines[i]->SetData((float*)ptrWork + startPtr, project.hiddenNo * partition[i][2]); // lungimea e in floati
      machines[i]->GoSending();
    }
    else
    {
      // nu pot trimite ponderile
      formConsole->AddMessage("Cannot send hoWeights to machine " + AnsiString(i));
    }

    startPtr += partition[i][2];
  }

  // sincronizare
  for(int i = 0; i < index; i++)
  {
    while(machines[i]->GetSendStatus())
    {
    }
  }

  // se inchide pravalia
  if (!UnmapViewOfFile(lpMapAddress))
  {
    formConsole->AddMessage("Cannot unmap view of file.");
  }

  CloseHandle(hMapFile);
  CloseHandle(handle);
}
//---------------------------------------------------------------------------

