#ifndef as_fcnt
#define as_fcnt

enum caller {call_atribuire, call_factor};

typedef struct
{
  int cod_lexical;
  void* valoare;
} atom_valoare;

int AnalizaSintactica(const char* filename);

#endif