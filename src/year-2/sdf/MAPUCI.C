#include <stdio.h>
#include <conio.h>
#include <string.h>

char source[80],dest[80],solutie[10][80],optim[80][10];
int crtline=0,max,count[10];

void handlesol()
 {
 }

void main()
 {
	int i,len;

	strcpy(source,"-SDSDS--------\0");
	strcpy(dest,"-------SSSDD--\0");
	strcpy(solutie[0],source);
	len=strlen(source);

	while(count[0]<len)
	 {
		while(count[crtline]<len)
		 {
			count[crtline]++;
			for(i=0;i<len;i++)
			 if ((solutie[crtline][i]=='S')&&solutie[crtline][i+1]=='D'))
					break;
			if (i==len)
				{
				 crtline--;
				 if (crtline<0)
					{
					 printf("nu exista solutie !");
					 halt;
					}
				 }
				 else
					{

					}
		 }
	 }
 }