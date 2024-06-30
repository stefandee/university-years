#include <io.h>
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <alloc.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "arbore.h"

class NewArb : public Arbore{
 public :
	virtual void Action(ANod *what){printf("%s\n",what->info.data);};
 };

void menu()
 {
	clrscr();
	gotoxy(10,10);printf("1.Afisare arbore");
	gotoxy(10,11);printf("2.Punctul b)");
	gotoxy(10,12);printf("3.Adincimea arborelui");
	gotoxy(10,13);printf("4.Frunze");
	gotoxy(10,14);printf("5.Descendenti");
	gotoxy(10,15);printf("6.Rude apropiate");
	gotoxy(10,16);printf("7.Suprimari");
	gotoxy(10,17);printf("8.Iesire");
 }

void main ()
 {
	List *L = new List;
	NewArb *A = new NewArb;
	int handle,key,cnt=0,lvl1,lvl2;
	char *word,temp;
	LNod* aux;
	ANod *nod1,*nod2;
	PString str;

	A->Init();

	//open a file for reading words into a list
	word = (char*) malloc(200);
	handle=open("paa1_3_4.tst",O_RDONLY);
	if (handle==-1) {
		printf("couldn't open file");
		exit(1);
		}
	while (!eof(handle)) {
	 read(handle,&temp,1);
	 if (isalnum(temp)) *(word+cnt++) = temp;
		else {
			*(word+cnt)='\0';
			str.Init(word);
			A->Ins(&str);
			cnt = 0;
		}
	}
	free(word);
	close(handle);

	menu();
	while((key=getch())!='8') {
	 switch(key) {
	 case '1' : clrscr();
							gotoxy(15,1);printf("Afisare arbore in inordine");gotoxy(1,10);A->Ino(A->Root);getch();clrscr();
							gotoxy(15,1);printf("Afisare arbore in preordine");gotoxy(1,10);A->Pre(A->Root);getch();clrscr();
							gotoxy(15,1);printf("Afisare arbore in postordine");gotoxy(1,10);A->Post(A->Root);getch();clrscr();
							A->TreePrint(40,1,A->Root);getch();
							menu();break;
	 case '2' : clrscr();

							printf("introduceti prima cheie : ");scanf("%s",word);str.Init(word);
							nod1 = A->Search(str,A->Root);//lvl1 = A->Depth(str);
							printf("introduceti a doua cheie : ");scanf("%s",word);str.Init(word);
							nod2 = A->Search(str,A->Root);//lvl2 = A->Depth(str);

							if ((nod1==NULL) || (nod2==NULL)) {printf("Un nod nu exista");getch();menu();break;};

							printf("nodul %s a fost gasit pe nivelul %d\n",nod1->info.data,nod1->aparitii);
							printf("nodul %s a fost gasit pe nivelul %d\n",nod2->info.data,nod2->aparitii);

							if (lvl1==lvl2) printf("nodurile sint pe acelasi nivel !");
								else if (lvl1>lvl2)
									if (A->Search(nod1->info,nod2)!=NULL) printf("nodul %s e stramos al nodului %s",nod2->info.data,nod1->info.data);
										else printf("nodul %s nu e stramos al nodului %s",nod2->info.data,nod1->info.data);
											else if (A->Search(nod2->info,nod1)!=NULL) printf("nodul %s e stramos al nodului %s",nod1->info.data,nod2->info.data);
										else printf("nodul %s nu e stramos al nodului %s",nod1->info.data,nod2->info.data);

							getch();
							menu();
							break;
	 }
	}
 }