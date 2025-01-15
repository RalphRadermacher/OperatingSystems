/* -------------------------------------------------------------------------- */

/*
 * Vorlesung Betriebssysteme an der DHBW Karlsruhe und Mannheim
 * 
 * Dozent: Dr. Ralph Radermacher
 */

/* -------------------------------------------------------------------------- */

#define ERROR  0
#define INFO   1
#define FINER  2

void logLocal (int level, const char *format, ...)
{
    
}
    
void logError (const char *format, ...)
{
    logLocal (ERROR, format, ...);
}
    
/* -------------------------------------------------------------------------- */

