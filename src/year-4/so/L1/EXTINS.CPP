#include <dos.h>
#include <stdio.h>
#include <conio.h>

void main()
{
  union REGS inregs;

  clrscr();
  while (!(inportb(0x60)==1))
  {
	int86(0x16,&inregs,&inregs);
	if (!inregs.h.al) printf("Extended code %i \n",inregs.h.ah);
	inregs.x.ax = 0;
  }
}