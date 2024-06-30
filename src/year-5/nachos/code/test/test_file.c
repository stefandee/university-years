// program ping in fisierul de iesire si dup'aia pong pe ecran din fisier

#define FISIER "out.txt"

#include "syscall.h"

int main(){

  OpenFileId handle;
  char actiuni[2] = {"Voi scrie in fisier\n", "Voi citi din fisier\n");
  char *mesaj = "Un caracter \n";
  char *dummy;
  int result;
  int mesajLung = strlen(mesaj);

  // scriu in fisier
  Write(actiuni[0], strlen(actiuni[0]), 1);
  Create("out.txt");
  handle = Open(FISIER);

  for(char c = '0'; c <= '9'; c++)
  {	
    Write(mesaj, mesajLung, handle);
    Write(&c, 1, handle);
  } 
  c = '\n';
  Write(c, 1, handle);
  Close(handle);

  // citesc din fisier
  Write(actiuni[1], strlen(actiuni[1]), 1);
  handle = Open(FISIER);
  while ( (result = Read(dummy, 1, handle)) != 0) {
    Write(dummy, result, 1);
  }
  Close(handle);
}

