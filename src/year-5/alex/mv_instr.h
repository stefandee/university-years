//---------------------------------------------------------------------------
#ifndef mv_instrH
#define mv_instrH
//---------------------------------------------------------------------------

#define MAX_INSTR 34

// codurile instructiunilor masinii virtuale
#define MV_NOP   0
#define MV_LOD   1
#define MV_LODI  2
#define MV_LODA  3
#define MV_LODX  4
#define MV_COPI  5

#define MV_STO   6
#define MV_MVRX  7
#define MV_RED   8

#define MV_UJP   9
#define MV_FJP   10

#define MV_LES   11
#define MV_LEQ   12
#define MV_GRT   13
#define MV_GEQ   14
#define MV_EQU   15
#define MV_NEQ   16

#define MV_ADD   17
#define MV_SUB   18
#define MV_MUL   19
#define MV_DIV   20
#define MV_MOD   21

#define MV_RBM   22
#define MV_CALL  23
#define MV_RET   24
#define MV_FCALL 25

#define MV_STOP  26
#define MV_ERR   27

#define MV_INP   28
#define MV_OUT   29

#define MV_CONV  30

#define MV_AND   31
#define MV_OR    32
#define MV_NOT   33

extern int mvInstrSize[MAX_INSTR];

#endif
