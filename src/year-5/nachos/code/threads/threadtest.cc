// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"

#include "synch.h"

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

#define DIM_BUFFER 10
#define DELAY 100000
#define ITERATII 100

int stivaVirf = 0;
char stiva[DIM_BUFFER];
Semaphore *mutex, *libere, *ocupate;
char mesaj[] = "Comunicare intre threaduri";
#define lungimeMesaj strlen(mesaj);

void Producator(int thread_no)
{
  int c = 0;

  for (int i=0; i < ITERATII; i++) 
  {
    libere->P();
    mutex->P();
    stiva[stivaVirf] = mesaj[c];
    stivaVirf++;
    c = (c+1) % lungimeMesaj;
    mutex->V();
    ocupate->V();
    for (int delay = 0; delay < DELAY; delay++);
  }
}
    
void Consumer(int thread_no)
{
  int i;

  for (int i=0; i < ITERATII; i++) 
  {
    ocupate->P();
    mutex->P();
    stivaVirf--;
    printf("%c", stiva[stivaVirf]);
    mutex->V();
    libere->V();
    for (int delay = 0; delay < DELAY; delay++);
  }
}



//----------------------------------------------------------------------
// ThreadTest
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

void
ThreadTest()
{
    DEBUG('t', "Program producator-consumator\n");

    Thread* threads[6];
    char id[20];

    mutex = new Semaphore("Mutex", 1);
    libere = new Semaphore("Libere", DIM_BUFFER-1);
    ocupate = new Semaphore("Ocupate", 0);

    for (int i = 0; i < 3; i++) 
    {
      sprintf(id, "Producator %d", i+1);
      threads[i] = new Thread(id);
    }
    for (int i = 3; i < 6; i++) 
    {
      sprintf(id, "Consumator %d", i-4);
      threads[i] = new Thread(id);
    }
      
    for (int i = 0; i < 3; i++)
      threads[i]->Fork(Producator, i+1);
    for (int i = 3; i < 6; i++)
      threads[i]->Fork(Consumator, i+1);
}



