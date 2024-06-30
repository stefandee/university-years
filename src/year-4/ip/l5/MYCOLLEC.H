#define _MYCOLLECTION

#ifndef _MYOBJECT
#include "myobject.h"
#endif

#ifndef _MYINTEGER
#include "myint.h"
#endif

#ifndef _MYSTRING
#include "mystring.h"
#endif

/*----------------------------*/
/*---------COLLECTION---------*/
/*----------------------------*/


typedef int  (      *condFuncType )(const class Object*, void* );
typedef void (      *iterFuncType )(      class Object*, void* );

class Node
{
 public:
  Object *info;
  Node *urm;
  Node(){info=NULL;urm=NULL;}
  Node(Object& o)
  {
    info = &o;
    urm=NULL;
  }
  ~Node(){delete info;}
};

class Collection : public Object
{
  void Insert(int Pos,Object &ob);
  void Remove(int Pos);
 public:
  Node *rad;
  Collection(){rad=NULL;}
  Collection(Object& o){rad=new Node;rad->info=&o;}
  Collection(Collection&);
  ~Collection();
  virtual char* nameOf(){return "Collection";}
  virtual int isEqual(Collection& s);
  virtual void printOn();
  void forEach(iterFuncType iterf, void *args);
  virtual void add(Object&);
  virtual void detach(Object&);
  int isEmpty(){return rad==NULL;}
  Object& firstThat(condFuncType condf, void *args);
};

