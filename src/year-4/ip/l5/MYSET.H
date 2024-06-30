#define _MYSET

#ifndef _MYCOLLECTION
#include "mycollec.h"
#endif

/*----------------------------*/
/*------------SET-------------*/
/*----------------------------*/

class Set :public Collection
{
 public:
  virtual char* nameOf(){return "Set";}
  virtual void printOn();
  friend Set& operator+(Set&,Set&);
  friend Set& operator*(Set&,Set&);
  friend Set& operator-(Set&,Set&);
  friend int operator<=(Set&,Set&);
  int isin(Object&);
  int Cardinal();
  virtual void add(Object&);
};
