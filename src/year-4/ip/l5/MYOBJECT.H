#include <iostream.h>
#define _MYOBJECT

/*----------------------------*/
/*-----------OBJECT-----------*/
/*----------------------------*/

class Object
{
 private:
  virtual int isEqual(Object&) { return 1;}
 public:
  virtual char *nameOf(){return "Object";}
  virtual void printOn(){cout << nameOf();}
  friend int operator==(Object&, Object&);
  friend int operator!=(Object&, Object&);
};

class ObjErr : public Object
{
 public :
   virtual char *nameOf(){return "Object Error";}
};

static ObjErr NOOBJECT;
#define ZERO ((ObjErr*) &NOOBJECT)




