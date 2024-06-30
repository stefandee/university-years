#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <process.h>
#include <stdlib.h>
#include <alloc.h>
#include <string.h>
#include <time.h>
#include <errno.h>

//definitions
#define cmdLineSize 512
#define prompter "DUDIX>\0"
//global variables
enum t_actions { NONE = -2, OTHER = -1, EXIT, DIR, TIME, DATE, ECHO } actions;
char* dayofweek[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"},
		 *command = (char*)malloc(cmdLineSize),
		 *arg[1];

//function declarations
void version();
void parseLine(char* string, int counter);
void doAction();

void main()
{
	char* cmdLine = (char*)malloc(cmdLineSize);
	int cmdCounter = 0;
	arg[0] = (char*)malloc(cmdLineSize);

	clrscr();
	version();
	printf("%s",prompter);

	while(1)
	{
		cmdLine[cmdCounter++] = getchar();
		if (cmdLine[cmdCounter-1] == 10) {
			parseLine(cmdLine,--cmdCounter);
			doAction();
			cmdCounter = 0;
			cprintf("%s",prompter);
		}
	}
}

void version()
{
	printf("Dudix v0.1\n");
}

void parseLine(char* string, int counter)
{
	int srcIndex = 0, comIndex = 0, argIndex = 0;
	//char *command = (char*)malloc(cmdLineSize);

	//ignoring start spaces
	while (string[srcIndex++] == ' ');

	//now _index will point to a letter
	srcIndex--;
	while ((string[srcIndex] != ' ') && (srcIndex<counter)) {
		command[comIndex++] = string[srcIndex++];
	}
	command[comIndex] = '\0';
	//printf("Command is %s\n",command);

	memchr(arg,' ',cmdLineSize);
	while (srcIndex<counter) arg[0][argIndex++] = string[srcIndex++];
	arg[0][argIndex] = '\0';
	//printf("Arg is %s\n",arg);

	if (comIndex != 0) actions = OTHER;
		else actions = NONE;
	if ((strcmpi(command,"EXIT") == 0) ||
			(strcmpi(command,"QUIT") == 0) ||
			(strcmpi(command,"BYE") == 0)) actions = EXIT;
	if (strcmpi(command,"TIME") ==0) actions = TIME;
	if (strcmpi(command,"DATE") ==0) actions = DATE;
	if (strcmpi(command,"DIR") ==0) actions = DIR;
	if (strcmpi(command,"ECHO") ==0) actions = ECHO;

}

void doAction()
{
	switch(actions) {
		case EXIT : printf("Dudix aborted...\n");
								exit(0);
		case DATE :	struct dosdate_t d;
								_dos_getdate(&d);
								printf("Current date is %s %d-%d-%d\n", dayofweek[d.dayofweek], d.day, d.month, d.year);
								break;
		case TIME : struct dostime_t t;
								_dos_gettime(&t);
								printf("Current time is %2d:%02d:%02d.%02d\n", t.hour, t.minute,
											 t.second, t.hsecond);
								break;
		case DIR : strcat(command," ");
							 strcat(command,arg[0]);
							 if (system(command) == -1) printf("%s.\n",sys_errlist[errno]);
							 break;
		case ECHO : printf("%s\n",arg[0]);
							 break;
		case OTHER : if (spawnv(P_WAIT,command,arg) == -1) printf("%s.\n",sys_errlist[errno]);
								 break;
	}
}

