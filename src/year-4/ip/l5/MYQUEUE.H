#define _MYQUEUE

#ifndef _MYCOLLECTION
#include "mycollec.h"
#endif

/*----------------------------*/
/*-----------QUEUE------------*/
/*----------------------------*/

class Queue :public Collection
{
 public:
  void Put(Object&);
  void Get();
  Object& Head();
  virtual char* nameOf(){ return "Queue"; }
  virtual void printOn();
};
