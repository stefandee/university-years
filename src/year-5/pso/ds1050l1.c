#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define RANDOM_SEND 10

typedef struct mymsg
{
  long mtype;
  char mtext[100];
};

char* produse[10] = { "piine", "lapte", "roshii", "varza", "oua  ", "salata", "cola", "iaurt", "pepeni", "marar"}; 

void main()
{
  pid_t proces1, proces2;
  int message_queue;
  struct mymsg buffer;
  int produs, i, len;

  printf("IPC laborator 1. Cozi de mesaje.\n");
  
  /* create a message queue */
  message_queue = msgget(IPC_PRIVATE, O_CREAT | S_IREAD | S_IWRITE);
  if (message_queue == -1)
    {
      perror("(fatal). Aborting execution.\n");
      exit(1);
    }

  proces1 = fork();
  if (proces1 < 0)
    {
      perror("(fatal). Aborting execution.\n");
      exit(1);
    }
  if (proces1 == 0)
    {
      printf("Proces 1 ready to send.\n");
      for(i = 0; i < RANDOM_SEND; i++)
	{
	  buffer.mtype = 1;
	  produs = (int)(10.0*rand()/(RAND_MAX+1.0));
	  buffer.mtext[0] = (char)strlen(produse[produs]) + 1;
	  if (msgsnd(message_queue, &buffer, 1, 0) == -1)
	    {
	      perror("(fatal sending length)");
	      exit(1);
	    }

	  buffer.mtype = 1;
	  strcpy(buffer.mtext, produse[produs]);
          if (msgsnd(message_queue, &buffer, strlen(produse[produs]) + 1, 0) == -1)
	    {
	      perror("(fatal in sending buffer)");
	      exit(0);
	    }
	  printf("Sent : %s\n", produse[produs]);
	  sleep(1);
	}
      
      buffer.mtext[0] = 20;
      msgsnd(message_queue, &buffer, 1, 0);
      printf("Proces 1 ended.\n");
      
      exit(0);
    }

  proces2 = fork();
  if (proces2 < 0)
    {
      perror("(fatal). Aborting execution.\n");
      exit(1);
    }
  if (proces2 == 0)
    {
      printf("Proces 2 ready to receive.\n");
      buffer.mtext[0] = '\0';
      while(1)
	{
	  if (msgrcv(message_queue, &buffer, 1, 0, 0) == -1)
	    {
	      perror("(fatal receiving length)");
	      exit(1);
	    }
	  if (buffer.mtext[0] == 20) break;
         
	  len = buffer.mtext[0];
	  if (msgrcv(message_queue, &buffer, len, 0, 0) == -1)
	    {
	      perror("(fatal receiving buffer");
	      exit(1);
	    }
	  printf("Received : %s\n", buffer.mtext, len);
	  sleep(1);
	}
      printf("Proces 2 ended.\n");
      exit(0);
    }
  
}
