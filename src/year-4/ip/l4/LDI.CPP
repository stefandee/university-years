#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream.h>

// should be removed for unix portability
#include <conio.h>
#include "mystring.h"

char CLista;

template <class TNod>
class Nod
{
  public :
  class TNod data;
  Nod  *prev, *next;
  Nod (TNod d)
  {
      prev = NULL;
      next = NULL;
      data = d;
  }
}

template <class TLDI>
class LDI
{
	 Nod<TLDI> *first, *last, *pos;
	 public :
		 LDI() { first = NULL; last = NULL; pos = NULL; }
		 int empty();
		 void put(TLDI);
		 void afis();
		 int isfirst();
		 int islast();
		 void advance();
		 void reverse();
		 void swap(int);
		 int position();
		 void put_i_th(TLDI, int);
		 int count();
		 TLDI item();
		 ~LDI() { Nod<TLDI> *tmp; for(tmp = first; tmp != last; ) { tmp = tmp->next; delete tmp; } }
		 TLDI& operator[](int i)
		 {
		     Nod<TLDI> *tmp;
		     int j = 1;

		     for(tmp = first; j < i; tmp = tmp->next, j++);
		     return tmp->data;
		 }
}

template <class TLDI> int LDI<TLDI>::empty()
{
	 return (first == NULL);
}

template <class TLDI> void LDI<TLDI>::put(TLDI d)
{
   Nod<TLDI> *tmp = new Nod<TLDI>(d);
   if (pos == NULL)
   {
      first = tmp;
      last = tmp;
      first->prev = NULL;
      first->next = last;
      last->next = NULL;
      last->prev = first;
      pos = first;
   }
   else
   {
      tmp->next = pos->next;
      pos->next = tmp;
      tmp->prev = pos;
      if (last == pos) last = tmp;
      pos = tmp;
   }
}

template <class TLDI> void LDI<TLDI>::put_i_th(TLDI d, int i)
{
	 Nod<TLDI> *tmp = new Nod<TLDI>(d), *nodtmp;
	 int j = 1;

	 if (first == NULL) return;
	 if (i < 0) return;
	 if (i == 1) { tmp->next = first; tmp->prev = NULL; first = tmp; return;}
	 if (i >= count()) { tmp->next = NULL; tmp->prev = last; last->next = tmp; return;}

	 for(nodtmp = first; j < i; nodtmp = nodtmp->next, j++);

	 nodtmp->prev->next = tmp;
	 tmp->next = nodtmp; tmp->prev = nodtmp->prev;
	 nodtmp->prev = tmp;
}


template <class TLDI> int LDI<TLDI>::isfirst()
{
	 return (pos == first);
}

template <class TLDI> int LDI<TLDI>::islast()
{
	 return (pos == last);
}

template <class TLDI> void LDI<TLDI>::advance()
{
	 pos = pos->next;
	 if (pos == NULL) pos = first;
}

template <class TLDI> void LDI<TLDI>::reverse()
{
	 pos = pos->prev;
	 if (pos == NULL) pos = last;
}

template <class TLDI> void LDI<TLDI>::swap(int k)
{
	 int j = 1;
	 TLDI tmp;
	 Nod<TLDI> *i;

	 if ((first == NULL) || (count() < k) || (k <= 0)) return;
	 for(i=first; (j < k); i = i->next, j++);

	 tmp = i->data; i->data = pos->data; pos->data = tmp;
}

template <class TLDI> int LDI<TLDI>::count()
{
	 int j = 0;
	 Nod<TLDI> *i;

	 if (first == NULL) return 0;
	 for(i=first; i != NULL; i = i->next, j++);
	 return j;
}

template <class TLDI> int LDI<TLDI>::position()
{
	 int j = 1;
	 Nod<TLDI> *i;

	 if (first == NULL) return 0;
	 for(i=first; i != pos; i = i->next, j++);
	 return j;
}

template <class TLDI> TLDI LDI<TLDI>::item()
{
	 return pos->data;
}

template <class TLDI> void LDI<TLDI>::afis()
{
	 Nod<TLDI> *i;
	 for(i=first; i != NULL; i = i->next)
	 {
	    switch (CLista)
	    {
	       case 'I' : printf("%d->", i->data);break;
	       case 'D' : printf("%f->", i->data);break;
	       case 'S' : printf("%s->", i->data);break;
	    }
	 }
	 printf("NULL \n");
}

// descriere : functia care deseneaza meniul
// inputs    : none
// outputs   : text pe ecran
void meniu()
{
		 printf("\n");
		 printf("<1> Count      <2> Empty\n");
		 printf("<3> IsFirst    <4> IsLast\n");
		 printf("<5> Pos        <6> Item  \n");
		 printf("<7> Put...     <8> Put_i_th... \n");
		 printf("<9> Swap...    <0> Show list\n");
		 printf("<A> Advance    <R> Reverse\n");
		 printf("\n");
}


// descriere : functia main
// inputs    : none
// outputs   : none
void main()
{
   char key;
   int index;
   char* datachr = (char*)malloc(255);
   int dataint;
   double datadbl;
   class MyStr x;
   LDI<class MyStr> sldi;
   LDI<int> ildi;
   LDI<double> dldi;

   printf("Cu ce lista lucram ? [I]nteger, [D]ouble, [S]tring ");
   scanf("%c", &CLista);
   CLista = toupper(CLista);
   if ((CLista != 'I') && (CLista != 'D') && (CLista != 'S')) { CLista = 'I'; printf("Assuming default list : INTEGER\n"); }

   meniu();
   while ( (key = toupper(getch())) != 'X')
     {
       switch(key)
       {
	   case '1' : switch(CLista)
		      {
			 case 'I' : printf("Lista are %d elemente\n",ildi.count());break;
			 case 'D' : printf("Lista are %d elemente\n",dldi.count());break;
			 case 'S' : printf("Lista are %d elemente\n",sldi.count());break;
		      }
		      break;
	   case '2' : switch(CLista)
		      {
			 case 'I' : if (ildi.empty()) printf("Lista e vida\n"); else printf("Lista nu e vida\n");break;
			 case 'D' : if (dldi.empty()) printf("Lista e vida\n"); else printf("Lista nu e vida\n");break;
			 case 'S' : if (sldi.empty()) printf("Lista e vida\n"); else printf("Lista nu e vida\n");break;
		      }
		      break;
	   case '3' : switch(CLista)
		      {
			 case 'I' : if (ildi.isfirst()) printf("E pe primul nod\n"); else printf("Nu e pe primul nod\n");break;
			 case 'D' : if (dldi.isfirst()) printf("E pe primul nod\n"); else printf("Nu e pe primul nod\n");break;
			 case 'S' : if (sldi.isfirst()) printf("E pe primul nod\n"); else printf("Nu e pe primul nod\n");break;
		      }
		      break;
	   case '5' : switch(CLista)
		      {
			 case 'I' : printf("Cursorul e pe pozitia %d \n",ildi.position());break;
			 case 'D' : printf("Cursorul e pe pozitia %d \n",dldi.position());break;
			 case 'S' : printf("Cursorul e pe pozitia %d \n",sldi.position());break;
		      }
		      break;
	   case '6' : switch(CLista)
		      {
			 case 'I' : printf("Nodul curent contine valoarea %i \n", ildi.item());break;
			 case 'D' : printf("Nodul curent contine valoarea %d \n", dldi.item());break;
			 case 'S' : printf("Nodul curent contine valoarea %s \n", sldi.item());break;
		      }
		      break;
	   case '7' : switch(CLista)
		      {
			 case 'I' : printf("Baga data : ");cin >> dataint;ildi.put(dataint); ildi.afis(); printf("Cursorul e pe pozitia %d \n",ildi.position());break;
			 case 'D' : printf("Baga data : ");cin >> datadbl;dldi.put(datadbl); dldi.afis(); printf("Cursorul e pe pozitia %d \n",dldi.position());break;
			 case 'S' : printf("Baga data : ");
				    scanf("%s",datachr);
				    sldi.put(MyStr(datachr));
				    sldi.afis();
				    printf("Cursorul e pe pozitia %d \n",sldi.position());
				    break;
		      }
		      break;
	   case '8' : printf("Baga indexu' : ");scanf("%d", &index);
		      switch(CLista)
		      {
			 case 'I' : printf("Baga data : ");cin >> dataint;ildi.put_i_th(dataint, index);ildi.afis();break;
			 case 'D' : printf("Baga data : ");cin >> datadbl;dldi.put_i_th(datadbl, index);dldi.afis();break;
			 case 'S' : printf("Baga data : ");scanf("%s",datachr);sldi.put_i_th(MyStr(datachr), index);sldi.afis();break;
		      }
		      break;
	   case '9' : printf("Baga indexu' : ");scanf("%d", &index);
		      switch(CLista)
		      {
			 case 'I' : ildi.swap(index);ildi.afis();break;
			 case 'D' : dldi.swap(index);ildi.afis();break;
			 case 'S' : sldi.swap(index);ildi.afis();break;
		      }
		      break;
	   case 'A' : switch(CLista)
		      {
			 case 'I' : ildi.advance();break;
			 case 'D' : dldi.advance();break;
			 case 'S' : sldi.advance();break;
		      }
		      break;
	   case 'R' : switch(CLista)
		      {
			 case 'I' : ildi.reverse();break;
			 case 'D' : dldi.reverse();break;
			 case 'S' : sldi.reverse();break;
		      }
		      break;
	   case '0' : switch(CLista)
		      {
			 case 'I' : ildi.afis();break;
			 case 'D' : dldi.afis();break;
			 case 'S' : sldi.afis();break;
		      }
		      break;
       }
       meniu();
     }
   free(datachr);
}