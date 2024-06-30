#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <string.h>

#define optiune1 " 1 . Introducere candidat "
#define optiune2 " 2 . Afisare "
#define optiune3 " 3 . Afara !!! "
#define optiune4 " 4 . Salvare "
#define optiune5 " 5 . Incarcare "

#define lnume 20
#define probe 3
#define calc_medie(n1,n2,n3) ((n1+n2+n3)/probe)
#define maxopt 400

typedef struct
		{ char nume[lnume];
		  float  note[probe];
		  float  media;
		  char sc;
		  char optiune;
		} candidat;
typedef candidat concurs[maxopt];
concurs autom,calc;
int aindex=0,cindex=0,locuri[2]={5,5};

void meniu()
{
clrscr();
gotoxy(15,10);printf(optiune1);
gotoxy(15,11);printf(optiune2);
gotoxy(15,12);printf(optiune3);
gotoxy(15,13);printf(optiune4);
gotoxy(15,14);printf(optiune5);
}

void introducere()
{
candidat manv;
clrscr();
gotoxy(15,10);printf(" Nume  : ");scanf("%20s",&manv.nume);
for (int i=0;i<probe;i++)
{
    gotoxy(15,11+i);
    printf(" Nota %d : ",i+1);
    scanf("%f",&manv.note[i]);
    if (manv.note[i]>10) i--;
}
manv.media=calc_medie(manv.note[0],manv.note[1],manv.note[2]);

while (gotoxy(15,11+probe),printf(" Stare civila  : "),manv.sc=getche(),(manv.sc!='i') && (manv.sc!='n'));
while (gotoxy(15,11+probe+1),printf(" Optiune  : "),manv.optiune=getche(),(manv.optiune!='a') && (manv.optiune!='c'));

switch (manv.optiune)
	{
	case 'a' : autom[aindex++]=manv;break;
	case 'c' : calc[cindex++]=manv;break;
	}
}

void sortare(concurs de_sort,int index)
{
int i,j;
for (i=0;i<index;i++)
     {
     for (j=i;j<index;j++)
	if (i!=j)
	{
	  candidat aux;
	  if (de_sort[i].media<de_sort[j].media)
	  {
	     aux=de_sort[i];
	     de_sort[i]=de_sort[j];
	     de_sort[j]=aux;
	  }

	  if (de_sort[i].media==de_sort[j].media)
	     if (de_sort[i].note[0]<de_sort[j].note[0])
	     {
		aux=de_sort[i];
		de_sort[i]=de_sort[j];
		de_sort[j]=aux;
	     }
       }
     }
}

void nume_sort(concurs de_sort,int index)
{
int i,j;
for (i=0;i<index;i++)
     for (j=i;j<index;j++)
	if (i!=j)
	{
	  candidat aux;
	  if (strcmp(de_sort[i].nume,de_sort[j].nume)>0)
	  {
	     aux=de_sort[i];
	     de_sort[i]=de_sort[j];
	     de_sort[j]=aux;
	  }
       }
}


void afisare()
{
concurs aresp,cresp;
int arindex=0,crindex=0;
clrscr();
//sortare
sortare(autom,aindex);
sortare(calc,cindex);
gotoxy(20,1);cprintf("Candidatii reusiti - ordinea mediilor");
gotoxy(10,2);cprintf("Automatica");gotoxy(50,2);cprintf("Calculatoare");

for (int i=0;i<aindex;i++)
    {
    if ( (i<locuri[0]) || ((autom[i].media==autom[i-1].media) && (autom[i].note[0]==autom[i-1].note[0])))
	{
	gotoxy(1,3+i%10);
	cprintf("%s %.2f",autom[i].nume,autom[i].media);
	}
    else aresp[arindex++]=autom[i];

    }
for (i=0;i<cindex;i++)
    {
    if ( (i<locuri[1]) || ((calc[i].media==calc[i-1].media) && (calc[i].note[0]==calc[i-1].note[0])))
	{
	gotoxy(40,3+i%10);
	cprintf("%s %.2f",calc[i].nume,calc[i].media);
	}
    else cresp[crindex++]=calc[i];
    }

getch();
clrscr();

gotoxy(17,1);cprintf("Candidatii nereusiti - ordinea alfabetica");
gotoxy(10,2);cprintf("Automatica");gotoxy(50,2);cprintf("Calculatoare");

nume_sort(aresp,arindex);
nume_sort(cresp,crindex);

for (i=0;i<arindex;i++)
    {
    gotoxy(1,3+i%10);
    cprintf("%s %.2f",aresp[i].nume,aresp[i].media);
    }
for (i=0;i<crindex;i++)
    {
    gotoxy(40,3+i%10);
    cprintf("%s %.2f",cresp[i].nume,cresp[i].media);
    }

}

void salvare()
{
FILE *f;
clrscr();

if ((f = fopen("ABURELL.DAT", "wb"))== NULL)
   {
   gotoxy(30,12);printf("Eroare : nu gasesc fisierul.\n");
   delay(500);
   return;
   }

gotoxy(36,12);printf("Salvez...");
delay(500);
fwrite(&aindex,sizeof(int),1,f);
fwrite(&cindex,sizeof(int),1,f);
fwrite(autom,sizeof(candidat),aindex,f);
fwrite(calc,sizeof(candidat),cindex,f);
fclose(f);
}

void incarcare()
{
FILE *f;
clrscr();

if ((f = fopen("ABURELL.DAT", "rb"))== NULL)
   {
   gotoxy(30,12);printf("Eroare : nu gasesc fisierul.\n");
   delay(500);
   return;
   }

gotoxy(36,12);printf("Incarc...");
fread(&aindex,sizeof(int),1,f);
fread(&cindex,sizeof(int),1,f);
fread(autom,sizeof(candidat),aindex,f);
fread(calc,sizeof(candidat),cindex,f);

delay(500);
fclose(f);
}

void main()
{
int key;
candidat manv;
meniu();
while (key=getch())
     {
	switch (key)
	{
	case '3' : exit(1);
	case '1' : introducere();meniu();break;
	case '2' : afisare();getch();meniu();break;
	case '4' : salvare();meniu();break;
	case '5' : incarcare();meniu();break;
	}
     };
getch();
}