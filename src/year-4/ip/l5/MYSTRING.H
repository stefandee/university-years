#include <alloc.h>
#include <string.h>

#define _MYSTRING

#ifndef _MYOBJECT
#include "myobject.h"
#endif

/*----------------------------*/
/*-----------STRING-----------*/
/*----------------------------*/

class String : public Object
{
  char* data;
 public:
  String(char* s)
  {
   data=(char*)malloc(strlen(s)+1);
   strcpy(data,s);
  }
  String(String& s)
  {
   data=(char*)malloc(strlen(s.data)+1);
   strcpy(data,s.data);
  }
  virtual char* nameOf(){return "String";}
  virtual int isEqual(Object& s){return !strcmp(data, ((String&)s).data);}
  virtual void printOn(){cout << data;}
  String& operator=(String&);
  friend String operator+(String&,String&);
  friend int operator<=(String&,String&);
  ~String(){if(data)free(data);}
};
