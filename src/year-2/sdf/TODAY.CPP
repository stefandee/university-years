
//#include <tabel_cu_prostii.h>
// ษอออออออออออออหอออออออออออออออออออออออออออออออออออออออออป
// บ 16.05.1996  บ TODAY'S THEME IS : Boscheti genealogici บ
// ศออัออออัอออออสอออออออออออออัออออออออออออออออออออัออออัอผ
//    ณ    ณ Author : unknown  ณ Place : AUT.UTT.RO ณ    ณ
//    ณ    ภ------------------ ม -------------------ู    ณ
//    ณ Tommorow is the contest ! Another 3 hours lost ! ณ
//    ฦออออออออออออออออออออออออออออออออออออออออออออออออออต
//    ณ       Kimba,Tamba,Mamba rules the software !     ณ
//    ิออออออออออออออออออออออออออออออออออออออออออออออออออพ

#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <alloc.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>

typedef struct Node
					{
					 char *name;
					 int sons;
					 struct Node* distsite[10];
					} Nd;
void main()
 {
  int gd=DETECT,gm;
  clrscr();
//  initgraph(&gd,&gm,"f:\\work\\tcpp\\bgi");
  char aux;
  char compose[100],c=0,parent[100],pc,son[100],sc;
  int handle;


  //reading from file the tree information...
  handle=open("treedata.dat",O_RDWR);
  while(!eof(handle))
	{
	  //reading one byte a time to compose the message
	  read(handle,&aux,1);
	  compose[c]=aux;
	  c++;//this is the way it should be!
	  compose[c]='\0';
	  if (strcmp(compose,"parent")==0)
		  {
			//now reading to the end o' line...
			pc=0;
			do
			{
			 read(handle,&aux,1);
			 parent[pc]=aux;
			 pc++;
			}
			while (aux!='\n');
			//here will come the insert function for parent (damn this C)
			pc--;
			parent[pc]='\0';
			printf("parent found : %s\n",parent);
			c=0;
		  }

	  if (strcmp(compose,"son")==0)
		  {
			//now reading to the end o' line...
			sc=0;
			do
			{
			 read(handle,&aux,1);
			 son[sc]=aux;
			 sc++;
			}
			while (aux!='\n');
			//here will come the insert function for son(using the previous parent name)
			//again damn this C
			sc--;
			son[sc]='\0';
			printf("son of parent %s is %s\n",parent,son);
			c=0;
		  }
	}

  //here will come the show routine
  getch();
//  closegraph();

 }