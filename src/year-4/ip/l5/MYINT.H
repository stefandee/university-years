#define _MYINTEGER

#ifndef _MYOBJECT
#include "myobject.h"
#endif

/*----------------------------*/
/*-----------INTEGER----------*/
/*----------------------------*/

class Integer: public Object
{
 public:
  int data;
  Integer(int v){ data = v; }
  Integer(Integer& i){ data = i.data; }
  virtual char* nameOf(){return "Integer";}
  virtual int isEqual(Object& i) { return data == ((Integer&)i).data; }
  virtual void printOn();
  friend Integer operator+(Integer&,Integer&);
  friend Integer operator-(Integer&,Integer&);
  friend Integer operator*(Integer&,Integer&);
  friend Integer operator/(Integer&,Integer&);
};
