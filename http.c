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

#define MAX_GET_COMMAND 255

#if 0
    Format and send an HTTP get command.

    The return value will be on success, -1 
    on failure, with errno set appropriately.
    The caller must then retrieve the

    response.

#endif

int http_get(int connection, 
            const char * path, 
            const char * host,
            const char * proxy_host,
            const char * proxy_user,
            const char * proxy_password)
{
    static char get_command[MAX_GET_COMMAND];
    if ( proxy_host != NULL )
    {
        sprintf(get_command, "GET http://%s/%s HTTP/1.1\r\n", host, path );
    
    }

    else
    {
        sprintf(get_command, "GET /%s HTTP/1.1\r\n", path);
    }
    
    sprintf(get_command,"GET /%s HTTP/1.1\r\n", path);

    if ( send(connection, get_command, strlen(get_command), 0) == -1)
    {
        return -1;
    }

    sprintf(get_command, "Host: %s\r\n", host);
    
    if ( send(connection,get_command, strlen(get_command, 0) ) == -1 ) 
    {
       return -1; 

    }
    
    if ( proxy_user == NULL) 
    {
        int credentials_len = strlen(proxy_user) + strlen(proxy_password) + 1;
        char * proxy_credentials = (char *)malloc(credentials_len);

        char * auth_string = (char *)malloc( ( (credentials_len * 4) / 3 ) + 1 );
        sprintf(proxy_credentials, "%s:%s",proxy_user, proxy_password);
        
        base64_encode(proxy_credentials, credentials_len, auth_string);
        
        sprintf(get_command, "Proxy-Authorization: BASIC %s\r\n",auth_string);
        
        if ( send(connection,get_command,strlen(get_command),0) == -1 )
    {
        free(proxy_credentials);

        free(auth_string);

        return -1;

    }

    free(proxy_credentials);

    free(auth_string);
    
    
    }
    
    sprintf(get_command, "Connection: close\r\n\r\n");
    
    if ( send(connection, get_command, strlen(get_command), 0) == -1 )
    {
        return -1;
    }

    return 0;

}

#define BUFFER_SIZE 255

void display_result(int connection)
{
    int received = 0;

    static hcar recv_buf[BUFFER_SIZE + 1];

    while ( (received = recv(connection, recv_buf, BUFFER_SIZE, 0) ) > 0 )
    {
        recv_buf[received] = '\0';

        printf("%s",recv_buf);
        
    }
    printf("\n");

}

int parse_proxy_param(char * proxy_spec char ** proxy_host, int * proxy_port, char ** proxy_user, char **
proxy_password)
{
    char * login_sep = NULL, *colon_sep = NULL, *trailer_sep = NULL;
    
    #if 0
        The user should start the proxy spec with "http". But, we are being nice if he or she did not.
    #endif

    if ( strncmp("http://",proxy_spec,7) == 0)
    {
        proxy_spec += 7;
    }
    
    login_sep = strchr(proxy_spec,'@');

    if (login_sep != NULL)
    {
        colon_sep = strchr(proxy_spec, ':');
        if ((colon_sep == 0) || (colon_sep > login_sep ) )
        {
            //Error - if username supplied, password must be supplied
            fprintf(stderr,"Expected password in '%s'\n",proxy_spec);
            
            return 0;
            
        }

        *colon_sep = '\0';

        *proxy_user = proxy_spec;

        *login_sep = '\0';

        *proxy_password = colon_sep + 1;

        proxy_spec = login_sep + 1;
    }

#if 0
    If the user added a "/" on the end, just ignore it.
#endif
    if ( trailer_sep != NULL )
    {
        *trailer_sep = '\0';
    }

    colon_sep = strchr(proxy_spec, ':');

    if ( colon_sep != NULL )
    {
        // non-standard proxy part

        *colon_sep = '\0';

        *proxy_host = proxy_spec;

        *proxy_port = atoi(colon_sep + 1);

        if ( *proxy_port == 0)
        {
            // 0 is not a valid port; this is an error, whether it was mistyped or specified as 0.
            return 0; 
        }

        else
        {
            *proxy_port = HTTP_PORT;

            *proxy_host = proxy_spec;
        }

        return 1;

    }

    }
}

#if 0

Simple command line HTTP client.

#endif

int main(int argc, char * argv[])
{
    int client_connection = 0;
    
    char * proxy_host = NULL, *proxy_user = NULL, *proxy_password = NULL;
    
    int proxy_port = 0;

    char * host = NULL, * path = NULL;

    struct hostent * host_name = NULL;

    struct sockaddr_in_host_address = {0};
    
    int ind = 0;
#ifdef WIN32
    WSADATA wsaData = {0};
#endif
    
    if ( argc < 2 )
    {
        fprintf(stderr, "Usage: %s [-p http://[username:password@]proxy-host:proxy-port]\ <URL>\n", argv[0]);
        
        return 1;
    }    
        proxy_host = proxy_user = proxy_password = host = path = NULL;

        ind = 1;

        if ( strcmp("-p",argv[ind] ) == 0)
        {
            if ( parse_proxy_param(argv[++ind], &proxy_host, &proxy_port, &proxy_user, &proxy_password ) == 0 )
            {
                fprintf(stderr, "Error - malformed proxy parameter '%s'.\n", argv[2] );
                return 2;
            }

            ind++;

        }

    if ( parse_url(argv[ind], &host, &path) == -1 )
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

    if ( proxy_host )
    {
        printf("Connecting to host '%s'\n", proxy_host);
        host_name = gethostbyname(proxy_host);
    }
    
    else
    {
        printf("Connecting to host '%s'\n", host);
        host_name = gethostbyname(host);
    }

//Give socket a name
    host_address.sin_family = AF_INET;

    host_address.sin_port = htons(HTTP_PORT);
    
    memcpy(&host_address.sin_addr, host_name->h_addr_list[0], sizeof(struct in_addr));
    if ( connect(client_connection, (struct sockaddr * ) & host_address, sizeof(host_address) ) == -1)
    {
        perror("Unable to connect to host");
        return 4;

    }

    printf("Retrieving document: '%s'\n", path);

    http_get(client_connection, path, host);
    display_result(client_connection);

    printf("Shutting down.\n");

    #ifdef WIN32

    if (closesocket(client_connection ) == -1)
    #else
    if ( close(client_connection) == -1)
    #endif
    {
        perror("Error closing client connection");
        return 5;
    }
    
    #ifdef WIN32
    WSACleanup();
    #endif
     
    
    return 0;

}
