//---------------------------------------------------------------------------
#ifndef sym_tabH
#define sym_tabH
//---------------------------------------------------------------------------

#define MAX_SYMS 8192
#define MAX_CONST 1024

enum _class { nume_program, nume_const, nume_vars, nume_funct, nume_proc, nume_paramv, nume_param, nume_tablou, nume_record, nume_cimp};
enum _tip { intreg = 0, real, charr, nedefinit};
enum _transm {valoare, referinta};

typedef struct pf_entry
{
  _tip tip;
  _transm transm;
  pf_entry* next;
} param_formal;

typedef struct rec_entry
{
  int index; // in ts
  rec_entry* next;
} record_list;

typedef struct
{
  _tip  tip;
  double valoare;
  int   valoare_i;
  char  valoare_c;
} tab_const_entry;

typedef struct
{
  char* nume;
  _class clasa;                   // ce fel de identificator e
  _tip tip;                       // pentru constante, param formali, var.simple, tablouri
  int val;                        // pentru constante - index in TAB_CONST
  int adrel;                      // pentru variabile
  int adrelNo;                    // pentru variabile, 1!
  int deplrec;                    // pentru recorduri
  int deplrecNo;                  // pentru recorduri, va substitui deplrec
  int nivel;                      // nivelul de imbricare
  int nr_par;                     // pentru proceduri/functii
  int dim_var;                    // pentru proceduri/functii
  int varNo;                      // pentru procs, funcs si prg, cite variabile sint
  int adr_start;                  // pentru functii/proceduri/program princ - de unde incepe codul
  param_formal* lista_par;
  int ind_min, ind_max;           // pentru tablouri
  record_list* lista_rec;         // pentru recorduri
  int incdom;
} sym_entry;

extern sym_entry TS[MAX_SYMS];
extern int TS_Virf;

int Cautare_Id(char* nume);
int Inserare_Id(char* nume);
sym_entry Get_Id(int index);
int Sterge_Id(int nivel);
int Verificare_TS();
void AllToScreen();

extern tab_const_entry Tab_Const[MAX_CONST];
void Init_Tab_Const();
int Inserare_Const(_tip tip, double valoare);
void Sterge_Const(int index);

extern int VNivel;
extern int ICod;

void Push_Bloc(int what);
int  Get_Bloc();
void Pop_Bloc();

#endif
