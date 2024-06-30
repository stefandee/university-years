#include <unistd.h>
#include <stdlib.h>

void main(int argc, char* argv[])
{
  pid_t pid;
  pid = vfork();
  if (argc<2) {
    printf("\n Eroare : mai putin de 2 parametri\n");
    exit(1);
  }
  if (pid<0) {
    perror("Eroare la vfork :");
    exit(1);
  }
  if (pid==0) {
    printf("\n Child with pid %d running...", getpid());
    if (execvp(argv[1], &argv[1])==-1) {
      perror("Execvp error :");
      exit(1);
    }
  }
  printf("Gata.\n");
}




