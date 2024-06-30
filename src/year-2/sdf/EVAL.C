#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <alloc.h>
#include <stdlib.h>

#define NUMAR 10

int atom,valoare;
typedef struct n
					{
						int v;
						struct n* left,*right;
					} nod;

nod* EXPRESIE(void);

int getstr(void)
	{
		char c;

		while((c=getchar())==' ' || (c=='\t'));

		if (!isdigit(c)) return c;

		valoare=c-'0';
		while(isdigit(c=getchar())) valoare=valoare*10+c-'0';

		ungetc(c,stdin);
		return NUMAR;
	}

nod* DoNode(int v,nod* left,nod* right)
	{
		nod* aux;
		if ( (aux=(nod*)malloc(sizeof(nod)))==NULL)
			{
				printf("Allocation error .");
				abort();
			}
			else
				{
					aux->left=left;
					aux->right=right;
					aux->v=v;
					return aux;
				}
	 return NULL;
	}

nod* FACTOR()
	{
		int op;
		nod* v;

		if (atom==NUMAR)
				{
					v=DoNode(valoare,NULL,NULL);
					atom=getstr();
					return v;
				}
		else if (atom=='(')
						{
							atom=getstr();
							v=EXPRESIE();
							if (atom==')') atom=getstr();
							return v;
						}
				 else return NULL;
	}

nod* TERMEN(void)
	{
		int op;
		nod *a,*b;

		a=FACTOR();

		while (atom=='*' || atom=='/')
			{
				op=atom;
				atom=getstr();
				b=FACTOR();
				a=DoNode(op,a,b);
			}
		return a;
	}

nod* EXPRESIE(void)
	{
		int op;
		nod *a,*b;

		a=TERMEN();

		while(atom=='+' || atom=='-')
			{
				op=atom;
				atom=getstr();
				b=TERMEN();
				a=DoNode(op,a,b);
			}
		return a;
	}

void PrintFP(nod* nodcrt)
	{
		if (nodcrt!=NULL)
				{
					PrintFP(nodcrt->left);
					PrintFP(nodcrt->right);
					switch(nodcrt->v)
						{
							case '+' :
							case '-' :
							case '*' :
							case '/' : printf("%c",nodcrt->v);break;
							default  : printf("%i",nodcrt->v);
						}
				}
	}

void PrintPaa(nod* nodcrt)
	{
		if (nodcrt!=NULL)
				{
					printf("(");
					PrintPaa(nodcrt->left);
					switch(nodcrt->v)
						{
							case '+' :
							case '-' :
							case '*' :
							case '/' : printf("%c",nodcrt->v);break;
							default  : printf("%i",nodcrt->v);
						}
					PrintPaa(nodcrt->right);
					printf(")");
				}
	}

int Eval(nod* crt)
	{
		if (crt!=NULL)
			{
				Eval(crt->left);
				Eval(crt->right);
				switch(crt->v)
					{
						case '+' : crt->v=crt->left->v+crt->right->v;break;
						case '-' : crt->v=crt->left->v-crt->right->v;break;
						case '*' : crt->v=crt->left->v*crt->right->v;break;
						case '/' : if (crt->right->v!=0) crt->v=crt->left->v*crt->right->v;
													else {
																printf("Divide by 0");
																abort();
															 }
					}
			}
		return NULL;
	}

void main(void)
	{
		nod* root;

		clrscr();
		printf("expresia : ");
		atom=getstr();
		root=EXPRESIE();
		printf("expresia in form poloneza : ");
		PrintFP(root);
		printf("\nexpresia cu paranteze e : ");
		PrintPaa(root);
		valoare=0;
		getch();
	}
