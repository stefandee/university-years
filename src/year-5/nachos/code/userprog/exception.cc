// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------

void inc_PC();
int readString(char *, int size);
void Create();
void Open();
void Close();
void Read();
void Write();


#define MAXFileName 100

void
ExceptionHandler(ExceptionType which)
{
  int type = machine->ReadRegister(2);
  
  if (which == SyscallException) {
    switch (type) {
    case SC_Halt:
      DEBUG('a', "Shutdown, initiated by user program.\n");
      interrupt->Halt();
      break;
    case SC_Exit:
      currentThread->Finish();
      break;
    case SC_Create:
      DEBUG('y', "Apel sistem Create...\n");
      Create();

      inc_PC();
      break;
    case SC_Open:
      DEBUG('y', "Apel sistem Open...\n");
      Open();

      inc_PC();
      break;
    case SC_Close:
      DEBUG('y', "Apel sistem Close...\n");
      Close();
      inc_PC();
      break;
    case SC_Read:
      DEBUG('y', "Apel sistem Read...\n");
      Read();
      inc_PC();
      break;
    case SC_Write:
      DEBUG('y', "Apel sistem Write...\n");
      Write();
      inc_PC();
      break;
    default:
      printf("Unexpected syscall exception %d\n", type);
      ASSERT(FALSE);
    }
  }
  else {
    printf("Unexpected user mode exception %d %d\n", which, type);
    ASSERT(FALSE);
  }
}

int
readString(char *s, int size)
{
  int arg = machine->ReadRegister(4); // arg 1
  int t;
  int n = -1;

  do {
    if (!machine->ReadMem(arg, 1, &t)) {
      printf("readString: Memory read error\n");
      return -1;
    }
    n++;
    s[n] = (char)t;
    arg++;
  } while ( (n < size) && (s[n] != '\0') );
  //printf("readString     Arg: %s\n", s);
  return 0;
}

void 
inc_PC()
{
  int pcAfter = machine->registers[NextPCReg] + 4;
  machine->registers[PrevPCReg] = machine->registers[PCReg];
  machine->registers[PCReg] = machine->registers[NextPCReg];
  machine->registers[NextPCReg] = pcAfter;
}  

void
Create()
{
  char *fileName;

  fileName = new char[MAXFileName];
  if( readString(fileName, MAXFileName) ) {
    DEBUG('y', "Create: file creation error\n");
    return;
  }
  fileSystem->Create(fileName, 0);
  DEBUG('y', "Create:file %s was sucessfully created\n", fileName);
  delete fileName;
}

void
Open()
{
  OpenFile *id;
  int fd;
  char *fileName = new char[MAXFileName];
  if ( readString(fileName, MAXFileName) ) {
    DEBUG('y', "Open: file system Open error\n");
    return;
  }    
  id = fileSystem->Open(fileName);
  delete fileName;
  if (id == NULL ) {
    machine->WriteRegister(2, -1);
    DEBUG('y', "Open: file system Open error\n");
    return;
  }
  fd = currentThread->AddFD(id);
  machine->WriteRegister(2, fd);
  DEBUG('y', "Open: file descriptor associated: %d\n", fd);
}

void 
Close()
{
  int fd =  machine->ReadRegister(4);
  int result;
  result = currentThread->DeleteFD(fd);
  if (result == -1) {
    DEBUG('y', "Close: No such file descriptor %d\n", fd);
    return;
  }
  DEBUG('y', "Close: ok\n");
}

void
Read()
{
  int arg = machine->ReadRegister(4);
  int size = machine->ReadRegister(5);
  int fd = machine->ReadRegister(6);
  char *buffer = new char[size];
  int numRead, i;

  OpenFile *fp = currentThread->RetrieveFD(fd);
  if (fp == NULL) {
    DEBUG('y', "Read: No such file descriptor: %d\n", fd);
    delete buffer;
    return;
  }
  numRead = fp->Read(buffer, size);
  for (i=0; i<numRead; i++)
    machine->WriteMem(arg+i, 1, (int)buffer[i]);
  machine->WriteRegister(2, numRead);
  delete buffer;
  DEBUG('y', "Read: read  %d bytes from %d fd\n", numRead, fd);
}

void 
Write()
{
  int fd = machine->ReadRegister(6);
  int size = machine->ReadRegister(5);
  char *buffer = new char[size];
  if (readString(buffer, size) ) {
    DEBUG('y', "Write: Error while reading parameters\n");
    machine->WriteRegister(2, -1);
    delete buffer;
    return;
  }
  OpenFile *fp = currentThread->RetrieveFD(fd);
  int numWritten;
  if (fp == NULL) {
    DEBUG('y', "Write: No such file descriptor: %d\n", fd);
    machine->WriteRegister(2, -1);
    delete buffer;
    return;
  }
  numWritten = fp->Write(buffer, size);
  machine->WriteRegister(2, numWritten);
  delete buffer;
  DEBUG('y', "Write: wrote %d bytes in fd no %d\n", numWritten, fd);
  //  printf("WRITE: buffer = %s, size=%d, fd=%d\n", buffer, size, fd); 
}
