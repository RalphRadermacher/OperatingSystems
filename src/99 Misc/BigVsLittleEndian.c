/* -------------------------------------------------------------------------- */

/*
 * Vorlesung Betriebssysteme an der DHBW Karlsruhe und Mannheim
 *
 * Dozent: Dr. Ralph Radermacher
 */

/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdint.h>

int main (void)
{
    uint32_t       x = 0X12345678;
    unsigned char *p = (unsigned char *) &x;

    for (int i = 0; i < 4; i++)
    {
        printf ("%02x ", p [i]);
    }
}

/* -------------------------------------------------------------------------- */

