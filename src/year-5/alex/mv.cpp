// un interpretor de cod virtual - masina virtuala
#include <stdio.h>
#include <stdlib.h>
#pragma hdrstop
#include <condefs.h>

//---------------------------------------------------------------------------
#include "mv_ops.h"
#include "Erori.h"
#include "mv_instr.h"

//---------------------------------------------------------------------------
USEUNIT("mv_ops.cpp");
USEUNIT("Erori.cpp");
USEUNIT("mv_instr.cpp");
USEUNIT("sym_tab.cpp");
//---------------------------------------------------------------------------
#pragma argsused
int main(int argc, char **argv)
{
   int result;

   printf("Virtual machine code interpreter\n");

   if (argc != 2)
   {
     printf("Usage mv filename[.obj]\n");
     exit(1);
   }

   // incarc codul virtual in memorie
   result = loadCode(argv[1]);
   if (result != 0)
   {
     Eroare(result);
     getchar();
     exit(1);
   }

   // rulez codul
   result = runCode();
   if (result != 0)
   {
     Eroare(result);
     getchar();
     exit(1);
   }

   printf("\nOk\n");
   getchar();
   return 0;
}
