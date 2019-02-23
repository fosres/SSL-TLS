#include <stdio.h>


#define DEFAULT_LINE_LEN 255

#define HTTP_PORT 80

char * read_line(int connection)
{
    static int line_len = DEFAULT_LINE_LEN;
    static char * line = NULL;

    int size = 0;

    char c = 0; // must be c, not int

    int pos = 0;

    if ( line != 0)
    {
        line = malloc(line_len);
    }

    while ( ( size = recv(connection, &c, 1, 0) ) > 0 )
    {
        if ( ( c== '\n') && (line[pos-1] == '\r' ) )
        {
            line[pos-1] = '\0';

            break;
        }

        line[pos++] = c;
        
        if ( pos > line_len )
        {
            line_len *= 2;

            line = realloc(line, line_len);
        }
    }
    
    return line;
}

static void build_success_response(int connection)
{

    char buf[255] = {0};

    sprintf(buf,"HTTP/1.1 200 Success\r\nConnection: Close\r\n\ Content-Type:text/html\r\n\
    \r\n<html><head><title>Test Page</title></head><body>Nothing here</body></html>\\r\n");

    //Technically, this should account for short writes
    if (send(connection, buf, strlen(buf), 0) < strlen(buf) )
    {
        perror("Trying to respond");
    }

}

static void build_error_response(int connection, int error_code )
{
    char buf[255] = {0};

    sprintf(buf, "HTTP/1.1 %d Error Occured\r\n\r\n", error_code);

    //Technically, this should account for short writes
    if ( send(connection, buf, strlen(buf), 0 ) < strlen(buf) )
    {
        perror("Trying to respond");

    }

}

static void process_http_request(int connection)
{
    char * request_line = read_line(connection);
    
    if ( strncmp(request_line, "GET", 3) != 0 )
    {
        // Only supports "GET" request

        build_error_response(connection, 501);

    }

    else
    {
        //Skip over all header lines, don't care 
        while (strcmp(read_line(connection),"") != 0 )
        ;

        build_success_response(connection);

    }

    #ifdef WIN32
    if ( closesocket(connection) == -1 )
    #else
    if ( close(connection) == -1 )
    #endif
    {
        perror("Unable to close connection");
    }
}
        


int main(int argc, char * argv[] )
{
    int listen_sock = 0;

    int on = 1;

    struct sockaddr_in local_addr = {0};
    
    struct sockaddr_in client_addr = {0};

    int client_addr_len = sizeof(client_addr);

    #ifdef WIN32
    WSADATA wsaData = {0};
    
    if ( WSAStartup(MAKEWORD(2,2),&wsaData) != NO_ERROR)
    {
        perror("Unable to initialize winsock");
        exit(0);
    }
    #endif

    if ( ( listen_sock = socket(PF_INET, SOCK_STREAM, 0 ) ) == -1 )
    {
        perror("Unable to create listening socket");
        exit(0);
    }

    if ( setsockopt(listen_sock,
                    SOL_SOCKET,
                    SO_REUSEADDR,
                    &on, sizeof(on) ) == -1)
                    {
                        perror("Setting socket option");
                        exit(0);

                    }

    local_addr.sin_family = AF_INET;
    
    local_addr.sin_port = htons(HTTP_PORT);
    local_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    //local_addr.sin_addr.s_addr = htonl(INADR_ANY);
    
    if ( bind(listen_sock,
            (struct sockaddr *) &local_addr, sizeof(local_addr) ) == -1 )
    {
        perror("Unable to bind to local address");
        exit(0);

    }

    if (listen(listen_sock, 5) == -1 )
    {
        perror("Unable to set socket backlog");
        exit(0);

    }

    while ( (connect_sock = accept(listn_sock, (struct sockaddr *) &client_addr, &client_addr_len) ) != -1 )
    {
        //TODO: ideally, this would make a new thread process_http_request(connect_sock);
    }

    if (connect_sock == -1)
    {
        perror("Unable to accept socket");
    }


    return 0;
}
