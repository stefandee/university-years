#include <string.h>
#include <alloc.h>
#include <stdio.h>


typedef int boolean;

class PString
 {
 public :
	char *data;
	void Init(char* what){data = (char*)malloc(strlen(what));strcpy(data,what);}
 };

typedef struct NL {
				PString info;
				NL *next;
				} LNod;

typedef struct NA {
				PString info;
				int aparitii;
				NA* left,*right;
				} ANod;

class List
 {
	LNod *First, *Cursor;

	public :
		List(){};
		~List(){};
		void Init(){ First = NULL;First->next = NULL; };
		void Del();
		void Ins(char* info);
		LNod* Elem(){
								 LNod* aux;
								 aux=Cursor;
								 Cursor=Cursor->next;
								 return aux;
								}
		void ResetCursor(){Cursor=First;};
		void Print();
 };

class Arbore
 {
	public :
	 ANod *Root;

	 Arbore      (){};
	 void Init   () { Root = NULL; }
	 void Ins    (PString*);
	 int  Depth  (PString what);
	 ANod*  Search (PString,ANod *);
	 void TreePrint(int,int,ANod*);
	 virtual void Action (ANod *what);
	 void Ino  (ANod *what){ 
													 if (what->left!=NULL) Ino(what->left);
													 Action(what);
													 if (what->right!=NULL) Ino(what->right);
													}
	 void Pre  (ANod *what){
													 Action(what);
													 if (what->left!=NULL) Ino(what->left);
													 if (what->right!=NULL) Ino(what->right);
												 };
	 void Post (ANod *what){
													 if (what->left!=NULL) Ino(what->left);
													 if (what->right!=NULL) Ino(what->right);
													 Action(what);
												 };
	 void Destroy(char *info){;};
	 ~Arbore     (){};
 };
