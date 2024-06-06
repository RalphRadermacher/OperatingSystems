/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include <errno.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/* -------------------------------------------------------------------------- */

#define SHM_ID   "SHM_TEST"
#define SHM_SIZE 32

/* -------------------------------------------------------------------------- */

int main (int argc, char *argv[])
{
    int   shmfd;
    char  msg [SHM_SIZE];
    void *addr;

    // Open shared memory
    
    if ((shmfd = shm_open (SHM_ID, O_CREAT | O_RDWR, 0666)) < 0)
    {
        fprintf (stderr, "ERROR: Shared memory creation failed (%s)\n", strerror (errno));
        return 1;
    }

    // Map shared memory
    
    if ((addr = mmap (NULL, SHM_SIZE, PROT_READ, MAP_SHARED, shmfd, 0)) == MAP_FAILED)
    {
        fprintf (stderr, "ERROR: Shared memory mapping failed (%s)\n", strerror (errno));
        return 1;
    }

    // Read message from shared memory
    
    memcpy (msg, addr, sizeof (msg));

    printf ( "Process %d: Read from shared memory: \"%s\"\n", getpid(), msg);

    return 0;
}

/* -------------------------------------------------------------------------- */
