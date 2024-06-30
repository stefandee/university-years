//Forma poloneza - evaluarea expresiilor

#include <stdio.h>
#include <conio.h>
#include <string.h>

int stack[30];
int sp=0;

void push(int v)
	{
		if (sp<29) stack[sp++]=v;
	}

int pop(void)
	{
		if (sp==0) return stack[0];
			 else { sp--;return stack[sp]; }
	}

void main(void)
	{
		char sir[30];
		int i;
		int x,y,z;

		clrscr();
		printf("Introduceti sirul : ");
		scanf("%s",&sir);

		for(i=0;i<strlen(sir);i++)
			{
				if (isdigit(sir[i])) push(sir[i]-'0');
					else switch(sir[i])
							 {
								case '+' : push(pop()+pop());break;
								case '-' : push(pop()-pop());break;
								case '*' : push(pop()*pop());break;
								case '/' : push(pop()/pop());break;
								default  : printf("Caracter necunoscut %c",sir[i]);exit();
							 }
			}
		printf("Valoarea expresiei este : %i",pop());
		getch();
	 }

