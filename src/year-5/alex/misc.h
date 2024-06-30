//---------------------------------------------------------------------------
#ifndef miscH
#define miscH
//---------------------------------------------------------------------------

// Structura ce se stocheaza pentru urmatorul pas (analiza sintactica)
typedef struct
{
  int cod_lexical;
  void* valoare;
} atom_valoare;

// Diverse teste
int IsKeyWord(char* what);

// Operatii cu fisiere
int  open_source(char* filename);
int  open_result(char* filename);
void getBack(unsigned char ch);
int  carurm();
int  getLines();

// Stari
#define  MAX_STARI    50

#define  S_ERR        0
#define  S_INTRM1     20
#define  S_MME        21
#define  S_DIF        22
#define  S_MMS        23
#define  S_INTRM2     24
#define  S_MMAE       25
#define  S_MMAS       26
#define  S_DOUAP      1
#define  S_DOUAPE     2
#define  S_INT        3
#define  S_PUNCT      4
#define  S_INTRM3     5
#define  S_EXP        6
#define  S_EXPP       7
#define  S_EXPM       8
#define  S_EXPNS      9
#define  S_INTB       10
#define  S_VECTDP     11
#define  S_SIR        12
#define  S_CHAR       13
#define  S_APS        14
#define  S_COMENT     15
#define  S_DP         16
#define  S_IDENT      32
#define  S_EOF        39
#define  S_INIT       40
#define  S_FINAL      41

// erori
#define INT_BASE_ERR  -2
typedef int(*tratare_stare)(char ch, int stare, atom_valoare* val);

extern int Tab_Stari[MAX_STARI][256];
extern tratare_stare Tab_Apel[MAX_STARI][256];

//  Functii de tratare a starilor
int printer(char ch, int stare, atom_valoare* val);        // gata - unused
int nothing(char ch, int stare, atom_valoare* val);        // gata - unused
int treat_eof(char ch, int stare, atom_valoare* val);      // gata - unused
int treat_id(char ch, int stare, atom_valoare* val);       // gata
int treat_num(char ch, int stare, atom_valoare* val);
int treat_sir(char ch, int stare, atom_valoare* val);      // gata
int treat_char(char ch, int stare, atom_valoare* val);     // gata
int treat_op_rel(char ch, int stare, atom_valoare* val);   // gata
int treat_dot(char ch, int stare, atom_valoare* val);
int treat_2p(char ch, int stare, atom_valoare* val);       // gata
int treat_sep(char ch, int stare, atom_valoare* val);      // gata

// Initializare tabela de stari
void InitTabele();

#endif
