#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <dos.h>
#include <string.h>

void main()
{
int i=0;
char password[2][10]={"STORM\0","LIGHT\0"},crt[10]="\0";
setcbrk(1);
do
{
clrscr();
gotoxy(30,10);printf("Enter curent password");
gotoxy(35,11);
for (i=0;i<10;i++)
	{
	crt[i]=toupper(getch());
	if (crt[i]==13) goto pass;
  printf("*");
	}
pass:crt[i]='\0';
}
while (strcmp(password[1],crt)!=0 && strcmp(password[0],crt)!=0);
}