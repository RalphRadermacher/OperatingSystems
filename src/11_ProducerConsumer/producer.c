/* -------------------------------------------------------------------------- */

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
        fprintf (stderr, "ERROR: SHM buffer initialisation failed (%s)\n", strerror (errno));
        return 1;
    }
    
    int item;
    int items = atoi (argv [1]);
    
    for (int i = 0; i < items; i++)
    {
        item = produce ();
        printf ("producer [%d].shm_buffer_put (%d)\n", *pnr, item);
        shm_buffer_put (item);
    }
}

/* -------------------------------------------------------------------------- */
