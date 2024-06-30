#include <fcntl.h>
#include <stdio.h>
//#include <io.h>
#include <stdlib.h>
//#include <conio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#pragma hdrstop

#include "misc.h"
//---------------------------------------------------------------------------
//USEUNIT("misc.cpp");
//---------------------------------------------------------------------------
#pragma argsused

int alex()
{
  atom_valoare*  av;
  unsigned char ch1, ch;
  int           stare = S_INIT;
  int           carurm_result = 1;
  int           retn;

  //carurm_result = carurm();
  //ch = (unsigned char)carurm_result;
  //ch1 = ch;
  av = new atom_valoare; 
  av->valoare = new char[128];
  ((char*)av->valoare)[0] = '\0';
	
  while((carurm_result >= 0) && (stare != S_FINAL) && (stare != S_ERR))
  {
    // citire din fisier
    carurm_result = carurm();
    ch = (unsigned char)carurm_result;
    ch1 = ch;
    //printf("%d %c\n", stare, ch);	

    retn = Tab_Apel[stare][ch1](ch1, stare, av);
    if (retn < 0) break;
    stare = Tab_Stari[stare][ch1];
  };

  delete av->valoare;
  delete av;	  

  if (retn < 0)
  {
    switch(retn)
    {
      case (INT_BASE_ERR) :
        printf("Eroare de conversie intreg/baza in intreg\n");
        break;
    }
  }

  if (carurm_result == -5)
  {
    return -5; //gata
  }
  if (carurm_result == -1)
  {
    return -1; //eroare de citire din fisier
  }
  if (stare == S_ERR)
  {
    return -2; // eroare lexicala
  }

  return 1;
}

int main(int argc, char **argv)
{
  int alex_result = 0;
  char filename[256], drive[12], dir[256], ext[12], result_path[256];

  //
  //  Sectziunea de initializari
  //
  if (argc != 2)
  {
    printf("Folosire : alex filename.\n");
    exit(1);
  }

  if ((open_source(argv[1])) == -1)
  {
    printf("Cannot open source file.\n");
    getchar();
    exit(1);
  }

  //_splitpath(argv[1], drive, dir, filename, ext);
  //strcpy(result_path, drive);
  //strcat(result_path, dir);
  //strcat(result_path, filename);
  //strcat(result_path, ".lex");
  strcpy(result_path, "temp.lex");
  if ((open_result(result_path) == -1))
  {
    printf("Cannot open %s for writing", result_path);
    getchar();
    exit(1);
  }

  InitTabele();

  //
  //  Bucla principala
  //
  while((alex_result = alex()) > 0);

  switch(alex_result)
  {
    //case -3 : printf("Alex error in line %d\n", getLines()); break;
    case -2 : printf("Alex error in line %d\n", getLines()); break;
    case -1 : printf("Error reading file\n", getLines()); break;
    case  -5 : printf("Alex finished succesfully\nTotal lines %d\n", getLines());break;
    case  1 : printf("This shouldn't happen\n");break;
  }

  //
  //  Gata
  //
  getchar();
  return 0;
}
