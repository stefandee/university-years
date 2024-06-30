#include <conio.h>
#include <stdio.h>
#include <math.h>

void showbits(unsigned int v);
void set(unsigned int* x,char p);
char get(unsigned int x,char p);


void main(void)
	{
		unsigned int x=0,y;
		char i;
		int p,n;

		clrscr();
		//citeste valorile...
		printf("valoarea lui y : ");
		scanf("%u",&y);

		printf("valoarea lui p : ");
		scanf("%u",&p);
		printf("valoarea lui n : ");
		scanf("%u",&n);

		showbits(y);
		for(i=n;i>=0;i--) if (get(y,i)==1) set(&x,p-(n-i));
		showbits(x);
		getch();
	}

void showbits(unsigned int v)
	{
		int i;
		for(i=15;i>=0;i--) printf("%u",get(v,i));
		printf("\n");
	}

void set(unsigned int* x,char p)
	{
		(*x)=(*x) | (unsigned int)pow(2,p);
	}

char get(unsigned int x,char p)
	{
		return x & (unsigned int)pow(2,p) ? 1 : 0;
	}