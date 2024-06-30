#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void main()
{
	FILE *in;
	long int crtPos=0, initFileSize=0;
	char c;

	if ((in = fopen("dplay.txt", "rb+")) == NULL)
	{
		 printf("Cannot open in file.\n");
		 exit(1);
	}
	fseek(in, 0L, SEEK_END);
	initFileSize = ftell(in);
	rewind(in);
	while (crtPos++<=initFileSize)
	{
		c = fgetc(in);
		if (isdigit(c))
		{
			fseek(in, 0L, SEEK_END);
			fputc(c, in);
			fseek(in, crtPos, SEEK_SET);
		}
	}
	fclose(in);
}