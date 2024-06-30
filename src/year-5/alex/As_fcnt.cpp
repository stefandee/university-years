// mai e de lucru la parametri de functie - numarul lor, tipul lor
// la expr(), termen(), factor();
// de revazut variabila();
#include <fcntl.h>
#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <conio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
//#include <unistd.h>
//#pragma hdrstop

#include "as_fcnt.h"
#include "codatom.h"
#include "sym_tab.h"
#include "gen_cod.h"
#include "mv_instr.h"

int Program_Sursa();     //OK
int Bloc(int* vadrel, int* vadrelNo, int* vdimv, int* vVarNo);              //OK
int Instr_Compusa();     //OK
int Instr();

// sint suficient de clare
int Antet_Func(int* vadrel, int* vadrelNo);        //OK
int Antet_Proc(int* vadrel, int* vadrelNo);        //OK

// vezi anexa_d.doc pentru a afla la ce se folosesc Atrib_tip si Atrib_val
int Lista_Decl_Const();  //OK
int Expr_Statica(_tip* Atrib_tip, float* Atrib_val);
int Termen_Static(_tip* Atrib_tip, float* Atrib_val);     //OK
int Factor_Static(_tip* Atrib_tip, float* Atrib_val);     //OK

// comentarii literare : parametrii start_TS si end_TS se folosesc in
// urmatorul mod : pentru declaratii multiple (sau simple) retin
// locul in care a fost inserat primul id si ultimul id (avind in vedere
// ca e stiva); apoi tip_tablou, tip_simplu si tip_record ii folosesc
// ca sa parcurga tabela de simboluri si sa completeze cimpul de tip si/sau
// clasa
int Lista_Decl_Var(int* vadrel, int* vadrelNo, int* vdimv, int* vVarNo);                           //OK
int Decl_Var(int* vadrel, int* vadrelNo, int* vdimv, int* vVarNo);                                 //OK
int Decl_Cimp(int start_TS, int end_TS, int* vadrel, int* vadrelNo, int* vdeplrec, int* vdeplrecNo);   //OK                                       //OK
int Tip(int start_TS, int end_TS, int* vadrel, int* vadrelNo);         //OK
int Tip_Tablou(int start_TS, int end_TS, int* vadrel, int* vadrelNo);  //OK
int Tip_Simplu(int start_TS, int end_TS, int* vadrel, int* vadrelNo);  //OK
int Tip_Record(int start_TS, int end_TS, int* vadrel, int* vadrelNo);  //OK

int Paramecii(int *start_TS, int* end_TS, int* vadrel, int* vadrelNo); //OK
int Decl_Parameci(int *up_start_TS, int* up_end_TS, int* vadrel, int* vadrelNo);      //OK
int Expr(_tip *tip, _transm *transm);
int Expr_Logica();
int Conditie();
int Apel_Func(int loc);
int Apel_Proc(int loc);
int Termen(_tip *tip, _transm *transm);
int Factor(_tip *tip, _transm *transm);
// loc e pentru apelurile de proc si func pe care variabila le recunoaste
int Variabila(_tip *tip, _transm *transm, int* loc);
int Instr_While();
int Instr_Read();
int Instr_Print();
int Instr_If();
int Instr_For();
int Instr_Repeat();
int Atribuire();
int Lista_Altern();
int Instr_Case();
int Ordinale();

atom_valoare av;

// variabile si functii pentru lucrul cu un fisier .LEX
long int lex_handle;

int open_source(const char* filename)
{
  if ((lex_handle = open(filename, O_RDONLY)) == -1)
     return -1;
  return 1;
}
//---------------------------------------------------------------------------

int GetAtom(int* cod_lexical, void* val)
{
  short int dimensiune = 0;
  //char valoare[128];

  if (read(lex_handle, cod_lexical, sizeof(short int)) == -1) return 2;
  if (read(lex_handle, &dimensiune, sizeof(short int)) == -1) return 2;
  // printf("%d\n", dimensiune);	
  if ((dimensiune < 0) || (dimensiune > 127)) return 5;

  switch(*cod_lexical)
  {
   case MAI_MIC_EGAL    :
   case DIFERIT         :
   case MAI_MIC_STRICT  :
   case MAI_MARE_EGAL   :
   case MAI_MARE_STRICT :
   case ATRIBUIRE       :
   case DOUA_PUNCTE     :
   case PARANTEZA_S     :
   case PARANTEZA_PS    :
   case PUNCT_VIRGULA   :
   case PLUS            :
   case MINUS           :
   case INMULTIT        :
   case IMPARTIT        :
   case EGAL            :
   case PARANTEZA_PD    :
   case PARANTEZA_D     :
   case VIRGULA         :
   case PUNCT           :
   case VECTOR          :
        return 0;
   case REAL_EXPONENT   :
   case REAL_SIMPLU     :
        double d;
        if (read(lex_handle, &d, dimensiune) == -1) return 2;
        *((double*)val) = d; 
        //printf("%i %f %f\n", dimensiune, *((double*)val), d);
        return 0;
   case INTREG_BAZA     :
   case INTREG_SIMPLU   :
        short int i;
        if (read(lex_handle, &i, dimensiune) == -1) return 2;
        *((int*)val) = i;
        //printf("%i %i %i\n", dimensiune, *((int*)val), i);
        return 0;
   case CAR             :
        if (read(lex_handle, (char*)val, dimensiune) == -1) return 2;
        return 0;
   case SIR_CAR         :
   case IDENTIFICATOR   :
   case KEYWORD         :
        if (read(lex_handle, (char*)val, dimensiune) == -1) return 2;
        return 0;
   default :
        return 5;
  }
}
//---------------------------------------------------------------------------


int AnalizaSintactica(const char* filename)
{
  Init_Tab_Const();

  if (open_source(filename) == -1) return 1;
  av.valoare = (char*) new char[256];

  initGenCod("out.kob");

  int result = Program_Sursa();

  // afisarea tabelei de simboluri
  AllToScreen();

  endGenCod();

  return result;
}
//---------------------------------------------------------------------------


int Bloc(int* vadrel, int* vadrelNo, int* vdimv, int* vVarNo)
{
  int result;

  while(1)
  {
    if (av.cod_lexical != KEYWORD) break;
    if (strcmp((char*)av.valoare, "const") == 0)
    {
      result = GetAtom(&av.cod_lexical, av.valoare);
      if (result != 0) return result;

      result = Lista_Decl_Const();
      /*
        artificiu mic :-) pt a functiona kestii de genul
        const
        begin = 0;
        begin
        si pentru
      */
      if (result == -1) continue;
      if (result != 0) return result;
      if (Verificare_TS() == -1) return 40;
    }
    if (strcmp((char*)av.valoare, "var") == 0)
    {
      result = GetAtom(&av.cod_lexical, av.valoare);
      if (result != 0) return result;

      result = Lista_Decl_Var(vadrel, vadrelNo, vdimv, vVarNo);
      if (result == -1) continue;
      if (result != 0) return result;
      if (Verificare_TS() == -1) return 40;
    }

    if (strcmp((char*)av.valoare, "procedure") == 0)
    {
      int vadrel_procs = 0, dimv = 0, varNo = 0, vadrelNo_procs = 0;

      result = GetAtom(&av.cod_lexical, av.valoare);
      if (result != 0) return result;

      VNivel++;

      // trimit loc pentru a afla unde s'a introdus functia in TS
      result = Antet_Proc(&vadrel_procs, &vadrelNo_procs);
      if (result != 0) return result;

      //TS[Get_Bloc()].adr_start = ICod + 1;

      result = GetAtom(&av.cod_lexical, av.valoare);
      if (result != 0) return result;
      result = Bloc(&vadrel_procs, &vadrelNo_procs, &dimv, &varNo);
      if (result != 0) return result;

      TS[Get_Bloc()].dim_var = dimv;
      TS[Get_Bloc()].varNo   = varNo;
      //TS[Get_Bloc()].nivel  += 1;

      if (Verificare_TS() == -1) return 40;

      Sterge_Id(VNivel);
      Pop_Bloc();

      VNivel--;

      // result = GetAtom(&av.cod_lexical, av.valoare);
      // if (result != 0) return result;

      // verific dc e ;
      if (av.cod_lexical != PUNCT_VIRGULA) return 6;

      result = GetAtom(&av.cod_lexical, av.valoare);
      if (result != 0) return result;
      continue;
    }

    if (strcmp((char*)av.valoare, "function") == 0)
    {
      int vadrel_funcs = 0, dimv = 0, varNo = 0, vadrelNo_funcs = 0;

      result = GetAtom(&av.cod_lexical, av.valoare);
      if (result != 0) return result;

      VNivel++;

      // trimit loc pentru a afla unde s'a introdus functia in TS
      result = Antet_Func(&vadrel_funcs, &vadrelNo_funcs);
      if (result != 0) return result;

      //TS[Get_Bloc()].adr_start = ICod + 1;

      result = GetAtom(&av.cod_lexical, av.valoare);
      if (result != 0) return result;
      result = Bloc(&vadrel_funcs, &vadrelNo_funcs, &dimv, &varNo);
      if (result != 0) return result;

      TS[Get_Bloc()].dim_var = dimv;
      TS[Get_Bloc()].varNo   = varNo;
      //TS[Get_Bloc()].nivel  += 1;

      if (Verificare_TS() == -1) return 40;

      Sterge_Id(VNivel);
      Pop_Bloc();

      VNivel--;

      //result = GetAtom(&av.cod_lexical, av.valoare);
      //if (result != 0) return result;

      // verific dc e ;
      if (av.cod_lexical != PUNCT_VIRGULA) return 6;

      result = GetAtom(&av.cod_lexical, av.valoare);
      if (result != 0) return result;
      continue;
    }

    // nici unul din keywordurile din lista -> poate fi o instr compusa
    //return 8;
    break;
  }

  // ---Code gen follows
  // ? converteste fcall in call
  int i, loc = Get_Bloc();
  TS[loc].adr_start = ICod + 1;

  if (VNivel > 1)
  {
    i = TS[loc].incdom;
    while (i < ICod + 1)
    {
      if ( (tabCod[i]     == MV_FCALL) &&
           (tabCod[i + 1] == loc))
      {
        // inlocuiesc FCALL cu CALL si params aferenti
        tabCod[i]     = MV_CALL;
        tabCod[i + 1] = TS[loc].adr_start;
      }

      i += mvInstrSize[tabCod[i]];
    }
  }
  else
  {
    tabCod[0] = ICod + 1; //TS[loc].adr_start;
    tabCod[1] = *vdimv;
    tabCod[2] = *vVarNo;
    tabCod[3] = 0; // pentru compatibilitate ... what a piece o'junk !
  }
  // Code gen ends---

  result = Instr_Compusa();
  if (result != 0) return result;

  // ---Code gen follows
  // ? finalizare pentru un bloc - se termina procedura sau prg
  if (VNivel > 1)
  {
    genCod0(MV_RET);
  }
  else
  {
    genCod0(MV_STOP);
  }
  // Code gen ends---

  return 0;
}
//---------------------------------------------------------------------------


int Program_Sursa()
{
  int result;
  int vadrel = 0, vdimv = 0, vadrelNo = 0, vVarNo = 0;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;

  // verific daca exista program
  if ((av.cod_lexical != KEYWORD) ||
      (strcmp((char*)av.valoare, "program") != 0)) return 3;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;

  // verific dc e identificator
  if (av.cod_lexical != IDENTIFICATOR) return 4;

  // este identificatorul ce contine numele programului
  int loc = Inserare_Id((char*)av.valoare);
  TS[loc].clasa = nume_program;
  TS[loc].nivel = VNivel;
  Push_Bloc(loc);

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;

  // verific dc e ;
  if (av.cod_lexical != PUNCT_VIRGULA) return 6;

  // citire in avans
  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;

  // initializez ICod
  ICod = 3;

  result = Bloc(&vadrel, &vadrelNo, &vdimv, &vVarNo);
  if (result != 0) return result;

  // completez dimensiunea variabilelor pt. prg.
  // de fapt, e cam redundanta treaba...oricum se mai face o data in Bloc()
  TS[loc].dim_var = vdimv;
  TS[loc].varNo   = vVarNo;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;

  // verific dc e .
  if (av.cod_lexical != PUNCT) return 7;
  Pop_Bloc();

  return 0;
}
//---------------------------------------------------------------------------


int Lista_Decl_Var(int* vadrel, int* vadrelNo, int* vdimv, int* vVarNo)
{
  int result;
  while(1)
  {
    if (av.cod_lexical != IDENTIFICATOR) return -1;
    result = Decl_Var(vadrel, vadrelNo, vdimv, vVarNo);
    if (result == -1) break;
    if (result != 0) return result;

    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
    if (av.cod_lexical != PUNCT_VIRGULA) return 6;

    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
  }

  return 0;
}

int Tip(int start_TS, int end_TS, int* vadrel, int* vadrelNo)
{
  int result;
  if (av.cod_lexical != KEYWORD) return 14;

  result = Tip_Simplu(start_TS, end_TS, vadrel, vadrelNo);
  if (result == 0) return 0;
  else if (result != -1) return result;

  result = Tip_Record(start_TS, end_TS, vadrel, vadrelNo);
  if (result == 0) return 0;
  else if (result != -1) return result;

  result = Tip_Tablou(start_TS, end_TS, vadrel, vadrelNo);
  if (result == 0) return 0;
  else if (result != -1) return result;

  return 14;
}
//---------------------------------------------------------------------------


int Tip_Simplu(int start_TS, int end_TS, int* vadrel, int* vadrelNo)
{
  if (av.cod_lexical != KEYWORD) return -1;
  if ((strcmp((char*)av.valoare, "integer") == 0) ||
      (strcmp((char*)av.valoare, "real") == 0) ||
      (strcmp((char*)av.valoare, "char") == 0))
  {
    // deci avem un tip simplu -  trebuie completat in TS
    for(int i = start_TS; i <= end_TS; i++)
    {
      TS[i].adrel = *vadrel;
      TS[i].adrelNo = *vadrelNo;
      *vadrelNo += 1;

      if (strcmp((char*)av.valoare, "integer") == 0)
      {
        TS[i].tip = intreg;
        *vadrel += sizeof(int);
      }
      if (strcmp((char*)av.valoare, "real") == 0)
      {
        TS[i].tip = real;
        *vadrel += sizeof(double);
      }
      if (strcmp((char*)av.valoare, "char") == 0)
      {
        TS[i].tip = charr;
        *vadrel += sizeof(char);
      }

      // pentru pastrarea consistentei, ar fi fost bine sa se completeze
      // clasa in functia Tip()
      TS[i].clasa = nume_vars;

      // trebuie completat si ADREL
    }
    return 0;
  }

  // nu e tip simplu
  return -1;
}
//---------------------------------------------------------------------------


int Tip_Tablou(int start_TS, int end_TS, int* vadrel, int* vadrelNo)
{
  int result;
  int ind_min, ind_max;
  int dummy1 = 0;
  int dummy2 = 0;

  if (strcmp((char*)av.valoare, "array") != 0) return -1;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;

  if (av.cod_lexical != PARANTEZA_PS) return 15;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  if ((av.cod_lexical != INTREG_SIMPLU) && (av.cod_lexical != INTREG_BAZA))
    return 17;
  // s'a citit indicele minim
  ind_min = *((int*)av.valoare);

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  if (av.cod_lexical != VECTOR) return 18;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  if ((av.cod_lexical != INTREG_SIMPLU) && (av.cod_lexical != INTREG_BAZA))
    return 17;
  // s'a citit indicele maxim
  ind_max = *((int*)av.valoare);
  if (ind_max < ind_min) return 46;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  if (av.cod_lexical != PARANTEZA_PD) return 16;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  if (av.cod_lexical != KEYWORD) return 19;
  if (strcmp((char*)av.valoare, "of") != 0) return 19;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;

  // asta e un artificiu - pt. ca tip simplu completeaza adrel
  // dar in cazul matricilor il completeaza prost
  result = Tip_Simplu(start_TS, end_TS, &dummy1, &dummy2);
  if (result == -1) return 20;

  // avem completate cimpurile de tip din TS, completeaza informatiile de
  // indice minim/maxim si clasa
  for(int i = start_TS; i <= end_TS; i++)
  {
    // completez adrel
    TS[i].adrel   = *vadrel;
    TS[i].adrelNo = *vadrelNo;
    *vadrelNo += (ind_max - ind_min + 1);

    switch(TS[i].tip)
    {
      case intreg :
        *vadrel += sizeof(int) * (ind_max - ind_min + 1);
        break;
      case real :
        *vadrel += sizeof(double) * (ind_max - ind_min + 1);
        break;
      case charr :
        *vadrel += sizeof(char) * (ind_max - ind_min + 1);
        break;
    }

    TS[i].clasa   = nume_tablou;
    TS[i].ind_min = ind_min;
    TS[i].ind_max = ind_max;
  }

  return 0;
}
//---------------------------------------------------------------------------


int Tip_Record(int start_TS, int end_TS, int* vadrel, int* vadrelNo)
{
  int result, decl_nr = 0, vdeplrec = 0, vdeplrecNo = 0;

  if (strcmp((char*)av.valoare, "record") != 0) return -1;

  while(1)
  {
    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;

    if ((av.cod_lexical == KEYWORD) &&
        (strcmp((char*)av.valoare, "end") == 0))
    {
      if (decl_nr == 0) return 47; // nu poate fi record gol
      break;  // ok, ne putem intoarce, s'au terminat inregistrarile
    }

    decl_nr++;

    result = Decl_Cimp(start_TS, end_TS, vadrel, vadrelNo, &vdeplrec, &vdeplrecNo); // si aici trebuie vazut
    if (result != 0) return result;

    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
    if (av.cod_lexical != PUNCT_VIRGULA) return 6;
  }

  // este un tip record, trebuie sa'i completam informatiile de clasa
  for(int i = start_TS; i <= end_TS; i++)
  {
    TS[i].clasa = nume_record;
  }

  return 0;
}
//---------------------------------------------------------------------------


int Decl_Cimp(int start_TS, int end_TS, int* vadrel, int* vadrelNo, int* vdeplrec, int* vdeplrecNo)
{
  int result, cimp_start_TS = -1, cimp_end_TS;

  while(1)
  {
    if (av.cod_lexical != IDENTIFICATOR) return 4;

    // avem un identificator;
    if (cimp_start_TS == -1)
    {
      cimp_start_TS = Inserare_Id((char*)av.valoare);
      cimp_end_TS = cimp_start_TS;
      if (cimp_start_TS == -1) return 40;
      if (cimp_start_TS == -2) return 41;

      TS[cimp_start_TS].nivel = VNivel;
    }
    else
    {
      cimp_end_TS = Inserare_Id((char*)av.valoare);
      if (cimp_end_TS == -1) return 40;
      if (cimp_end_TS == -2) return 41;

      TS[cimp_end_TS].nivel = VNivel;
    }

    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
    if (av.cod_lexical == DOUA_PUNCTE) break;
    if (av.cod_lexical != VIRGULA) return 12;

    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
  }

  if (av.cod_lexical != DOUA_PUNCTE) return 13;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;

  // completarea adrel este corecta
  result = Tip_Simplu(cimp_start_TS, cimp_end_TS, vadrel, vadrelNo);
  if (result == -1) return 20;

  // cimpurile au tipurile completate; acum trebuie completata clasa lor
  // (nume_cimp) si lista_rec
  // recs va fi intotdeauna capul listei, recs_ant va fi elementul anterior
  rec_entry* recs = NULL, *recs_ant;

  for(int i = cimp_start_TS; i <= cimp_end_TS; i++)
  {
    // completez vdeplrec
    TS[i].deplrec   = *vdeplrec;
    TS[i].deplrecNo = *vdeplrecNo;
    *vdeplrecNo += 1;
    switch(TS[i].tip)
    {
      case intreg :
        *vdeplrec += sizeof(int);
        break;
      case real :
        *vdeplrec += sizeof(double);
        break;
      case charr :
        *vdeplrec += sizeof(char);
        break;
    }

    TS[i].clasa = nume_cimp;
    recs = NULL;
    for(int j = start_TS; j <= end_TS; j++)
    {
      recs_ant = new rec_entry;
      recs_ant->next = recs;
      recs_ant->index = j;
      recs = recs_ant;
    }
    TS[i].lista_rec = recs; // capul listei din lista
  }

  return 0;
}
//---------------------------------------------------------------------------


int Decl_Var(int* vadrel, int* vadrelNo, int* vdimv, int* vVarNo)
{
  int result, id_nr = 0, start_TS = -1, end_TS, startadrel = *vadrel,
      startadrelNo = *vadrelNo;

  while(1)
  {
    if (av.cod_lexical != IDENTIFICATOR) break;
    id_nr++;

    // avem un identificator;
    if (start_TS == -1)
    {
      start_TS = Inserare_Id((char*)av.valoare);
      end_TS = start_TS;
      if (start_TS == -1) return 40;
      if (start_TS == -2) return 41;

      TS[start_TS].nivel = VNivel;
    }
    else
    {
      end_TS = Inserare_Id((char*)av.valoare);
      if (end_TS == -1) return 40;
      if (end_TS == -2) return 41;

      TS[end_TS].nivel = VNivel;
    }

    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;

    if (av.cod_lexical == DOUA_PUNCTE) break;
    if (av.cod_lexical != VIRGULA) return 12;

    // citire in avans
    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
  }

  if (id_nr == 0) return 4;
  if (av.cod_lexical != DOUA_PUNCTE) return 13;

  // citire in avans
  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;

  result = Tip(start_TS, end_TS, vadrel, vadrelNo);
  if (result != 0) return result;

  // calclulez vdimv
  *vdimv += (*vadrel - startadrel);
  *vVarNo += (*vadrelNo - startadrelNo);

  if (Verificare_TS() == -1)
  {
    return 40;
  }
  // sau return Tip()
  return 0;
}
//---------------------------------------------------------------------------


int Lista_Decl_Const()
{
  int result;
  int loc;
  float  Atrib_val;
  _tip Atrib_tip;
  //int id_nr = 0; //!!!!

  while(1)
  {
    if (av.cod_lexical == IDENTIFICATOR)
    {
      // deci avem identificator -> constanta
      // verific daca identificarul nu a mai fost inserat
      loc = Inserare_Id((char*)av.valoare);
      // if (loc == -1) return 40;
      if (loc == -2) return 41;
      
      TS[loc].clasa = nume_const;
      TS[loc].nivel = VNivel;

      if (Verificare_TS() == -1) return 40; // eroare - e multiplu declarat

      result = GetAtom(&av.cod_lexical, av.valoare);
      if (result != 0) return result;
      // egal ?
      if (av.cod_lexical == EGAL)
      {
        //in avans
        result = GetAtom(&av.cod_lexical, av.valoare);
        if (result != 0) return result;

        //printf("%d\n", av.cod_lexical);
        result = Expr_Statica(&Atrib_tip, &Atrib_val);
        if ((result != -1) && (result != 0)) return result;

        // deci a venit si valoarea si tipul constantei - ce fain :-)
        if (result == -1)
        {
          if (av.cod_lexical != PUNCT_VIRGULA) return 6;
        }
        else if (result != 0) return result;
        
        TS[loc].val = Inserare_Const(Atrib_tip, Atrib_val);

        // verific ;
        //printf("%d %s", av.cod_lexical, (char*)av.valoare);
        // urmatorul atom
        //result = GetAtom(&av.cod_lexical, av.valoare);
        //if (result != 0) return result;
      }
      else return 9; // egal expected
    }
    else
    {
      //if ((av.cod_lexical != KEYWORD) ||
      //   (strcmp((char*)av.valoare, "begin") != 0)) return 4;
      return -1;  //
    }

    // urmatoarea
    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
  }

  // daca e numai const, fara nici un fel de lista de constante ?
  // return 0;
}
//---------------------------------------------------------------------------


int Expr_Statica(_tip* Atrib_tip, float* Atrib_val)
{
  int result;
  float Atrib_val1;
  _tip Atrib_tip1;
  enum _op {plus, minus, none};
  _op op;

  result = Termen_Static(Atrib_tip, Atrib_val);
  if ((result != 0) && (result != -1)) return result;

  while(1)
  {
    op = none;
    if (av.cod_lexical == PLUS) op = plus;
    else if (av.cod_lexical == MINUS) op = minus;

    if (op == none) return -1; // nu mai exista plus/minus

    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;

    result = Termen_Static(&Atrib_tip1, &Atrib_val1);
    if ((result != 0) && (result != -1)) return result;

    // avem tipul si valoarea noului termen
    if (*Atrib_tip != Atrib_tip1)
    {
      if ((*Atrib_tip == charr) || (Atrib_tip1 == charr))
      {
        //TS_Error(3);
        return 42;
      }
      if ((*Atrib_tip) == intreg) *Atrib_tip = real;
    }

    //result = GetAtom(&av.cod_lexical, av.valoare);
    //if (result != 0) return result;

    // acum fa operatiile
    if (op == plus)
    {
      *Atrib_val = *Atrib_val + Atrib_val1;
      if (*Atrib_tip == charr)
      {
        // verificare de range la char
        if (*Atrib_val > 255) *Atrib_val = 255 - *Atrib_val;
      }
    }
    else
    {
      *Atrib_val = *Atrib_val - Atrib_val1;
      // analog, range la 0
      if (*Atrib_val < 0) *Atrib_val = -(*Atrib_val);
    }
  }
}
//---------------------------------------------------------------------------


int Termen_Static(_tip* Atrib_tip, float* Atrib_val)
{
  int result;
  float Atrib_val1;
  _tip Atrib_tip1;
  enum _op {mul, per, mod, div, none};
  _op op;

  result = Factor_Static(Atrib_tip, Atrib_val);
  if (result != 0) return result;

  while(1)
  {
    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;

    // aici avem operator
    op = none;
    if (av.cod_lexical == INMULTIT) op = mul;
    else
    {
      if (av.cod_lexical == IMPARTIT) op = per;
      else
      {
        if (av.cod_lexical == KEYWORD)
        {
          if (strcmp((char*)av.valoare, "mod") == 0) op = mod;
          if (strcmp((char*)av.valoare, "div") == 0) op = div;
        }
      }
    }

    if (op == none) return -1;

    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;

    result = Factor_Static(&Atrib_tip1, &Atrib_val1);
    if (result != 0) return result;

    // avem tipul si valoarea noului factor
    if ((*Atrib_tip) != Atrib_tip1)
    {
      if ((*Atrib_tip == charr) || (Atrib_tip1 == charr))
      {
        //TS_Error(3);
        return 42;
      }
      if (*Atrib_tip == intreg) *Atrib_tip = real;
    }

    if (op == mul)
    {
      *Atrib_val = *Atrib_val * Atrib_val1;
      if (*Atrib_tip == charr) if (*Atrib_val > 255.0) *Atrib_val = 255.0 - *Atrib_val;
    }
    else
    if (op == per)
    {
      if (Atrib_val1 == 0)
      {
        //TS_Error(5);
        return 43;
      }

      *Atrib_val = *Atrib_val/Atrib_val1;

      if (*Atrib_tip == charr) *Atrib_val = (char)*Atrib_val;
    }

    // mai trebuie implementate si mod/div, dar nu acum

    /*
    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
    */
  }
}
//---------------------------------------------------------------------------


int Factor_Static(_tip* Atrib_tip, float* Atrib_val)
{
  int result;
  int loc;

  if (av.cod_lexical == IDENTIFICATOR)
  {
    loc = Cautare_Id((char*)av.valoare);
    if (loc == -1)
    {
      return 39;
    }
    if (TS[loc].val == nedefinit)
    {
      return 44;
    }
    if (TS[loc].clasa != nume_const)
    {
      return 45;
    }

    *Atrib_tip = Tab_Const[TS[loc].val].tip;
    *Atrib_val = Tab_Const[TS[loc].val].valoare;

    return 0;
  }
  
  if ((av.cod_lexical == INTREG_BAZA) || (av.cod_lexical == INTREG_SIMPLU))
  {
    *Atrib_tip = intreg;
    *Atrib_val = *((int*)av.valoare);
    return 0;
  }

  if ((av.cod_lexical == REAL_EXPONENT) || (av.cod_lexical == REAL_SIMPLU))
  {
    *Atrib_tip = real;
    *Atrib_val = *((double*)av.valoare);
    return 0;
  }

  if (av.cod_lexical == CAR)
  {
    *Atrib_tip = charr;
    *Atrib_val = *((char*)av.valoare);
    return 0;
  }

  // if (av.cod_lexical == SIR_CAR) return 0;
  if (av.cod_lexical != PARANTEZA_S) return 21;

  // citire in avans
  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  result = Expr_Statica(Atrib_tip, Atrib_val);
  if ((result != 0) && (result != -1)) return result;

  //result = GetAtom(&av.cod_lexical, av.valoare);
  //if (result != 0) return result;
  if (av.cod_lexical != PARANTEZA_D) return 22;
  return 0;
}
//---------------------------------------------------------------------------


int Antet_Func(int* vadrel, int* vadrelNo)
{
  int result;
  int start_TS = -1, end_TS = -1;
  int dummy1, dummy2;
  int loc;

  if (av.cod_lexical != IDENTIFICATOR) return 4;

  // immm, deci e o functie - sa o inseram in TS
  loc = Inserare_Id((char*)av.valoare);
  TS[loc].nivel = VNivel - 1; // artificiu, functia tre' sa fie pe nivel de sus
  TS[loc].incdom = ICod + 1;
  TS[loc].adr_start = -1;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;

  result = Paramecii(&start_TS, &end_TS, vadrel, vadrelNo);
  if ((result != 0) && (result != -1)) return result;

  // -1 inseamna ca nu are parametri
  if (result != -1)
  {
    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
  }
  if (av.cod_lexical != DOUA_PUNCTE) return 13;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;

  // se completeaza tipul functiei
  result = Tip_Simplu(loc, loc, &dummy1, &dummy2); // trebuie vazut cum se face aici !!!
  TS[loc].adrel   = -2;
  TS[loc].adrelNo = -2;
  if (result == -1) return 20;
  if (result != 0) return result;

  // acum se fac si alte completari
  // pentru rezolvarea apelurilor zise forward
  Push_Bloc(loc);
  // nr_par
  // nr_par
  if (start_TS != -1) TS[loc].nr_par = end_TS - start_TS + 1;
  else TS[loc].nr_par = 0;
  // lista de parameci :-)
  pf_entry* pf = NULL, *pf_ant;
  TS[loc].clasa = nume_funct;

  if (start_TS != -1)
  {
    for(int i = start_TS; i <= end_TS; i++)
    {
      pf_ant = new pf_entry;
      pf_ant->next = pf;
      pf_ant->tip = TS[i].tip;
      if (TS[i].clasa == nume_param) pf_ant->transm = valoare;
      else pf_ant->transm = referinta;
      pf = pf_ant;
    }
    TS[loc].lista_par = pf; // capul listei din lista :-)

    // lista trebuie inversata, pentru a fi mai usor la verificarea
    // parametrilor (in Apel_func si Apel_proc)
    pf_entry *pf1 = TS[loc].lista_par, *pf2, *pf3;

    pf2       = pf1->next;
    pf1->next = NULL;

    while(pf2 != NULL)
    {
      pf3       = pf2->next;
      pf2->next = pf1;
      pf1       = pf2;
      pf2       = pf3;
    }

    TS[loc].lista_par = pf1;
  }

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  if (av.cod_lexical != PUNCT_VIRGULA) return 6;

  return 0;
}
//---------------------------------------------------------------------------


int Antet_Proc(int* vadrel, int* vadrelNo)
{
  int result;
  int start_TS = -1, end_TS = -1;
  int loc;

  if (av.cod_lexical != IDENTIFICATOR) return 4;

  // immm, deci e o functie - sa o inseram in TS
  loc               = Inserare_Id((char*)av.valoare);
  TS[loc].nivel     = VNivel - 1; // artificiu, functia tre' sa fie pe nivel de sus
  TS[loc].clasa     = nume_proc;
  TS[loc].adrel     = -1;
  TS[loc].adrelNo   = -1;
  TS[loc].adr_start = -1;
  TS[loc].incdom    = ICod + 1;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  result = Paramecii(&start_TS, &end_TS, vadrel, vadrelNo); // AICI DE VAZUT !!!
  if ((result != 0) && (result != -1)) return result;

  // -1 inseamna ca nu are parametri
  if (result != -1)
  {
    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
  }
  // test de ;
  if (av.cod_lexical != PUNCT_VIRGULA) return 6;

  // acum se fac si alte completari
  // pentru rezolvarea apelurilor zise forward
  Push_Bloc(loc);
  // nr_par
  if (start_TS != -1) TS[loc].nr_par = end_TS - start_TS + 1;
  else TS[loc].nr_par = 0;

  if (start_TS != -1)
  {
    // lista de parameci :-)
    pf_entry* pf = NULL, *pf_ant;
    for(int i = start_TS; i <= end_TS; i++)
    {
      pf_ant = new pf_entry;
      pf_ant->next = pf;
      pf_ant->tip = TS[i].tip;
      if (TS[i].clasa == nume_param) pf_ant->transm = valoare;
      else pf_ant->transm = referinta;
      pf = pf_ant;
    }
    TS[loc].lista_par = pf; // capul listei din lista :-)

    // lista trebuie inversata, pentru a fi mai usor la verificarea
    // parametrilor (in Apel_func si Apel_proc)
    pf_entry *pf1 = TS[loc].lista_par, *pf2, *pf3;

    pf2       = pf1->next;
    pf1->next = NULL;

    while(pf2 != NULL)
    {
      pf3       = pf2->next;
      pf2->next = pf1;
      pf1       = pf2;
      pf2       = pf3;
    }

    TS[loc].lista_par = pf1;
  }

  return 0;
}
//---------------------------------------------------------------------------


int Paramecii(int *start_TS, int* end_TS, int* vadrel, int* vadrelNo)
{
  int result, supl_start;
  int firstPass = 0;

  if (av.cod_lexical != PARANTEZA_S) return -1;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;

  while(1)
  {
    // artificiu
    if (firstPass == 0)
    {
      result    = Decl_Parameci(start_TS, end_TS, vadrel, vadrelNo);
      firstPass = 1;
    }
    else result = Decl_Parameci(&supl_start, end_TS, vadrel, vadrelNo);
    if (result != 0) return result;

    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;

    if (av.cod_lexical != PUNCT_VIRGULA) break;

    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
  }

  if (av.cod_lexical != PARANTEZA_D) return 22;
  return 0;
}
//---------------------------------------------------------------------------


int Decl_Parameci(int* up_start_TS, int* up_end_TS, int* vadrel, int* vadrelNo)
{
  int result;
  // default, se pp transmis prin valoare, pina la noi ordine
  _class clasa = nume_param;
  int start_TS = -1, end_TS = -1;

  if (av.cod_lexical == KEYWORD)
    if (strcmp((char*)av.valoare, "var") != 0)
    {
      return 24;
    }
    else
    {
      // e un parametru transmis prin referinta
      result = GetAtom(&av.cod_lexical, av.valoare);
      if (result != 0) return result;
      clasa = nume_paramv;
    }

  // ok, it's not a keyword
  while(1)
  {
    if (av.cod_lexical != IDENTIFICATOR) return 4;

    // avem un identificator;
    if (start_TS == -1)
    {
      start_TS = Inserare_Id((char*)av.valoare);
      end_TS = start_TS;
      //if (start_TS == -1) return 40;
      if (start_TS == -2) return 41;

      TS[start_TS].nivel = VNivel;
    }
    else
    {
      end_TS = Inserare_Id((char*)av.valoare);
      //if (end_TS == -1) return 40;
      if (end_TS == -2) return 41;

      TS[end_TS].nivel = VNivel;
    }

    // bring in the next atom
    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;

    if (av.cod_lexical != VIRGULA) break;

    // next atom
    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
  }

  // we should find at least :
  if (av.cod_lexical != DOUA_PUNCTE) return 13;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  // tip_simplu va completa si adrel
  result = Tip_Simplu(start_TS, end_TS, vadrel, vadrelNo); // analog !!!
  if (result == -1) return 20;
  if (result != 0) return result;

  // se completeaza parametrii cu informatie; tipul il avem completat
  *up_start_TS = start_TS;
  *up_end_TS   = end_TS;

  for(int i = start_TS; i <= end_TS; i++)
  {
    TS[i].clasa = clasa;
  }

  // de returnat
  *up_start_TS = start_TS;
  *up_end_TS = end_TS;

  return 0;
}
//---------------------------------------------------------------------------


int Instr_Compusa()
{
  int result;

  // verific daca exista begin
  if ((av.cod_lexical != KEYWORD) ||
      (strcmp((char*)av.valoare, "begin") != 0)) return -1;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;

  while(1)
  {
    // suport pentru instructiunea vida
    if ((av.cod_lexical == KEYWORD) &&
        (strcmp((char*)av.valoare, "end") == 0)) break;

    result = Instr();
    if (result != 0) return result;

    //result = GetAtom(&av.cod_lexical, av.valoare);
    //if (result != 0) return result;
    // verific ; sau end
    if (av.cod_lexical != PUNCT_VIRGULA)
    {
      if ((av.cod_lexical != KEYWORD) &&
          (strcmp((char*)av.valoare, "end") != 0)) return 11;
      return 6; // sau break;
    }
    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
  }

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  
  return 0;
}
//---------------------------------------------------------------------------


int Instr()
{
  int result;

  result = Instr_Read();
  if (result == 0) return 0;
  if ((result != 0) && (result != -1)) return result;

  result = Instr_While();
  if (result == 0) return 0;
  if ((result != 0) && (result != -1)) return result;

  result = Instr_Repeat();
  if (result == 0) return 0;
  if ((result != 0) && (result != -1)) return result;

  result = Instr_If();
  if (result == 0) return 0;
  if ((result != 0) && (result != -1)) return result;

  result = Instr_Compusa();
  if (result == 0) return 0;
  if ((result != 0) && (result != -1)) return result;

  result = Instr_For();
  if (result == 0) return 0;
  if ((result != 0) && (result != -1)) return result;

  result = Instr_Print();
  if (result == 0) return 0;
  if ((result != 0) && (result != -1)) return result;

  result = Instr_Case();
  if (result == 0) return 0;
  if ((result != 0) && (result != -1)) return result;

  result = Atribuire();
  if (result == 0) return 0;

  if ((result != 0) && (result != -1)) return result;

  return 33;
}
//---------------------------------------------------------------------------


int Instr_While()
{
  int result, label1, label2;

  // verifica daca este o instructiune de tip while
  if ((av.cod_lexical != KEYWORD) ||
      (strcmp((char*)av.valoare, "while") != 0)) return -1;

  // da, este; urmatorul atom
  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;

  // ---Code gen follows
  // ?
  label1 = ICod + 1;
  // Code gen ends---

  result = Conditie();
  if (result != 0) return result;

  // ---Code gen follows
  // ?
  label2 = ICod + 1;
  genCod1(MV_FJP, 0);
  // Code gen ends---

  // e do ?
  //result = GetAtom(&av.cod_lexical, av.valoare);
  //if (result != 0) return result;
  if ((av.cod_lexical != KEYWORD) ||
      (strcmp((char*)av.valoare, "do") != 0)) return -1;

  // gata pentru instructiune
  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  
  result = Instr();
  if (result != 0) return result;

  // ---Code gen follows
  // ?
  genCod1(MV_UJP, label1);
  tabCod[label2 + 1] = ICod + 1;
  // Code gen ends---

  return 0;
}
//---------------------------------------------------------------------------


int Conditie()
{
  int result;

  while(1)
  {
    if ((av.cod_lexical == KEYWORD) &&
        (strcmp((char*)av.valoare, "not") == 0))
    {
      genCod0(MV_NOT);
      result = GetAtom(&av.cod_lexical, av.valoare);
      if (result != 0) return result;
    }

    result = Expr_Logica();
    if (result != 0) return result;

    if (av.cod_lexical != KEYWORD) break;
    else
    {
      if ((strcmp((char*)av.valoare, "and") != 0) &&
          (strcmp((char*)av.valoare, "or") != 0))
         break;
      if (strcmp((char*)av.valoare, "and") == 0) genCod0(MV_AND);
      else genCod0(MV_AND);   
    }

    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
  }

  //result = GetAtom(&av.cod_lexical, av.valoare);
  //if (result != 0) return result;
  return 0;
}
//---------------------------------------------------------------------------


int Expr_Logica()
{
  int result;
  _tip tip1, tip2;
  _transm transm1, transm2;
  enum _ops {rop_egal, rop_diferit, rop_mme, rop_mmae, rop_mms, rop_mmas} op;

  result = Expr(&tip1, &transm1);
  if ((result != 0) && (result != -1)) return result;

  switch(av.cod_lexical)
  {
    case EGAL            :
      op = rop_egal;
      break;
    case DIFERIT         :
      op = rop_diferit;
      break;
    case MAI_MIC_EGAL    :
      op = rop_mme;
      break;
    case MAI_MARE_EGAL   :
      op = rop_mmae;
      break;
    case MAI_MIC_STRICT  :
      op = rop_mms;
      break;
    case MAI_MARE_STRICT :
      op = rop_mmas;
      break;
    default :
         return 28;      
  }
  
  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  result = Expr(&tip2, &transm2);
  if ((result != 0) && (result != -1)) return result;

  if ((tip1 != tip2) && ((tip1 == charr) || (tip2 == charr)))
  {
    return 69;
  }

  // ---Code gen follows
  // ? expresie relationala
  if (tip1 != tip2)
  {
    if (tip1 == intreg) genCod2(MV_CONV, real, 1);
    else genCod2(MV_CONV, real, 0);
  }

  switch(op)
  {
    case rop_egal :
      genCod0(MV_EQU);
      break;
    case rop_diferit :
      genCod0(MV_NEQ);
      break;
    case rop_mme :
      genCod0(MV_LEQ);
      break;
    case rop_mms :
      genCod0(MV_LES);
      break;
    case rop_mmas :
      genCod0(MV_GRT);
      break;
    case rop_mmae :
      genCod0(MV_GEQ);
      break;
  }
  // Code gen ends---

  return 0;
}
//---------------------------------------------------------------------------


int Expr(_tip *tip, _transm *transm)
{
  int result;
  _tip tip1;
  _transm transm1;
  enum _op {plus, minus, none};
  _op op;

  result = Termen(tip, transm);
  if ((result != 0) && (result != -1)) return result;

  while(1)
  {
    // aici avem operator
    op = none;
    if (av.cod_lexical == PLUS) op = plus;
    else if (av.cod_lexical == MINUS) op = minus;

    if (op == none) return -1; // nu mai exista plus/minus

    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;

    result = Termen(&tip1, &transm1);
    if ((result != 0) && (result != -1)) return result;

    // avem deja un operator, deci transmisia e prin valoare
    transm = valoare;

    // verificari de tip
    if ((tip1 == charr) && (*tip == charr))
    {
      return 42; // tipuri incompatibile in operatie
    }

    // ---Code gen follows
    // ?
    if (*tip != tip1)
    {
      if (*tip == intreg)
      {
        genCod2(MV_CONV, real, 1);
      }
      else
      {
        genCod2(MV_CONV, real, 0);
      }
    }
    if (op == plus)
    {
      genCod0(MV_ADD);
    }
    else
    {
      genCod0(MV_SUB);
    }
    // Code gen ends---

    if (tip1 == *tip)
    {
      *tip = tip1;
    }
    else
    {
      *tip = real;
    }
  }
}
//---------------------------------------------------------------------------


int Termen(_tip *tip, _transm *transm)
{
  int result;
  _tip tip1;
  _transm transm1;
  enum _op {mul, per, mod, div, none};
  _op op;

  result = Factor(tip, transm);
  if (result != 0) return result;

  while(1)
  {
    // result = GetAtom(&av.cod_lexical, av.valoare);
    // if (result != 0) return result;

    // aici avem operator
    op = none;
    if (av.cod_lexical == INMULTIT) op = mul;
    else
    {
      if (av.cod_lexical == IMPARTIT) op = per;
      else
      {
        if (av.cod_lexical == KEYWORD)
        {
          if (strcmp((char*)av.valoare, "mod") == 0) op = mod;
          if (strcmp((char*)av.valoare, "div") == 0) op = div;
        }
      }
    }

    if (op == none) return -1;

    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;

    result = Factor(&tip1, &transm1);
    if (result != 0) return result;

    // ---Code gen follows
    // ?
    if (*tip != tip1)
    {
      if (*tip == intreg)
      {
        genCod2(MV_CONV, real, 1);
      }
      else
      {
        genCod2(MV_CONV, real, 0);
      }
    }

    switch(op)
    {
      case per :
        genCod0(MV_DIV);
        break;
      case mul :
        genCod0(MV_MUL);
        break;
      case div :
        genCod0(MV_MOD);
        break;
    }
    // Code gen ends---

    if ((op == mod) || (op == div))
    {
      if ((tip1 != intreg) || (*tip != intreg))
      {
        return 42;
      }
      *tip = intreg;
    }
    else
    {
      if ((tip1 == charr) || (*tip == charr))
      {
        return 42;
      }
      if (op == per)
      {
        *tip = real;
      }
      else
      {
        if (tip1 == *tip)
        {
          *tip = tip1;
        }
        else
        {
          *tip = real;
        }
      }
    }
  }
}
//---------------------------------------------------------------------------


int Factor(_tip *tip, _transm *transm)
{
  int result, loc;
  //_tip tip1;
  _transm transm1;

  //if (av.cod_lexical == IDENTIFICATOR) return 0;
  if ((av.cod_lexical == INTREG_BAZA) || (av.cod_lexical == INTREG_SIMPLU))
  {
    // ---Code gen follows
    // ? aduce in vf. stivei o constanta
    genCod1(MV_LODI, Inserare_Const(intreg, *((int*)av.valoare)));
    // Code gen ends---

    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
    *tip    = intreg;
    *transm = valoare;
    return 0;
  }
  if ((av.cod_lexical == REAL_EXPONENT) || (av.cod_lexical == REAL_SIMPLU))
  {
    // ---Code gen follows
    // ? aduce in vf. stivei o constanta
    genCod1(MV_LODI, Inserare_Const(real, *((double*)av.valoare)));
    // Code gen ends---

    *tip = real;
    *transm = valoare;
    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
    return 0;
  }
  if (av.cod_lexical == CAR)
  {
    // ---Code gen follows
    // ? aduce in vf. stivei o constanta
    genCod1(MV_LODI, Inserare_Const(charr, *((char*)av.valoare)));
    // Code gen ends---

    *tip = charr;
    *transm = valoare;
    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
    return 0;
  }

  if (av.cod_lexical == PARANTEZA_S)
  {
    result = Expr(tip, transm);
    if ((result != 0) && (result != -1)) return result;

    if (av.cod_lexical != PARANTEZA_D) return 22;
  }

  result = Variabila(tip, transm, &loc);
  if (result != 0) return result;

  // verific de apel de functie
  if (TS[loc].clasa == nume_funct)
  {
    // ---Code gen follows
    // ? aloca memorie pentru variabilele locale functiei
    genCod2(MV_RBM, TS[loc].varNo, 2);
    // Code gen ends---
    result = Apel_Func(loc);

    // OARE !?
    if (TS[loc].adr_start < 0) genCod3(MV_FCALL, loc, TS[loc].nr_par, TS[loc].nivel + 1);
    else genCod3(MV_CALL, TS[loc].adr_start, TS[loc].nr_par, TS[loc].nivel + 1);

    return 0;
  }

  // ar fi trebuit sa fie macar (
  return 0;
  
  // citire in avans
  // result = GetAtom(&av.cod_lexical, av.valoare);
  // if (result != 0) return result;
  /*
  transm1 = valoare;
  result = Variabila(tip, &transm1, &loc);
  if (result == -3) return 50; // am gasit un apel de procedura
  if (result == 0)
  {
    //result = GetAtom(&av.cod_lexical, av.valoare);
    //if (result != 0) return result;
    *transm = transm1;
    return 0;
  }
  if ((result != 0) && (result != -1) && (result != -2)) return result;
  if (result == -2)
  {
    // ---Code gen follows
    // ? aloca memorie pentru variabilele locale functiei
    genCod2(MV_RBM, TS[loc].varNo, 2);
    // Code gen ends---

    result = Apel_Func(loc);

    // OARE !?
    if (TS[loc].adr_start < 0) genCod3(MV_FCALL, loc, TS[loc].nr_par, TS[loc].nivel);
    else genCod3(MV_CALL, TS[loc].adr_start, TS[loc].nr_par, TS[loc].nivel);

    *tip = TS[loc].tip;
    *transm = valoare;
    if (result == 0)
    {
      return 0;
    }
    if ((result != 0) && (result != -1)) return result;
  }

  // nu e apel de functie
  if (av.cod_lexical != PARANTEZA_S) return 21;
  result = Expr(tip, transm);
  if ((result != 0) && (result != -1)) return result;

  //result = GetAtom(&av.cod_lexical, av.valoare);
  //if (result != 0) return result;
  if (av.cod_lexical != PARANTEZA_D) return 22;
  return 0;
  */
}
//---------------------------------------------------------------------------


int Apel_Func(int loc)
{
  int result;
  _tip tip1;
  _transm transm1;
  pf_entry *pf;

  //result = Cautare_Id((char*)av.valoare);
  //if (result == -1) return 39;
  
  //if (av.cod_lexical != IDENTIFICATOR) return -1;
  //result = GetAtom(&av.cod_lexical, av.valoare);
  //if (result != 0) return result;

  if ((TS[loc].nr_par > 0) && (av.cod_lexical != PARANTEZA_S)) return 68;
  if ((TS[loc].nr_par == 0) && (av.cod_lexical == PARANTEZA_S)) return 67;

  if (av.cod_lexical == PARANTEZA_S)
  {
    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
  }

  pf = TS[loc].lista_par;

  // verificarea numarului de parametri
  if (TS[loc].nr_par > 0)
  {
    while(1)
    {
      result = Expr(&tip1, &transm1);
      if ((result != 0) && (result != -1)) return result;

      // verificarea parametrilor la apelul de functie - tip si transmisie
      if ((pf->tip != tip1) && (pf->tip != real) && (tip1 != intreg))
      {
        return 66;
      }

      if ((pf->transm == referinta) && (transm1 != referinta))
      {
        return 52;
      }

      pf = pf->next;

      if (av.cod_lexical != VIRGULA) break; // atunci e paranteza sau eroare

      if (pf == NULL)
      {
        return 67;
      }

      result = GetAtom(&av.cod_lexical, av.valoare);
      if (result != 0) return result;
    }

    if (pf != NULL)
    {
      return 68;
    }

    if (av.cod_lexical != PARANTEZA_D) return 22;

    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
  }

  return 0;
}
//---------------------------------------------------------------------------


// TREBUIE VERIFICATA
int Atribuire()
{
  int     result, loc, gasit;
  _tip    tip, tip1;
  _transm transm1;
  //char    nume[255];

  if (av.cod_lexical != IDENTIFICATOR) return -1;

  // caut identificatorul
  loc = Cautare_Id((char*)av.valoare);
  if (loc == -1) return 39; // nu e declarata

  // urmatorul atom
  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;

  switch(TS[loc].clasa)
  {
    case nume_proc   :
      // ---Code gen follows
      // ? aloca memorie pentru variabilele locale procedurii
      genCod2(MV_RBM, TS[loc].varNo, 1);
      // Code gen ends---

      // pentru pastrarea compatibilitatii, se citeste un atom in prealabil
      // result = GetAtom(&av.cod_lexical, av.valoare);
      // if (result != 0) return result;

      result = Apel_Proc(loc);
      if (result != 0) return result;

      // MODIFIED
      if (TS[loc].adr_start < 0) genCod3(MV_FCALL, loc, TS[loc].nr_par, TS[loc].nivel + 1);
      else genCod3(MV_CALL, TS[loc].adr_start, TS[loc].nr_par, TS[loc].nivel + 1);

      return 0;

    case nume_funct  :
      // e si altceva pe linga numele de functie ?
      // alta eroare trebuie sa returneze de fapt, da' ma rog
      if (av.cod_lexical != ATRIBUIRE) return 52;

      // numele functiei nu poate fi atribuit decit in interiorul ei
      if (Get_Bloc() != loc) return 74;

      // ---Code gen follows
      // ?
      genCod2(MV_LODA, VNivel, TS[loc].adrelNo);
      // Code gen ends---
      
      tip = TS[loc].tip;

      break;

    case nume_param  :
    case nume_vars   :
      // ---Code gen follows
      // ?
      genCod2(MV_LODA, TS[loc].nivel, TS[loc].adrelNo);
      // Code gen ends---

      tip = TS[loc].tip;

      break;

    case nume_tablou :
      // verific de [
      if (av.cod_lexical != PARANTEZA_PS) return 73;

      result = GetAtom(&av.cod_lexical, av.valoare);
      if (result != 0) return result;

      result = Expr(&tip1, &transm1);
      if ((result != 0) && (result != -1)) return result;
      if (tip1 != intreg) return 55; // un tablou nu poate fi indexat decit de intreg

      // ---Code gen follows
      // ? secventa de verificare a indicelui
      genCod0(MV_COPI);
      genCod1(MV_LODI, Inserare_Const(intreg, TS[loc].ind_min));
      genCod0(MV_LES);
      genCod1(MV_FJP, ICod + 5);
      genCod1(MV_ERR, 71);
      genCod0(MV_COPI);
      genCod1(MV_LODI, Inserare_Const(intreg, TS[loc].ind_max));
      genCod0(MV_GRT);
      genCod1(MV_FJP, ICod + 5);
      genCod1(MV_ERR, 72);

      // ? secventa de aducere a adresei in vf. stivei
      genCod1(MV_LODI, Inserare_Const(intreg, TS[loc].ind_min));
      genCod0(MV_SUB);
      genCod2(MV_LODA, TS[loc].nivel, TS[loc].adrelNo);
      genCod0(MV_ADD);
      // Code gen ends---

      if (av.cod_lexical != PARANTEZA_PD) return 16;

      // urmatorul atom
      result = GetAtom(&av.cod_lexical, av.valoare);
      if (result != 0) return result;

      tip = TS[loc].tip;
     break;

    case nume_record :
      // verific .
      if (av.cod_lexical != PUNCT) return 7;

      result = GetAtom(&av.cod_lexical, av.valoare);
      if (result != 0) return result;

      if (av.cod_lexical != IDENTIFICATOR) return 4;

      // avem numele cimpului si numele variabilei; verific daca cimpul e
      // valid
      record_list* cap;
      gasit = 0;

      // caut acum orice nume cimp care are ca parinte pe loc adica nume
      for(int i = TS_Virf; i > 0; i--)
      {
        if (TS[i].clasa == nume_cimp)
        {
          cap = TS[i].lista_rec;
          while(cap != NULL)
          {
            if ((cap->index == loc) &&
               (strcmp(TS[i].nume, (char*)av.valoare) == 0))
            {
              gasit = 1;
              tip    = TS[cap->index].tip; // returneza tipul recordului
              // ---Code gen follows
              // ? incarcare a valorii cimpului de structura
              genCod1(MV_LODI, Inserare_Const(intreg, TS[cap->index].deplrecNo));
              genCod0(MV_MVRX);
              genCod2(MV_LODX, TS[loc].nivel, TS[loc].adrelNo);
              // Code gen ends---
              break;
            }
            cap = cap->next;
          }
        }
      }

      if (gasit == 0) return 48; // nu e membru al recordului;
      break;

    default     :
      return 52;
  }

  if (av.cod_lexical != ATRIBUIRE) return 30;
  
  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;

  result = Expr(&tip1, &transm1);
  if ((result != 0) && (result != -1)) return result;

  // fac verificari de tipuri
  if (tip1 != tip)
  {
    if ((tip == intreg) || (tip == charr) || (tip1 == charr))
    {
      return 42; //tipuri incompatibile
    }

    // ---Code gen follows
    // ? conversie
    genCod2(MV_CONV, real, 0);
    // Code gen ends---
  }
  genCod0(MV_STO);

  return 0;

  /*
  result = Variabila(&tip, &transm, &loc, call_atribuire);
  if (result == -2) return 0;
  if ((result != 0) && (result != -3)) return result;
  if (result == -3)
  {
    // we got a procedure call
    // ---Code gen follows
    // ? aloca memorie pentru variabilele locale functiei
    genCod2(MV_RBM, TS[loc].varNo, 2);
    // Code gen ends---

    result = Apel_Proc(loc);

    // OARE !?
    if (TS[loc].adr_start < 0) genCod3(MV_FCALL, loc, TS[loc].nr_par, TS[loc].nivel);
    else genCod3(MV_CALL, TS[loc].adr_start, TS[loc].nr_par, TS[loc].nivel);

    if (result != 0) return result;
    return 0;
  }

  if (av.cod_lexical != ATRIBUIRE) return 30;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;

  result = Expr(&tip1, &transm1);
  if ((result != 0) && (result != -1)) return result;

  // fac verificari de tipuri
  if (tip1 != tip)
  {
    if ((tip == intreg) || (tip == charr) || (tip1 == charr))
    {
      return 42; //tipuri incompatibile
    }

    // ---Code gen follows
    // ? conversie
    genCod2(MV_CONV, real, 0);
    // Code gen ends---
  }
  genCod0(MV_STO);

  return 0;
  */
}
//---------------------------------------------------------------------------


// TREBUIE VERIFICATA
int Variabila(_tip *tip, _transm *transm, int* loc)
{
  int     result, gasit;
  _tip    tip1;
  _transm transm1;
  //char    nume[255];

  if (av.cod_lexical != IDENTIFICATOR) return -1;

  // verificare generala - nu se face verificare de tip
  *loc = Cautare_Id((char*)av.valoare);
  if (*loc == -1) return 39; // nu e declarata

  switch(TS[*loc].clasa)
  {
    case nume_const  :
      // ---Code gen follows
      // ? incarca in vf. stivei constanta de la indexul din Tab_Const
      genCod1(MV_LODI, TS[*loc].val);
      // Code gen ends---

      *tip    = Tab_Const[TS[*loc].val].tip;
      *transm = valoare;
      break;

    case nume_funct  :
      // ---Code gen follows
      // ?
      genCod2(MV_LODA, TS[*loc].nivel + 1, TS[*loc].adrelNo);
      // Code gen ends---

      *tip = TS[*loc].tip;
      *transm = valoare;
      break;

    case nume_param  :
    case nume_vars   :
      // ---Code gen follows
      // ?
      genCod2(MV_LOD, TS[*loc].nivel, TS[*loc].adrelNo);
      // Code gen ends---

      *tip = TS[*loc].tip;
      *transm = referinta;
      break;

    case nume_paramv :
      // ---Code gen follows
      // ?
      genCod2(MV_LOD, TS[*loc].nivel, TS[*loc].adrelNo);
      // Code gen ends---

      *tip = TS[*loc].tip;
      *transm = valoare;
      break;
      
    case nume_record :
      // verific .
      result = GetAtom(&av.cod_lexical, av.valoare);
      if (result != 0) return result;

      if (av.cod_lexical != PUNCT) return 7;

      result = GetAtom(&av.cod_lexical, av.valoare);
      if (result != 0) return result;

      if (av.cod_lexical != IDENTIFICATOR) return 4;

      // avem numele cimpului si numele variabilei; verific daca cimpul e
      // valid
      record_list* cap;
      gasit = 0;

      // caut acum orice nume cimp care are ca parinte pe loc adica nume
      for(int i = TS_Virf; i > 0; i--)
      {
        if (TS[i].clasa == nume_cimp)
        {
          cap = TS[i].lista_rec;
          while(cap != NULL)
          {
            if ((cap->index == *loc) &&
               (strcmp(TS[i].nume, (char*)av.valoare) == 0))
            {
              gasit = 1;
              *tip    = TS[cap->index].tip; // returneza tipul recordului
              *transm = referinta;
              // ---Code gen follows
              // ? incarcare a valorii cimpului de structura
              genCod1(MV_LODI, Inserare_Const(intreg, TS[cap->index].deplrecNo));
              genCod0(MV_MVRX);
              genCod2(MV_LODX, TS[*loc].nivel, TS[*loc].adrelNo);
              // Code gen ends---
              break;
            }
            cap = cap->next;
          }
        }
      }

      if (gasit == 0) return 48; // nu e membru al recordului;

      break;

    case nume_tablou :
      // verific de paranteza [
      result = GetAtom(&av.cod_lexical, av.valoare);
      if (result != 0) return result;

      if (av.cod_lexical != PARANTEZA_PS) return 73;

      result = GetAtom(&av.cod_lexical, av.valoare);
      if (result != 0) return result;

      result = Expr(&tip1, &transm1);
      if ((result != 0) && (result != -1)) return result;
      if (tip1 != intreg) return 55; // un tablou nu poate fi indexat decit de intreg

      // ---Code gen follows
      // ? secventa de verificare a indicelui
      genCod0(MV_COPI);
      genCod1(MV_LODI, Inserare_Const(intreg, TS[*loc].ind_min));
      genCod0(MV_LES);
      genCod1(MV_FJP, ICod + 5);
      genCod1(MV_ERR, 71);
      genCod0(MV_COPI);
      genCod1(MV_LODI, Inserare_Const(intreg, TS[*loc].ind_max));
      genCod0(MV_GRT);
      genCod1(MV_FJP, ICod + 5);
      genCod1(MV_ERR, 72);

      // ? aducerea valorii in vf stivei
      genCod1(MV_LODI, Inserare_Const(intreg, TS[*loc].ind_min));
      genCod0(MV_SUB);
      genCod0(MV_MVRX);
      genCod2(MV_LODX, TS[*loc].nivel, TS[*loc].adrelNo);
      // Code gen ends---

      if (av.cod_lexical != PARANTEZA_PD) return 16;

      *tip    = TS[*loc].tip;
      *transm = referinta;
      break;
      
    case nume_program :
      return 53;

    default :
      return 72;
  }

  // urmatorul atom
  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  return 0;

  /*
  // vad daca e constanta
  if (TS[*loc].clasa == nume_const)
  {
    if (who == call_atribuire) return 52; // o constanta nu poate fi in stinga unei atribuiri
    // ---Code gen follows
    // ? incarca in vf. stivei constanta de la indexul din Tab_Const
    genCod1(MV_LODI, TS[*loc].val);
    // Code gen ends---

    *tip    = Tab_Const[TS[*loc].val].tip;
    *transm = valoare;
  }

  // pastrez numele pentru a face verificare de cimp la record
  strcpy(nume, (char*)av.valoare);

  //result = GetAtom(&av.cod_lexical, av.valoare);
  //if (result != 0) return result;

  switch(TS[*loc].clasa)
  {
    case nume_funct :
      // ---Code gen follows
      // ?
      switch(who)
      {
        case call_factor :
          if (TS[*loc].clasa == nume_funct)
             genCod2(MV_LODA, TS[*loc].nivel, TS[*loc].adrelNo);
          else genCod2(MV_LOD, TS[*loc].nivel, TS[*loc].adrelNo);
          *tip = TS[*loc].tip;
          *transm = valoare;
          break;
        case call_atribuire :
          if (TS[*loc].nivel != VNivel - 1) return 52; // e supra-verificare
          *tip = TS[*loc].tip;
          *transm = referinta;
      }
      // Code gen ends---

      result = GetAtom(&av.cod_lexical, av.valoare);
      if (result != 0) return result;
      return -2; // apel de functie
    case nume_proc :
      result = GetAtom(&av.cod_lexical, av.valoare);
      if (result != 0) return result;
      return -3; // apel de procedura
  }

  /*
  // de fapt, nu merge prea bine, trebuie facut un pic
  // altfel
  if ((av.cod_lexical == PARANTEZA_S) || (av.cod_lexical == PUNCT_VIRGULA))
  {
    // s'ar putea sa fie apel de procedura -> verific daca a fost declarata
    if (*loc == -1) return 50; // nu a fost declarata
    if (TS[*loc].clasa == nume_funct)
    {
      // ---Code gen follows
      // ?
      switch(who)
      {
        case call_factor :
          if (TS[*loc].clasa == nume_funct)
             genCod2(MV_LODA, TS[*loc].nivel, TS[*loc].adrelNo);
          else genCod2(MV_LOD, TS[*loc].nivel, TS[*loc].adrelNo);
          break;
        case call_atribuire :
          return 52; // e supra-verificare
      }
      // Code gen ends---

      *tip = TS[*loc].tip;
      *transm = valoare;
      result = GetAtom(&av.cod_lexical, av.valoare);
      if (result != 0) return result;
      return -2; // apel de functie
    }
    else
    {
      if (TS[*loc].clasa == nume_proc)
      {
        result = GetAtom(&av.cod_lexical, av.valoare);
        if (result != 0) return result;
        return -3; // apel de procedura
      }
    }
  }
  */

  /*
  if ((av.cod_lexical != PARANTEZA_PS) && (av.cod_lexical != PUNCT))
  {
    //result = GetAtom(&av.cod_lexical, av.valoare);
    //if (result != 0) return result;
    // completez informatiile de tip
    *tip = TS[*loc].tip;
    if (TS[*loc].clasa == nume_program) return 53;

    // ???
    if ((who == call_atribuire) && (TS[*loc].clasa == nume_paramv)) return 52; // a fost apelata de atribuire

    // testez apel de procedura
    if (TS[*loc].clasa == nume_proc) return -3;

    if (TS[*loc].clasa == nume_paramv) *transm = valoare;
    else *transm = referinta;

    // ---Code gen follows
    // ? incarca o adresa
    switch(who)
    {
      case call_factor :
        if ( (TS[*loc].clasa == nume_param) ||
             (TS[*loc].clasa == nume_funct))
             genCod2(MV_LODA, TS[*loc].nivel, TS[*loc].adrelNo);
        else genCod2(MV_LOD, TS[*loc].nivel, TS[*loc].adrelNo);
        break;
      case call_atribuire :
        if (TS[*loc].clasa == nume_funct) genCod2(MV_LODA, VNivel - 1, TS[*loc].adrelNo);
        else genCod2(MV_LODA, TS[*loc].nivel, TS[*loc].adrelNo);
        break;
    }
    // Code gen ends---

    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;

    return 0; // e variabila simpla sau parametru formal
  }

  switch(av.cod_lexical)
  {
    case PARANTEZA_PS :
        result = GetAtom(&av.cod_lexical, av.valoare);
        if (result != 0) return result;
        if (TS[*loc].clasa != nume_tablou) return 54; // nu e tablou

        result = Expr(&tip1, &transm1);
        if ((result != 0) && (result != -1)) return result;
        if (tip1 != intreg) return 55; // un tablou nu poate fi indexat decit de intreg

        // ---Code gen follows
        // ? secventa de verificare a indicelui, comuna pentru atribuire/factor
        genCod0(MV_COPI);
        genCod1(MV_LODI, Inserare_Const(intreg, TS[*loc].ind_min));
        genCod0(MV_LES);
        genCod1(MV_FJP, ICod + 5);
        genCod1(MV_ERR, 71);
        genCod0(MV_COPI);
        genCod1(MV_LODI, Inserare_Const(intreg, TS[*loc].ind_max));
        genCod0(MV_GRT);
        genCod1(MV_FJP, ICod + 5);
        genCod1(MV_ERR, 72);
        // Code gen ends---

        // ---Code gen follows
        // ? secventa de incarcare a adresei elementului de tablou
        switch(who)
        {
          case call_factor :
            genCod1(MV_LODI, Inserare_Const(intreg, TS[*loc].ind_min));
            genCod0(MV_SUB);
            genCod0(MV_MVRX);
            genCod2(MV_LODX, TS[*loc].nivel, TS[*loc].adrelNo);
            break;
          case call_atribuire :
             genCod1(MV_LODI, Inserare_Const(intreg, TS[*loc].ind_min));
             genCod0(MV_SUB);
             genCod2(MV_LODA, TS[*loc].nivel, TS[*loc].adrelNo);
             genCod0(MV_ADD);
             break;
        }
        // Code gen ends---

        *tip    = TS[*loc].tip;
        *transm = referinta;
        //result = GetAtom(&av.cod_lexical, av.valoare);
        //if (result != 0) return result;
        if (av.cod_lexical != PARANTEZA_PD) return result;
        break;
    case PUNCT :
        result = GetAtom(&av.cod_lexical, av.valoare);
        if (result != 0) return result;
        if (av.cod_lexical != IDENTIFICATOR) return 4;

        // avem numele cimpului si numele variabilei; verific daca cimpul e
        // valid
        if (TS[*loc].clasa != nume_record) return 56;
        record_list* cap;
        int gasit = 0;

        // caut acum orice nume cimp care are ca parinte pe loc adica nume
        for(int i = TS_Virf; i > 0; i--)
        {
          if (TS[i].clasa == nume_cimp)
          {
            cap = TS[i].lista_rec;
            while(cap != NULL)
            {
              if ((cap->index == *loc) &&
                 (strcmp(TS[i].nume, (char*)av.valoare) == 0))
              {
                gasit = 1;
                *tip    = TS[cap->index].tip; // returneza tipul recordului
                *transm = referinta;
                // ---Code gen follows
                // ? incarcare a valorii cimpului de structura
                switch(who)
                {
                  case call_factor :
                    genCod1(MV_LODI, Inserare_Const(intreg, TS[cap->index].deplrecNo));
                    genCod0(MV_MVRX);
                    genCod2(MV_LODX, TS[*loc].nivel, TS[*loc].adrelNo);
                    break;
                  case call_atribuire :
                     genCod2(MV_LODA, TS[*loc].nivel, TS[*loc].adrelNo);
                     genCod1(MV_LODI, Inserare_Const(intreg, TS[cap->index].deplrecNo));
                     genCod0(MV_ADD);
                     break;
                }
                // Code gen ends---
                break;
              }
              cap = cap->next;
            }
          }
        }

        if (gasit == 0) return 48; // nu e membru al recordului;
        break;
  }

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  return 0;
  */
}
//---------------------------------------------------------------------------


int Instr_Read()
{
  int result, loc;
  _tip tip1;
  _transm transm1;

  if ((av.cod_lexical != KEYWORD) ||
      (strcmp((char*)av.valoare, "read") != 0)) return -1;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  if (av.cod_lexical != PARANTEZA_S) return 21;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  while(1)
  {
    result = Variabila(&tip1, &transm1, &loc);
    if (result != 0) return result;

    if (TS[loc].clasa == nume_funct) return 52;
    //if (result == -2) return 27;
    //if ((result != 0) && (result != -1)) return result;

    // verificare de tip
    if (transm1 == valoare) return 52;

    // ---Code gen follows
    // ?
    genCod1(MV_INP, (int)tip1);
    genCod0(MV_STO);
    // Code gen ends---

    if (av.cod_lexical != VIRGULA) break; // atunci e paranteza sau eroare
    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
  }

  if (av.cod_lexical != PARANTEZA_D) return 26;
  
  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  return 0;
}
//---------------------------------------------------------------------------


int Instr_If()
{
  int result, label1, label2;

  if ((av.cod_lexical != KEYWORD) ||
      (strcmp((char*)av.valoare, "if") != 0)) return -1;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  result = Conditie();
  if ((result != 0) && (result != -1)) return result;

  // ---Code gen follows
  // ? scrie fjp, si lasa cimpul de salt sa fie completat mai incolo
  label1 = ICod + 1;
  genCod1(MV_FJP, 0);
  // Code gen ends---

  //result = GetAtom(&av.cod_lexical, av.valoare);
  //if (result != 0) return result;
  if ((av.cod_lexical != KEYWORD) ||
      (strcmp((char*)av.valoare, "then") != 0)) return 29;


  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  result = Instr();
  if (result != 0) return result;
  
  // ---Code gen follows
  // ? completeaza cimpul de salt anterior; se sare peste ramura then
  tabCod[label1 + 1] = ICod + 1;
  // Code gen ends---

  //result = GetAtom(&av.cod_lexical, av.valoare);
  //if (result != 0) return result;
  if ((av.cod_lexical != KEYWORD) ||
      (strcmp((char*)av.valoare, "else") != 0)) return 0;

  // ---Code gen follows
  // ? sar ramura de else
  label2 = ICod + 1;
  genCod1(MV_UJP, 0);
  tabCod[label1 + 1] = ICod + 1;
  // Code gen ends---

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  result = Instr();
  if (result != 0) return result;

  // ---Code gen follows
  // ?
  tabCod[label2 + 1] = ICod + 1;
  // Code gen ends---

  return 0;
}
//---------------------------------------------------------------------------


int Instr_Repeat()
{
  int result, label1;

  if ((av.cod_lexical != KEYWORD) ||
      (strcmp((char*)av.valoare, "repeat") != 0)) return -1;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;

  // ---Code gen follows
  // ?
  label1 = ICod + 1;
  // Code gen ends---

  result = Instr();
  if (result != 0) return result;

  if ((av.cod_lexical != KEYWORD) ||
      (strcmp((char*)av.valoare, "until") != 0)) return 77;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  
  result = Conditie();
  if ((result != 0) && (result != -1)) return result;

  // ---Code gen follows
  // ?
  //genCod0(MV_NOT); 
  genCod1(MV_FJP, label1);
  // Code gen ends---

  return 0;
}
//---------------------------------------------------------------------------


int Instr_For()
{
  int     result, loc, label1, label2, label3, label4, label5;
  _tip    tip1;
  _transm transm1;
  enum _forDir {for_up, for_down} forDir;

  if ((av.cod_lexical != KEYWORD) ||
      (strcmp((char*)av.valoare, "for") != 0)) return -1;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;

  result = Variabila(&tip1, &transm1, &loc);
  if (result != 0) return result;

  if (TS[loc].clasa != nume_vars) return 78; 

  //if (result == -2) return 27;
  //if ((result != 0) && (result != -1)) return result;

  // tip intreg e necesar la index
  if (tip1 != intreg) return 64;

  if (av.cod_lexical != ATRIBUIRE) return 30;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;

  result = Expr(&tip1, &transm1);
  if ((result != 0) && (result != -1)) return result;

  // ---Code gen follows
  // ? atribuie expresie la variabila index a for'ului
  genCod0(MV_STO);
  // Code gen ends---

  if (tip1 != intreg) return 65;

  if (av.cod_lexical != KEYWORD) return 31;
  else
  {
    if ((strcmp((char*)av.valoare, "to") != 0) &&
        (strcmp((char*)av.valoare, "downto") != 0))
      return 31;
  }

  if (strcmp((char*)av.valoare, "to") == 0) forDir = for_up;
  else forDir = for_down;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;

  result = Expr(&tip1, &transm1);
  if ((result != 0) && (result != -1)) return result;

  if (tip1 != intreg) return 65;

  // ---Code gen follows
  // ?
  label1 = ICod + 1;
  genCod0(MV_COPI);
  // incarc valoarea variabilei contor - numai variabila simpla
  genCod2(MV_LOD, TS[loc].nivel, TS[loc].adrelNo);
  switch(forDir)
  {
    case for_up   :
      genCod0(MV_GEQ);
      break;
    case for_down :
      genCod0(MV_LEQ);
      break;
  }

  label2 = ICod + 1;
  genCod1(MV_FJP, 0);

  label3 = ICod + 1;
  label4 = ICod + 1;
  genCod1(MV_UJP, 0);
  // Code gen ends---

  if ((av.cod_lexical == KEYWORD) &&
      (strcmp((char*)av.valoare, "step") == 0))
  {
    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;

    label5 = ICod + 1;
    result = Expr(&tip1, &transm1);

    // ---Code gen follows
    // ? exista clauza step, se sare la evaluarea contorului
    label4 = ICod + 1;
    genCod1(MV_UJP, 0);
    // Code gen ends---

    if (tip1 != intreg) return 65;

    if ((result != 0) && (result != -1)) return result;
  }

  // ---Code gen follows
  // ? daca nu exista step se elimina ujp, altfel se completeaza argumentul cu label3
  // ? adica inceputul buclei
  if (label3 == label4) /*ICod = label3;*/ tabCod[label3] = MV_NOP;
  else tabCod[label3 + 1] = ICod + 1;
  // Code gen ends---

  if ((av.cod_lexical != KEYWORD) ||
      (strcmp((char*)av.valoare, "do") != 0)) return 32;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  result = Instr();

  // ---Code gen follows
  // ?
  genCod2(MV_LODA, TS[loc].nivel, TS[loc].adrelNo);
  genCod2(MV_LOD, TS[loc].nivel, TS[loc].adrelNo);
  if (label3 < label4)
  {
    genCod1(MV_UJP, label5);
    tabCod[label4 + 1] = ICod + 1;
  }
  else
  {
    genCod1(MV_LODI, Inserare_Const(intreg, 1));
  }

  switch(forDir)
  {
    case for_up   :
      genCod0(MV_ADD);
      break;
    case for_down :
      genCod0(MV_SUB);
      break;
  }

  genCod0(MV_STO);
  genCod1(MV_UJP, label1);
  tabCod[label2 + 1] = ICod + 1;
  genCod0(MV_RED);
  // Code gen ends---

  if (result != 0) return result;
  return 0;
}
//---------------------------------------------------------------------------


int Instr_Print()
{
  int     result, i;
  _tip    tip1;
  _transm transm1;

  if ((av.cod_lexical != KEYWORD) ||
      (strcmp((char*)av.valoare, "print") != 0)) return -1;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;

  if (av.cod_lexical != PARANTEZA_S) return 21;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;

  while(1)
  {
    if (av.cod_lexical == SIR_CAR)
    {
      // ---Code gen follows
      // ? afisare stringuri
      for(i = 0; i < strlen((char*)av.valoare); i++)
      {
        genCod1(MV_LODI, Inserare_Const(charr, ((char*)av.valoare)[i]));
        genCod0(MV_OUT);
      }
      // Code gen ends---

      result = GetAtom(&av.cod_lexical, av.valoare);
      if (result != 0) return result;
    }
    else
    {
      // trebuie sa fie expresie
      result = Expr(&tip1, &transm1);

      // ---Code gen follows
      // ? afisare
      genCod0(MV_OUT);
      // Code gen ends---

      if ((result != 0) && (result != -1)) return result; // -1 = urmatorul atom
    }

    if (av.cod_lexical != VIRGULA) break;

    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
  }

  if (av.cod_lexical != PARANTEZA_D) return 22;
  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  return 0;
}
//---------------------------------------------------------------------------


// se poate substitui si cu Apel_Func...cred la ora asta (4.45 a.m.)
int Apel_Proc(int loc)
{
  int       result;
  _tip      tip1;
  _transm   transm1;
  pf_entry* pf;

  if ((TS[loc].nr_par > 0) && (av.cod_lexical != PARANTEZA_S)) return 68;
  if ((TS[loc].nr_par == 0) && (av.cod_lexical == PARANTEZA_S)) return 67;

  if (av.cod_lexical == PARANTEZA_S)
  {
    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
  }

  pf = TS[loc].lista_par;

  // verificarea numarului de parametri
  if (TS[loc].nr_par > 0)
  {
    //result = GetAtom(&av.cod_lexical, av.valoare);
    //if (result != 0) return result;

    while(1)
    {
      result = Expr(&tip1, &transm1); // trebuie revazut, de testat dc transm1 == nr_par
      if ((result != 0) && (result != -1)) return result;

      // verificarea parametrilor la apelul de functie - tip si transmisie
      if ((pf->tip != tip1) && (pf->tip != real) && (tip1 != intreg))
      {
        return 66;
      }

      if ((pf->transm == referinta) && (transm1 != referinta))
      {
        return 52;
      }

      pf = pf->next;

      if (av.cod_lexical != VIRGULA) break; // atunci e paranteza sau eroare

      if (pf == NULL)
      {
        return 67;
      }

      result = GetAtom(&av.cod_lexical, av.valoare);
      if (result != 0) return result;
    }

    if (pf != NULL)
    {
      return 68;
    }


    if (av.cod_lexical != PARANTEZA_D) return 22;

    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
  }

  return 0;
}
//---------------------------------------------------------------------------


int Instr_Case()
{
  int result;
  _tip tip1;
  _transm transm1;

  if ((av.cod_lexical != KEYWORD) ||
      (strcmp((char*)av.valoare, "case") != 0)) return -1;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  result = Expr(&tip1, &transm1);
  if ((result != 0) && (result != -1)) return result;

  if ((av.cod_lexical != KEYWORD) ||
      (strcmp((char*)av.valoare, "of") != 0)) return 34;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  // apel la alternative
  result = Lista_Altern();
  if (result != 0) return result;

  if ((av.cod_lexical != KEYWORD) ||
      (strcmp((char*)av.valoare, "end") != 0)) return 35;
      
  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  return 0;
}
//---------------------------------------------------------------------------


int Lista_Altern()
{
  int result;

  while(1)
  {
    result = Ordinale();
    if (result == -1) return 38;
    
    if (av.cod_lexical != DOUA_PUNCTE) return 13;

    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
    // instructiuni
    result = Instr();
    if ((result != 0) && (result != -1)) return result;

    if (av.cod_lexical != PUNCT_VIRGULA) break;

    // next atom
    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;

    if (av.cod_lexical == KEYWORD)
    {
      if (strcmp((char*)av.valoare, "otherwise") == 0) break;
      if (strcmp((char*)av.valoare, "end") == 0) break;
    }
  }

  if ((av.cod_lexical != KEYWORD) ||
      (strcmp((char*)av.valoare, "otherwise") != 0)) return 0;

  result = GetAtom(&av.cod_lexical, av.valoare);
  if (result != 0) return result;
  // instructiuni
  result = Instr();
  if ((result != 0) && (result != -1)) return result;

  return 0;
}
//---------------------------------------------------------------------------


int Ordinale()
{
  int result, ord_nr = 0;
  
  while(1)
  {
    if ((av.cod_lexical != INTREG_BAZA) && (av.cod_lexical != INTREG_SIMPLU))
    {
      break; 
    }

    ord_nr++;
    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
    // check for ,
    if (av.cod_lexical != VIRGULA) break;

    // bring in next atom
    result = GetAtom(&av.cod_lexical, av.valoare);
    if (result != 0) return result;
  }

  if (ord_nr == 0) return -1;
  //result = GetAtom(&av.cod_lexical, av.valoare);
  //if (result != 0) return result;
  return 0;
}
//---------------------------------------------------------------------------

