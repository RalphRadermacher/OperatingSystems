/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/* -------------------------------------------------------------------------- */

int main (int argc, char* argv[])
{
    int i;
    
    printf ("Child process (%d)", getpid ());
    
    for (i = 0; i < argc; i++)
    {
		printf (" %s", argv [i]);
	}
	
	printf ("\n");
	
    return 0;
}

/* -------------------------------------------------------------------------- */
