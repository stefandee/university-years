#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void drawmenu()
{
  clrscr();
  printf("1. Optiunea unu \n");
  printf("2. Optiunea doi \n");
  printf("3. Optiunea trei \n");
  printf("4. Exit \n");
}

void main()
{
  char c;
  drawmenu();
  while (c=getch())
  {
	switch (c) {
	  case ('1') : exit(1);
	  case ('2') : exit(2);
	  case ('3') : exit(3);
	  case ('4') : exit(4);
	}
  }
}