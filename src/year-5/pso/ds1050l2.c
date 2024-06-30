#include <unistd.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <stdio.h>

int up(int semset) 
{
  struct sembuf temp;

  temp.sem_num = 0;
  temp.sem_op = 1;
  temp.sem_flg = 0;
  
  return semop(semset, &temp, 1);
}

int down(int semset)
{
  struct sembuf temp;

  temp.sem_num = 0;
  temp.sem_op = -1;
  temp.sem_flg = 0;
  
  return semop(semset, &temp, 1);
}

void main()
{
  pid_t reader1, reader2, onscreen;
  int bytes[3];
  int handle1, handle2;
  int charread1 = 0, charread2 = 0, charread = 0;
  int mutex;
  int fd[2];

  printf("Getting a semaphore...\n");
  mutex = semget(IPC_PRIVATE, 1, IPC_CREAT);
  if (mutex == -1)
    {
      perror("Err creating semaphore set : ");
      exit(1);
    }
  
  printf("Opening file 1...\n");
  if ((handle1 = open("text1", O_RDWR)) == -1) 
    {
      printf("Err opening test1\n");
      exit(1);
    };
  if ((handle2 = open("text2", O_RDWR)) == -1) 
    {
      printf("Err opening test2\n");
      exit(1);
    }; 
  
  printf("Start...");

  if (pipe(fd) < 0)
    {
      printf("Err opening pipe");
    }
  
  reader1 = fork();
  if (reader1 < 0)
    {
      perror("Fork 1 writer err : ");
      exit(1);
    }
  if (reader1 == 0)
    {
      close(fd[0]);
      bytes[0] = 0;
      while(1)
	{
	  down(mutex);
	  if (read(handle1, &charread1, 1) <= 0) 
	    {
	      up(mutex);
	      break;
	    }
	  up(mutex);
	  sleep(1);
	  if (write(fd[1], &charread1, 1) < 0)
	    {
	      perror("Err writing in pipe 1 : ");
	      exit(0);
	    }
	  bytes[0]++;
	}
      printf("Reader 1 is out...");
      close(fd[1]);
      exit(0);
    }

  reader2 = fork();
  if (reader2 < 0)
    {
      perror("Fork 2 writer err : ");
      exit(1);
    }
  if (reader2 == 0)
    {
      close(fd[0]);
      bytes[1] = 0;
      while(1)
	{
	  down(mutex);
	  if (read(handle2, &charread2, 1) <= 0) 
	    {
	      up(mutex);
	      break;
	    }
	  up(mutex);
	  if (write(fd[1], &charread2, 1) < 0)
	    {
	      perror("Err writing in pipe 2 : ");
	      exit(0);
	    }
	  bytes[1]++;
	}
      printf("Reader 2 is out...");
      close(fd[1]);
      exit(0);
    }    

  onscreen = fork();
  if (onscreen < 0)
    {
      perror("Fork reader err : ");
      exit(1);
    }
  if (onscreen == 0)
    {
      close(fd[1]);
      bytes[2] = 0;
      while(read(fd[0], &charread, 1) >= 0)
	{
	  printf("%c\n", charread);
	  sleep(1);
	  bytes[2]++;
	}
      printf("Reader is out...");
      close(fd[0]);
      exit(0);
    }
}




