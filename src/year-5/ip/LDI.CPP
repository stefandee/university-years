#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// should be removed for unix portability
#include <conio.h>

//char list[3][10] = {"Interger", "Double", "String"};
//int crtlist = 0;

template <class TNod>
class Nod
{
  public :
  TNod data;
  Nod  *prev, *next;
  Nod (TNod d)
  {
      prev = NULL; next = NULL;
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
		 TLDI	item();
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
			 first = tmp;last = tmp;
			 first->prev = NULL;first->next = last;
			 last->next = NULL; last->prev = first;
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
	 /* AICI TREBUIE UMBLAT */
	 for(i=first; i != NULL; i = i->next) printf("%d -> ", i->data);
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
		 int data;
		 LDI<int> ldi;

		 meniu();
		 while ( (key = toupper(getch())) != 'X')
     {
       switch(key)
       {
		 case '1' : printf("Lista are %d elemente\n",ldi.count());break;
		 case '2' : if (ldi.empty()) printf("Lista e vida\n"); else printf("Lista nu e vida\n");break;
		 case '3' : if (ldi.isfirst()) printf("E pe primul nod\n"); else printf("Nu e pe primul nod\n");break;
		 case '4' : if (ldi.islast()) printf("E pe ultimul nod\n"); else printf("Nu e pe ultimul nod\n");break;
		 case '5' : printf("Cursorul e pe pozitia %d \n",ldi.position());break;
		 case '6' : /* AICI TREBUIE UMBLAT */
								printf("Nodul curent contine valoarea %d \n", ldi.item());
								break;
		 case '7' : /* AICI TREBUIE UMBLAT */
								printf("Baga data : ");scanf("%d", &data);
								ldi.put(data); ldi.afis(); printf("Cursorul e pe pozitia %d \n",ldi.position());
								break;
		 case '8' : /* AICI TREBUIE UMBLAT */
								printf("Baga data : ");scanf("%d", &data);
								printf("Acum baga indexu' : ");scanf("%d", &index);
								ldi.put_i_th(data, index);
								ldi.afis();
								break;
		 case '9' : printf("Baga indexu' : ");scanf("%d", &index);
								ldi.swap(index);
								break;
		 case 'A' : ldi.advance();break;
		 case 'R' : ldi.reverse();break;
		 case '0' : ldi.afis();break;
       }
       meniu();
     }
}