/* -------------------------------------------------------------------------- */

/*
 * Vorlesung Betriebssysteme an der DHBW Karlsruhe und Mannheim
 * 
 * Dozent: Dr. Ralph Radermacher
 * 
 * Aufgabe - Argumente
 * 
 * Schreiben Sie ein C-Programm args.c, das die Argumente der Kommandozeile 
 * in der Standausgabe ausgibt.
 */
 
/* -------------------------------------------------------------------------- */

#include <stdio.h>

/* -------------------------------------------------------------------------- */
 
int main (int argc, char* argv[])
{
    int i;
    
    for (i = 0; i < argc; i++)
    {
        printf ("argv [%d] = %s\n", i, argv [i]);
    }

    return 0;
}

/* -------------------------------------------------------------------------- */
