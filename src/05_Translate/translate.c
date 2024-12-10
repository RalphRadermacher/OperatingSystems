/* -------------------------------------------------------------------------- */

/*
 * Vorlesung Betriebssysteme an der DHBW Karlsruhe und Mannheim
 * 
 * Dozent: Dr. Ralph Radermacher
 * 
 * Aufgabe - Translate
 * 
 * Schreiben Sie ein C-Programm translate.c, das Zeichenketten aus der 
 * Standeingabe einliest und nach einer Übersetzung in der 
 * Standardausgabe wieder ausgibt. Die Übersetzung wird durch zwei 
 * gleichlange Argumente der Kommandozeile set1 und set2 definiert 
 * und geschieht wie folgt, für der jeden Buchstaben der eingelesenen 
 * Zeichenketten wird in nachdem ersten Auftreten des Buchstabens
 * in dem Argumente set1 gesucht. Falls der Buchstabe nicht im 
 * Argument set1 gefunden wird, bleibt der Buchstabe unverändert. 
 * Falls der Buchstabe im Argument set1 an der i-ten Stelle zum 
 * ersten Mal auftritt, wird der Buchstabe durch den Buchstabe 
 * an der i-ten Stelle des Arguments set2 ersetzt.
 * 
 */
 
* -------------------------------------------------------------------------- */

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

