#include <stdio.h>
#include <dos.h>

char workpal[255][2];

void vga256(void)
{
 asm {
				mov ax,0x13
				int 0x10
			}
}

void done256(void)
{ asm { mov ax,0x0003
			 int 0x10
			}
}

void loadpal(char* fname)
{ FILE* fp=NULL;
	fp=fopen(fname,"r");
	fread(&workpal,768,1,fp);
	fclose(fp);
}

void setpal(void)
{  unsigned s,o;
	 s=FP_SEG(workpal);
	 o=FP_OFF(workpal);

asm { mov ax,0x1013
				mov es,s
				mov dx,o
				mov bx,0
				mov cx,256
				int 0x10
			}
}

