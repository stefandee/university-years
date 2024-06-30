//search

#include <string.h>
#include <stdio.h>
#include <conio.h>

void BM(char *what,char *where)
 {
	int st[255],i,j,k,lenw,lens;

	lenw=strlen(where);
	lens=strlen(what);
	for(i=0;i<255;i++) st[i]=lens;
	for(i=0;i<lens;i++) st[what[i]]=lens-i-1;

	printf("metoda BM\n");

	j=lens-1;
	while(j<lenw)
	 {
		i=lens-1;k=j;
		while( (i>0) && (what[i]==where[k]) )
		 {
			i--;
			k--;
		 }
		if ( (i==0) && (what[i]==where[k]) )
		 {
			printf("sirul %s se alfa pe pozitia %d",what,k);
			return ;
		 }
		j+=st[where[k]];
	 }
	printf("sirul %s nu a fost gasit",what);
 }

void Direct(char *what,char *where)
 {
	int i=0,j=0,lenw,flag,lens;

	lenw=strlen(where);
	lens=strlen(what);

	printf("metoda Directa\n");

	while(j<lenw)
	 {
		i=0;flag=0;
		while((what[i]!='\0') && (what[i]==where[i+j])) i++;
		if (i==lens)
			{
			 printf("sirul %s se gaseste pe pozitia %d\n",what,j);
			 flag=1;
			 break;
			}
		j++;
	 }
 if (!flag) printf("sirul %s nu a fost gasit .\n",what);
 }



void main()
 {
	char string[255],sub[255];

	clrscr();

	strcpy(string,"aconpilarea constrconcon un tablou d de deplasari, continind cite\0");
	printf("sirul de cautat : ");
	scanf("%s",&sub);

	Direct(sub,string);
	BM(sub,string);

	getch();
 }
