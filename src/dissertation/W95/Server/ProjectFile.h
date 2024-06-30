//---------------------------------------------------------------------------
#ifndef ProjectFileH
#define ProjectFileH
//---------------------------------------------------------------------------

#include "Defs.h"

#define DATA_START sizeof(TProjectFile)
#define MAX_PROJECT_NAME_SIZE 64

class CProject
{
private:
protected:

public:
  // la naiba cu incapsularea 
  // cine vrea, sa treaca variabilele in private:
  // si sa faca functii de acces la ele, ca io nu mai am kef...acum
  AnsiString projectName;

  int    inputsNo, hiddenNo, outputsNo;     // configuratia retelei
  int    patternCount;                      // cite paternuri exista aici
  bool   hasBeenTrained;                    // daca exista ponderi, urmeaza in fisier si cimpul e true
  bool   isMomentumTerm;
  float  momentumTerm;                      // memorie suplimentara
  float  learningRate;                      // eta
  int    saveCount;                         // cite paternuri sint procesate pina cind se cere salvarea pe disc
  TActivation functHidden, functOutput;     // functiile de activare pentru fiecare strat

  AnsiString fileName;

  __fastcall CProject();
  void       DefaultProject();
  int        SaveProject();
  int        LoadProject();
  bool       DeleteProject();
  void       LoadInputPatternX(int index, float* data);
  void       LoadTargetPatternX(int index, float* data);
  int        AddPatternSet(float* data);
  void       SaveWeights(float* dataIH, float* dataHO);
  __fastcall ~CProject();
};

#endif
