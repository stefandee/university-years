#include <fcntl.h>
#include <stdio.h>
#include <io.h>
#include <stdlib.h>
//#include <conio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#pragma hdrstop
//---------------------------------------------------------------------------

#include "mv_ops.h"
#include "erori.h"
#include "mv_instr.h"
#include "sym_tab.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

int             mvTabCod[65536];
int             mvSp;
int             mvVBaza;
int             mvNi;
int             mvRx;
int             mvIe;
int             showAsm = false;
_mvStats        mvSt;
_stack_entry    mvStiva    [MAX_STIVA];
_baza_entry     mvBaza     [MAX_BAZA];
tab_const_entry mvTabConst [MAX_CONST];

//---------------------------------------------------------------------------

// Descriere   :  incarca in memorie un fisier care contine program
// Param       :  filename - numele fisierului
// Rezultat    :  codul de eroare/ 0 in caz de succes
// Comentarii  :  n'avem
int loadCode  (const char* fileName)
{
  int   handle, i;
  int   dummy;
  char  fileId[32];

  // deschid fisierul
  handle = open(fileName, O_RDONLY | O_BINARY);
  if (handle == -1) return 57;

  // incarc identificatorul de fisier
  if (read(handle, fileId, 32) == -1) return 59;

  if (strcmp(fileId, OBJ_FILE_ID) != 0) return 60;

  // citesc tabela de constante
  if (read(handle, mvTabConst, sizeof(mvTabConst)) <= 0) return 61;

  // aloc memorie pentru cod - fara teste de eroare
  int currentPos = lseek(handle, 0, SEEK_CUR);
  int endPos     = lseek(handle, 0, SEEK_END);
  int codeLen    = (endPos - currentPos + 1);

  lseek(handle, currentPos, SEEK_SET);

  //mvTabCod = new int[codeLen / sizeof(int)];

  // citesc codul din fisier
  /*
  for(i = 0; i < codeLen / sizeof(int); i++)
  {
     read(handle, &mvTabCod[i], sizeof(int));
     //mvTabCod[i] = dummy;
     if (showAsm) printf("%d ", mvTabCod[i]);
  }
  */
  
  if (read(handle, (char*)mvTabCod, codeLen) == -1) return 62;

  // inchid fisierul
  close(handle);

  return 0;
}
//---------------------------------------------------------------------------

// Descriere   :  ruleaza codul incarcat anterior
// Param       :  nimic
// Rezultat    :  cod de eroare/ 0 in caz de succes
// Comentarii  :  nu este ;-)
int runCode()
{
  int result, i, nivel, adrel, adr, iConst, boolResult, nrLoc, adr_salt, nr_par;
  double value; 

  // executivul, de fapt urmeaza de aici
  // ar fi o idee ca fiecare ramura de case sa contina
  // un apel de functie care sa trateze instructiunea respectiva,
  // sau macar pe grupuri

  // obs : primele 2 intrari din mvTabCod sint adresa de start a
  //       programului si dimensiunea stivei
  mvNi            = mvTabCod[0];
  // aici e mai ciudat...nu mai folosesc dim_var ci varNo, pentru ca ...
  mvSp            = mvTabCod[2];
  mvSt            = mv_activ;
  mvIe            = 0;
  mvVBaza         = 0;
  mvBaza[0].nivel = 1;
  mvBaza[0].bloc  = 0;

  while (mvSt == mv_activ)
  {
    switch(mvTabCod[mvNi])
    {
      // Incarca in vf. stivei valoarea calculata pe baza arg. nivel si adrel
      case MV_LOD   :
        if (showAsm) printf("MV_LOD\n");
        i     = mvVBaza;
        nivel = mvTabCod[mvNi + 1];
        adrel = mvTabCod[mvNi + 2];

        while (nivel != mvBaza[i].nivel) i--;
        adr = mvBaza[i].bloc + adrel;
        while (mvStiva[adr].tipNod == mv_adresa) adr = mvStiva[adr].aInfo;

        mvSp++;
        mvStiva[mvSp] = mvStiva[adr];

        mvNi += 3;
        break;

      // Incarca in vf. stivei constanta data de arg. iConst din mvTabConst
      case MV_LODI  :
        if (showAsm) printf("MV_LODI\n");
        iConst = mvTabCod[mvNi + 1];

        mvSp++;
        switch(mvTabConst[iConst].tip)
        {
          case intreg :
            mvStiva[mvSp].tipNod = mv_intreg;
            mvStiva[mvSp].iInfo  = (int)mvTabConst[iConst].valoare;
            break;
          case real :
            mvStiva[mvSp].tipNod = mv_real;
            mvStiva[mvSp].rInfo  = mvTabConst[iConst].valoare;
            break;
          case charr :
            mvStiva[mvSp].tipNod = mv_char;
            mvStiva[mvSp].cInfo  = (char)mvTabConst[iConst].valoare;
            break;
        }


        mvNi += 2;
        break;

      // Incarca in vf. stivei adresa calculata pe baza argumentelor
      case MV_LODA  :
        if (showAsm) printf("MV_LODA\n");
        i     = mvVBaza;
        nivel = mvTabCod[mvNi + 1];
        adrel = mvTabCod[mvNi + 2];

        mvSp++;
        while (nivel != mvBaza[i].nivel) i--;

        adr                  = mvBaza[i].bloc + adrel;
        mvStiva[mvSp].tipNod = mv_adresa;
        mvStiva[mvSp].aInfo  = adr;

        mvNi += 3;
        break;

      // Analog ca mai sus, dar la calc. adr se adauga mvRx
      case MV_LODX  :
        if (showAsm) printf("MV_LODX\n");
        i     = mvVBaza;
        nivel = mvTabCod[mvNi + 1];
        adrel = mvTabCod[mvNi + 2];

        while (nivel != mvBaza[i].nivel) i--;
        adr = mvBaza[i].bloc + adrel + mvRx;
        while (mvStiva[adr].tipNod == mv_adresa) adr = mvStiva[adr].aInfo;

        mvSp++;
        mvStiva[mvSp] = mvStiva[adr];

        mvNi += 3;
        break;

      // Creaza un nod nou in vf stivei completat cu continutul vf. vechi
      case MV_COPI  :
        if (showAsm) printf("MV_COPI\n");
        mvSp++;

        mvStiva[mvSp] = mvStiva[mvSp - 1];

        mvNi += 1;
        break;

      // Depune val. din vf stivei la adr. din nodul de sub vf. si
      // elimina 2 noduri din stiva
      case MV_STO   :
        if (showAsm) printf("MV_STO\n");

        mvSp -= 2;
        adr = mvStiva[mvSp + 1].aInfo;

        while (mvStiva[adr].tipNod == mv_adresa) adr = mvStiva[adr].aInfo;

        mvStiva[adr] = mvStiva[mvSp + 2];

        mvNi += 1;
        break;

      // Muta in reg. index val. din vf.stivei
      case MV_MVRX  :
        if (showAsm) printf("MV_MVRX\n");
        mvRx = mvStiva[mvSp].aInfo; // sau care informatie ?
        mvSp--;

        mvNi += 1;
        break;

      // Elimina un nod din stiva
      case MV_RED   :
        if (showAsm) printf("MV_RED\n");
        mvSp--;
        mvNi += 1;
        break;

      // Salt neconditionat la instr. de la adresa adr
      case MV_UJP   :
        if (showAsm) printf("MV_UJP\n");
        adr = mvTabCod[mvNi + 1];

        mvNi = adr;
        break;

      // Salt conditionat de valoarea din vf. stivei; se elimina vf.
      case MV_FJP   :
        if (showAsm) printf("MV_FJP\n");
        adr = mvTabCod[mvNi + 1];

        if (mvStiva[mvSp].iInfo == 0) mvNi = adr;
        else mvNi += 2;

        mvSp--;
        break;

      // Test < intre val. de sub vf. si cea din vf.; se elimina cele 2 noduri
      // si se introduce un nod cu iInfo 1 sau 0
      case MV_LES   :
        if (showAsm) printf("MV_LES\n");
        boolResult = 0;

        mvSp--;
        switch(mvStiva[mvSp].tipNod)
        {
          case mv_intreg :
            if (mvStiva[mvSp].iInfo < mvStiva[mvSp + 1].iInfo) boolResult = 1;
            break;
          case mv_real   :
            if (mvStiva[mvSp].rInfo < mvStiva[mvSp + 1].rInfo) boolResult = 1;
            break;
          case mv_char   :
            if (mvStiva[mvSp].cInfo < mvStiva[mvSp + 1].cInfo) boolResult = 1;
            break;
        }

        mvStiva[mvSp].tipNod = mv_intreg;
        mvStiva[mvSp].iInfo  = boolResult;

        mvNi += 1;
        break;

      // <=
      case MV_LEQ   :
        if (showAsm) printf("MV_LEQ\n");
        boolResult = 0;

        mvSp--;
        switch(mvStiva[mvSp].tipNod)
        {
          case mv_intreg :
            if (mvStiva[mvSp].iInfo <= mvStiva[mvSp + 1].iInfo) boolResult = 1;
            break;
          case mv_real   :
            if (mvStiva[mvSp].rInfo <= mvStiva[mvSp + 1].rInfo) boolResult = 1;
            break;
          case mv_char   :
            if (mvStiva[mvSp].cInfo <= mvStiva[mvSp + 1].cInfo) boolResult = 1;
            break;
        }

        mvStiva[mvSp].tipNod = mv_intreg;
        mvStiva[mvSp].iInfo  = boolResult;

        mvNi += 1;
        break;

      // >
      case MV_GRT   :
        if (showAsm) printf("MV_GRT\n");
        boolResult = 0;

        mvSp--;
        switch(mvStiva[mvSp].tipNod)
        {
          case mv_intreg :
            if (mvStiva[mvSp].iInfo > mvStiva[mvSp + 1].iInfo) boolResult = 1;
            break;
          case mv_real   :
            if (mvStiva[mvSp].rInfo > mvStiva[mvSp + 1].rInfo) boolResult = 1;
            break;
          case mv_char   :
            if (mvStiva[mvSp].cInfo > mvStiva[mvSp + 1].cInfo) boolResult = 1;
            break;
        }

        mvStiva[mvSp].tipNod = mv_intreg;
        mvStiva[mvSp].iInfo  = boolResult;

        mvNi += 1;
        break;

      // >=
      case MV_GEQ   :
        if (showAsm) printf("MV_GEQ\n");
        boolResult = 0;

        mvSp--;
        switch(mvStiva[mvSp].tipNod)
        {
          case mv_intreg :
            if (mvStiva[mvSp].iInfo >= mvStiva[mvSp + 1].iInfo) boolResult = 1;
            break;
          case mv_real   :
            if (mvStiva[mvSp].rInfo >= mvStiva[mvSp + 1].rInfo) boolResult = 1;
            break;
          case mv_char   :
            if (mvStiva[mvSp].cInfo >= mvStiva[mvSp + 1].cInfo) boolResult = 1;
            break;
        }

        mvStiva[mvSp].tipNod = mv_intreg;
        mvStiva[mvSp].iInfo  = boolResult;

        mvNi += 1;
        break;

      // ==
      case MV_EQU   :
        if (showAsm) printf("MV_EQU\n");
        boolResult = 0;

        mvSp--;
        switch(mvStiva[mvSp].tipNod)
        {
          case mv_intreg :
            if (mvStiva[mvSp].iInfo == mvStiva[mvSp + 1].iInfo) boolResult = 1;
            break;
          case mv_real   :
            if (mvStiva[mvSp].rInfo == mvStiva[mvSp + 1].rInfo) boolResult = 1;
            break;
          case mv_char   :
            if (mvStiva[mvSp].cInfo == mvStiva[mvSp + 1].cInfo) boolResult = 1;
            break;
        }

        mvStiva[mvSp].tipNod = mv_intreg;
        mvStiva[mvSp].iInfo  = boolResult;

        mvNi += 1;
        break;

      // !=
      case MV_NEQ   :
        if (showAsm) printf("MV_NEQ\n");
        boolResult = 0;

        mvSp--;
        switch(mvStiva[mvSp].tipNod)
        {
          case mv_intreg :
            if (mvStiva[mvSp].iInfo != mvStiva[mvSp + 1].iInfo) boolResult = 1;
            break;
          case mv_real   :
            if (mvStiva[mvSp].rInfo != mvStiva[mvSp + 1].rInfo) boolResult = 1;
            break;
          case mv_char   :
            if (mvStiva[mvSp].cInfo != mvStiva[mvSp + 1].cInfo) boolResult = 1;
            break;
        }

        mvStiva[mvSp].tipNod = mv_intreg;
        mvStiva[mvSp].iInfo  = boolResult;

        mvNi += 1;
        break;

      // Aduna val. din vf. si de sub vf., elimina cele 2 noduri si pune inf.
      // in vf.
      case MV_ADD   :
        if (showAsm) printf("MV_ADD\n");
        mvSp--;

        if (mvStiva[mvSp].tipNod == mv_adresa)
        {
          mvStiva[mvSp].aInfo = mvStiva[mvSp].aInfo + mvStiva[mvSp + 1].iInfo;
        }
        else
        {
          if (mvStiva[mvSp + 1].tipNod == mv_adresa)
          {
            mvStiva[mvSp].tipNod = mv_adresa;
            mvStiva[mvSp].aInfo  = mvStiva[mvSp].iInfo + mvStiva[mvSp + 1].aInfo;
          }
          else
          {
            switch(mvStiva[mvSp].tipNod)
            {
              case mv_intreg :
                mvStiva[mvSp].iInfo += mvStiva[mvSp + 1].iInfo;
                break;
              case mv_real   :
                mvStiva[mvSp].rInfo += mvStiva[mvSp + 1].rInfo;
                break;
              case mv_char   :
                mvStiva[mvSp].cInfo += mvStiva[mvSp + 1].cInfo;
                break;
            }
          }
        }

        mvNi += 1;
        break;

      // Scadere
      case MV_SUB   :
        if (showAsm) printf("MV_SUB\n");
        mvSp--;

        switch(mvStiva[mvSp].tipNod)
        {
          case mv_intreg :
            mvStiva[mvSp].iInfo = mvStiva[mvSp].iInfo - mvStiva[mvSp + 1].iInfo;
            break;
          case mv_real   :
            mvStiva[mvSp].rInfo = mvStiva[mvSp].rInfo - mvStiva[mvSp + 1].rInfo;
            break;
          case mv_char   :
            mvStiva[mvSp].cInfo = mvStiva[mvSp].cInfo - mvStiva[mvSp + 1].cInfo;
            break;
        }

        mvNi += 1;
        break;

      case MV_MUL   :
        if (showAsm) printf("MV_MUL\n");
        mvSp--;

        switch(mvStiva[mvSp].tipNod)
        {
          case mv_intreg :
            mvStiva[mvSp].iInfo = mvStiva[mvSp].iInfo * mvStiva[mvSp + 1].iInfo;
            break;
          case mv_real   :
            mvStiva[mvSp].rInfo = mvStiva[mvSp].rInfo * mvStiva[mvSp + 1].rInfo;
            break;
          case mv_char   :
            mvStiva[mvSp].cInfo = mvStiva[mvSp].iInfo * mvStiva[mvSp + 1].cInfo;
            break;
        }

        mvNi += 1;
        break;

      case MV_DIV   :
        if (showAsm) printf("MV_DIV\n");
        mvSp--;

        switch(mvStiva[mvSp].tipNod)
        {
          case mv_intreg :
            if (mvStiva[mvSp + 1].iInfo > 0) mvStiva[mvSp].iInfo = mvStiva[mvSp].iInfo / mvStiva[mvSp + 1].iInfo;
            else
            {
              mvSt   = mv_err;
              result = 65; // divide by 0
            }
            break;
          case mv_real   :
            if (mvStiva[mvSp + 1].rInfo > 0) mvStiva[mvSp].rInfo = mvStiva[mvSp].rInfo / mvStiva[mvSp + 1].rInfo;
            else
            {
              mvSt   = mv_err;
              result = 65; // divide by 0
            }
            break;
          case mv_char   :
            if (mvStiva[mvSp + 1].cInfo > 0) mvStiva[mvSp].cInfo = mvStiva[mvSp].cInfo / mvStiva[mvSp + 1].cInfo;
            else
            {
              mvSt   = mv_err;
              result = 65; // divide by 0
            }
            break;
        }

        mvNi += 1;
        break;

      case MV_MOD   :
        if (showAsm) printf("MV_MOD\n");
        mvSp--;

        if (mvStiva[mvSp + 1].iInfo > 0) mvStiva[mvSp].iInfo = mvStiva[mvSp].iInfo % mvStiva[mvSp + 1].iInfo;
        else
        {
          mvSt   = mv_err;
          result = 65; // divide by 0
        }

        mvNi += 1;
        break;

      case MV_RBM   :
        if (showAsm) printf("MV_RBM\n");

        mvSp += mvTabCod[mvNi + 2];
        mvStiva[mvSp].iInfo  = mvTabCod[mvNi + 1];
        mvStiva[mvSp].tipNod = mv_intreg;

        mvNi += 3;
        break;

      case MV_FCALL :
        if (showAsm) printf("MV_FCALL\n");
        break;
      case MV_CALL  :
        if (showAsm) printf("MV_CALL\n");

        adr_salt = mvTabCod[mvNi + 1];
        nr_par   = mvTabCod[mvNi + 2];
        nivel    = mvTabCod[mvNi + 3];

        mvVBaza++;
        mvBaza[mvVBaza].nivel = nivel;
        mvBaza[mvVBaza].bloc  = mvSp - nr_par + 1;
        mvSp += mvStiva[mvBaza[mvVBaza].bloc - 1].iInfo;
        mvStiva[mvBaza[mvVBaza].bloc - 1].aInfo = mvNi + 4;

        mvNi = adr_salt;
        break;

      case MV_RET   :
        if (showAsm) printf("MV_RET\n");
        mvSp = mvBaza[mvVBaza].bloc - 2;

        mvNi = mvStiva[mvSp + 1].aInfo;

        mvVBaza--;
        break;

      // Opreste programul
      case MV_STOP  :
        if (showAsm) printf("MV_STOP\n");
        mvSt = mv_stop;
        break;

      // Eroare - opreste programul  
      case MV_ERR   :
        if (showAsm) printf("MV_ERR\n");
        mvSt = mv_err;
        mvIe = mvTabCod[mvNi+1];
        break;

      // Pune in vf. stivei o valoare citita
      case MV_INP   :
        if (showAsm) printf("MV_INP\n");
        mvSp++;

        mvStiva[mvSp].tipNod = (_stack_type)mvTabCod[mvNi + 1];

        switch(mvStiva[mvSp].tipNod)
        {
          case mv_intreg :
            scanf("%d", &mvStiva[mvSp].iInfo);
            break;
          case mv_real   :
            scanf("%f", &mvStiva[mvSp].rInfo);
            break;
          case mv_char   :
            scanf("%c", &mvStiva[mvSp].cInfo);
            break;
        }

        mvNi += 2;
        break;

      // Scoate pe ecran valoarea din vf. stivei si o elimina
      case MV_OUT   :
        if (showAsm) printf("MV_OUT\n");
        switch(mvStiva[mvSp].tipNod)
        {
          case mv_intreg :
            printf("%d", mvStiva[mvSp].iInfo);
            break;
          case mv_real   :
            printf("%f", mvStiva[mvSp].rInfo);
            break;
          case mv_char   :
            printf("%c", mvStiva[mvSp].cInfo);
            break;
        }


        mvSp--;
        mvNi += 1;
        break;

      // Converteste valoarea din vf.stivei sau de sub ea la tipul indicat
      case MV_CONV  :
        if (showAsm) printf("MV_CONV\n");
        nrLoc = mvTabCod[mvNi + 2];

        switch (mvStiva[mvSp - nrLoc].tipNod)
        {
          case mv_intreg :
            value = mvStiva[mvSp - nrLoc].iInfo;
            break;
          case mv_real   :
            value = mvStiva[mvSp - nrLoc].rInfo;
            break;
          case mv_char   :
            value = mvStiva[mvSp - nrLoc].cInfo;
            break;
        }

        mvStiva[mvSp - nrLoc].tipNod = (_stack_type)mvTabCod[mvNi + 1];

        switch (mvStiva[mvSp - nrLoc].tipNod)
        {
          case mv_intreg :
            mvStiva[mvSp - nrLoc].iInfo = (int)value;
            break;
          case mv_real   :
            mvStiva[mvSp - nrLoc].rInfo = value;
            break;
          case mv_char   :
            mvStiva[mvSp - nrLoc].cInfo = (char)value;
            break;
        }

        mvNi += 3;
        break;

      // And asupra celor 2 valori din vf. stivei, cu plasarea rez. in vf.
      case MV_AND   :
        if (showAsm) printf("MV_AND\n");
        mvSp--;

        mvStiva[mvSp].iInfo = mvStiva[mvSp].iInfo & mvStiva[mvSp + 1].iInfo;

        mvNi += 1;
        break;

      // Or asupra celor 2 valori din vf. stivei, cu plasarea rez. in vf.
      case MV_OR    :
        if (showAsm) printf("MV_OR\n");
        mvSp--;

        mvStiva[mvSp].iInfo = mvStiva[mvSp].iInfo | mvStiva[mvSp + 1].iInfo;

        mvNi += 1;
        break;

      // Negatia asupra valorii din vf. stivei
      case MV_NOT   :
        if (showAsm) printf("MV_NOT\n");
        mvStiva[mvSp].iInfo = 1 - mvStiva[mvSp].iInfo;

        mvNi += 1;
        break;

      // Instructiunea "nimic", pentru ca sa arate bine :-)
      case MV_NOP   :
        if (showAsm) printf("MV_NOP\n");
        mvNi += 1;
        break;
        
      // Instructiune invalida
      default       :
        return 63;
    }
  }

  if (mvSt == mv_err) return result;

  return 0;
}
//---------------------------------------------------------------------------


