#ifndef WINIO
#define WINIO
#include "kernel.h"

enum _winstatus {ACTIVE, INACTIVE};
typedef struct
{
  _winstatus active;
  int x_pos, y_pos;
  int x_len, y_len;
  int color;
} _win_init;

class Intrare
{
  public:
    friend executor;
    void operator >>(int*);
    void operator >>(char*);
};

class Iesire
{
  public:
    friend executor;
    void operator <<(int*);
    void operator <<(char*);
};

#endif