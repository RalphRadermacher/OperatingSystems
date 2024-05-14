/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
/* -------------------------------------------------------------------------- */

#define BUF_SIZE 1024

/* -------------------------------------------------------------------------- */

char transChar (char src, char s1 [], char s2 [])
{
	int i;
	int n = strlen (s1);
	
	for (i = 0; i < n; i++)
	{
		if (src == s1 [i])
		{
			return s2 [i];
		}
    }	
    
    return src;
}

/* -------------------------------------------------------------------------- */

char* transString (char src [], char tgt [], char s1 [], char s2 [])
{
	int i;
	int n = strlen (src);
	
	for (i = 0; i < n; i++)
	{
		tgt [i] = transChar (src [i], s1, s2);
	}
	
	tgt [n] = '\0';
	
	return tgt;
}

/* -------------------------------------------------------------------------- */

int main (int argc, char* argv[])
{
    if (argc != 3)
    {
		fprintf (stderr, "USAGE: %s <set1> <set2>\n", argv [0]);
		exit (1); 
	}
	
	if (strlen (argv [1]) != strlen (argv [2]))
	{
		fprintf (stderr, "ERROR: <set1> and <set2> must be the same length\n");
		exit (1); 
	}
	
	// Copy args
	
	char* set1 = argv [1];
	char* set2 = argv [2];
	
    // Buffers
    
	char source [BUF_SIZE];
	char target [BUF_SIZE];
	
	while (scanf ("%s", source) != EOF) 
	{ 
        transString (source, target, set1, set2);
        
        printf ("%s\n", target);
    }

    return 0;
}

/* -------------------------------------------------------------------------- */

