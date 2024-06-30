#define MAXARB 200
#define MAXALFAB 256
#define MAXZONA 200

typedef struct _elarb{
	   int fiu_sting,fiu_drept,parinte;
	   }elarb;
typedef elarb tarbore[MAXARB];
typedef struct _elalfabet{
	   char car;
	   double prob;
	   int radac;
	   } elalfabet;
typedef  elalfabet talfabet[MAXALFAB];
typedef struct _elzona{
	  double greut;
	  int radacina;
	  }elzona;
typedef  elzona tzona[MAXZONA];


extern tarbore arbore;
extern   int pozarb=0;
extern talfabet alfabet;
extern   int pozalf=0;
extern tzona zona;
extern   int pzona=0;


int creeaza(int arbs,int arbd){
 pozarb++;
 arbore[pozarb].fiu_sting=zona[arbs].radacina;
 arbore[pozarb].fiu_drept=zona[arbd].radacina;
 arbore[pozarb].parinte=0;

 arbore[zona[arbs].radacina].parinte=pozarb;
 arbore[zona[arbd].radacina].parinte=pozarb;
 return pozarb;
}

void greutmin(int* min,int* min1){
  /* arborii cei mai usori din zona */
  int i;
   if(zona[1].greut<zona[2].greut){
	      (*min)=1; (*min1)=2; }
   else { (*min)=2; (*min1)=1; }
   for(i=1;i<=pzona;i++)
     if(zona[i].greut<zona[(*min)].greut){
	 (*min1)=(*min);
	 (*min)=i;}
      else if(zona[i].greut<zona[(*min1)].greut){
		 (*min)=(*min1);
		 (*min1)=i;     }
  }


void huff(void){
  int i,j,radnou;

  while(pzona>1){
     greutmin(&i,&j);
     radnou=creeaza(i,j);
      zona[i].greut=zona[i].greut+zona[j].greut;
      zona[i].radacina=radnou;
      zona[j]=zona[pzona];
      pzona--;
    }
  }