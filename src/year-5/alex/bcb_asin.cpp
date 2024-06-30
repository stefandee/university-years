#include <condefs.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#pragma hdrstop

#include "codatom.h"
#include "erori.h"
#include "As_fcnt.h"

USEUNIT("Erori.cpp");
USEUNIT("As_fcnt.cpp");
USEUNIT("sym_tab.cpp");
USEUNIT("gen_cod.cpp");
USEUNIT("mv_instr.cpp");
//---------------------------------------------------------------------------
#pragma argsused
//---------------------------------------------------------------------------
void main(int argc, char **argv)
{
  clrscr();

  if (argc != 2)
  {
    printf("Folosire : asin filename.\n");
    exit(1);
  }

  printf("Analizor sintactic\n");

  Eroare(AnalizaSintactica(argv[1]));

  getchar();
}
