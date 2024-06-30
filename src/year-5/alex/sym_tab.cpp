//---------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#pragma hdrstop

#include "sym_tab.h"

#define TS_MAX_ERRORS 7

//---------------------------------------------------------------------------
#pragma package(smart_init)

// tabela de simboluri, organizata ca stiva
sym_entry TS[MAX_SYMS];

// virful stivei din tabela de simboluri
int TS_Virf = -1;

// variabila globala, care tine nivelul curent de imbricare
int VNivel = 1;

// blocurile active - o stiva
int St_Bloc[1024];

// indicator de stiva
int VStb = 0;

// tabela de constante
tab_const_entry Tab_Const[MAX_CONST];

// numarul de constante
int Const_Virf;

int Cautare_Id(char* nume)
{
  int i;

  for(i = TS_Virf; i > 0; i--)
  {
    if ((strcmp(TS[i].nume, nume) == 0) && (TS[i].clasa != nume_cimp)) return i;
  }

  return -1;
}

// verifica corectitudinea tabelei de simboluri - identificatori multiplu declarati
// variabile pe acelasi nivel cu acelasi nume si clasa diferita de nume_cimp
// sau nume
int Verificare_TS()
{
  int i, j;
  rec_entry* recsi, *recsj;
  
  for(i = 0; i <= TS_Virf; i++)
  {
    for(j = 0; j <= TS_Virf; j++)
    {
      if (i != j)
      {
        if (TS[i].nivel == TS[j].nivel)
        {
          if (strcmp(TS[i].nume, TS[j].nume) == 0)
          {
            if ((TS[i].clasa == nume_cimp) && (TS[j].clasa == nume_cimp))
            {
               // avem 2 cimpuri cu acelasi nume;
               // parcurg lista_rec sa vad daca au acelasi parinte
               // daca da, atunci eroare
               recsi = TS[i].lista_rec;
               while(recsi != NULL)
               {
                 recsj = TS[j].lista_rec;
                 while(recsj != NULL)
                 {
                   if (recsj->index == recsi->index) return -1; // eroare
                   recsj = recsj->next;
                 }
                 recsi = recsi->next;
               }
            }
            else
            {
              if ((TS[i].clasa != nume_cimp) && (TS[j].clasa != nume_cimp)) return -1;
            }
          }
        }
      }
    }
  }
  return 1;
}

int Inserare_Id(char* nume)
{
  // verific daca nu cumva id a mai fost declarat o data in acest bloc
  /*
  if (TS_Virf != -1)
  {
    for(int i = TS_Virf; i > 0; i--)
    {
      if ((strcmp(TS[i].nume, nume) == 0) && (TS[i].nivel == VNivel)) return -1;
    }
  }
  */
  // inc virf
  TS_Virf++;
  if (TS_Virf >= MAX_SYMS) return -2;

  // seteaza pe null pointerii - pentru verificari ulterioare
  TS[TS_Virf].nume = new char[strlen(nume) + 1];
  strcpy(TS[TS_Virf].nume, nume);
  strcat(TS[TS_Virf].nume, "\0");
  TS[TS_Virf].lista_par = NULL;
  TS[TS_Virf].lista_rec = NULL;
  // gata
  return TS_Virf;
}

sym_entry Get_Id(int index)
{
  // doar stub, pentru moment
  index++;
}

// sterge toti identificatorii de acelasi nivel
int Sterge_Id(int nivel)
{
  int succes = -1;

  for(int i = TS_Virf; i > 0; i--)
  {
    if (TS[i].nivel == nivel)
    {
      // sterge id
      delete TS[i].nume;
      // sterge param_formal
      param_formal* next_pf;
      while(TS[i].lista_rec != NULL)
      {
        next_pf = TS[i].lista_par->next;
        delete TS[i].lista_par;
        TS[i].lista_par = next_pf;
      }
      // sterge record_list
      record_list* next_rl;
      while(TS[i].lista_rec != NULL)
      {
        next_rl = TS[i].lista_rec->next;
        delete TS[i].lista_rec;
        TS[i].lista_rec = next_rl;
      }
      // pentru orice eventualitate
      TS[i].nivel = -1;
      // decrementeaza virful
      TS_Virf--;
      succes = 1;
    }
  }

  return succes;
}

void Init_Tab_Const()
{
  for(int i = 0; i < MAX_CONST; i++)
  {
    Tab_Const[i].tip = nedefinit;
  }
}

// returneaza indexul sau -1 daca nu se mai poae introdduce nimic
int Inserare_Const(_tip tip, double valoare)
{
  for(int i = 0; i < MAX_CONST; i++)
  {
    if (Tab_Const[i].tip == nedefinit)
    {
      Tab_Const[i].tip     = tip;
      Tab_Const[i].valoare = valoare;
      return i;
    }
  }

  // nu mai e loc in tabela de constante
  return -1;
}

void Sterge_Const(int index)
{
  Tab_Const[index].tip = nedefinit;
}

void TypeConst(int i)
{
  // char* tipuri[4] = {"intreg", "real", "char", "nedefinit"};
  
  printf("constanta %s de ", TS[i].nume);
  switch(Tab_Const[TS[i].val].tip)
  {
    case intreg :
      printf("tip intreg, valoare %d ", (int)Tab_Const[TS[i].val].valoare);
      break;
    case real :
      printf("tip real, valoare %f ", Tab_Const[TS[i].val].valoare);
      break;
    case charr :
      printf("tip char, valoare %c ", (char)Tab_Const[TS[i].val].valoare);
      break;
  }
  
  printf("pe nivel %d\n", TS[i].nivel);
}

void TypeVars(int i)
{
  printf("variabila %s de ", TS[i].nume);
  switch(TS[i].tip)
  {
    case intreg :
      printf("tip intreg ");
      break;
    case real :
      printf("tip real ");
      break;
    case charr :
      printf("tip char ");
      break;
  }
  
  printf("pe nivel %d\n", TS[i].nivel);
}

void TypeTablou(int i)
{
  printf("tablou %s de ", TS[i].nume);
  switch(TS[i].tip)
  {
    case intreg :
      printf("intregi ");
      break;
    case real :
      printf("reali ");
      break;
    case charr :
      printf("chars ");
      break;
  }

  printf("intre indici %d si %d ", TS[i].ind_min, TS[i].ind_max);
  printf("pe nivel %d\n", TS[i].nivel);
}

void TypeRecord(int i)
{
  printf("record %s pe nivel %d\n", TS[i].nume, TS[i].nivel);
}

void TypeCimp(int i)
{
  printf("cimp de record %s de tip ", TS[i].nume);
  switch(TS[i].tip)
  {
    case intreg :
      printf("intreg ");
      break;
    case real :
      printf("real ");
      break;
    case charr :
      printf("char ");
      break;
  }

  rec_entry* recs = TS[i].lista_rec;

  printf(", apartine de");
  while(recs != NULL)
  {
    printf(" %s", TS[recs->index].nume);
    recs = recs->next;
  }

  printf(", adrel e %d, deplrec e %d", TS[i].adrel, TS[i].deplrec);
  printf(", pe nivel %d\n", TS[i].nivel);
}

void TypeFunct(int i)
{
  printf("functie %s de tip ", TS[i].nume);
  switch(TS[i].tip)
  {
    case intreg :
      printf("intreg ");
      break;
    case real :
      printf("real ");
      break;
    case charr :
      printf("char ");
      break;
  }
  printf("cu %d parametri, pe nivel %d, ", TS[i].nr_par, TS[i].nivel);
  printf("memoria ocupata de variabilele locale e %d sau %d locatii\n", TS[i].dim_var, TS[i].varNo);
}

void TypeProg(int i)
{
  printf("program %s %d octeti pentru variabile sau %d locatii\n", TS[i].nume, TS[i].dim_var, TS[i].varNo);
}

void TypeParams(int i)
{
  printf("parametru formal %s de tip ", TS[i].nume);
  switch(TS[i].tip)
  {
    case intreg :
      printf("intreg ");
      break;
    case real :
      printf("real ");
      break;
    case charr :
      printf("char ");
      break;
  }
  printf(", pe nivel %d\n", TS[i].nivel);
}

void TypeProc(int i)
{
  printf("procedura %s ", TS[i].nume);
  printf("cu %d parametri, pe nivel %d, ", TS[i].nr_par, TS[i].nivel);
  printf("memoria ocupata de variabilele locale e %d octeti sau %d variabile\n", TS[i].dim_var, TS[i].varNo);
}

void AllToScreen()
{
  // char out[256];

  for(int i = 0; i <= TS_Virf; i++)
  {
    switch(TS[i].clasa)
    {
      case nume_const :
        TypeConst(i);
        break;
      case nume_vars :
        TypeVars(i);
        break;
      case nume_tablou :
        TypeTablou(i);
        break;
      case nume_record :
        TypeRecord(i);
        break;
      case nume_cimp :
        TypeCimp(i);
        break;
      case nume_program :
        TypeProg(i);
        break;
      case nume_funct :
        TypeFunct(i);
        break;
      case nume_proc :
        TypeProc(i);
        break;
      case nume_paramv :
      case nume_param :
        TypeParams(i);
        break;
    }
  }
}

// trei functii care se joaca cu ST_Bloc si VStb
void Push_Bloc(int what)
{
  VStb++;
  St_Bloc[VStb] = what;
}

int Get_Bloc()
{
  return St_Bloc[VStb];
}

void Pop_Bloc()
{
  VStb--;
}

