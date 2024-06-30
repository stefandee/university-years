#include <stdio.h>
#include <io.h>
#include <conio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys\stat.h>

#define N 100

int handle[2];
int *aux=0;

void ScrieN_uplu(int what,int n)
 {
  int i=0;
  while ((i<n) && (!eof(handle[0])))
	{
	 read(handle[0],aux,2);
	 if (write(handle[what],aux,2)==-1) printf("error writing file");
	 i++;
	}
 }

void Injumatatire(int n)
 {
  int d;
  d=eof(handle[0]);
  while (!d)
	{
	 d=eof(handle[0]);
	 ScrieN_uplu(1,n);
	 ScrieN_uplu(2,n);
	}
 }

void Interclasare(int n,int* s)
 {
  int i,j,*x,*y;
  int termb,termc;
  termb=eof(handle[1]);
  termc=eof(handle[2]);
  x=(int*)malloc(2);
  y=(int*)malloc(2);

  if (!termb) read(handle[1],x,2);
  if (!termc) read(handle[2],y,2);

  do
  {
	i=0;j=0;
	//interclasarea unui n-uplu
	while ((i<n) &&(j<n) && (!termb) &&(!termc))
	 {
	  if (x < y)
		{
		 write(handle[0],x,2);
		 i++;
		 if (eof(handle[1])) termb=1; else read(handle[1],x,2);
		}
		else
		 {
		  write(handle[0],y,2);
		  j++;
		  if (eof(handle[2])) termc=1; else read(handle[2],y,2);
		 }
	 }
	 //copierea restului n-uplului de pe "b"
	 while ((i<n) && (!termb))
	  {
		write(handle[0],x,2);
		i++;
		if (eof(handle[1])) termb=1; else read(handle[1],x,2);
	  }
	 //copierea restului n-uplului de pe "c"}
	 while ((j<n) && (!termc))
	  {
		write(handle[0],y,2);
		j++;
		if (eof(handle[2])) termc=1; else read(handle[2],y,2);
	  }
	 if ((!termb) || (!termc)) *s=(*s)+1;
	 }
	 while ((!termb) || (!termc));
  free(x);free(y);
 }
void Trei_Benzi(void)
 {
  int p,*k;
  p=1;
  k=(int*)malloc(2);
  do
	{
	Injumatatire(p);
	k=0;
	Interclasare(p,k);
	p=p*2;
	}
  while  (k!=0);
 free(k);
 }

void main(void)
 {
 int i;
 clrscr();
 aux=(int*)malloc(2);
 randomize();

 handle[0]=creat("a.dat",S_IFREG);
 handle[1]=open("b.dat",O_RDWR);
 handle[2]=open("c.dat",O_RDWR);
 for(i=0;i<5;i++,*aux=rand(),write(handle[0],aux,2),printf("%d\n",*aux));
 close(handle[0]);

 printf("sortare...\n");
dos.h
 handle[0]=open("a.dat",O_RDWR);
 Trei_Benzi();
 close(handle[0]);

 handle[0]=open("a.dat",O_RDONLY);
 for(i=0;i<5;i++,read(handle[0],aux,2),printf("%i\n",*aux));

 close(handle[0]);
 close(handle[1]);
 close(handle[2]);
 }
