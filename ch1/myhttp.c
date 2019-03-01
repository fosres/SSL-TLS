#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#define MAX_BUFFER_SIZE 1024

#define GET_REQUEST_LEN 32

#define TEST_LEN ( ( (MAX_BUFFER_SIZE)*(2) )+ (GET_REQUEST_LEN) )

void get_params(char const * uri,char ** hostname,char ** pathname)
{
	static char host[MAX_BUFFER_SIZE];

	static char url[MAX_BUFFER_SIZE];

	strncat(url,uri,MAX_BUFFER_SIZE-strlen(url)-1);


	if ( strstr(url,"http://") != NULL )
	{ 
		strncat(*hostname,&url[abs(strstr(url,"http://")-&url[0]) + 7],MAX_BUFFER_SIZE - strlen(*hostname)-1);


		
	}

	else
	{
		strncat(*hostname,&url[0],MAX_BUFFER_SIZE-strlen(*hostname)-1);

		
	}
	

	if (strstr(*hostname,"/") != NULL)	
	{	
		strncat(*pathname,&url[abs( strstr(*hostname,"/")  - &url[0] ) + 1],MAX_BUFFER_SIZE-strlen(*pathname)-1);
	}

	else
	{
		*pathname[0] = '\0';	
			
	}

	
	if (strstr(*hostname,"/") != NULL)
	{
		*hostname[abs(strstr(*hostname,"/") - *hostname)] = '\0'; 
	}
}

int main(int argc, char ** argv)
{
	if ( argc < 2)
	{
		fprintf(stderr,"%d: Missing URL",__LINE__);

		exit(EXIT_FAILURE);
	}	
	
	static struct addrinfo hints, *res = NULL, *p = NULL; 

	int sockd = 0;

	static char msg[MAX_BUFFER_SIZE];

	static char test[1024*2+32];

	static char host[MAX_BUFFER_SIZE];

	static char * host_p = &host[0];

	static char path[MAX_BUFFER_SIZE];

	static char * path_p = &path[0];

//	get_params(argv[1],&host_p,&path_p);

	snprintf(test,TEST_LEN,"GET /%s HTTP/1.1\n\n\0",path);

	int recv_bytes = 0, sent_bytes = 0, gstrerror = 0;

	memset(&hints,0,sizeof(hints));

	hints.ai_family = AF_UNSPEC;

	hints.ai_socktype = SOCK_STREAM;
	
	if ( (gstrerror = getaddrinfo(argv[1],"http",&hints,&res) ) != 0)
	{
		fprintf(stderr,"%d: getaddrinfo(): %s\n",__LINE__,gai_strerror(gstrerror));
		exit(EXIT_FAILURE);

	}

	for ( p = res; p!= NULL; p = p->ai_next)
	{
		if ( (p->ai_family == AF_INET) && ((sockd = socket(p->ai_family,p->ai_socktype,p->ai_protocol)) != -1) )
		{
			if (connect(sockd,(struct sockaddr *)p->ai_addr,p->ai_addrlen) != -1)
			{ res = p; break; }	
			
		}

	}
	
	if ( p == NULL)
	{
		fprintf(stderr,"%d: ",__LINE__);
		perror("socket()");
		exit(EXIT_FAILURE);
	}

	printf("Data Sent and Received\n");
	
	if ( (sent_bytes = send(sockd,test,strlen(test),0)) == -1)
	{
		fprintf(stderr,"%d: ",__LINE__);

		perror("send");
		
		exit(EXIT_FAILURE);
	}

	printf("Bytes sent: %d\n",sent_bytes);
			
#if 0
	if ( ( recv_bytes = recv(sockd,msg,sizeof(msg),0) ) == -1 )
	{
		fprintf(stderr,"%d: ",__LINE__);
		perror("recv()");
		exit(EXIT_FAILURE);
	}
#endif

	printf("%s",recv_bytes,msg);

	while ( ( ( recv_bytes = recv(sockd,msg,sizeof(msg),0) )  >= 0 ) 
		&& (msg[0] != '\0') )
	{
		printf("%s",msg);
		
		memset(msg,0,sizeof(msg));	
	}


	close(sockd);
		
	freeaddrinfo(res);

	return 0;
}
