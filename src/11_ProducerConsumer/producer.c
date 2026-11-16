/* -------------------------------------------------------------------------- */

#include <stdlib.h>
#include <time.h>

#include "shm_buffer.h"

/* -------------------------------------------------------------------------- */

int produce ()
{
    return rand () % 100;
}

/* -------------------------------------------------------------------------- */

int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf (stderr, "USAGE: %s <no_of_items>\n", argv [0]);        
        return 1;
    }
    
    if (shm_buffer_init (0) < 0)
    {
        fprintf (stderr, "ERROR: SHM buffer initialization failed (%s)\n", strerror (errno));
        return 1;
    }
    
    srand ((unsigned) time (NULL));

    int item;
    int items = atoi (argv [1]);
    
    for (int i = 0; i < items; i++)
    {
        // printf ("producer [%d].shm_buffer_put ()\n", getpid ());
        // shm_buffer_print ();
        item = produce ();
        shm_buffer_put (item);
        printf ("producer [%d].shm_buffer_put (%d)\n", getpid (), item);
        // shm_buffer_print ();
   }
}

/* -------------------------------------------------------------------------- */
