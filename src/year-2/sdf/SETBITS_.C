#include <conio.h>
#include <stdio.h>
#include <math.h>

void showbits(unsigned int v);
char get(unsigned int x,char p);


void main(void)
	{
		unsigned int x=0,y;
		char i;
		unsigned int p,n;

		clrscr();
		//citeste valorile...
		printf("valoarea lui y : ");
		scanf("%u",&y);

		printf("valoarea lui p : ");
		scanf("%u",&p);
		printf("valoarea lui n : ");
		scanf("%u",&n);

		showbits(y);
		y=y & ~(~0 << n);
		showbits(y);
		x=y << (p-n);
		showbits(x);
		getch();
	}

void showbits(unsigned int v)
	{
		int i;
		for(i=15;i>=0;i--) printf("%u",get(v,i));
		printf("\n");
	}

char get(unsigned int x,char p)
	{
		return x & (unsigned int)pow(2,p) ? 1 : 0;
	}
