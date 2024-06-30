// taierea optima a frunzei la caini
#include <stdio.h>
#include <conio.h>

int lungimi[10][2],bucati,lungfir,solutie[10],c,solexist;

void Bomb_Track(int crtlen)
 {
 int i,j,k,l,found;
 for(i=0;i<bucati;i++)
	if ((crtlen-lungimi[i][0]>=0)
		//&& (lungimi[i][1]==0)
		//scoateti comentariul de mai sus daca vreti numar limitat de sfori
		)
		{
		 if (crtlen-lungimi[i][0]==0)
			{
			 solutie[c]=lungimi[i][0];
			 c++;
			 found=0;
			 for(k=0;k<c;k++)
			  for(l=k;l<c;l++)
				if ((solutie[k]>solutie[l]) && (l!=k)) found=1;
			 if (found==0)
			  {
				printf("O solutie este : ");
				for(j=0;j<c;j++) printf("%d ",solutie[j]);
				printf("\n");
				solexist=1;
			  }
			 c--;
			}
			else
			 {
			  lungimi[i][1]=1;
			  solutie[c]=lungimi[i][0];
			  c++;
			  Bomb_Track(crtlen-lungimi[i][0]);
			  c--;
			  lungimi[i][1]=0;
			 }
		}
 }

void main()
 {
  int i,aux;

  printf("Lungimea firului ? ");
  scanf("%d",&lungfir);
  printf("Cite bucati ? ");
  scanf("%d",&bucati);
  for(i=0;i<bucati;i++)
	{
	 printf("Bucata %d ",i);
	 scanf("%d",&aux);
	 lungimi[i][0]=aux;
	 lungimi[i][1]=0;//not used
	}
  solexist=0;
  Bomb_Track(lungfir);
  if (!solexist) printf("Nu exista solutie.\n");
 }