/* -------------------------------------------------------------------------- */

/*
 * Vorlesung Betriebssysteme an der DHBW Karlsruhe und Mannheim
 * 
 * Dozent: Dr. Ralph Radermacher
 */

/* -------------------------------------------------------------------------- */

#include <sys/socket.h>
#include <netdb.h>
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

#define PORT_NUMBER 5000

int port = PORT_NUMBER;

/* -------------------------------------------------------------------------- */

#define BUF_SIZE 5 
#define WORKERS  5

pthread_t wIds [WORKERS]; // Ids of the worker threads
int       wNrs [WORKERS]; // Nr of the worker threads
 
/* -------------------------------------------------------------------------- */

#define MIME_TYPE_DEFAULT "ext/html"

char* mimeTypes [][2] = 
{
    {".html", "text/html"},
    {".css",  "text/css"},
    {".js",   "application/js"},
    {".jpg",  "image/jpeg"},
    {".png",  "image/png"},
    {".gif",  "image/gif"},
    {".html", "text/html"},
    { NULL,    NULL}    
};

char* getMimeType (char *fileName)
{
    const char *dot = strrchr (fileName, '.');
    
    if (dot == NULL)
    {
        return MIME_TYPE_DEFAULT;
    }
    
    for (int i = 0; mimeTypes [i][0] != NULL; i++)
    {
        if (strcmp (dot, mimeTypes [i][0]) == 0)
        {
            return mimeTypes [i][1];
        }
    }
    
    return  MIME_TYPE_DEFAULT;
}

/* -------------------------------------------------------------------------- */

void getFileURL (char *route, char *fileURL)
{
      char *question = strrchr (route, '?');
      
      if (question)
      {
          *question = '\0';
      }
    
      if (route [strlen (route) - 1] == '/')
      {
          strcat (route, "index.html");
      }
    
      strcpy (fileURL, "htdocs");
      strcat (fileURL, route);
    
      const char *dot = strrchr(fileURL, '.');
      
      if (!dot || dot == fileURL)
      {
          strcat (fileURL, ".html");
      }
}

/* -------------------------------------------------------------------------- */

void *worker (int *wnr)
{
    int   connFd;
    int   nBytes = 0;
    
    char  recvBuf [1024];
    char  method  [32];
    char  route   [1924];
     
    logI ("Worker %d started\n", *wnr);
    
    while (1)
    {
        connFd = bufferGet ();
        
        if ((nBytes = read (connFd, recvBuf, sizeof (recvBuf) - 1)) > 0)
        {
            recvBuf [nBytes] = '\0';
        
            sscanf (recvBuf, "%s %s", method, route);

            logI ("Worker %d : %s %s\n", *wnr, method, route);
            
            const char response[] = "HTTP/1.1 404 Not Found\r\n\n";
            send (connFd, response, sizeof (response), 0);

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
        wNrs [i] = i;
    }
    
    for (i = 0; i < WORKERS; i++)
    {
        pthread_create (&wIds [i], NULL, (void*) worker, (void*) &wNrs [i]);
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
    setsockopt (listenFd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    
    memset (&servAddr, '0', sizeof (servAddr));

    servAddr.sin_family      = AF_INET;
    servAddr.sin_addr.s_addr = htonl (INADDR_LOOPBACK);
    servAddr.sin_port        = htons (port); 

    bind   (listenFd, (struct sockaddr*) &servAddr, sizeof (servAddr)); 
    listen (listenFd, 10); 
    
    char hostBuffer    [NI_MAXHOST];
    char serviceBuffer [NI_MAXSERV];
    
    getnameinfo 
    (
        (struct sockaddr *) &servAddr, 
        sizeof (servAddr), 
        hostBuffer,
        sizeof (hostBuffer), 
        serviceBuffer, 
        sizeof (serviceBuffer), 
        0
     );
    
    logI ("%s is listening on http://%s:%s/\n", argv [0], hostBuffer, serviceBuffer);
    
    while (1)
    {
        connFd = accept (listenFd, (struct sockaddr*) NULL, NULL); 
        
        logI ("Connection accepted on port %d\n", port);
        
        bufferPut (connFd);
     }
}

/* -------------------------------------------------------------------------- */

