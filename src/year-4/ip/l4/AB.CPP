#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// should be removed for unix portability
#include <conio.h>
#include "mystring.h"

char CArb;

template <class TANod>
class Nod
{
  public :
  TANod data;
  Nod *left, *right;
  Nod (TANod d)
  {
     left = NULL;
     right = NULL;
     data = d;
  }
}

template <class TAB>
class AB
{
   Nod<TAB>* root;

   /* functie recursiva de adaugat un nod la arbore */
   void r_put(Nod<TAB>* crt, Nod<TAB>* in)
   {
      if (crt->data > in->data)
      {
	 if (crt->left == NULL) crt->left = in;
	 else r_put(crt->left, in);
      }
      else if (crt->right == NULL) crt->right= in; else r_put(crt->right, in);
   }

   /* functie recursiva de afisat nodurile */
   void r_afis(Nod<TAB>* crt, int spaces)
   {
      int i;
      if (crt != NULL)
      {
	 for(i = 0; i < spaces; i++) printf(" ");
	 switch (CArb)
	 {
	     case 'I' : printf("юд%d\n", crt->data);break;
	     case 'D' : printf("юд%f\n", crt->data);break;
	     case 'S' : printf("юд%s\n", crt->data);break;
	 }
	 r_afis(crt->left, spaces+3);
	 r_afis(crt->right, spaces+3);
      }
   }

   /* functie recursiva de numarat noduri*/
   int r_count(Nod<TAB> *crt)
   {
      int leftcount = 0, rightcount = 0;
      if (crt->left != NULL) leftcount = r_count(crt->left);
      else leftcount = 0;
      if (crt->right != NULL) rightcount = r_count(crt->right);
      else rightcount = 0;
      return leftcount + rightcount + 1;
   }

   void r_inordine(Nod<TAB> *crt)
   {
      if (crt->left != NULL) r_inordine(crt->left);
      switch (CArb)
      {
	  case 'I' : printf("%d ", crt->data);break;
	  case 'D' : printf("%f ", crt->data);break;
	  case 'S' : printf("%s ", crt->data);break;
      }
      if (crt->right != NULL) r_inordine(crt->right);
   }

   void r_preordine(Nod<TAB> *crt)
   {
      switch (CArb)
      {
	  case 'I' : printf("%d ", crt->data);break;
	  case 'D' : printf("%f ", crt->data);break;
	  case 'S' : printf("%s ", crt->data);break;
      }
      if (crt->left != NULL) r_preordine(crt->left);
      if (crt->right != NULL) r_preordine(crt->right);
   }

   void r_postordine(Nod<TAB> *crt)
   {
      if (crt->left != NULL) r_postordine(crt->left);
      if (crt->right != NULL) r_postordine(crt->right);
      switch (CArb)
      {
	  case 'I' : printf("%d ", crt->data);break;
	  case 'D' : printf("%f ", crt->data);break;
	  case 'S' : printf("%s ", crt->data);break;
      }
   }

   public :
      AB() { root = NULL; }
      int count();
      int empty() { return (root == NULL); }
      void put(TAB data);
      void afis();
      void inordine();
      void preordine();
      void postordine();
}

template <class TAB> void AB<TAB>::put(TAB data)
{
   Nod<TAB> *in = new Nod<TAB>(data);
   if (root == NULL) root = new Nod<TAB>(data);
      else r_put(root, in);
}

template <class TAB> void AB<TAB>::afis()
{
    r_afis(root, 0);
}

template <class TAB> int AB<TAB>::count()
{
    if (root == NULL) return 0; else return r_count(root);
}

template <class TAB> void AB<TAB>::inordine()
{
    if (root != NULL) r_inordine(root);
}

template <class TAB> void AB<TAB>::preordine()
{
    if (root != NULL) r_preordine(root);
}

template <class TAB> void AB<TAB>::postordine()
{
    if (root != NULL) r_postordine(root);
}

void meniu()
{
   printf("\n");
   printf("<C> Count     <E> Empty\n");
   printf("<P> Put       <A> Afisare\n");
   printf("<I> Inordine    <R> Preordine    <S> Postordine\n");
   printf("<X> Exit\n");
   printf("\n");
}

/*switch(CArb)
		    {
		       case 'I' : ;break;
		       case 'D' : ;break;
		       case 'S' : ;break;
		    }
		    break;*/
void main()
{
   char key;
   int dataint;
   float datadbl;
   char* datachr;
   AB<int> iab;
   AB<double> dab;
   AB<class MyStr> sab;

   printf("Cu ce arbore lucram ? ([I]nteger, [D]ouble, [S]tring) ");
   scanf("%c", &CArb);
   CArb = toupper(CArb);
   if ((CArb != 'I') && (CArb != 'D') && (CArb != 'S')) { CArb = 'I'; printf("Assuming default list : INTEGER\n"); }

   meniu();
   while ( (key = toupper(getch())) != 'X')
   {
      switch(key)
      {
	 case 'P' : switch(CArb)
		    {
		       case 'I' : printf("Da'i cu informatzia : ");scanf("%d", &dataint);iab.put(dataint);break;
		       case 'D' : printf("Da'i cu informatzia : ");scanf("%f", &datadbl);dab.put(datadbl);break;
		       case 'S' : printf("Da'i cu informatzia : ");scanf("%s", datachr);sab.put(MyStr(datachr));break;
		    }
		    break;
	 case 'A' : switch(CArb)
		    {
		       case 'I' : iab.afis();break;
		       case 'D' : dab.afis();break;
		       case 'S' : sab.afis();break;
		    }
		    break;
	 case 'E' : switch(CArb)
		    {
		       case 'I' : if (iab.empty()) printf("Arborele e gol (pushka).\n"); else printf("Arborele nu e gol.\n"); break;
		       case 'D' : if (dab.empty()) printf("Arborele e gol (pushka).\n"); else printf("Arborele nu e gol.\n"); break;;
		       case 'S' : if (sab.empty()) printf("Arborele e gol (pushka).\n"); else printf("Arborele nu e gol.\n"); break;
		    }
		    break;
	 case 'C' : switch(CArb)
		    {
		       case 'I' : printf("Arborele contzine %d nod(uri).\n", iab.count());break;
		       case 'D' : printf("Arborele contzine %d nod(uri).\n", dab.count());break;
		       case 'S' : printf("Arborele contzine %d nod(uri).\n", sab.count());break;
		    }
		    break;
	 case 'I' : switch(CArb)
		    {
		       case 'I' : iab.inordine();break;
		       case 'D' : dab.inordine();break;
		       case 'S' : sab.inordine();break;
		    }
		    break;
	 case 'R' : switch(CArb)
		    {
		       case 'I' : iab.preordine();break;
		       case 'D' : dab.preordine();break;
		       case 'S' : sab.preordine();break;
		    }
		    break;
	 case 'S' : switch(CArb)
		    {
		       case 'I' : iab.postordine();break;
		       case 'D' : dab.postordine();break;
		       case 'S' : sab.postordine();break;
		    }
		    break;
      }
      meniu();
   }
}
