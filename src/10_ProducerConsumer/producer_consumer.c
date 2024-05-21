/* -------------------------------------------------------------------------- */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

/* -------------------------------------------------------------------------- */

#define BUF_SIZE 5

int buffer [BUF_SIZE];
int readPos  = 0;
int writePos = 0;

int get ()
{
    int bufElem;
    
    bufElem = buffer [readPos];
    readPos = (readPos + 1) % BUF_SIZE;

    return bufElem;
}

void put (int bufElem)
{
    buffer [writePos] = bufElem;
    writePos = (writePos + 1) % BUF_SIZE;
}

/* -------------------------------------------------------------------------- */

sem_t mutex;
sem_t empty;
sem_t full;

int getSynchronized ()
{
    int bufElem;
    
    sem_wait (&empty);
    sem_wait (&mutex);
    
    bufElem = get ();

    sem_post (&mutex);
    sem_post (&full);
    
    return bufElem;
}

void putSynchronized (int bufElem)
{
    sem_wait (&full);
    sem_wait (&mutex);
    
    put (bufElem);

    sem_post (&mutex);
    sem_post (&empty);
}

/* -------------------------------------------------------------------------- */

int main (int argc, char *argv[]) 
{
    sem_init (&mutex, 0, 1);
    sem_init (&empty, 0, 0);
    sem_init (&full,  0, BUF_SIZE);

    putSynchronized (5);
    putSynchronized (3);
    putSynchronized (1);
    
    printf ("-> %d\n", getSynchronized ());
    printf ("-> %d\n", getSynchronized ());
    printf ("-> %d\n", getSynchronized ());
    
    sem_destroy (&full);
    sem_destroy (&empty);
    sem_destroy (&full);
}

/* -------------------------------------------------------------------------- */


