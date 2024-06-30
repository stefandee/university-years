#include <stdio.h>

void main(void)
	{
		char *p="ex amen\0",t[]="e xamen\0";
		int i;

		printf("%s %s",p,t);
		getch();

		for(i=0;(i<6) || (t[i]=' ');++i);
	}
