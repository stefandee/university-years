//----------------------------------------------------------------------------
// UNIT 	    : proces
// TIP  	    : sursa
// DESCRIERE        : implementarile claselor pentru un kernel
// VERSIUNE         : :-)
//----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <alloc.h>
#include <conio.h>
#pragma hdrstop
#include "kernel.h"

_proces* _executor::tabela_procese;
int _executor::numar_procese;
int _executor::proces_curent;
int _executor::numar_procese_inex;
int _executor::tick_count;
void interrupt ( *_executor::oldhandler)(...);

_proces::_proces()
{
  stare = SUSPENDAT;
  urm = 0;
  cuante_delay = 0;
  nume[0] = '\0';
}

void _proces::initproces(info_init_proces init, unsigned int sp)
{
  stare = init.stare;
  strcpy(nume, init.nume);
  //urm = 0;
  //cuante_delay = 0;
  printf(">initproces %s \n", nume);

  env->j_ds = _DS;
  env->j_es = _ES;
  env->j_si = _SI;
  env->j_di = _DI;
  env->j_bp = _BP;
  env->j_ss = _SS;
  env->j_cs = _CS;
  env->j_ip = FP_OFF(init.adresa_proces);
  env->j_flag = 0x200;
  env->j_sp = sp;

  if (init.win.active == ACTIVE)
  {
    x_pos = init.win.x_pos;
    y_pos = init.win.y_pos;
    x_len = init.win.x_len;
    y_len = init.win.y_len;
    color = init.win.color;
    x_cursor = 1;
    y_cursor = 2;
    //textbackground(color);
    //window(x_pos, y_pos, x_pos + x_len, y_pos + y_len);
    clrscr();
  }
  active = init.win.active;
}

_executor::_executor(pinfo_init_proces tabela_init, int nr_procese)
{
  int i;

  printf(">_executor constructor : under construction\n");
  if (tabela_init == NULL)
  {
    printf(">err : tabela de procese vida.\n");
    exit(1);
  }

  // init numarul de procese
  numar_procese = nr_procese+1;

  // calculeaza suma stivelor
  int suma_stivelor = 0;
  for(i = 0; i < numar_procese-1; i++)
    suma_stivelor += tabela_init[i].dim_stiva;
  suma_stivelor += NULL_PROCESS_STACK_SIZE;
  tabela_procese = new _proces[numar_procese];

  // artificii
  char* p1 = new char[coreleft() - suma_stivelor - PADDING_STACK];
  char *p2 = new char[suma_stivelor];
  delete p1;
  unsigned int stive_start = (unsigned)p2; // sau FP_OFF(p2)

  //stive_start += tabela_init[0].dim_stiva;
  for(i = 0;i < numar_procese-1; i++)
  {
    stive_start += tabela_init[i].dim_stiva;
    tabela_procese[i].initproces(tabela_init[i], stive_start);
  }

  numar_procese_inex = 0;

  // insert proces nul
  info_init_proces null_process_init =
  {
    &(_executor::functia_nul),
    "PROCES NUL",
    NULL_PROCESS_STACK_SIZE,
    PREGATIT
  };
  tabela_procese[numar_procese-1].initproces(null_process_init, stive_start + NULL_PROCESS_STACK_SIZE);

}

void _executor::run()
{
  int proces_curent;
  // gasire primul proces pregatit
  for(proces_curent = 0; proces_curent < numar_procese; proces_curent++)
    if (tabela_procese[proces_curent].stare == PREGATIT) break;

  // dezactivare intreruperi
  disable();
  // iau rutina veche de intrerupere
  oldhandler = getvect(CLOCK_INTERRUPT);
  // setez handlerul de intrerupere pe clocker
  setvect(CLOCK_INTERRUPT, &(_executor::clocker));
  tick_count = 0;

  // gata !!!
  longjmp(tabela_procese[proces_curent].env,1);
}

void interrupt _executor::clocker(...)
{
  // apelare handler vechi de intrerupere
  //asm pushf;
  (*oldhandler)();
  // actualizare timp sistem
  tick_count++;
  cedeaza_UC();
}

void interrupt _executor::cedeaza_UC(...)
{
  // gasire proces pregatit
  int proces_vechi = proces_curent;
  if (tabela_procese[proces_curent].stare == ACTIV) tabela_procese[proces_curent].stare = PREGATIT;

  proces_curent++;
  proces_curent = (proces_curent % numar_procese);
  for(; tabela_procese[proces_curent].stare != PREGATIT;)
  {
    proces_curent++;
    proces_curent = (proces_curent % numar_procese);
  }

  // artificiu
  if (setjmp(tabela_procese[proces_vechi].env)) return;
  else longjmp(tabela_procese[proces_curent].env, 1);
}

int _executor::pregatire(int nr)
{
  if ((tabela_procese[nr].stare == SUSPENDAT) && (nr < numar_procese))
  {
    tabela_procese[nr].stare = PREGATIT;
  }
  cedeaza_UC();
  return 0;
}

int _executor::suspendare()
{
  tabela_procese[proces_curent].stare = SUSPENDAT;
  cedeaza_UC();
  return 0;
}

int _executor::terminare()
{
  numar_procese_inex++;
  tabela_procese[proces_curent].stare = INEXISTENT;
  cedeaza_UC();
  return 0;
}

void _executor::functia_nul()
{
  while(1)
  {
    if ((numar_procese-1) > numar_procese_inex)
    {
      cedeaza_UC();
    }
    else
    {
      out();
    }
  }
}

void _executor::out()
{
  disable();
  setvect(CLOCK_INTERRUPT, oldhandler);
  enable();
  exit(0);
}