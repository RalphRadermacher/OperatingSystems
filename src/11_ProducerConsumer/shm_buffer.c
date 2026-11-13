/* -------------------------------------------------------------------------- */

#include "shm_buffer.h"

/* -------------------------------------------------------------------------- */

void          *shmAddr;
int           shmSize;

int           *shmAddrInt;

struct sems_t *sems;
int           *buffer;

int           *writePos;
int           *readPos;

/* -------------------------------------------------------------------------- */

struct sems_t
{
    sem_t mutex;
    sem_t empty;
    sem_t full;
};

/* -------------------------------------------------------------------------- */

int shm_buffer_init (int resetBuf)
{
    int shmFd;
    
     // Open shared memory
    
    if ((shmFd = shm_open (SHM_BUFFER_NAME, O_CREAT | O_RDWR, 0666)) < 0)
    {
        return -1;
    }

    // Adjust shared memory size
    
    shmSize = sizeof (struct sems_t) + (SHM_BUFFER_SIZE + 2) * sizeof (int);
    
    if (ftruncate (shmFd, shmSize) < 0)
    {
        return -2;
    }

    // Map shared memory
    
    if ((shmAddr = mmap (NULL, shmSize, PROT_WRITE, MAP_SHARED, shmFd, 0)) == MAP_FAILED)
    {
        return -3;
    }

    // Set the pointers
    
    sems       = (struct sems_t*) shmAddr;

    shmAddrInt = (int *) (shmAddr + sizeof (struct sems_t));
    
    buffer     = shmAddrInt;
    writePos   = shmAddrInt + SHM_BUFFER_SIZE;
    readPos    = shmAddrInt + SHM_BUFFER_SIZE + 1;
    
    // Create semaphores
 
    sem_init (&sems -> mutex, 1, 1);
    sem_init (&sems -> empty, 1, 0);
    sem_init (&sems -> full,  1, SHM_BUFFER_SIZE);

   
    if (resetBuf)
    {
        for (int i = 0; i < SHM_BUFFER_SIZE; i++)
        {
            buffer [i] = -1;
        }
        
        *writePos = 0;
        *readPos  = 0;
    }
    
    return 0;
}

/* -------------------------------------------------------------------------- */

void shm_buffer_print ()
{
    printf ("Buffer: ");

    for (int i = 0; i < SHM_BUFFER_SIZE + 2; i++)
    {
        printf (" %4d", buffer [i]);
    }
    
    printf ("\n");
}

/* -------------------------------------------------------------------------- */

void shm_buffer_put_local (int bufElem)
{
    buffer [*writePos] = bufElem;
    *writePos = (*writePos + 1) % SHM_BUFFER_SIZE;
}

/* -------------------------------------------------------------------------- */

int shm_buffer_get_local ()
{
    int bufElem;
    
    bufElem = buffer [*readPos];
    *readPos = (*readPos + 1) % SHM_BUFFER_SIZE;

    return bufElem;
}

/* -------------------------------------------------------------------------- */

void shm_buffer_put (int bufElem)
{
    sem_wait (&sems -> full);
    sem_wait (&sems -> mutex);
    
    shm_buffer_put_local (bufElem);

    sem_post (&sems -> mutex);
    sem_post (&sems -> empty);
}

/* -------------------------------------------------------------------------- */

int shm_buffer_get ()
{
    int bufElem;
    
    sem_wait (&sems -> empty);
    sem_wait (&sems -> mutex);
    
    bufElem = shm_buffer_get_local ();

    sem_post (&sems -> mutex);
    sem_post (&sems -> full);

    return bufElem;
}

/* -------------------------------------------------------------------------- */


