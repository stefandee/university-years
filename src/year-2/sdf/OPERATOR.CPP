#include <string.h>
#include <stdio.h>
#include <alloc.h>
#include <conio.h>

typedef int boolean;

class PString
 {
 public :
	char *data;
	void Init(char* what){data = (char*)malloc(strlen(what));strcpy(data,what);}
 };

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

void main()
{
 PString p1,p2;

 p1.Init("data");
 p2.Init("mare");
 clrscr();
 if (p1<p2) printf("p1 mai mic ca p2");
	else printf("p2 mai mic ca p1");
 getch();
}

