//----------------------------------------------------------------------------
// UNIT 	    : sem
// TIP  	    : sursa
// DESCRIERE        : implementarea semafoarelor
// VERSIUNE         : :-)
//----------------------------------------------------------------------------
#include "sem.h"

_semafor::_semafor(int val)
{
  valoare = val;
  prim_proces_blocat = ultim_proces_blocat = -1;
}

void _semafor::P(void)
{
  asm pushf
  asm cli

  if (--valoare < 0)
  {
    _executor::tabela_procese[_executor::proces_curent].stare = BLOCAT;
    if (prim_proces_blocat == -1)
    {
      prim_proces_blocat = ultim_proces_blocat = _executor::proces_curent;
    }
    else
    {
      _executor::tabela_procese[ultim_proces_blocat].urm = _executor::proces_curent;
      ultim_proces_blocat = _executor::proces_curent;
    }

    _executor::tabela_procese[_executor::proces_curent].urm = -1;
    //asm sti;
    asm popf;
    _executor::cedeaza_UC();
  }
  else
  {
    //asm sti;
    asm popf;
  }
}

void _semafor::V(void)
{
  asm pushf
  asm cli

  ++valoare;
  if (prim_proces_blocat != -1)
  {
    _executor::tabela_procese[prim_proces_blocat].stare = PREGATIT;
    prim_proces_blocat = _executor::tabela_procese[prim_proces_blocat].urm;
    if (prim_proces_blocat == -1) ultim_proces_blocat = -1;

    //asm sti;
    asm popf;
    _executor::cedeaza_UC();
  }
  else
  {
    //asm sti;
    asm popf;
  }
}
