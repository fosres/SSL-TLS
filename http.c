#if 0
    Copyright 2018-INFINITY Tanveer Salim
    
    Adapated from Joshua Davies's original

    http.c file

    GNU GPL v2.0 License

#endif

#if 0
    This proram performs a simple

    non-encrypted HyperText Transfer

    Protocol Connection
#endif
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#else
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#endif

#define HTTP_PORT 80

#if 0
    The following will parse the URL to arrive
    at the proper file within the website
    directory.

    The function will return 0 if parsing
    successful; -1 if it fails.

    parse_url looks for all "//" and '/'
    and replaces them with null-terminators
    so the compiler can accept the host
    and path as individual strings.

    host is the string starting IMMEDIATELY
    AFTER the "//" in the URL and the first
    '/' in the URL after the "//".

    path is everything after the host
#endif



int parse_url(char * uri, char ** host, char ** path)
{
    char * pos = NULL;

    if ( (pos = strstr(uri,"//")) == NULL )
    {
        return -1;

    }
#if 0
 assigns char immediately after "//" in URL
#endif
    
    *host = pos + 2;

    if ( (pos = strchr(*host,'/') ) == NULL)
    {
        *path = NULL;

    }

    else
    {
        *pos = '\0';

        *path = pos + 1;

    }

    return 0;

}

#if 0

Simple command line HTTP client.

#endif

int main(int argc, char * argv[])
{
    int client_connection = 0;

    char * host = NULL, * path = NULL;

    struct hostent * host_name = NULL;

    struct sockaddr_in_host_address = {0};

#ifdef WIN32
    WSADATA wsaData = {0};
#endif
    
    if ( argc < 2 )
    {
        fprintf(stderr, "Usage: %s: <URL>\n", argv[0]);
        return 1;
    }

    if ( parse_url(argv[1], &host, &path) == -1 )
    {
        fprintf(stderr, "Error - malformed URL '%s'\n", argv[1]);

        return 1;
    
    }

    printf("Connecting to host '%s'\n", host);

#if 0
Step 1: After the URL has been parsed and 

the host is established, you must make a

socket to it. The domain host name (e.g.

www.server.com is converted to a 32-bit

IPv4 decimal number. Such as 100.218.64.2

You need to call the "gethostname" library

function to do this, and connect to the

server.

#endif

#ifdef WIN32
    
    if ( WSAStartup(MAKEWORD(2,2), &wsaData) != NO_ERROR )
    {
        fprintf(stderr, "Error, unable to initialize winsock.n");

        return 2;
    }

#endif

    client_connection = socket(PF_INET, SOCK_STREAM, 0);

    if ( client_connection == -1 )
    {
        perror( "Unable to create local socket");
        return 2;
    }

    host_name = gethostbyname(host);

    if ( host_name == NULL )
    {
        perror("Error in name resolution");

        return 3;
    }

    host_address.sin_family = AF_INET;

    host_address.sin_port = htons(HTTP_PORT);
    return 0;
}
