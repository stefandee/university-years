#include <fcntl.h>
#include <stdio.h>
//#include <io.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
//#pragma hdrstop

#include "misc.h"
#include "codatom.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

char* KeyWords[] =
{
  "and",
  "array",
  "begin",
  "case",
  "char",
  "const",
  "div",
  "do",
  "downto",
  "else",
  "end",
  "for",
  "function",
  "if",
  "integer",
  "mod",
  "not",
  "of",
  "or",
  "otherwise",
  "print",
  "procedure",
  "program",
  "read",
  "real",
  "record",
  "repeat",
  "step",
  "then",
  "to",
  "until",
  "var",
  "while"
};


// Test - what e un keyword
int IsKeyWord(char* what)
{
  int i = 0;
  for(i = 0; i < sizeof(KeyWords)/sizeof(KeyWords[0]); i++)
    if (strcmp(what, KeyWords[i]) == 0) return i;
  return -1;  
}
//---------------------------------------------------------------------------

int lines_count = 0;
long int file_handle;
long int result_handle;

// Una din rutinele de baza - returneaza urmatorul caracter din fisier
int carurm()
{
  unsigned char char_read;
  int len;

  if ((len = read(file_handle, &char_read, 1)) == -1)
  {
    printf("carurm : error reading file.\n");
    return -1;
  }
  if ((unsigned int)char_read == '\n') lines_count++;
  if (len == 0)
  {
    return -5; // some finishing code
  }  
  return (int)char_read;
}
//---------------------------------------------------------------------------

int open_source(char* filename)
{
  file_handle = open(filename, O_RDWR /*| O_BINARY*/);
  if (file_handle == -1)
  {
    return -1;
  }
  return 1;
}

int open_result(char* filename)
{
  result_handle = open(filename, O_RDWR | O_CREAT, S_IREAD | S_IWRITE);
  if (result_handle == -1)
  {
    return -1;
  }
  return 1;
}

// Se intoarce in fisier cu un octet in spate
void getBack(unsigned char ch)
{
  if ((ch != ' ') && (ch != '\n') && (ch != '\t'))
  {
    lseek(file_handle, -1, SEEK_CUR);
  }
  /*
  long pos = lseek(file_handle, 0, SEEK_CUR);
  lseek(file_handle, pos-1, SEEK_SET);
  */
}
//---------------------------------------------------------------------------

// returneaza numarul de linii analizate
int getLines()
{
  return lines_count;
}
//---------------------------------------------------------------------------
void WriteCod(int cod_lexical)
{
  int size = 0;
  write(result_handle, &cod_lexical, sizeof(int));
  write(result_handle, &size, sizeof(int));
}
//---------------------------------------------------------------------------

void WriteInt(int cod_lexical, int what)
{
  int size = sizeof(int);
  write(result_handle, &cod_lexical, sizeof(int));
  write(result_handle, &size, sizeof(int));
  write(result_handle, &what, sizeof(int));
}
//---------------------------------------------------------------------------

void WriteCharP(int cod_lexical, const char* what)
{
  int size = strlen(what)+1;
  write(result_handle, &cod_lexical, sizeof(int));
  write(result_handle, &size, sizeof(int));
  write(result_handle, what, strlen(what)+1);
}
//---------------------------------------------------------------------------

void WriteFloat(int cod_lexical, float what)
{
  int size = sizeof(float);
  write(result_handle, &cod_lexical, sizeof(int));
  write(result_handle, &size, sizeof(int));
  write(result_handle, &what, sizeof(float));
}
//---------------------------------------------------------------------------

void WriteDouble(int cod_lexical, double what)
{
  int size = sizeof(double);
  write(result_handle, &cod_lexical, sizeof(int));
  write(result_handle, &size, sizeof(int));
  write(result_handle, &what, sizeof(double));
}
//---------------------------------------------------------------------------

void WriteChar(int cod_lexical, char what)
{
  int size = sizeof(char);
  write(result_handle, &cod_lexical, sizeof(int));
  write(result_handle, &size, sizeof(int));
  write(result_handle, &what, sizeof(char));
}
//---------------------------------------------------------------------------

// conversie din string in format [nnn]#[s] in intreg
int baza_conv(char* what)
{
  return -1; // OK code
}
//---------------------------------------------------------------------------

int Tab_Stari[MAX_STARI][256];
tratare_stare Tab_Apel[MAX_STARI][256];

// rutina generala de tratare a starii
int printer(char ch, int stare, atom_valoare* av)
{
   printf("%c", ch);
}

int nothing(char ch, int stare, atom_valoare* av)
{
  //printf("Nothing happened!\n");
  return 0;
}

int treat_eof(char ch, int stare, atom_valoare* av)
{
  printf("EOF reached !\n");
  if (stare == S_INIT) av->cod_lexical = FILE_END; 
  return 0;
}

int treat_id(char ch, int stare, atom_valoare* val)
{
  switch(stare)
  {
    case S_INIT :
         //val->valoare = new char[128];
         val->cod_lexical = IDENTIFICATOR;
	 strcpy((char*)val->valoare, "\0");
         strncat((char*)val->valoare, &ch, 1);
         break;
    case S_IDENT :
         if ((!isalpha(ch)) && (!isdigit(ch)))
         {
           getBack(ch);
           strcat((char*)val->valoare, "\0");
           if (IsKeyWord((char*)val->valoare) >= 0)
           {
             printf("Cuvint cheie : %s\n", (char*)val->valoare);
             val->cod_lexical = KEYWORD;
           }
           else printf("Identificator : %s\n", (char*)val->valoare);
           WriteCharP(val->cod_lexical, (char*)val->valoare);
         }
         else strncat((char*)val->valoare, &ch, 1);
         break;
  }
  return 0;
}

int treat_num(char ch, int stare, atom_valoare* val)
{
  //atof atol strtod
  switch(stare)
  {
    case (S_INIT) :
        //val->valoare = new char[128];
        val->cod_lexical = INTREG_SIMPLU;
	      strcpy((char*)val->valoare, "\0");
        strncat((char*)val->valoare, &ch, 1);
        break;
    case (S_INT) :
        if ((ch != '.') && (ch != '#'))
        {
          if (!isdigit(ch))
          {
            getBack(ch);
            strcat((char*)val->valoare, "\0");
            val->cod_lexical = INTREG_SIMPLU;
            int d = atol((char*)val->valoare);
            // verificari de overflow ?
            printf("Intreg simplu : %d\n", d);
            WriteInt(val->cod_lexical, d);
          }
          else strncat((char*)val->valoare, &ch, 1);
        }
        else
        {
          strncat((char*)val->valoare, &ch, 1);
        }
        break;
    case (S_PUNCT):
	strncat((char*)val->valoare, &ch, 1);
	break;
    case (S_INTB) :
        if (!isdigit(ch) && !isalpha(ch))
        {
          getBack(ch);
          strcat((char*)val->valoare, "\0");
          val->cod_lexical = INTREG_BAZA;
          printf("Intreg in baza %s ", (char*)val->valoare);
          int d = baza_conv((char*)val->valoare);
          if (d == -2) return INT_BASE_ERR;
          else
          {
            printf("in zecimal, %d\n", d);
          }
          WriteInt(val->cod_lexical, d);
        }
        else strncat((char*)val->valoare, &ch, 1);
        break;
    case (S_INTRM3) :
	      if (toupper(ch) != 'E')
	      {
	        if (!isdigit(ch))
	        {
	          getBack(ch);
	          strcat((char*)val->valoare, "\0");
	          val->cod_lexical = REAL_SIMPLU;
            printf("Real simplu %s\n", (char*)val->valoare);
            *((double*)val->valoare) = atof((char*)val->valoare);
	          printf("dupa conversie %f\n", *((double*)val->valoare));
            WriteDouble(val->cod_lexical, *((double*)val->valoare));
	        }
	        else strncat((char*)val->valoare, &ch, 1);
	      }
        else strncat((char*)val->valoare, &ch, 1);
	      break;
    case (S_EXP) :
        strncat((char*)val->valoare, &ch, 1);
	break;
    case (S_EXPNS) :
        if (!isdigit(ch))
        {
	        getBack(ch);
	        strcat((char*)val->valoare, "\0");
                val->cod_lexical = REAL_EXPONENT;
	        printf("Real cu exponent fara semn %s\n", (char*)val->valoare);
	        *((double*)val->valoare) = atof((char*)val->valoare);
	        printf("dupa conversie %f\n", *((double*)val->valoare));
          WriteDouble(val->cod_lexical, *((double*)val->valoare));
        }
        else strncat((char*)val->valoare, &ch, 1);
	      break;
    case (S_EXPP):
    case (S_EXPM):
	      if (!isdigit(ch))
              {
	              getBack(ch);
	              strcat((char*)val->valoare, "\0");
                      val->cod_lexical = REAL_EXPONENT;
	              printf("Real cu exponent si semn %s\n", (char*)val->valoare);
	              *((double*)val->valoare) = atof((char*)val->valoare);
	              printf("dupa conversie %f\n", *((double*)val->valoare));
                WriteDouble(val->cod_lexical, *((double*)val->valoare));
              }
        else strncat((char*)val->valoare, &ch, 1);
	      break;
  }
  return 0;
}

int treat_sir(char ch, int stare, atom_valoare* val)
{
  switch(stare)
  {
    case (S_INIT) :
         //val->valoare = new char[128];
         val->cod_lexical = SIR_CAR;
         strcpy((char*)val->valoare, "\0");
        break;
    case (S_SIR) :
         if (ch == '"')
         {
           strcat((char*)val->valoare, "\0");
           printf("Sir de caractere : %s\n", (char*)val->valoare);
           WriteCharP(val->cod_lexical, (char*)val->valoare);
         }
         else strncat((char*)val->valoare, &ch, 1);
        break;
  }
  return 0;
}

int treat_char(char ch, int stare, atom_valoare* val)
{
  switch(stare)
  {
    case (S_INIT) :
        //val->valoare = new char[2];
        val->cod_lexical = CAR;
        break;
    case (S_CHAR) :
        ((char*)val->valoare)[0] = ch;
        break;
    case (S_APS) :
        printf("Caracter : %c\n", ((char*)val->valoare)[0]);
        WriteChar(val->cod_lexical, ((char*)val->valoare)[0]);
        break;
  }
  return 0;
}

int treat_dot(char ch, int stare, atom_valoare* val)
{
  // !!!
  // printf("In treat_dot\n");
  switch(stare)
  {
    case (S_INIT) :
        val->cod_lexical = PUNCT;
        //printf("Separator .\n");
        break;
    case (S_DP) :
	      if (ch == '.')
	      {
          val->cod_lexical = VECTOR;
	        printf("Vector ..\n");
          WriteCod(val->cod_lexical);
	      }
	      else
	      {
                getBack(ch);
	        val->cod_lexical = PUNCT;
	        printf("Separator .\n");
          WriteCod(val->cod_lexical);
	      }
	      break;
    case (S_PUNCT) :
        // e redundanta comparatia
        if (ch == '.')
        {
          char* temp = new char[128];
          int d;
          strncpy(temp, (char*)val->valoare, strlen((char*)val->valoare)-1);
          d = atol(temp);
          printf("Numar : %d\n", d);
          WriteInt(INTREG_SIMPLU, d);
          printf("Vector ..\n");
          WriteCod(VECTOR);
          delete temp;
        }
        break;    
  }
  return 0;
}

int treat_2p(char ch, int stare, atom_valoare* val)
{
  switch (stare)
  {
    case (S_INIT) :
        val->cod_lexical = DOUA_PUNCTE;
        break;
    case (S_DOUAP) :
        if (ch == '=')
        {
          val->cod_lexical = ATRIBUIRE;
          WriteCod(val->cod_lexical);
          printf("Atribuire :=\n");
        }
        else
        {
          getBack(ch);
          WriteCod(val->cod_lexical);
          printf("Colon :\n");
        }
        break;
  }
  return 0;
}

int treat_op_rel(char ch, int stare, atom_valoare* val)
{
  switch(stare)
  {
    case (S_INIT) :
        val->cod_lexical = MAI_MIC_STRICT;
        break;
    case (S_INTRM1) :
        if (ch == '=')
        {
          val->cod_lexical = MAI_MIC_EGAL;
          WriteCod(val->cod_lexical);
          printf("Operator relational : <=\n");
        }
        else if (ch == '>')
        {
          val->cod_lexical = DIFERIT;
          WriteCod(val->cod_lexical);
          printf("Operator relational : <>\n");
        }
        else
        {
          getBack(ch);
          val->cod_lexical = MAI_MIC_STRICT;
          WriteCod(val->cod_lexical);
          printf("Operator relational : <\n");
        }
        break;
    case (S_INTRM2) :
        if (ch == '=')
        {
          val->cod_lexical = MAI_MARE_EGAL;
          WriteCod(val->cod_lexical);
          printf("Operator relational : >=\n");
        }
        else
        {
          getBack(ch);
          val->cod_lexical = MAI_MARE_STRICT;
          WriteCod(val->cod_lexical);
          printf("Operator relational : >\n");
        }
        break;
  }
  return 0;
}

int treat_sep(char ch, int stare, atom_valoare* val)
{
  switch (ch)
  {
    case ('[') :
        val->cod_lexical = PARANTEZA_PS;
        WriteCod(val->cod_lexical);
        printf("Separator [\n");
        break;
    case (']') :
        val->cod_lexical = PARANTEZA_PD;
        WriteCod(val->cod_lexical);
        printf("Separator ]\n");
        break;
    case ('(') :
        val->cod_lexical = PARANTEZA_S;
        WriteCod(val->cod_lexical);
        printf("Separator (\n");
        break;
    case (')') :
        val->cod_lexical = PARANTEZA_D;
        WriteCod(val->cod_lexical);
        printf("Separator )\n");
        break;
    case ('+') :
        val->cod_lexical = PLUS;
        WriteCod(val->cod_lexical);
        printf("Operator +\n");
        break;
    case ('-') :
        val->cod_lexical = MINUS;
        WriteCod(val->cod_lexical);
        printf("Operator -\n");
        break;
    case ('*') :
        val->cod_lexical = INMULTIT;
        WriteCod(val->cod_lexical);
        printf("Operator *\n");
        break;
    case ('/') :
        val->cod_lexical = IMPARTIT;
        WriteCod(val->cod_lexical);
        printf("Operator /\n");
        break;
    case ('=') :
        val->cod_lexical = EGAL;
        WriteCod(val->cod_lexical);
        printf("Egal =\n");
        break;
    case (';') :
        val->cod_lexical = PUNCT_VIRGULA;
        WriteCod(val->cod_lexical);
        printf("Separator ;\n");
        break;
    case (',') :
        val->cod_lexical = VIRGULA;
        WriteCod(val->cod_lexical);
        printf("Separator ,n");
        break;
  }
  return 0;
}
//---------------------------------------------------------------------------

// Initializeaza Tab_Stari si Tab_Apel
void InitTabele()
{
  int i, j;

  // Initializare toate starile pe starea de eroare
  for(i = 0; i < MAX_STARI; i++)
    for(j = 0; j < 256; j++)
      {
        Tab_Stari[i][j] = S_ERR;
        Tab_Apel[i][j] = nothing;
      }

  // set the eof
  for(i = 0; i < MAX_STARI; i++)
  {
    Tab_Apel[i][EOF] = treat_eof;
    //Tab_Stari[i][EOF] = S_FINAL;
  }

  for(i = 'A'; i <= 'Z'; i++)
  {
    Tab_Stari[S_INIT][i] = S_IDENT; Tab_Stari[S_INIT][tolower(i)] = S_IDENT;
    Tab_Apel[S_INIT][i] = treat_id; Tab_Apel[S_INIT][tolower(i)] = treat_id;
    Tab_Stari[S_IDENT][i] = S_IDENT; Tab_Stari[S_IDENT][tolower(i)] = S_IDENT;
    Tab_Apel[S_IDENT][i] = treat_id; Tab_Apel[S_IDENT][tolower(i)] = treat_id;
    Tab_Stari[S_INTB][i] = S_INTB; Tab_Stari[S_INTB][tolower(i)] = S_INTB;
    Tab_Apel[S_INTB][i] = treat_num; Tab_Apel[S_INTB][tolower(i)] = treat_num;
  }

  for(i = '0'; i <= '9'; i++)
  {
    Tab_Stari[S_INIT][i] = S_INT; Tab_Apel[S_INIT][i] = treat_num;
    Tab_Stari[S_INT][i] = S_INT; Tab_Apel[S_INT][i] = treat_num;
    Tab_Stari[S_PUNCT][i] = S_INTRM3; Tab_Apel[S_PUNCT][i] = treat_num;
    Tab_Stari[S_IDENT][i] = S_IDENT; Tab_Apel[S_IDENT][i] = treat_id;
    Tab_Stari[S_INTRM3][i] = S_INTRM3; Tab_Apel[S_INTRM3][i] = treat_num;
    Tab_Stari[S_EXP][i] = S_EXPNS; Tab_Apel[S_EXP][i] = treat_num;
    Tab_Stari[S_EXPNS][i] = S_EXPNS; Tab_Apel[S_EXPNS][i] = treat_num;
    Tab_Stari[S_EXPP][i] = S_EXPP; Tab_Apel[S_EXPP][i] = treat_num;
    Tab_Stari[S_EXPM][i] = S_EXPM; Tab_Apel[S_EXPM][i] = treat_num;
    Tab_Stari[S_INTB][i] = S_INTB; Tab_Apel[S_INTB][i] = treat_num;
  }

  Tab_Stari[S_INIT]['<'] = S_INTRM1; Tab_Apel[S_INIT]['<'] = treat_op_rel; 
  Tab_Stari[S_INIT]['>'] = S_INTRM2; Tab_Apel[S_INIT]['>'] = treat_op_rel;
  /*Tab_Stari[S_INTRM1]['='] = S_MME; Tab_Apel[S_INTRM1]['='] = treat_op_rel;
  Tab_Stari[S_INTRM1]['>'] = S_DIF; Tab_Apel[S_INTRM1]['>'] = treat_op_rel;
  Tab_Stari[S_INTRM2]['='] = S_MMAE; Tab_Apel[S_INTRM2]['='] = treat_op_rel;*/

  Tab_Stari[S_INIT][':'] = S_DOUAP; Tab_Apel[S_INIT][':'] = treat_2p;
  /*Tab_Stari[S_DOUAP]['='] = S_FINAL; Tab_Apel[S_DOUAP]['='] = treat_2p;*/

  for(i = 32 /* !!! */; i < 256; i++)
  {
    Tab_Stari[S_SIR][i] = S_SIR;
    Tab_Apel[S_SIR][i] = treat_sir;
  }
  Tab_Stari[S_INIT]['"'] = S_SIR; Tab_Apel[S_INIT]['"'] = treat_sir;
  Tab_Stari[S_SIR]['"'] = S_FINAL; Tab_Apel[S_SIR]['"'] = treat_sir;

  for(i = 32 /* !!! */; i < 256; i++)
  {
    Tab_Stari[S_CHAR][i] = S_APS;
    Tab_Apel[S_CHAR][i] = treat_char;
  }
  Tab_Stari[S_INIT]['\''] = S_CHAR; Tab_Apel[S_INIT]['\''] = treat_char;
  Tab_Stari[S_APS]['\''] = S_FINAL; Tab_Apel[S_APS]['\''] = treat_char;

  for(i = 0; i < 256; i++)
  {
    Tab_Stari[S_COMENT][i] = S_COMENT;
    Tab_Apel[S_COMENT][i] = nothing;
  }
  Tab_Stari[S_INIT]['{'] = S_COMENT; Tab_Apel[S_INIT]['{'] = nothing;
  Tab_Apel[S_COMENT]['}'] = nothing;
 Tab_Stari[S_COMENT]['}'] = S_FINAL;	

  Tab_Stari[S_INTRM3]['e'] = S_EXP; Tab_Apel[S_INTRM3]['e'] = treat_num;
  Tab_Stari[S_INTRM3]['E'] = S_EXP; Tab_Apel[S_INTRM3]['E'] = treat_num;

  Tab_Stari[S_EXP]['+'] = S_EXPP; Tab_Apel[S_EXP]['+'] = treat_num;
  Tab_Stari[S_EXP]['-'] = S_EXPM; Tab_Apel[S_EXP]['-'] = treat_num;

  Tab_Stari[S_INT]['#'] = S_INTB; Tab_Apel[S_INT]['#'] = treat_num;

  // de verificat
  Tab_Stari[S_INT]['.'] = S_PUNCT; Tab_Apel[S_INT]['.'] = treat_num;
  Tab_Stari[S_PUNCT]['.'] = S_FINAL; Tab_Apel[S_PUNCT]['.'] = treat_dot;
  Tab_Stari[S_INIT]['.'] = S_DP; Tab_Apel[S_INIT]['.'] = treat_dot;

  Tab_Apel[S_INIT]['['] = treat_sep; Tab_Stari[S_INIT]['['] = S_FINAL;
  Tab_Apel[S_INIT][']'] = treat_sep; Tab_Stari[S_INIT][']'] = S_FINAL;
  Tab_Apel[S_INIT]['('] = treat_sep; Tab_Stari[S_INIT]['('] = S_FINAL;
  Tab_Apel[S_INIT][')'] = treat_sep; Tab_Stari[S_INIT][')'] = S_FINAL;
  Tab_Apel[S_INIT][';'] = treat_sep; Tab_Stari[S_INIT][';'] = S_FINAL;
  Tab_Apel[S_INIT][','] = treat_sep; Tab_Stari[S_INIT][','] = S_FINAL;
  Tab_Apel[S_INIT]['+'] = treat_sep; Tab_Stari[S_INIT]['+'] = S_FINAL;
  Tab_Apel[S_INIT]['-'] = treat_sep; Tab_Stari[S_INIT]['-'] = S_FINAL;
  Tab_Apel[S_INIT]['*'] = treat_sep; Tab_Stari[S_INIT]['*'] = S_FINAL;
  Tab_Apel[S_INIT]['/'] = treat_sep; Tab_Stari[S_INIT]['/'] = S_FINAL;
  Tab_Apel[S_INIT]['='] = treat_sep; Tab_Stari[S_INIT]['='] = S_FINAL;

  Tab_Stari[S_INIT][' ']  = S_INIT; Tab_Apel[S_INIT][' ']   = nothing;
  Tab_Stari[S_INIT]['\n'] = S_INIT; Tab_Apel[S_INIT]['\n']  = nothing;
  Tab_Stari[S_INIT]['\t'] = S_INIT; Tab_Apel[S_INIT]['\t']  = nothing;
  Tab_Stari[S_INIT]['\r']   = S_INIT; Tab_Apel[S_INIT]['\r'] = nothing;

  // de verificat
  for(i = 0; i < 256; i++)
  {
    if ((!isdigit(i)) && (!isalpha(i)))
    {
      Tab_Stari[S_IDENT][i] = S_FINAL;
      Tab_Apel[S_IDENT][i] = treat_id;
      Tab_Stari[S_INTB][i] = S_FINAL; Tab_Apel[S_INTB][i] = treat_num;
    }
    if (!isdigit(i))
    {
      if (toupper(i) != 'E')
      {
        Tab_Stari[S_INTRM3][i] = S_FINAL;
        Tab_Apel[S_INTRM3][i] = treat_num;
      }
      Tab_Stari[S_EXPP][i] = S_FINAL; Tab_Apel[S_EXPP][i] = treat_num;
      Tab_Stari[S_EXPM][i] = S_FINAL; Tab_Apel[S_EXPM][i] = treat_num;
      Tab_Stari[S_EXPNS][i] = S_FINAL; Tab_Apel[S_EXPNS][i] = treat_num;
      //Tab_Stari[S_INTB][i] = S_FINAL; Tab_Apel[S_INTB][i] = treat_num;
      if ((i != '.') && (i != '#'))
      {
        Tab_Stari[S_INT][i] = S_FINAL;
        Tab_Apel[S_INT][i] = treat_num;
      }
    }
    /*
    if (i != '=')
    {
      Tab_Stari[S_DOUAP][i] = S_FINAL;
      Tab_Apel[S_DOUAP][i] = treat_2p;
    }
    */
    
    Tab_Stari[S_DOUAP][i] = S_FINAL;
    Tab_Apel[S_DOUAP][i] = treat_2p;

    Tab_Stari[S_INTRM1][i] = S_FINAL;
    Tab_Apel[S_INTRM1][i] = treat_op_rel;

    Tab_Stari[S_INTRM2][i] = S_FINAL;
    Tab_Apel[S_INTRM2][i] = treat_op_rel;

    Tab_Stari[S_DP][i] = S_FINAL;
    Tab_Apel[S_DP][i] = treat_dot;	
    
    /*if ((i != '=') && (i != '>'))
    {
      Tab_Stari[S_INTRM1][i] = S_FINAL;
      Tab_Apel[S_INTRM1][i] = treat_op_rel;
    }*/
  }
}

