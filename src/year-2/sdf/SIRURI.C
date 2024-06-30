#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 100


char model[8]="CAUT",sir[N];

void RawSearch()
 {
  int i,j,ml,flag;
  ml=strlen(model);
  for(i=0;i<N;i++)
	{
	 for(j=0;j<ml;j++) if (model[j]!=sir[i+j]) j=ml+6;
	 if (j==ml)
		 {
		  printf("metoda RAW : Am gasit sirul %s in sirul mare pe pozitia %d\n",model,i);
		  return;
		 }
	}
 }

void KMPSearch()
 {
  int i,j,k,ml,d[8];

  ml=strlen(model);
  j=0;k=-1;d[0]=-1;

  while (j<ml-1)
	{
	 while ((k>=0) && (model[j]!=model[k])) k=d[k];
	 j++;k++;
	 if (model[j]==model[k]) d[j]=d[k];
			 else d[j]=k;
	}

	i=0;j=0;
	while ((j<ml) && (i<N))
	  {
		while ((j>=0) && (sir[i]!=model[j])) j=d[j];
		j++;i++;
	  }
	printf("metoda KMP : Am gasit sirul %s in sirul mare pe pozitia %d\n",model,i-ml);
 }

void BMSearch()
 {
  int i,j,k,ml,d[256];

  ml=strlen(model);
  for(i=0;i<255;i++) d[i]=ml;
  for(j=0;j<ml-2;j++) d[model[j]]=ml-j-1;

  i=ml;j=ml;
  while ((j>0) && (i<=N))
	{
	 j=ml;k=i;
	 while ((j>0) && (sir[k-1]==model[j-1]))
	  {
		k=k-1;j=j-1;
	  }
	if (j>0) i=i+d[sir[k-1]];
	}
  printf("metoda BM : Am gasit sirul %s in sirul mare pe pozitia %d\n",model,i-ml);
 }

void main(void)
 {
  int i,pos;

  randomize();clrscr();

  printf("Introduceti sirul model : ");scanf("%s",&model);
  for(i=0;i<N;i++) sir[i]=random(128)+32;
  pos=random(N-strlen(model));
  for(i=pos;i<pos+strlen(model);i++) sir[i]=model[i-pos];
  pos=random(N-strlen(model));
	for(i=pos;i<pos+strlen(model)/2;i++) sir[i]=model[i-pos];

  printf("sirul sursa e : %s\n",sir);
  printf("sirul %s e in sir pe pozitia %d\n",model,pos);
  RawSearch();
  KMPSearch();
  BMSearch();
 }
