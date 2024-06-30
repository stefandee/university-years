#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <dir.h>
#include <process.h>
#include <stdlib.h>
#include <alloc.h>
#include <string.h>
#include <time.h>
#include <errno.h>

//global variables
int maxdepth = 0, allfiles = 0;
long int maxlength = -1;
char* onoff[2] = {"off","on"};

//functions definitions
void recDirList(char* currentDir, char* dstDir, int depth);

void main(int argc, char* argv[])
{
   clrscr();
   if (argc<3) {
      printf("Insufficient parameters : need at least srcdir and destdir");
      exit(0);
   }
   printf("Found %d parameter(s)\n",argc-1);
   for(int i=1;i<argc;i++)
   {
     if (argv[i][0]=='-')
     {
			 switch (argv[i][1])
			 {
					case 'a' : allfiles = 1;
							 printf("Hidden files copy is %s.\n",onoff[allfiles]);
							 break;
					case 'd' : {
									char temp[32];
									strcpy(temp,argv[i]+2);
									maxdepth = atoi(temp);
									printf("Maximum directory depth set at %d.\n",maxdepth);
									break;
							 }
					case 'l' : {
									char temp[32];
									strcpy(temp,argv[i]+2);
									maxlength = atol(temp);
									printf("File maximum size set at %li.\n",maxlength);
									break;
							 }
					default : printf("Invalid switch : -%c",argv[i][1]);
							exit(0);
			 }
     }
     else break;
   }
   if ((i+1>=argc) || (i>=argc))
   {
     printf("Parameters present, need source directory AND dest directory !\n");
     exit(0);
   }
   recDirList(argv[i],argv[i+1],0);
}

void recDirList(char* currentDir, char* dstDir, int depth)
{
	struct ffblk ffblk;
	int done, mdStatus, tempAttr;
	char* temp = (char*)malloc(512);
	char* dstTemp = (char*)malloc(512);

	if (depth<=maxdepth) {
		 strcpy(temp, currentDir);
		 strcat(temp, "\\*.*");

		 done = findfirst(temp, &ffblk, FA_RDONLY | FA_HIDDEN | FA_DIREC | FA_ARCH);
		 while (!done)
		 {
				if ((strcmp(ffblk.ff_name,".") != 0) && (strcmp(ffblk.ff_name,"..") != 0))
				{
					 /*for(i=0;i<depth;i++) printf("  ");
					 printf("  %s\n", ffblk.ff_name);*/
					 if (ffblk.ff_attrib == FA_DIREC)
					 {
							strcpy(temp, currentDir);
							strcat(temp, "\\");
							strcat(temp, ffblk.ff_name);
							//now create directory
							strcpy(dstTemp, dstDir);
							strcat(dstTemp, "\\");
							strcat(dstTemp, ffblk.ff_name);
							mdStatus = mkdir(dstTemp);
							if (mdStatus)
							{
								 printf("Cannot create directory : %s\n",dstTemp);
								 printf("Subdirs in path may not exist.\n");
								 exit(1);
							}
							depth++;
							recDirList(temp, dstTemp, depth);
							depth--;
					 }
					 else if (ffblk.ff_fsize<maxlength)
								{
									 tempAttr = ffblk.ff_attrib & FA_HIDDEN;
									 if (((tempAttr !=0) && (allfiles==1)) || (tempAttr == 0))
									 {
											//now move file
											strcpy(temp, currentDir);
											strcat(temp, "\\");
											strcat(temp, ffblk.ff_name);

											strcpy(dstTemp, dstDir);
											strcat(dstTemp, "\\");
											strcat(dstTemp, ffblk.ff_name);
											if (rename(temp,dstTemp)==0) printf("%s was moved to %s\n",temp,dstTemp);
												 else perror("Move ");
									 }
								}
				}
				done = findnext(&ffblk);
		 }
	}
	free(temp);
	free(dstTemp);
}