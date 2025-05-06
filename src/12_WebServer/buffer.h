/* -------------------------------------------------------------------------- */

/*
 * Vorlesung Betriebssysteme an der DHBW Karlsruhe und Mannheim
 * 
 * Dozent: Dr. Ralph Radermacher
 */

/* -------------------------------------------------------------------------- */

#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>

/* -------------------------------------------------------------------------- */

int  bufferInit (int sz);
int  bufferGet  ();
void bufferPut  (int bufElem);

/* -------------------------------------------------------------------------- */


