/* -------------------------------------------------------------------------- */

/*
 * Vorlesung Betriebssysteme an der DHBW Karlsruhe und Mannheim
 * 
 * Dozent: Dr. Ralph Radermacher
 */

/* -------------------------------------------------------------------------- */

#include "buffer.h"

/* -------------------------------------------------------------------------- */

// Buffer

int size;
int *buffer;
int readPos  = 0;
int writePos = 0;

/* -------------------------------------------------------------------------- */

int getLocal ()
{
    int bufElem;
    
    bufElem = buffer [readPos];
    readPos = (readPos + 1) % size;

    return bufElem;
}

void putLocal (int bufElem)
{
    buffer [writePos] = bufElem;
    writePos = (writePos + 1) % size;
}

/* -------------------------------------------------------------------------- */

// Semaphore

sem_t mutex;
sem_t empty;
sem_t full;

/* -------------------------------------------------------------------------- */

int bufferInit (int sz)
{
    size   = sz,
    buffer = malloc (size * sizeof (int));
    
    sem_init (&mutex, 0, 1);
    sem_init (&empty, 0, 0);
    sem_init (&full,  0, size);
    
    return 0;
}

int bufferGet ()
{
    int bufElem;
    
    sem_wait (&empty);
    sem_wait (&mutex);
    
    bufElem = getLocal ();

    sem_post (&mutex);
    sem_post (&full);

    return bufElem;
}

void bufferPut (int bufElem)
{
    sem_wait (&full);
    sem_wait (&mutex);
    
    putLocal (bufElem);

    sem_post (&mutex);
    sem_post (&empty);
}

/* -------------------------------------------------------------------------- */
