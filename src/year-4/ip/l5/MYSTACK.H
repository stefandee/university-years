#define _MYSTACK

#ifndef _MYCOLLECTION
#include "mycollec.h"
#endif

/*----------------------------*/
/*-----------STACK------------*/
/*----------------------------*/

class Stack :public Collection
{
 public:
  void Push(Object&);
  void Pop();
  Object& Top();
  virtual char* nameOf(){return "Stack";}
  virtual void printOn();
};

