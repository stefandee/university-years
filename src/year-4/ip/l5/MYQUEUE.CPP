#include "myqueue.h"

void static writem(Object *o, void* s)
{
 o->printOn();
 cout << ' ' << (char*)s << ' ';
}

void Queue::Put(Object& o)
{
 add(o);
}

void Queue::Get()
{
 Node *p,*aux;
 for(p=aux=rad;aux&&aux->urm;p=aux,aux=aux->urm);
 if(p)
 {
  p->urm=NULL;
  if(p==rad)rad=NULL;
  delete aux;
 }
}

Object& Queue::Head()
{
 Node *p;
 for(p=rad;p&&p->urm;p=p->urm);
 return p ? *(p->info):(Object)*ZERO; // E BINE ?!
}

void Queue::printOn()
{
 cout << "/Q ";
 forEach(writem,"->");
 cout << (char)8 << (char)8 << (char)8 << " Q/";
}

