#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <conio.h>

#define N 3
typedef int way[N][N];

int x=0,y=0;

void showay(way W,int basex,int basey)
	{
		int i,j;

		clrscr();
    textcolor(15);
		for(i=0;i<N;i++)
			for(j=0;j<N;j++)
				{
					
					gotoxy(basex+j*3,basey+i);
					if ((W[i][j]<10)&&(W[i][j]>=0)) cprintf("%i",W[i][j]);
																					else cprintf("ì");
				}

		textcolor(2);
		gotoxy(basex+y*3,basey+x);
		if ((W[x][y]<10)&&(W[x][y]>=0)) cprintf("%i",W[x][y]);
			else cprintf("ì");
	}

void ReallyDoFloyd(way W,way *P)
	{
		int i,j,k;
		way A;

		for(i=0;i<N;i++)
			for(j=0;j<N;j++)
				{
					A[i][j]=W[i][j];
					*P[i][j]=0;
				}

		for(k=0;k<N;k++)
			for(i=0;i<N;i++)
				for(j=0;j<N;j++)
						{
							if (A[i][k]+A[k][j]<A[i][j]) A[i][j]=A[i][k]+A[k][j];
							*P[i][j]=k;
						}
	 showay(A,30,10);
	 textcolor(15);
	 gotoxy(30,9);
	 cprintf("Matricea costurilor : ");

	 getch();
	 }



void main()
	{
		int i,j;
		char key;
		way W,P;
		union REGS R_IN,R_OUT;

		clrscr();
		for(i=0;i<N;i++)
			for(j=0;j<N;j++)
				{
					if (i!=j) W[i][j]=random(10)+1;
										else W[i][j]=0;
				}

		while ((key=inportb(0x60))!=1)
			{
				switch (key)
				 {
					 case 72 : x--;if (x<0) x=N-1;showay(W,10,10);break;
					 case 80 : x++;if (x>N-1) x=0;showay(W,10,10);break;
					 case 75 : y--;if (y<0) y=N-1;showay(W,10,10);break;
					 case 77 : y++;if (y>N-1) y=0;showay(W,10,10);break;
					 case 71 : W[x][y]++;showay(W,10,10);break;
					 case 79 : W[x][y]--;showay(W,10,10);break;
					 case 28 : ReallyDoFloyd(W,&P);
				 }
				delay(70);
				R_IN.x.ax=0x0c02;
				intdos(&R_IN,&R_OUT);
			}
	}
