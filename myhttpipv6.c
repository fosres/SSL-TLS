#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char ** argv)
{
	if ( argc < 2)
	{
		fprintf(stderr,"%d: Missing URL",__LINE__);

		exit(EXIT_FAILURE);
	}	
	
	static struct addrinfo hints, *res = NULL, *p = NULL; 

	static struct sockaddr_in6 * ip6 = NULL;	
	
	int sockd = 0;

	static char msg[1024];

	char const * test = "GET / HTTP/1.1\n\n\0";

	char ipstr = "\0";

	int recv_bytes = 0, sent_bytes = 0, gstrerror = 0;

	memset(&hints,0,sizeof(hints));

	hints.ai_family = AF_INET;

	hints.ai_socktype = SOCK_STREAM;
	
	if ( (gstrerror = getaddrinfo(argv[1],"http",&hints,&res) ) != 0)
	{
		fprintf(stderr,"%d: getaddrinfo(): %s\n",__LINE__,gai_strerror(gstrerror));
		exit(EXIT_FAILURE);

	}

	for ( p = res; p!= NULL; p = p->ai_next)
	{
		if ( (p->ai_family == AF_INET) 
			&& 
			( ( sockd = socket(p->ai_family,p->ai_socktype,p->ai_protocol) ) != -1) )
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
			

	if ( ( recv_bytes = recv(sockd,msg,sizeof(msg),0) ) == -1 )
	{
		fprintf(stderr,"%d: ",__LINE__);
		perror("recv()");
		exit(EXIT_FAILURE);
	}

	printf("Bytes received: %d\n%s",recv_bytes,msg);

	close(sockd);
		
	freeaddrinfo(res);

	return 0;
}
