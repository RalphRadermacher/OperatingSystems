/* -------------------------------------------------------------------------- */

/*
 * Vorlesung Betriebssysteme an der DHBW Karlsruhe und Mannheim
 * 
 * Dozent: Dr. Ralph Radermacher
 */

/* -------------------------------------------------------------------------- */

#include <stdarg.h>
#include <stdio.h>

#include "logging.h"

/* -------------------------------------------------------------------------- */

int logLevel = INFO;

/* -------------------------------------------------------------------------- */
  
void logging (int level, const char *format, ...)
{
    if (level > logLevel)
    {
        return;
    }
    
    va_list args;
    
    va_start (args, format);
    vprintf (format, args);
    va_end (args);
}
    
/* -------------------------------------------------------------------------- */
