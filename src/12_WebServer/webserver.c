/* -------------------------------------------------------------------------- */

/*
 * Vorlesung Betriebssysteme an der DHBW Karlsruhe und Mannheim
 * 
 * Dozent: Dr. Ralph Radermacher
 */

/* -------------------------------------------------------------------------- */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <pthread.h>

#include "buffer.h"
#include "logging.h"

/* -------------------------------------------------------------------------- */

#define BUF_SIZE 5 
#define WORKERS  5

pthread_t wids [WORKERS];
int       workers [WORKERS];
 
/* -------------------------------------------------------------------------- */

void *worker (int *wnr)
{
    int   connFd;
    int   nBytes = 0;
    char  recvBuf [1024];
     
    logI ("Worker %d started\n", *wnr);
    
    while (1)
    {
        connFd = bufferGet ();
        
        if ((nBytes = read (connFd, recvBuf, sizeof (recvBuf) - 1)) > 0)
        {
            recvBuf [nBytes] = 0;
        
            logI ("Worker %d : %s\n", *wnr, recvBuf);
        } 

        close (connFd);
    }
}

/* -------------------------------------------------------------------------- */

int initialize ()
{
    int i;
    
    bufferInit (BUF_SIZE);
    
    for (i = 0; i < WORKERS; i++)
    {
        workers [i] = i;
    }
    
    for (i = 0; i < WORKERS; i++)
    {
        logI ("create (%d)\n", workers [i]);
        pthread_create (&wids [i], NULL, (void*) worker, (void*) &workers [i]);
    }
    
    return 0;
}

/* -------------------------------------------------------------------------- */

int main (int argc, char *argv[])
{
    int                listenFd = 0; 
    int                connFd   = 0;
    struct sockaddr_in servAddr; 

    initialize ();
    
    listenFd = socket (AF_INET, SOCK_STREAM, 0);
    
    memset (&servAddr, '0', sizeof (servAddr));

    servAddr.sin_family      = AF_INET;
    servAddr.sin_addr.s_addr = htonl (INADDR_ANY);
    servAddr.sin_port        = htons (5000); 

    bind (listenFd, (struct sockaddr*) &servAddr, sizeof (servAddr)); 

    listen (listenFd, 10); 
    
    while (1)
    {
        connFd = accept (listenFd, (struct sockaddr*) NULL, NULL); 
        
        logI ("Connection accepted on port %d\n", 5000);
        
        bufferPut (connFd);
     }
}

/* -------------------------------------------------------------------------- */

