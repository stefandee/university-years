//---------------------------------------------------------------------------
#ifndef mv_opsH
#define mv_opsH
//---------------------------------------------------------------------------

#define OBJ_FILE_ID "Cod obiect pentru compilator"

#define MAX_STIVA 2048
#define MAX_BAZA  2048

enum _mvStats    {mv_activ, mv_stop, mv_err};
enum _stack_type {mv_intreg = 0, mv_real, mv_char, mv_adresa};

typedef struct
{
  _stack_type tipNod;
  int         iInfo;
  double      rInfo;
  char        cInfo;
  int         aInfo;
} _stack_entry;

typedef struct
{
  int         bloc;
  int         nivel;
} _baza_entry;


int loadCode  (const char* fileName);
int runCode   (                    );

#endif
