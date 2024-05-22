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

int produce ()
{
    return rand () % 100;
}

/* -------------------------------------------------------------------------- */

#define PRODUCERS  5
#define CONSUMERS  3
#define ITEMS      1

#define ITEM_SUM  (PRODUCERS * CONSUMERS * ITEMS)

#define PRODUCER_ITEMS ITEM_SUM / PRODUCERS
#define CONSUMER_ITEMS ITEM_SUM / CONSUMERS

void *producer (int *pnr)
{
    int item;
    
    for (int i = 0; i < PRODUCER_ITEMS; i++)
    {
        item = produce ();
        printf ("producer [%d].put (%d)\n", *pnr, item);
        putSynchronized (item);
    }
    
    pthread_exit (0);
}

void *consumer (int *cnr)
{
    for (int i = 0; i < CONSUMER_ITEMS; i++)
    {
        printf ("consumer [%d].get () = %d\n", *cnr, getSynchronized ());
    } 
    
    pthread_exit (0);
}

/* -------------------------------------------------------------------------- */

int main (int argc, char *argv[]) 
{
    int       producers [PRODUCERS];
    int       consumers [CONSUMERS];
    
    pthread_t pids      [PRODUCERS];
    pthread_t cids      [CONSUMERS];
    
    int       i;
    
    for (i = 0; i < PRODUCERS; i++)
    {
        producers [i] = i;
    }
    
    for (i = 0; i < CONSUMERS; i++)
    {
        consumers [i] = i;
    }
    
    sem_init (&mutex, 0, 1);
    sem_init (&empty, 0, 0);
    sem_init (&full,  0, BUF_SIZE);

    for (i = 0; i < CONSUMERS; i++)
    {
        pthread_create (&cids [i], NULL, (void*) consumer, (void*) &consumers [i]);
    }
    
    for (i = 0; i < PRODUCERS; i++)
    {
        pthread_create (&pids [i], NULL, (void*) producer, (void*) &producers [i]);
    }
    
    for (i = 0; i < PRODUCERS; i++)
    {
        pthread_join (pids [i], NULL);
    }
    
    for (i = 0; i < CONSUMERS; i++)
    {
        pthread_join (cids [i], NULL);
    }
        
    sem_destroy (&full);
    sem_destroy (&empty);
    sem_destroy (&full);
}

/* -------------------------------------------------------------------------- */


