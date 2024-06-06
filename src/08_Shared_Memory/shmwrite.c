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

#define MESSAGE  "Message from process %d"

/* -------------------------------------------------------------------------- */

int main (int argc, char *argv[])
{
    int  shmfd;
    void *addr;
    char msg [SHM_SIZE];

    // Open shared memory
    
    if ((shmfd = shm_open (SHM_ID, O_CREAT | O_RDWR, 0666)) < 0)
    {
        fprintf (stderr, "ERROR: Shared memory creation failed (%s)\n", strerror (errno));
        return 1;
    }

    // Adjust shared memory size
    
    if (ftruncate (shmfd, SHM_SIZE) < 0)
    {
        fprintf (stderr, "ERROR: Shared memory extention failed (%s)\n", strerror (errno));
        return 1;
    }

    // Map shared memory
    
    if ((addr = mmap (NULL, SHM_SIZE, PROT_WRITE, MAP_SHARED, shmfd, 0)) == MAP_FAILED)
    {
        fprintf (stderr, "ERROR: Shared memory mapping failed (%s)\n", strerror (errno));
        return 1;
    }

    // Create message and write it to shared memory
    
    sprintf (msg, MESSAGE, getpid ());
    memcpy (addr, msg, strlen (msg) + 1);

    printf ("Process %d: Written to shared memory: \"%s\"\n", getpid (), msg);

    return 0;
}

/* -------------------------------------------------------------------------- */
