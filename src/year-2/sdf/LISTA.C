#include <alloc.h>
#include <conio.h>
#include <stdio.h>

typedef struct pers
				{
				char nume[10];
				int virsta;
				struct pers* urm;
				} persoana;

persoana *first=NULL,*dummy=NULL;

void menu(void)
{
clrscr();
gotoxy(10,10);printf("1 . Introducere in lista");
gotoxy(10,11);printf("2 . Afisare lista");
gotoxy(10,12);printf("3 . Stergere din lista");
gotoxy(10,13);printf("4 . Iesire");
}

void baga(void);
void scrie(void);

void main(void)

{char ch="";
menu();
dummy=(persoana*)malloc(sizeof(persoana));

while (ch!='4')
			{
				ch=getch();
				switch(ch)
				{
					case '1' : baga();getch();menu();break;
					case '2' : scrie();getch();menu();break;
					case '3' : ;
				}
			}
}

void baga(void)
{
persoana *p1=NULL,*p2=NULL,*p3=NULL;
char nume[10];
int virsta;
clrscr();
p2=(persoana*)malloc(sizeof(persoana));
gotoxy(10,10);printf("Numele : ");scanf("%s",nume);
gotoxy(10,11);printf("Virsta : ");scanf("%d",&virsta);
for(p1=p3=first;strcmp(p1->nume,nume)<0 && p1!=NULL;p3=p1,p1=p1->urm);
if (p1==first)
		{
		p2=(persoana*)malloc(sizeof(persoana));
		p2->urm=first;
		strcpy(p2->nume,nume);
		p2->virsta=virsta;
		first=p2;
		printf("primul !");
		}
		else if (p1==NULL)
						{
						p2=(persoana*)malloc(sizeof(persoana));
						p3->urm=p2;
						p2->urm=NULL;
						strcpy(p2->nume,nume);
						p2->virsta=virsta;
						printf("la capat !");
						}
						else {
									p2=(persoana*)malloc(sizeof(persoana));
									p2->urm=p1;
									p3->urm=p2;
									strcpy(p2->nume,nume);
									p2->virsta=virsta;
									printf("intre !");
								 };
}

void scrie(void)
{
persoana *p1=NULL;
clrscr();
if (first==NULL)
		{
		gotoxy(10,10);
		printf("Lista e goala !");
		return 0;
		}
gotoxy(1,1);
for(p1=first;p1!=NULL;p1=p1->urm) printf("\n%s  %i",p1->nume,p1->virsta);
}












