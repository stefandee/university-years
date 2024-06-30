#include "arbore.h"
#include <conio.h>

boolean operator >(PString s1, PString s2)
 {
	if (strcmp(s1.data,s2.data)>0) return 1;
		else return 0;
 }

boolean operator <(PString s1, PString s2)
 {
	if (strcmp(s1.data,s2.data)<0) return 1;
		else return 0;
 }

boolean operator ==(PString s1, PString s2)
 {
	if (strcmp(s1.data,s2.data)==0) return 1;
		else return 0;
 }

void List::Del()
 {
	LNod* aux,*aux1;
	if (First==NULL) return;
		 else for(aux=First;aux!=NULL;aux1=aux->next,free(aux->info.data),free(aux),aux=aux1);
 }

void List::Ins(char* info)
 {
	LNod* aux;
	aux = (LNod*)malloc(sizeof(NL));
	aux->info.Init(info);
	aux->next = First;
	First = aux;
	Cursor = First;
 }

void List::Print()
 {
	LNod* aux;
	for(aux = First;aux != NULL;printf("%s\n",aux->info.data),aux = aux ->next);
 }

ANod* recursiv(ANod* celcrt,PString info)
	{
		if (celcrt->info==info) return celcrt;
		if (celcrt->info>info)
			if (celcrt->left==NULL) return celcrt;
				else return recursiv(celcrt->left,info);
		if (celcrt->info<info)
			if (celcrt->right==NULL) return celcrt;
				else return recursiv(celcrt->right,info);
	}

void Arbore::Ins(PString* info)
	{
		ANod *crt=NULL, *aux;

		if (Root==NULL)
			{
				aux=new ANod;
				aux->info=*info;
				aux->left = NULL;
				aux->right = NULL;
				aux->aparitii = 1;
				Root=aux;
				return;
			}

		crt=recursiv(Root,*info);

		if (crt->info>*info){
			aux=(ANod *)malloc(sizeof(ANod));
			aux->left=NULL;
			aux->right=NULL;
			aux->info=*info;
			crt->left=aux;
			aux->aparitii=1;
			}
			else if (crt->info<*info){
						aux=(ANod *)malloc(sizeof(ANod));
						aux->left=NULL;
						aux->right=NULL;
						aux->info=*info;
						crt->right=aux;
						aux->aparitii=1;
						}
						else crt->aparitii++;
	}

void Arbore::Action (ANod *what)
 {
 }

int DepthRec(int level,PString what,ANod *celcrt)
 {
	if (celcrt->info==what) return level;
		else if (celcrt->info>what){
					 return DepthRec(level++,what,celcrt->left);
					 }
					 else{
						return DepthRec(level++,what,celcrt->right);
					 }
	level--;
 }

int Arbore::Depth (PString what)
 {
	return DepthRec(0,what,Root);
 }

ANod* Arbore::Search(PString what,ANod *celcrt)
 {
	if (celcrt==NULL) return 0;
		else if (celcrt->info>what) return Search(what,celcrt->left);
					else if (celcrt->info<what) return Search(what,celcrt->right);
								else return celcrt;
 }

void Arbore::TreePrint(int x,int y,ANod *celcrt)
 {
	x-=4;y++;if (celcrt->left!=NULL) TreePrint(x,y,celcrt->left);x+=4;y--;
	gotoxy(x,y);printf("%s",celcrt->info.data);
	x+=4;y++;if (celcrt->right!=NULL) TreePrint(x,y,celcrt->right);x-=4;y--;
 }

