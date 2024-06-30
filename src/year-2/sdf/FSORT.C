//Interclasare 3 benzi

#include <sys\stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <fcntl.h>
#include <dos.h>
#include <io.h>

int handle_a,handle_b,handle_c;

void ScrieNuplu(int handle,int N)
 {
	int i=0,aux;

	while ( (i<N) && (!eof(handle_a)) )
	 {
		i++;
		read(handle_a,&aux,2);
		if(write(handle,&aux,2)==-1)
		 {
			perror("Error ");
			abort();
		 }
	 }
 }

void Injumatatire(int N)
 {
	int aux;

	handle_a=open("temp_a.fil",O_RDWR);
	handle_b=open("temp_b.fil",O_CREAT | O_RDWR);
	handle_c=open("temp_c.fil",O_CREAT | O_RDWR);

	while(!eof(handle_a))
	 {
		ScrieNuplu(handle_b,N);
		ScrieNuplu(handle_c,N);
	 }
	close(handle_a);
	close(handle_b);
	close(handle_c);
 }

void Interclasare(int N,int *s)
 {
	int termb,termc,i,j,auxb,auxc;

	handle_a=open("temp_a.fil",O_CREAT | O_RDWR);
	handle_b=open("temp_b.fil",O_RDWR);
	handle_c=open("temp_c.fil",O_RDWR);

	termb = eof(handle_b);termc = eof(handle_c);

	if (!termb) read(handle_b,&auxb,2);
	if (!termc) read(handle_c,&auxc,2);

	do
	 {
		i=0;j=0;
		while ((i<N) && (j<N) && (!termb) && (!termc))
		 if (auxb<auxc)
			{
			 write(handle_a,&auxb,2);
			 i++;
			 if (eof(handle_b)) termb = eof(handle_b);
				else read(handle_b,&auxb,2);
			}
			else
			 {
			 write(handle_a,&auxc,2);
			 j++;
			 if (eof(handle_c)) termc = eof(handle_c);
				else read(handle_c,&auxc,2);
			 };
	 while ((i<N) && (!termb))
		{
		 write(handle_a,&auxb,2);i++;
		 if (eof(handle_b)) termb = eof(handle_b);
			else read(handle_b,&auxb,2);
		}
	 while ((j<N) && (!termc))
		{
		 write(handle_a,&auxc,2);j++;
		 if (eof(handle_c)) termc = eof(handle_c);
			else read(handle_c,&auxc,2);
		}
	 if ((!termb) && (!termc)) *s+=1;
	 }
	while ((!termb) || (!termc));

	close(handle_a);
	close(handle_b);
	close(handle_c);
 }

void main()
 {
	int p=1,k,aux,handle;

	clrscr();

	handle_a=open("temp_a.fil",O_RDWR | O_CREAT);
	randomize();
	for (k=0;k<5;k++)
	 {
	 aux=random(100);
	 write(handle_a,&aux,2);
	 printf("%i ",aux);
	 }
	printf("\n");
	close(handle_a);

	do
	 {
		Injumatatire(p);
		k=0;
		Interclasare(p,&k);
		p=2*p;
	 }
	while (!k);

	handle=open("temp_a.fil",O_RDWR);
	for (k=0;k<5;k++)
	 {
		read(handle,&aux,2);
		printf("%i\n",aux);
	 }
	close(handle);
	getch();
 }