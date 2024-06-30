#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <io.h>
#include <fcntl.h>

typedef char text[80];
text text_curent,text_codat;
int dimensiune;


void meniu(void)
	{
		clrscr();
		gotoxy(10,10);printf("1 . Introducere de la tastatura");
		gotoxy(10,11);printf("2 . Introducere din fisier a textului de codat");
		gotoxy(10,12);printf("3 . Codare text curent");
		gotoxy(10,13);printf("4 . Introducere din fisier a textului codat");
		gotoxy(10,14);printf("5 . Decodare text curent");
		gotoxy(10,15);printf("6 . Iesire");
	}

void citeste(char* citit)
	{
		char c,i;

		for(i=0;i<80;i++) citit[i]='*';

		clrscr();
		printf("Introduceti textul : ");
		dimensiune=0;
		while((c=getche())!='\\')
			{
				if (c==' ') c='*';
				citit[dimensiune++]=c;
			}
		citit[dimensiune]='*';
		dimensiune--;
	}

void incarca(char* citit,char filename[10])
	{
		int haandle;
		char i;

		for(i=0;i<80;i++) citit[i]='*';
		i=0;
		clrscr();
		dimensiune=0;
		haandle=open(filename,O_RDWR | O_TEXT);
		do
			{
				read(haandle,&citit[i++],1);
				if (citit[i-1]==' ') citit[i-1]='*';
			}
		while(citit[i-1]!='\\');
		citit[i-1]='*';
		dimensiune=i-1;
	 }

void codeaza()
	{
		char matrix[100][100],aux;
		int i,j;
		int dim,count=0;

		clrscr();
		dim=sqrt(dimensiune)+1;
		gotoxy(1,1);printf("Textul are %d caractere , matricea de codare are dimensiunile %d X %d",dimensiune,dim,dim);
		for(i=0;i<dim;i++)
			for(j=0;j<dim;j++)
				{
					matrix[i][j]=text_curent[i*dim+j];
					gotoxy(10+j,10+i);
					printf("%c",matrix[i][j]);
				}
		gotoxy(1,20);printf("Textul codat este : ");
		for(i=0;i<dim;i++)
			for(j=i;j>=0;j--)
				{
					if ((i%2)==0) printf("%c",aux=matrix[j][i-j]);
						else printf("%c",aux=matrix[i-j][j]);
					text_codat[count++]=aux;
				}
		for(i=1;i<dim;i++)
			for(j=i;j<dim;j++)
				{
					if ((i%2)==0) printf("%c",aux=matrix[j][dim-1-(j-i)]);
							else printf("%c",aux=matrix[dim-1-(j-i)][j]);
					text_codat[count++]=aux;
				}
		getch();
	}

void decodeaza()
	{
		char matrix[100][100],aux;
		int i,j;
		int dim,count=0;

		clrscr();
		dim=sqrt(dimensiune)+1;
		gotoxy(1,1);printf("Textul codat are %d caractere , matricea de codare are dimensiunile %d X %d",dimensiune,dim,dim);
		text_codat[dim*dim]='\0';
		gotoxy(1,2);printf("Textul pentru decodare este : ");

		for(i=0;i<dim;i++)
			for(j=i;j>=0;j--)
				{
					aux=text_codat[count++];
					printf("%c",aux);
					if ((i%2)==0) matrix[j][i-j]=aux;
						else matrix[i-j][j]=aux;
					
				}
		for(i=1;i<dim;i++)
			for(j=i;j<dim;j++)
				{
					aux=text_codat[count++];
					printf("%c",aux);
					if ((i%2)==0) matrix[j][dim-1-(j-i)]=aux;
							else matrix[dim-1-(j-i)][j]=aux;
				}

		for(i=0;i<dim;i++)
			for(j=0;j<dim;j++)
				{
					text_curent[i*dim+j]=matrix[i][j];
					gotoxy(10+j,10+i);
					printf("%c",matrix[i][j]);
				}

		text_curent[dim*dim]='\0';
		gotoxy(1,20);printf("Textul decodat este : %s",text_curent);

		getch();
	}


void main(void)
	{
		int key;
		meniu();
		while((key=getch())!='6')
			{
				switch(key)
					{
					case '1' : citeste(&text_curent);getch();meniu();break;
					case '2' : incarca(&text_curent,"DE_CODAT.DAT\0");getch();meniu();break;
					case '3' : codeaza();meniu();break;
					case '4' : incarca(&text_codat,"CODAT.DAT\0");meniu();break;
					case '5' : decodeaza();meniu();break;
					}
			}
	}