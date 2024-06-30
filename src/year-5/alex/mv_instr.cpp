//---------------------------------------------------------------------------
#pragma hdrstop

#include "mv_instr.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

int mvInstrSize[MAX_INSTR] =
{
  1, // MV_NOP
  3, // MV_LOD
  2, // MV_LODI
  3, // MV_LODA
  3, // MV_LODX
  1, // MV_COPI
  1, // MV_STO
  1, // MV_MVRX
  1, // MV_RED
  2, // MV_UJP
  2, // MV_FJP
  1, // MV_LES
  1, // MV_LEQ
  1, // MV_GRT
  1, // MV_GEQ
  1, // MV_EQU
  1, // MV_NEQ
  1, // MV_ADD
  1, // MV_SUB
  1, // MV_MUL
  1, // MV_DIV
  1, // MV_MOD
  3, // MV_RBM
  3, // MV_FCALL
  3, // MV_CALL
  1, // MV_RET
  1, // MV_STOP
  2, // MV_ERR
  2, // MV_INP
  1, // MV_OUT
  3, // MV_CONV
  1, // MV_AND
  1, // MV_OR
  1, // MV_NOT
};

