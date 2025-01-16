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

#include "logging.h"

/* -------------------------------------------------------------------------- */

#define WORKERS 5

/* -------------------------------------------------------------------------- */

/*
void *worker (int *pnr)
{
}
*/
/* -------------------------------------------------------------------------- */

int main (int argc, char *argv[])
{
    int                listenFd = 0; 
    int                connFd   = 0;
    struct sockaddr_in servAddr; 

    int                nBytes = 0;
    char               recvBuf [1024];
     
    listenFd = socket (AF_INET, SOCK_STREAM, 0);
    
    memset (&servAddr, '0', sizeof (servAddr));

    servAddr.sin_family      = AF_INET;
    servAddr.sin_addr.s_addr = htonl (INADDR_ANY);
    servAddr.sin_port        = htons (5000); 

    bind (listenFd, (struct sockaddr*) &servAddr, sizeof (servAddr)); 

    listen (listenFd, 10); 
    
        logE ("Connection accepted on port %d\n", nBytes);

    while (1)
    {
        connFd = accept (listenFd, (struct sockaddr*) NULL, NULL); 

        logging (1, "Connection accepted on port %d\n", 5000);

        while ((nBytes = read (connFd, recvBuf, sizeof (recvBuf) - 1)) > 0)
        {
            recvBuf [nBytes] = 0;
        
            logging (1, "Message: %s\n", recvBuf);
        } 

        close (connFd);
        sleep (1);
     }
}

/* -------------------------------------------------------------------------- */

