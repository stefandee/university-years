//---------------------------------------------------------------------------
#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#pragma hdrstop

#include "gen_cod.h"
#include "sym_tab.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

int fileHandle;

// variabila globala, utilizata la completarea cimpurilor INC_DOM si ADR_START
int ICod;

// pointer global la codul generat
int tabCod[65536];

// Descriere   : deschide/creaza fisierul de cod
// Param       : numele fisierului
// Rezultat    :
// Comentarii  :
int initGenCod(const char* fileName)
{
  char id[32];

  //tabCod = new int[MAX_PRG_SIZE];
  fileHandle = open(fileName, O_CREAT | O_RDWR | O_BINARY, S_IREAD | S_IWRITE);

  strcpy(id, OBJ_FILE_ID);

  write(fileHandle, id,        32);

  return 0;
}
//---------------------------------------------------------------------------

// Descriere   : termina generarea de cod, scriind tabela de constante,
//               tabela de cod si inchizind fisierul
// Param       : n/a
// Rezultat    :
// Comentarii  :
int endGenCod()
{
  int i, dummy;
  
  write(fileHandle, Tab_Const, sizeof(Tab_Const));
  write(fileHandle, tabCod,    (ICod + 1) * sizeof(int));

  close(fileHandle);

  return 0;
}
//---------------------------------------------------------------------------

// Descriere   : genereaza o instructiune fara parametri
// Param       : n/a
// Rezultat    :
// Comentarii  :
void genCod0(int instr)
{
  printf(" %d = %d \n", ICod +1, instr);
  tabCod[++ICod] = instr;
}
//---------------------------------------------------------------------------

// Descriere   : genereaza o instructiune cu 1 parametru
// Param       : param1 - primul parametru
// Rezultat    :
// Comentarii  :
void genCod1(int instr, int param1)
{
  printf(" %d = %d \n", ICod +1, instr);
  tabCod[++ICod] = instr;
  tabCod[++ICod] = param1;
}
//---------------------------------------------------------------------------

// Descriere   : genereaza o instructiune cu 2 parametri
// Param       : param1 - primul parametru, etc
// Rezultat    :
// Comentarii  :
void genCod2(int instr, int param1, int param2)
{
  printf(" %d = %d \n", ICod +1, instr);
  tabCod[++ICod] = instr;
  tabCod[++ICod] = param1;
  tabCod[++ICod] = param2;
}
//---------------------------------------------------------------------------

// Descriere   : genereaza o instructiune cu 3 parametri
// Param       : param1 - primul parametru, etc
// Rezultat    :
// Comentarii  :
void genCod3(int instr, int param1, int param2, int param3)
{
  printf(" %d = %d \n", ICod +1, instr);
  tabCod[++ICod] = instr;
  tabCod[++ICod] = param1;
  tabCod[++ICod] = param2;
  tabCod[++ICod] = param3;
}
//---------------------------------------------------------------------------
