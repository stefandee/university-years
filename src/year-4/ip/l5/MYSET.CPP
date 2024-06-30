#include "myset.h"

void writem(Object *o, void* s)
{
 if(!strcmp(o->nameOf(),"Integer"))
 {
  Integer *p=(Integer*)o;
  p->printOn();
 }
 if(!strcmp(o->nameOf(),"String"))
 {
  String *p=(String*)o;
  p->printOn();
 }
 if(!strcmp(o->nameOf(),"Integer"))
 {
  Integer *p=(Integer*)o;
  p->printOn();
 }
 cout << ' ' << (char*)s << ' ';
}

void Set::printOn()
{
 cout << "{ ";
// forEach(writem,",");
 cout << (char)8 << (char)8 << '}';
}

static Set *rez;

Set& operator+(Set& a,Set& b)
{
 if(rez)delete rez;
 rez=new Set(a);
 Node *p;
 for(p=b.rad;p;p=p->urm)
  rez->add(*(p->info));
 return *rez;
}

Set& operator*(Set& a,Set& b)
{
 if(rez)delete rez;
 Node *p;
 for(p=b.rad;p;p=p->urm)
  if(a.isin(*(p->info)))
     rez->add(*(p->info));
 return *rez;
}

Set& operator-(Set& a,Set& b)
{
 if(rez)delete rez;
 Node *p;
 for(p=a.rad;p;p=p->urm)
  if(!b.isin(*(p->info)))
     rez->add(*(p->info));
 return *rez;
}

int Set::isin(Object& o)
{
 Node *p;
 for(p=rad;p;p=p->urm)
  if(*(p->info)==o)return 1;
 return 0;
}

int Set::Cardinal()
{
 int i=0;
 Node *p=rad;
 for(;p;p=p->urm,i++);
 return i;
}

int operator<=(Set& a,Set& b)
{
 Node *p;
 for(p=a.rad;p;p=p->urm)
  if(!b.isin(*(p->info)))return 0;
 return 1;
}

void Set::add(Object& o)
{
 if(!isin(o))add(o);
}

