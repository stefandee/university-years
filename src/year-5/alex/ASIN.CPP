#include <stdlib.h>
#include <stdio.h>
//#include <conio.h>
//#pragma hdrstop

#include "codatom.h"
#include "erori.h"
#include "as_fcnt.h"

void main(int argc, char **argv)
{
  //clrscr();

  if (argc != 2)
  {
    printf("Folosire : asin filename.\n");
    exit(1);
  }

  printf("Analizor sintactic\n");

  Eroare(AnalizaSintactica(argv[1]));

  getchar();
}