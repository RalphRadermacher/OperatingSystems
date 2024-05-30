/* -------------------------------------------------------------------------- */

#include "shm_buffer.h"

/* -------------------------------------------------------------------------- */

void *shmAddr;
int  shmSize;

int  *shmAddrInt;
int  *buffer;

int  *writePos;
int  *readPos;

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
    
    shmSize = (SHM_BUFFER_SIZE + 2) * sizeof (int);
    
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
    
    shmAddrInt = (int *) shmAddr;
    
    buffer   = shmAddrInt;
    writePos = shmAddrInt + SHM_BUFFER_SIZE;
    readPos  = shmAddrInt + SHM_BUFFER_SIZE + 1;
    
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
    for (int i = 0; i < SHM_BUFFER_SIZE + 2; i++)
    {
        printf (" %4d", buffer [i]);
    }
    
    printf ("\n");
}

/* -------------------------------------------------------------------------- */

void shm_buffer_put (int bufElem)
{
    buffer [*writePos] = bufElem;
    *writePos = (*writePos + 1) % SHM_BUFFER_SIZE;
}

/* -------------------------------------------------------------------------- */

int shm_buffer_get ()
{
    int bufElem;
    
    bufElem = buffer [*readPos];
    *readPos = (*readPos + 1) % SHM_BUFFER_SIZE;

    return bufElem;
}

/* -------------------------------------------------------------------------- */


