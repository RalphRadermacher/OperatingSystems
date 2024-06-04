/* -------------------------------------------------------------------------- */

#include "shm_buffer.h"

/* -------------------------------------------------------------------------- */

int main (int argc, char *argv[])
{
    if (shm_buffer_init (1) < 0)
    {
        fprintf (stderr, "ERROR: SHM buffer initialisation failed (%s)\n", strerror (errno));
        return 1;
    }
    
    shm_buffer_print ();
    shm_buffer_put   (4);
    shm_buffer_print ();
    shm_buffer_get   ();
    shm_buffer_print ();
 
}

/* -------------------------------------------------------------------------- */
