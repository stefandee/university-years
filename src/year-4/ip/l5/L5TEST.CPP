// language include files
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <io.h>
#include <sys\stat.h>

// personal include files
#include "mystring.h"
#include "myint.h"
#include "mycollec.h"
#include "myqueue.h"
#include "myset.h"
#include "mystack.h"

// the file variable
FILE* hscript;

// various constant strings -> for comparings
char* id_int="int:";
char* id_str="str:";
char* id_col="col:";
char* id_set="set:";
char* id_queue="queue:";
char* id_stack="stack:";
char* id_echo="echo";

// internal variables of all defined types
Collection collection;
Integer integer(0);
String string("");
Queue queue;
Set set;
Stack stack;
int whatvar = -1;
int linenr = 0;

// main script function. No INs, no OUTs
void ReadOneLine()
{
  char* crap, *temp;
  crap = new char[1024];
  temp = new char[1024];
  memset(temp, '\0', 1024);

  // read one line till the end
  fgets(crap, 1023, hscript);
  linenr++;

  // now process this line
  switch (crap[0])
  {
    case '#' : break; // commented line
    case '*' : if (whatvar == 0)
	       {
		  memcpy(temp, crap+1, strlen(crap)-1);
		  temp[strlen(temp)-1]='\0';
		  Integer tempint(atoi(temp));
		  integer = integer * tempint;
	       }
	       else printf("!!! ERROR in line %i (* is reserved for int class).\n", linenr);
	       break;
    case '-' : if (whatvar == 0)
	       {
		  memcpy(temp, crap+1, strlen(crap)-1);
		  temp[strlen(temp)-1]='\0';
		  Integer tempint(atoi(temp));
		  integer = integer - tempint;
	       }
	       else printf("!!! ERROR in line %i (- is reserved for int class).\n", linenr);
	       break;
    case '/' : if (whatvar == 0)
	       {
		  memcpy(temp, crap+1, strlen(crap)-1);
		  temp[strlen(temp)-1]='\0';
		  Integer tempint(atoi(temp));
		  integer = integer / tempint;
	       }
	       else printf("!!! ERROR in line %i (/ is reserved for int class).\n", linenr);
	       break;
    case '=' : memcpy(temp, crap+1, strlen(crap)-1);
	       temp[strlen(temp)-1]='\0';
	       switch(whatvar)
	       {
		 case 0 : integer.data = atoi(temp); break;
		 case 1 : { String tempstr(temp); string = tempstr; break; }
		 default : printf("!!! ERROR in line %i (improper use of =)\n", linenr);
	       }
	       break;
    case '+' : memcpy(temp, crap+1, strlen(crap)-1);
	       temp[strlen(temp)-1]='\0';
	       switch(whatvar)
	       {
		 case 0 : { Integer tempint(atoi(temp)); integer = integer + tempint; } break;
		 case 1 : { String tempstr(temp); string = string + tempstr; break; }
		 default : printf("!!! ERROR in line %i (improper use of =)\n", linenr);
	       }
	       break;
  }

  // 2-chars long commands
  memset(temp, '\0', 1024); memcpy(temp, crap, 2); strcat(temp, '\0');
  if ((strcmpi(temp, "<=") == 0) && (whatvar == 1))
  {
     memcpy(temp, crap+2, strlen(crap)-2);
     temp[strlen(temp)-1]='\0';
     int pos = (string<=String(temp));
     if (pos == -1) printf("Substring '%s' not found.\n", temp);
	else printf("Found '%s' in position %d\n", temp, pos);
  }

  // 3-chars long commands
  memset(temp, '\0', 1024); memcpy(temp, crap, 3); strcat(temp, '\0');
  if ((strcmpi(temp, "add") == 0) && (whatvar == 2))
  {
     memcpy(temp, crap+3, strlen(crap)-3);
     temp[strlen(temp)-1]='\0';
     int rez = atoi(temp);
     Integer* i = new Integer(rez);
     if (rez == 0)
     {
	 String* s = new String(temp);
	 collection.add(*s);
     }
     else collection.add(*i);
  }

  if ((strcmpi(temp, "put") == 0) && (whatvar == 5))
  {
     memcpy(temp, crap+3, strlen(crap)-3);
     temp[strlen(temp)-1]='\0';
     int rez = atoi(temp);
     Integer* i = new Integer(rez);
     if (rez == 0)
     {
	 String* s = new String(temp);
	 queue.add(*s);
     }
     else queue.add(*i);
  }
  if ((strcmpi(temp, "get") == 0) && (whatvar == 5))
  {
     queue.Get();
  }
  if ((strcmpi(temp, "pop") == 0) && (whatvar == 4))
  {
     stack.Pop();
  }
  if ((strcmpi(temp, "top") == 0) && (whatvar == 4))
  {
     (stack.Top()).printOn();
     printf("\n");
  }

  // 4-chars long commands
  memset(temp, '\0', 1024); memcpy(temp, crap, 4); strcat(temp, '\0');
  // echo detected, read the parameter
  if (strcmpi(temp,id_echo) == 0) { memcpy(temp, crap+5, strlen(crap)-5); printf("%s", temp); return; }
  // check for id of var
  if (strcmpi(temp,id_set) == 0) { whatvar = 3; }
  if (strcmpi(temp,id_int) == 0) { whatvar = 0; }
  if (strcmpi(temp,id_col) == 0) { whatvar = 2; }
  if (strcmpi(temp,id_str) == 0) { whatvar = 1; }
  if ((strcmpi(temp, "head") == 0) && (whatvar == 5))
  {
     (queue.Head()).printOn();
     printf("\n");
  }
  if ((strcmpi(temp, "push") == 0) && (whatvar == 4))
  {
     memcpy(temp, crap+4, strlen(crap)-4);
     temp[strlen(temp)-1]='\0';
     int rez = atoi(temp);
     Integer* i = new Integer(rez);
     if (rez == 0)
     {
	 String* s = new String(temp);
	 stack.Push(*s);
     }
     else stack.Push(*i);
  }

  // 5-chars long commands
  memset(temp, '\0', 1024); memcpy(temp, crap, 5); strcat(temp, '\0');
  if (strcmpi(temp,id_queue) == 0) { whatvar = 5; }
  if (strcmpi(temp,id_stack) == 0) { whatvar = 4; }

  // 6-chars long commands
  memset(temp, '\0', 1024); memcpy(temp, crap, 6); strcat(temp, '\0');
  if (strcmpi(temp, "nameof") == 0)
  {
     switch (whatvar)
     {
       case 0 : printf("%s\n", integer.nameOf()); break;
       case 1 : printf("%s\n", string.nameOf()); break;
       case 2 : printf("%s\n", collection.nameOf()); break;
       case 3 : printf("%s\n", set.nameOf()); break;
       case 4 : printf("%s\n", stack.nameOf()); break;
       case 5 : printf("%s\n", queue.nameOf()); break;
     }
  }
  if ((strcmpi(temp, "detach") == 0) && (whatvar == 2))
  {
     memcpy(temp, crap+6, strlen(crap)-6);
     temp[strlen(temp)-1]='\0';
     int rez = atoi(temp);
     if (rez == 0)
     {
	 //String* s = new String(temp);
	 collection.detach(String(temp));
     }
     else
     {
	 collection.detach(Integer(rez));
     }
  }
  if (strcmpi(temp,id_queue) == 0) { whatvar = 5; }
  if (strcmpi(temp,id_stack) == 0) { whatvar = 4; }

  // 7-chars long commands
  memset(temp, '\0', 1024); memcpy(temp, crap, 7); strcat(temp, '\0');
  if (strcmpi(temp, "printon") == 0)
  {
     switch (whatvar)
     {
       case 0 : integer.printOn(); printf("\n"); break;
       case 1 : string.printOn(); printf("\n"); break;
       case 2 : collection.printOn(); printf("\n"); break;
       case 3 : set.printOn(); printf("\n"); break;
       case 4 : stack.printOn(); printf("\n"); break;
       case 5 : queue.printOn(); printf("\n"); break;
     }
  }

  delete temp;
  delete crap;
}

void main(int argn, char** args)
{

  printf("\nL5 script test v1.0\n");
  if (argn != 2)
  {
     printf("Fatal : too many or too less parameters.");
     exit(1);
  }

  if ((hscript = fopen(args[1], "r+")) == NULL)
  {
     printf("Fatal : cannot open file %s.", args[1]);
     exit(1);
  }

  printf("Processing script file %s...\n\n",args[1]);
  while(!feof(hscript))
  {
    ReadOneLine();
    if (linenr%24 == 0)
    {
      printf("\nPress ANY key...\n");
      getchar();
    }
  }

  // ok, game over
}