#include <stdio.h>
#include <conio.h>
#include <alloc.h>

typedef struct cel
				{
					int info;
					struct cel *left,*right;
				}
				celula;

celula *root;

void meniu()
	{
		clrscr();
		gotoxy(10,10);printf("1.Introducere");
		gotoxy(10,11);printf("2.Aratare");
		gotoxy(10,12);printf("3.Stergere");
		gotoxy(10,13);printf("4.Iesire");
	}

void introd();
void afisare();
void sterge();

void main(void)
	{
		char ch;
		meniu();
		while((ch=getch())!='4')
			{
				switch (ch)
					{
						case '1' : introd();meniu();break;
						case '2' : afisare();getch();meniu();break;
						case '3' : sterge();meniu();break;
					}
			}
	}

static int info;

void getinfo(int* where)
	{
		gotoxy(10,10);printf("Valoarea de introdus : ");
		scanf("%d",where);
	}

celula* recursiv(celula* celcrt,int info)
	{
		if (celcrt->info>info)
			if (celcrt->left==NULL) return celcrt;
				else recursiv(celcrt->left,info);
		if (celcrt->info<=info)
			if (celcrt->right==NULL) return celcrt;
				else recursiv(celcrt->right,info);
	}

void introd()
	{
		celula *crt=NULL,*aux;
		clrscr();
		getinfo(&info);
		aux=(celula *)malloc(sizeof(celula));
		if (root==NULL)
			{
				aux->info=info;
				aux->left=NULL;
				aux->right=NULL;
				root=aux;
				return;
			}

		crt=recursiv(root,info);
		aux->left=NULL;
		aux->right=NULL;
		aux->info=info;
		if (crt->info>=info) crt->left=aux;
			else crt->right=aux;
	}

static int x,y;

void recafis(celula* crt)
	{
		x-=4;y++;if (crt->left!=NULL) recafis(crt->left);x+=4;y--;
		gotoxy(x,y);printf("%d ",crt->info);
		x+=4;y++;if (crt->right!=NULL) recafis(crt->right);x-=4;y--;
	}

void afisare()
	{
	clrscr();
	x=40;y=1;
	recafis(root);
	}
void sterge()
	{
	}


