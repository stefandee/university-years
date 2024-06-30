//sortari

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#define N 5

int desort[N],original[N];

void Replace(int *s,int* d)
 {
	int i;
	for(i=0;i<N;i++,d[i]=s[i]);
 }

void Generate(int *s)
 {
	int i;
	randomize();
	for(i=0;i<N;i++,s[i]=random(100));
 }

void Print(int *s,char *txt)
 {
	int i;
	printf("%s",txt);
	for(i=0;i<N-1;i++,printf("%d ",s[i]));
	printf("\n");
 }

void Insertie(int* s)
 {
	int i,j;

	for(i=2;i<N;i++)
	 {
		s[0]=s[i];j=i-1;
		while(s[j]>s[0])
		 {
			s[j+1]=s[j];
			j--;
		 }
		s[j+1]=s[0];
	 }
 }

void Selectie(int *s)
 {
	int i,j,k,x;
	for(i=0;i<N-1;i++)
	 {
		x=s[i];k=i;
		for(j=i+1;j<N;j++)
		 if (s[j]<=x)
			{
			 k=j;
			 x=s[j];
			}
		s[k]=s[i];s[i]=x;
	 }
 }

void main()
 {
	clrscr();
	Generate(original);
	Replace(original,desort);
	Print(original,"Tabloul nesortat este : ");Insertie(desort);Print(desort,"Tabloul sortat cu Insertie : ");
	Replace(original,desort);
	Print(original,"Tabloul nesortat este : ");Selectie(desort);Print(desort,"Tabloul sortat cu Selectie : ");
	getch();
 }