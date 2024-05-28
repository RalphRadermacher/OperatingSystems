/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/* -------------------------------------------------------------------------- */

int main (int argc, char* argv[])
{
    pid_t  pid;
    int    fdPair [2]; 
    
    if (pipe (fdPair) < 0)
    {
        fprintf (stderr, "ERROR: Pipe creation failed (%s)\n", strerror (errno));
        return 1;
    }
       
    if ((pid = fork ()) < 0)
    {
        fprintf (stderr, "ERROR: Fork failed (%s)\n", strerror (errno));
        return 1;
    }
    
    if (pid != 0)
    {
        int  i;
        
        // Parent process closes the the output side of the pipe

        close (fdPair [0]);
        
        printf ("Parent process (%d)\n", getpid ());
        
        for (i = 1; i < argc; i++)
        {
           printf ("Parent> %s (%d)\n", argv [i], strlen (argv [i]));
           write (fdPair [1], argv [i], strlen (argv [i]));
        }
        
        close (fdPair [1]);
        
        wait (NULL);
    }
    else
    {
        char str [1024];
        int  nBytes;
       
        // Child process closes the input side of the pipe

        close (fdPair [1]);
       
        printf ("Child process (%d)\n", getpid ());
        
        while ((nBytes = read (fdPair [0], str, sizeof (str))) > 0)
        {    
            str [nBytes] = '\0';
            printf ("Child> %s (%d)\n", str, nBytes);
        }
              
        if (nBytes < 0)
        {
            fprintf (stderr, "ERROR: Read failed (%s)\n", strerror (errno));
            return 1;
        }
    
        close (fdPair [0]);
    }
    
    return 0;
}        
