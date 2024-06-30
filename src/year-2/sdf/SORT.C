#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#define N 1000

long C,M,Elapsed;
int aux[N],tab[N];

void Replace(int *s,int *d,int To)
 {
  int i;
  for(i=0;i<To;i++,s[i]=d[i]);
 }

void Insertie(void)
 {
  clock_t gti,gtf;
  int i,j,x;

  printf("Sortare prin insertie...in curs de executie ");
  C=0;M=0;gti=clock();

  for(i=1;i<N;i++)
   {
	 x=tab[i];j=i-1;
	 M++;
	 while(tab[j]>x)
	  {
		tab[j+1]=tab[j];
		M++;
		C++;
		j-=1;
	  }
	 tab[j+1]=x;
	 M++;
   }
  gtf=clock();
  Elapsed=gtf-gti;
  printf("\nDone. Comparatii : %ld , Atribuiri : %ld , Timp : %f.Apasa o tasta\n",C,M,(float)Elapsed/CLK_TCK);
  getch();
 }

void InsBin()
 {
  clock_t gti,gtf;
  int i,j,s,d,m,x;

  printf("Sortare prin insertie binara ...in curs de executie ");
  C=0;M=0;gti=clock();
 for(i=0;i<N;i++)
  {
	x=tab[i];s=1;d=i-1;
	M++;
	while (s<=d)
	 {
	  m=(s+d)/2;
	  if (tab[m]>x) d=m-1;
			else s=m+1;
	  C++;C++;
	 }
	 for (j=i-1;j>s;j--,M++) tab[j+1]=tab[j];
	 tab[s]=x;
	 M++;
  }
  gtf=clock();
  Elapsed=gtf-gti;
  printf("\nDone. Comparatii : %ld , Atribuiri : %ld , Timp : %f.Apasa o tasta.\n",C,M,(float)Elapsed/CLK_TCK);
  getch();
 }

void Selectie()
 {
  clock_t gti,gtf;
  int i,j,k,x;

  printf("Sortare prin selectie ...in curs de executie ");
  C=0;M=0;gti=clock();

  for(i=1;i<N;i++)
	{
	  k=i; x=tab[i];M++;
	  for (j=i+1;j<N;j++)
		if (tab[j] < x)
			{
			 x=tab[j];
			 M++;C++;
			 k=j;
			}
	  tab[k]=tab[i]; tab[i]=x;
	  M+=2;
	 }

  gtf=clock();
  Elapsed=gtf-gti;
  printf("\nDone. Comparatii : %ld , Atribuiri : %ld , Timp : %f.Apasa o tasta.\n",C,M,(float)Elapsed/CLK_TCK);
  getch();

 }
void SelPerf()
 {
  clock_t gti,gtf;
  int i,j,min,x;

  printf("Sortare prin selectie performanta...in curs de executie ");
  C=0;M=0;gti=clock();

  for(i=1;i<N;i++)
	{
	 min=i;
	 M++;
	 for(j=i+1;j<N;j++) if (tab[j]<tab[min]) { min=j;M++;C++;C++;}
	 x=tab[min]; tab[min]=tab[i]; tab[i]=x;
	 M+=3;
	 C++;
	}

  gtf=clock();
  Elapsed=gtf-gti;
  printf("\nDone. Comparatii : %ld , Atribuiri : %ld , Timp : %f.Apasa o tasta.\n",C,M,(float)Elapsed/CLK_TCK);
  getch();
 }
void Bubble()
 {
  clock_t gti,gtf;
  int i,j,min,x;
  printf("Sortare prin bubble...in curs de executie ");
  C=0;M=0;gti=clock();

  for(i=1;i<N;i++,C++)
	for(j=N;j>i;j--,C++)
	 if (tab[j-1]>tab[j])
		{
		 x=tab[j-1];
		 tab[j-1]=tab[j];
		 tab[j]=x;
		 M+=3;
		 C++;
		}

  gtf=clock();
  Elapsed=gtf-gti;
  printf("\nDone. Comparatii : %ld , Atribuiri : %ld , Timp : %f.Apasa o tasta.\n",C,M,(float)Elapsed/CLK_TCK);
  getch();
 }

void Toate()
 {
  printf("KARG of WOS 21.03.1996\n");
  Replace(aux,tab,N);Insertie();Replace(tab,aux,N);
  Replace(aux,tab,N);InsBin();Replace(tab,aux,N);
  Replace(aux,tab,N);Selectie();Replace(tab,aux,N);
  Replace(aux,tab,N);SelPerf();Replace(tab,aux,N);
  Replace(aux,tab,N);Bubble();Replace(tab,aux,N);
  getch();
 }

void meniu(void)
 {
  clrscr();
  gotoxy(10,10);printf("1.Sortare prin Insertie");
  gotoxy(10,11);printf("2.Sortare prin Insertie binara");
  gotoxy(10,12);printf("3.Sortare prin selectie");
  gotoxy(10,13);printf("4.Sortare prin selectie performanta");
  gotoxy(10,14);printf("5.Sortare prin bubblesort");
  gotoxy(10,15);printf("6.Toate");
  gotoxy(10,16);printf("7.Exit");
 }

void main(void)
 {
  int i;
  char key;

  randomize();
  for(i=0;i<N;i++,tab[i]=rand(),aux[i]=tab[i]);

  meniu();
  while((key=getch())!='7')
	{
	 switch(key)
	  {
		case '1' : clrscr();Replace(aux,tab,N);Insertie();Replace(tab,aux,N);meniu();break;
		case '2' : clrscr();Replace(aux,tab,N);InsBin();Replace(tab,aux,N);meniu();break;
		case '3' : clrscr();Replace(aux,tab,N);Selectie();Replace(tab,aux,N);meniu();break;
		case '4' : clrscr();Replace(aux,tab,N);SelPerf();Replace(tab,aux,N);meniu();break;
		case '5' : clrscr();Replace(aux,tab,N);Bubble();Replace(tab,aux,N);meniu();break;
		case '6' : clrscr();Replace(aux,tab,N);Toate();Replace(tab,aux,N);meniu();
     }
	}
 }