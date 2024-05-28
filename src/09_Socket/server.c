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

/* -------------------------------------------------------------------------- */

int main (int argc, char *argv[])
{
    int                listenFd   = 0; 
    int                connFd     = 0;
    struct sockaddr_in servAddr; 

    char               sendBuf [1025];
    time_t             ticks; 

    listenFd = socket (AF_INET, SOCK_STREAM, 0);
    
    memset (&servAddr, '0', sizeof (servAddr));
    memset (sendBuf,   '0', sizeof (sendBuf)); 

    servAddr.sin_family      = AF_INET;
    servAddr.sin_addr.s_addr = htonl (INADDR_ANY);
    servAddr.sin_port        = htons (5000); 

    bind (listenFd, (struct sockaddr*) &servAddr, sizeof (servAddr)); 

    listen (listenFd, 10); 

    while (1)
    {
        connFd = accept (listenFd, (struct sockaddr*) NULL, NULL); 

        ticks = time (NULL);
        snprintf (sendBuf, sizeof (sendBuf), "%.24s", ctime (&ticks));
        
        printf ("Connection accepted at %s\n", sendBuf);

        write (connFd, sendBuf, strlen (sendBuf)); 

        close (connFd);
        sleep (1);
     }
}

/* -------------------------------------------------------------------------- */

