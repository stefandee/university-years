//---------------------------------------------------------------------------
#ifndef gen_codH
#define gen_codH
//---------------------------------------------------------------------------

#define OBJ_FILE_ID "Cod obiect pentru compilator"

#define INT           sizeof(int)
#define MAX_PRG_SIZE  65536

int  initGenCod(const char* fileName);
int  endGenCod();
void genCod0(int instr);
void genCod1(int instr, int param1);
void genCod2(int instr, int param1, int param2);
void genCod3(int instr, int param1, int param2, int param3);

extern int ICod;
extern int tabCod[65536];

#endif
