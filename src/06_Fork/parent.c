/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* -------------------------------------------------------------------------- */

int main (int argc, char* argv[])
{
    pid_t pid;
    
    if ((pid = fork ()) < 0)
    {
		fprintf (stderr, "Fork failed\n");
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
		
		execvp (argv [1], argv + 2);
	}
    
    return 0;
}

/* -------------------------------------------------------------------------- */
