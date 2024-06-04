/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include <errno.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/* -------------------------------------------------------------------------- */

#define SHM_BUFFER_NAME "SHM_BUFFER"
#define SHM_BUFFER_SIZE 5

/* -------------------------------------------------------------------------- */

int  shm_buffer_init  (int resetBuf);
void shm_buffer_put   (int bufElem);
int  shm_buffer_get   ();
void shm_buffer_print ();

/* -------------------------------------------------------------------------- */
