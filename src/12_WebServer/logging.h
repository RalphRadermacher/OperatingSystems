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

void logging (int level, const char *format, ...);

/* -------------------------------------------------------------------------- */

#define logE(format, ...) logging (ERROR, format, __VA_ARGS__)
#define logI(format, ...) logging (INFO,  format, __VA_ARGS__)
#define logF(format, ...) logging (FINER, format, __VA_ARGS__)

/* -------------------------------------------------------------------------- */

