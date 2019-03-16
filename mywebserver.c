#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define DEFAULT_LINE_LEN 256

#define HTTP_PORT 80

char * read_line(int sockd)
{
    static int line_len = DEFAULT_LINE_LEN;
    
    static char * line = NULL;

    int size = 0;

    char c = 0; // must be c, not int

    int pos = 0;

    if ( line != 0)
    {
        line = calloc(DEFAULT_LINE_LEN,sizeof(char));
    }

    while ( ( size = recv(sockd, &c, 1, 0) ) > 0 )
    {
        if ( ( c == '\n') && (line[pos-1] == '\r' ) )
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

static void build_success_response(int sockd)
{

    char buf[255] = {0};

    sprintf(buf,"HTTP/1.1 200 Success\r\nConnection: Close\r\n\ Content-Type:text/html\r\n\
    \r\n<html><head><title>Test Page</title></head><body>Nothing here</body></html>\\r\n");

    //Technically, this should account for short writes
    if (send(sockd, buf, strlen(buf), 0) < strlen(buf) )
    {
        fprinf(stderr,"%d: ",__LINE__); 
	perror("Trying to respond");
	exit(1);
    }

}

static void build_error_response(int sockd, int error_code )
{
    static char buf[255];

    sprintf(buf, "HTTP/1.1 %d Error Occured\r\n\r\n", error_code);

    //Technically, this should account for short writes
    if ( send(sockd, buf, strlen(buf), 0 ) < strlen(buf) )
    {
        fprintf(stderr,"%d: ",__LINE__); 
	perror("Trying to respond");
	exit(1);

    }

}

static void process_http_request(int sockd)
{
    char * request_line = read_line(sockd);
    
    if ( strncmp(request_line, "GET", 3) != 0 )
    {
        // Only supports "GET" request

        build_error_response(sockd, 501);

    }

    else
    {
        //Skip over all header lines, don't care 
        while (strcmp(read_line(sockd),"") != 0 )
        ;

        build_success_response(sockd);

    }

}
        


int main(int argc, char * argv[] )
{
    int listen_sock = 0;

    int connect_sock =  0;

    int on = 1;

    static struct sockaddr_in local_addr;
    
    static struct sockaddr_in client_addr;

    int client_addr_len = sizeof(client_addr);

    if ( ( listen_sock = socket(PF_INET, SOCK_STREAM, 0 ) ) == -1 )
    {
       	fprintf(stderr,"%d: ",__LINE__); 
	perror("Unable to create listening socket");
        exit(1);
    }

    if ( setsockopt(listen_sock,
                    SOL_SOCKET,
                    SO_REUSEADDR,
                    &on, sizeof(on) ) == -1)
                    {
                       	fprintf(stderr,"%d: ",__LINE__); 
			perror("Setting socket option");
                        exit(1);

                    }

    local_addr.sin_family = AF_INET;
    
    local_addr.sin_port = htons(HTTP_PORT);
    local_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    //local_addr.sin_addr.s_addr = htonl(INADR_ANY);
    
    if ( bind(listen_sock,
            (struct sockaddr *) &local_addr, sizeof(local_addr) ) == -1 )
    {
       	fprintf(stderr,"%d: ",__LINE__); 
	perror("Unable to bind to local address");
        exit(1);

    }

    if (listen(listen_sock, 5) == -1 )
    {
       	fprintf(stderr,"%d: ",__LINE__); 
	perror("Unable to set socket backlog");
        exit(1);

    }

    while ( (connect_sock = accept(listen_sock, (struct sockaddr *) &client_addr, &client_addr_len) ) != -1 )
    {
        //TODO: ideally, this would make a new thread process_http_request(connect_sock);
	
	process_http_request(connect_sock);
    }

    if (connect_sock == -1)
    {
       	fprintf(stderr,"%d: ",__LINE__); 
	perror("Unable to accept socket");
	exit(1);
    }


    return 0;
}
