// #include <condefs.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#pragma hdrstop

#include "kernel.h"
#include "sem.h"
#include "winio.h"
//---------------------------------------------------------------------------
// USEUNIT("Kernel.cpp");
//---------------------------------------------------------------------------

void functie_test1();
void functie_test2();
void functie_test3();

_info_init_proces procese[3] =
  {
    {functie_test1, "proces 1", 2048, PREGATIT, {ACTIVE, 1, 1, 20, 9, BLUE}},
    {functie_test2, "proces 2", 2048, PREGATIT, {ACTIVE, 40, 13, 30, 10, RED}},
    {functie_test3, "proces 3", 2048, PREGATIT, {ACTIVE, 5, 5, 20, 15, GREEN}}
  };

class _executor executor(procese, 3);

Iesire out;
Intrare in;

void functie_test3()
{
  for(int i = 0; i < 20; i++)
  {
    out << "hhhh\r\n";
  }

  executor.terminare();
}

void functie_test2()
{
  int a;

  in >> &a;

  for(int i = 0; i < 5; i++)
  {
    a += i;
    out << &a;
    out << &i;
    out << "\r\n";
  }
  executor.terminare();
}

void functie_test1()
{
  for(int i = 0; i < 23; i++)
  {
    out << "functie2\r\n";
  }

  executor.terminare();
}


void main()
{
  textbackground(BLACK);
  clrscr();
  printf("Kernel tester.\n\n");
  executor.run();
  getchar();
  textbackground(BLACK);
}
