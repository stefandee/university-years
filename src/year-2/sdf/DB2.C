#include <stdio.h>
#include <conio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <io.h>
#include <dos.h>
#include <string.h>
#include <stdlib.h>

struct Ang { char nume[11];
		      int virsta;
		      char adresa[11];
		      char functie[5];
		    } a;

void menu(void)
{
clrscr();
gotoxy(10,10);printf("1 . Introducere persoana ");
gotoxy(10,11);printf("2 . Cautare persoana ");
gotoxy(10,12);printf("3 . Returneaza virsta unei persoane");
gotoxy(10,13);printf("4 . Returneaza adresa unei persoane");
gotoxy(10,14);printf("6 . Iesire");
}

void main(void)
{
  int fhandle,c=0;
  clrscr();
  fhandle=open("database.a",O_RDWR,S_IFREG);
  if (fhandle==-1) { printf("File does not exist.I will creat it !");
		    fhandle=open("database.a",O_CREAT | O_RDWR,S_IFREG);
		  }
  delay(500);
  window(0,0,79,24);
  menu();
  while (1!=0)
	{ c=getch();
	  switch (c)
	  {case '1' : { int rc;
		     clrscr() ;
		     gotoxy(10,10);printf("numele : ");
		     scanf("%s",&a.nume);
		     gotoxy(10,11);printf("adresa : ");
		     scanf("%s",&a.adresa);
		     gotoxy(10,12);printf("functia : ");
		     scanf("%s",&a.functie);
		     gotoxy(10,13);printf("virsta : ");
		     scanf("%d",&a.virsta);
		     rc=write(fhandle,&a,sizeof(a));
		     if (rc==-1) { gotoxy(10,14);
				   printf("eroare de scriere in fisier");
				   delay(500);}
		     menu();
		     break;
		     }
	  case '2' : { char cauta[11];
		       int rc;
		       clrscr();
		       gotoxy(10,10);
		       printf("ce nume cautati ? ");
		       scanf("%s",&cauta);
		      while ((rc=read(fhandle,&a,sizeof(a)))!=-1)
		       {
		       if (strcmp(a.nume,cauta)==0)
			  { clrscr();
			    printf("persoana cautata are datele : ");
			    printf("%s %s %d %s ",a.nume,a.adresa,a.virsta,a.functie);
			    getch();
			    menu();
			    break;
			   }
		       }
		       break;
		       }
	  case '6' : exit(1);
	  }
	 c=0;
	}

  getch();
}





