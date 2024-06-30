#include<stdio.h>
#include<conio.h>
#include"huff.c"

tarbore arbore;
 int pozarb;
talfabet alfabet;
 int pozalf;
tzona zona;
 int pzona;

int tab[256];

void det_alfabet(char* nfis){
/* determina alfabetul citind din fisier*/
int i,j,cr,sum;
FILE* fisier;
char r;
long f;

  for(i=0;i<=255;i++) tab[i]=0;
 fisier=fopen(nfis,"r");
 if(fisier==NULL) {
     printf(" fisierul nu se poate citi!");
     exit(1);
     }
 sum=0;
  while((cr=fscanf(fisier,"%c",&r))==1){
   printf("%c",r); sum++;
   if( ((int)r)==10) tab[13]++;
   tab[(int)r]++;
   }
 fclose(fisier);
for(i=0;i<=255;i++)
   if(tab[i]!=0) {
      pozalf++;
       pozarb++; pzona++;
      alfabet[pozalf].car=(char)i;
      alfabet[pozalf].prob=zona[pozalf].greut=tab[i]/(double)sum;
      zona[pozalf].radacina=pozalf;
	alfabet[pozalf].radac=0;
    }
}


void getsir(int i,char* sir){
  int c,l;
  char d;
 c=0;
  while(arbore[i].parinte!=0){
      if(arbore[arbore[i].parinte].fiu_sting==i) {
	     sir[c]='0';
	     c++;
	     }
      else {
	     sir[c]='1';
	     c++;
	     }
      i=arbore[i].parinte;
	  }
  sir[c]='\0';
    l=strlen(sir);
  for(c=0;c<l/2;c++) {
       d=sir[c];
       sir[c]=sir[l-c-1];
       sir[l-c-1]=d;
       }
 return sir;
}


unsigned char prin(int tab[8]){
  int i;
  unsigned char t=0,k=1;
   for(i=7;i>=0;i--){
	      t=t|(k*tab[i]);
	      k=k<<1;
	 }
  return t;
}
void compr(char s[256],int* pt,int tab[8]){
 int i;
 for(i=0;i<strlen(s);i++){
   (*pt)++;
   if((*pt)==8){
		(*pt)=0;
		 printf("%c",prin(tab));
		 }
    tab[*pt]=s[i]-'0';
  }
}



void afisir(char* nfis){
FILE* fi;
int y,cr;
 int poztab=-1,tabel[8];
 char r,si[256];


 fi=fopen(nfis,"r");
 if(fi==NULL) { printf("Nu pot citi fisierul "); exit(1); }
  while((cr=fscanf(fi,"%c",&r))==1){
   y=1;
   while(alfabet[y].car!=r) y++;
	     getsir(y,si);
	     compr(si,&poztab,tabel);
   }

 fclose(fi);
 if(poztab!=7) printf("%c",prin(tabel));
}




void main(void){
char name[20];
int c,i,j,l;
char sir[256],d;

 clrscr();
 printf(" Dati numele fisierului ");
 gets(name);
 printf("\n");
 det_alfabet(name);
   huff();
 for(j=1;j<=pozalf;j++){
   getsir(j,sir);
   printf("\n%c %s",alfabet[j].car,sir);
 }

printf("\n\n\n    Sirul codificat:\n ");
afisir(name);

 getch();
}

