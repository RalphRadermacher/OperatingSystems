/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include <sys/types.h>
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
        printf ("Parent process (%d) of child process (%d)\n", getpid (), pid);
	}
	else
	{
        printf ("Child process (%d)\n", getpid ());
	}
    
    return 0;
}

/* -------------------------------------------------------------------------- */
