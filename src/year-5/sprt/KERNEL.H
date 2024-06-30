//----------------------------------------------------------------------------
// UNIT 	    : proces
// TIP  	    : header
// DESCRIERE    : clase pentru un kernel
// VERSIUNE     : :-)
//----------------------------------------------------------------------------

#ifndef kernelH
#define kernelH

#include <setjmp.h>
#include "winio.h"

enum stari { INEXISTENT, BLOCAT, SUSPENDAT, INTIRZIAT, PREGATIT, ACTIV };

#define LNUME 255
#define NULL_PROCESS_STACK_SIZE 512
#define PADDING_STACK 256
#define CLOCK_INTERRUPT 0x1C

typedef struct _info_init_proces{
  void* adresa_proces;            // adresa initiala a procesului (a functiei ce-l implementeaza )
  char * nume;                    // numele procesului
  int dim_stiva;                  // necesarul de stiva ( in octeti )
  stari stare;     		            // starea initiala;
  _win_init win;
} info_init_proces, *pinfo_init_proces;

class _proces {
 public:
  stari stare;                  // starea procesului
  char nume[LNUME];              // numele
  jmp_buf env;                  // structura pentru salvarea contextului
  int urm;                      // cursor spre urmatorul proces din lista
  unsigned char cuante_delay;   // numarul de cuante de intirziere

  _winstatus active;
  int x_pos, y_pos, x_len, y_len;
  int x_cursor, y_cursor;
  int color;

  _proces();
  void initproces(info_init_proces init, unsigned int sp);
  ~_proces() {};
};

typedef _proces* pproces;

class _executor {
public:
  void static interrupt cedeaza_UC(...);
  void static interrupt clocker(...);
  static void interrupt ( *oldhandler)(...);
  static int tick_count;
  static _proces* tabela_procese;
  static int numar_procese;
  static int proces_curent;
  static int numar_procese_inex;

  _executor(pinfo_init_proces tabela_init, int nr_procese);
  static int pregatire(int nr_proces);
  static void run();
  static int suspendare();
  static int terminare();
  static void out();
  static int getTickCount() { return tick_count; };
  static void functia_nul();
  ~_executor() {};
};

#endif