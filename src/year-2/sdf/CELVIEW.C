#include <stdio.h>
#include <dos.h>
#include <fcntl.h>
#include <io.h>
#include "graphics.c"

void main(void)

{ long fh,i;
	unsigned char far* screen;
	char workpal[256][2];
	char byte;

	screen=(char*)MK_FP(0xA000,0);
	if (FP_SEG(screen)==0) {exit(1);};
	printf("\n%ld",FP_SEG(screen));
	getch();
	asm { mov ax,0x0013;
				int 0x10;
			}
	fh=_open("earthmap.pal",O_RDWR);
	_read(fh,workpal,768);
	if (fh==-1) {
							exit(1);
							};

	for(i=0;i<=255;i++) {
										 outportb(0x3c8,i);
										 outportb(0x3c9,workpal[i][0]);
										 outportb(0x3c9,workpal[i][1]);
										 outportb(0x3c9,workpal[i][2]);
										 };

	_close(fh);

	fh=_open("earthmap.cel",O_RDWR);

	lseek(fh,800,SEEK_SET);
	_read(fh,(char*)screen,64000);
	getch();
	_close(fh);
	done256();
}