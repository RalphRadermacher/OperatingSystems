/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* -------------------------------------------------------------------------- */

int main (int argc, char* argv[])
{
    pid_t pid;
    
    if (argc <= 1)
    {
		fprintf (stderr, "USAGE: %s <child program> <child args ...>\n", argv [0]);
		return -1;
	}
	
    if ((pid = fork ()) < 0)
    {
		fprintf (stderr, "ERROR: Fork failed (%s)\n", strerror (errno));
		return 1;
	}
    
    if (pid != 0)
    {
		// I'm the parent
		
        printf ("Parent process (%d)\n", getpid ());
        wait (NULL);
 	}
 	else
 	{
		// I'll be the child 
		
		if (execvp (argv [1], argv + 2) < 0)
		{
			fprintf (stderr, "ERROR: Could not execute \"%s\" (%s)\n", argv [1], strerror (errno));
			return -1;
		}
	}
    
    return 0;
}

/* -------------------------------------------------------------------------- */
