#include <stdio.h>
#include <string.h>
#include "mycollec.h"

void static writem(Object *o, void* s)
{
 /*if(strcmp(o->nameOf(),"String") == 0)
 {
  String *p=(String*)o;
  p->printOn();
 }
 if(strcmp(o->nameOf(),"Integer") == 0)
 {
  Integer *p=(Integer*)o;
  p->printOn();
 }*/
 o->printOn();
 cout << ' ' << (char*)s << ' ';
}

Collection::Collection(Collection& c)
{
 rad=new Node(*(c.rad->info));
 Node *p1,*p2,*aux;
 aux=rad;
 for(p2=c.rad;p2;p2=p2->urm)
 {
  p1=new Node(*(p2->info));
  aux->urm=p1;
  aux=p1;
 }
}

int Collection::isEqual(Collection& s)
{
 Node *p1,*p2;
 for(p1=rad,p2=s.rad;p1&&p2;p1=p1->urm,p2=p2->urm)
	if(!((*(p1->info))!=(*(p2->info))))return 0;
 if(p1||p2)return 0;
 return 1;
}

void Collection::printOn()
{
 cout << "( ";
 forEach(writem,";");
 cout << (char)8 << (char)8 << ")";
}


void Collection::Insert(int Pos,Object &ob)
{
 Node *p,*aux;
 int i;
 for(p=rad,i=0;p&&i<Pos-1;p=p->urm,i++);
 aux=new Node(ob);
 if(!i && p)
 {
  aux->urm=rad;
  rad=aux;
 }
 else if (p)
 {
  aux->urm=p->urm;
  p->urm=aux;
 }
}

void Collection::Remove(int Pos)
{
 Node *p,*aux;
 int i;
 for(i=0,aux=p=rad;aux&&i<Pos-1;i++,p=aux,aux=aux->urm);
 if(!i && aux)
 {
  rad=rad->urm;
  delete aux;
 }
 else if (aux)
 {
  p->urm=aux->urm;
  delete aux;
 }
}

void Collection::forEach(iterFuncType iterf, void *args)
{
 Node *p;
 for(p=rad; p; p=p->urm) //aici era o mika eroare
   (*iterf) (p->info,args);
}

void Collection::add(Object& o)
{
 Node *aux;
 aux=new Node(o);
 // printf("%s ", o.nameOf());
 //aux->info->printOn();
 aux->urm=rad;
 rad=aux;
}

void Collection::detach(Object& o)
{
 Node *p,*aux;
 for(p=aux=rad;aux && *(aux->info) != o; p = aux, aux = aux->urm);
 if((aux==p) && (p))
 {
  rad=rad->urm;
  delete aux;
 }
 else if(aux)
 {
  p->urm=aux->urm;
  delete aux;
 }
}

Object& Collection::firstThat(condFuncType condf, void *args)
{
 Node *p;
 for(p=rad;p;p=p->urm)
  if( (*condf) (p->info,args) )
   return (*(p->info));
 return *ZERO;
}


Collection::~Collection()
{
 Node *p=rad;
 while(rad)
 {
  rad=rad->urm;
  delete p;
  p=rad;
 }
}

