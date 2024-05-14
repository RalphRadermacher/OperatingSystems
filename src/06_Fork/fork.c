/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

/* -------------------------------------------------------------------------- */

int main (int argc, char* argv[])
{
    pid_t pid;
    
    if ((pid = fork ()) < 0)
    {
		fprintf (stderr, "ERROR: Fork failed (%s)\n", strerror (errno));
		return 1;
	}
    
    if (pid != 0)
    {
        printf ("Parent process (%d) of child process (%d)\n", getpid (), pid);
	}
	else
	{
        printf ("Child process (%d)\n", getpid ());
	}
    
    return 0;
}

/* -------------------------------------------------------------------------- */
