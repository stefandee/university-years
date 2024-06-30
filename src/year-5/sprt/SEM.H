//----------------------------------------------------------------------------
// UNIT 	    : sem
// TIP  	    : header
// DESCRIERE        : clasa semafor
// VERSIUNE         : :-)
//----------------------------------------------------------------------------

#ifndef SEMH
#define SEMH
#include "kernel.h"

class _semafor
{
  int valoare;        // numarul de resurse disponibile
  int prim_proces_blocat,ultim_proces_blocat;

  public:
    friend executor;
    _semafor(int val);// valoarea initiala
    void P(void);    // neintreruptibile, echivaleaza cu instructiuni
    void V(void);
};

#endif