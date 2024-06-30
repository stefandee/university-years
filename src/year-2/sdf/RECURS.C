#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <alloc.h>

#define N 10

int tab[N];

typedef struct lst {
					int inf;
					struct lst* urm;
					} lista;
lista *first=NULL;

void baza(long int base,long int nr)
 {
  long int aux1,aux2;
  aux1=nr%base;aux2=nr/base;
  if (aux2) baza(base,aux2);
  if (aux1>9) printf("%c",(aux1-10+'A'));
	else printf("%c",(aux1+'0'));
 }

void tabinv(int dim,int cnt)
 {
  cnt+=1;
  if (cnt<dim) tabinv(dim,cnt);
  printf("%d ",tab[cnt]);
 }

void baga_in_lista(lista ce)
 {
  lista * aux,*aux1;
  aux=(lista*)malloc(sizeof(lista));
  aux->inf=ce.inf;
  aux->urm=NULL;
  if (first==NULL) first=aux;
	else
	 {
	  /*aux->urm=first->urm;*/
	  for(aux1=first;(aux1->urm!=NULL);aux1=aux1->urm);
	  aux1->urm=aux;
	 }
 }

void listeaza()
 {
  lista * aux;
  for(aux=first;(aux!=NULL);printf("%i ",aux->inf),aux=aux->urm);
 }

void listainv(lista* aux)
 {
  if (aux->urm!=NULL) listainv(aux->urm);
  printf("%d ",aux->inf);
 }

void main()
 {
  int i, n,b;
  lista ce;

  clrscr();
  printf ("numarul: ");
  scanf ("%d",&n);


  printf ("\nbaza: ");
  scanf ("%d",&b);
  printf("nr in baza este : ");baza(b,n);
  printf("\ntabloul este : ");for(i=0;i<N;i++,printf("%i ",tab[i]=random(30)));
  printf("\ntabloul inversat este : ");tabinv(N,0);
  printf("\n");
  for(i=0;i<10;i++)
	{
	 ce.inf=random(255);
	 printf("%i ",ce.inf);
	 baga_in_lista(ce);
	}
  printf("\n");listeaza();printf("\n");listainv(first);
  getch();
 }