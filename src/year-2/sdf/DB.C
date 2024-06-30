#include <stdio.h>
#include <conio.h>

void main(void)
{ int i;
  for(i=0;i<16;i++) { outportb(0x3c8,i);
		      outportb(0x3c9,0);
		      outportb(0x3c9,0);
		      outportb(0x3c9,0);
		    }
getch();
}