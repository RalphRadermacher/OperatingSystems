/* -------------------------------------------------------------------------- */

/*
 * Vorlesung Betriebssysteme an der DHBW Karlsruhe und Mannheim
 * 
 * Dozent: Dr. Ralph Radermacher
 */

/* -------------------------------------------------------------------------- */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

/* -------------------------------------------------------------------------- */

int main (int argc, char *argv[])
{
    int                sockFd = 0;
    int                nBytes = 0;
    char               recvBuf [1024];
    struct sockaddr_in servAddr; 

    if (argc != 2)
    {
        fprintf (stderr, "USAGE: %s <ip of server> \n", argv[0]);
        return 1;
    } 

    memset (recvBuf, '0', sizeof(recvBuf ));
    
    if ((sockFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf (stderr, "ERROR: Could not create socket (%s)\n", strerror (errno));
        return 1;
    } 

    memset (&servAddr, '0', sizeof (servAddr)); 

    servAddr.sin_family = AF_INET;
    servAddr.sin_port   = htons (5000); 

    if (inet_pton (AF_INET, argv [1], &servAddr.sin_addr) <= 0)
    {
        fprintf (stderr, "ERROR: inet_pton error occured (%s)\n", strerror (errno));
        return 1;
    } 

    if (connect(sockFd, (struct sockaddr *) &servAddr, sizeof (servAddr)) < 0)
    {
       fprintf (stderr, "ERROR: Connect failed (%s)\n", strerror (errno));
       return 1;
    } 

    while ((nBytes = read (sockFd, recvBuf, sizeof (recvBuf) - 1)) > 0)
    {
        recvBuf [nBytes] = 0;
        
        printf ("Reply from server: %s\n", recvBuf);
    } 

    if (nBytes < 0)
    {
        fprintf (stderr, "ERROR: Read error (%s)\n", strerror (errno));
    } 

    return 0;
}

/* -------------------------------------------------------------------------- */

