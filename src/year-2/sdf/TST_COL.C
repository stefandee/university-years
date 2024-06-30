
#include <conio.h>

int main(void)
{
   int i;

   for (i=0; i<15; i++)
   {
       textcolor(i);
       cprintf("Foreground Color\r\n");
   }

   return 0;
}
