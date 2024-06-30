#include "mystack.h"

void static writem(Object *o, void* s)
{
 o->printOn();
 cout << ' ' << (char*)s << ' ';
}

void Stack::printOn()
{
 cout << "/S ";
 forEach(writem,"->");
 cout << (char)8 << (char)8 << (char)8 << " S/";
}

void Stack::Push(Object& o)
{
 Node *aux=new Node(o);
 aux->urm=rad;
 rad=aux;
}

void Stack::Pop()
{
 Node *aux=rad;
 if(rad)
 {
  rad=rad->urm;
  delete aux;
 }
}

Object& Stack::Top()
{
 return *(rad->info);
}

